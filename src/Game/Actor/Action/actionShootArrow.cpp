#include "Game/Actor/Action/actionShootArrow.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Camera/CameraMgr.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

ShootArrow::ShootArrow(const InitArg& arg) : ActionEx(arg) {}

void ShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    m32();
    auto* actor = mActor;
    const sead::Vector3f vel = actor->getVelocity();
    const f32 speed = vel.length();
    _78.value = speed;
    _78.prev_value = speed;
    sead::Vector3f ang_vel = actor->getAngVelocity();
    ang_vel.x = 0;
    ang_vel.z = 0;
    _a8 = ang_vel.length();
    _84.value = ang_vel;
    _84.prev_value = ang_vel;
    _ac = false;
}

void ShootArrow::sub_710024E90C() {
    _78 *= *mStopSpeedRatio_s;
    _78.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        sub_710072C1B4(controller, mActor->getMtx().getBase(2));
        controller->sub_7100F5E7F0(_78.value * 30.0f);
    }
}

void ShootArrow::sub_710024E994() {
    _84 *= *mStopRotSpeedRatio_s;
    _84.updateStats();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(_84.value * 30.0f);
}

void ShootArrow::m33(const sead::Vector3f& pos, const sead::Vector3f* pos2) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100016494();
    sub_71005D80FC(mActor, *mWeaponIdx_s, pos, 0, 1.0f, pos2, nullptr);
}

void ShootArrow::m34() {
    sub_710024E90C();
    sub_710024E994();
}

void ShootArrow::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: stack layout only: the original puts `target` in the slot of the Unk_71002eda38 temporary (sp+0x18) and
// `pos` below it (sp+0x8); ours merges `pos` with the temporary and keeps `target` apart
void ShootArrow::calc_() {
    if (sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
        sead::Vector3f pos;
        sead::Vector3f target;
        if (sub_710024EB30(&target, &pos))
            m33(pos, &target);
        else
            m33(pos, nullptr);
        _ac = true;
    }
    m34();
    if (isFinishedAS(0, 0)) {
        setFinished();
        return;
    }
    if (!_ac)
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

// NON_MATCHING: float scheduling.
bool ShootArrow::sub_710024EB30(sead::Vector3f* out_target, sead::Vector3f* out_pos) {
    const sead::Vector3f front = mActor->getMtx().getBase(2);
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f to_target{target.x - mActor->getMtx()(0, 3), 0,
                             target.z - mActor->getMtx()(2, 3)};
    const f32 distance = to_target.normalize();
    sead::Vector3f side;
    side.setCross(to_target, sead::Vector3f::ey);
    side.normalize();

    const f32 scale = distance * *mOffsetRateByDist_s + 1.0f;
    f32 max = *mOffsetRangeMax_s;
    f32 min = *mOffsetRangeMin_s * scale;
    if (distance >= 40.0f)
        min = sead::Mathf::max(*mOffsetRangeMinOutOfScreen_s, min);
    if (ksys::sub_7100D8C4F8(mActor->getMtx().getTranslation())) {
        max *= scale;
    } else {
        min = *mOffsetRangeMinOutOfScreen_s;
        max = *mOffsetRangeMaxOutOfScreen_s;
    }
    if (min > max) {
        min = 0.0f;
        max = 1.0f;
    }
    const f32 offset = sead::GlobalRandom::instance()->getF32Range(min, max);
    const f32 sign = s32((sead::GlobalRandom::instance()->getU32() & 2) - 1);
    const f32 horizontal_distance = sead::Mathf::max(
        sead::Vector2f(target.x - mActor->getMtx()(0, 3), target.z - mActor->getMtx()(2, 3)).length(),
        3.5f);

    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    out_pos->x = sign * side.x * offset + actor_pos.x + front.x * horizontal_distance;
    out_pos->y = target.y + sign * side.y * offset;
    out_pos->z = sign * side.z * offset + front.z * horizontal_distance + actor_pos.z;
    if (horizontal_distance < 4.5f)
        return false;

    const sead::Vector3f base = actor_pos + sead::Vector3f::ey;
    const f32 height = out_pos->y - base.y;
    if (height >= 0.0f)
        return false;
    const f32 length = sead::Vector2f(out_pos->x - base.x, out_pos->z - base.z).length();
    if (std::atan2(sead::Mathf::abs(height), length) < sead::Mathf::deg2rad(30))
        return false;
    *out_target = base + front * 2.5f;
    return true;
}

bool ShootArrow::isChangeable() const {
    return false;
}

void ShootArrow::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action

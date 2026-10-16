#include "Game/Actor/Action/actionForkASTrgShootArrow.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

ForkASTrgShootArrow::ForkASTrgShootArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgShootArrow::~ForkASTrgShootArrow() = default;

bool ForkASTrgShootArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = false;
}

void ForkASTrgShootArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgShootArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsEndState_s, "IsEndState");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: stack layout only (the original puts `pos` below `dir` and the Unk_71002eda38 temporary shares the slot
// of `dir`; ours shares the temporary with `pos`)
void ForkASTrgShootArrow::calc_() {
    if (sub_71005DD780(mActor, 0x47, nullptr, *mTargetBone_s, *mSeqBank_s)) {
        sead::Vector3f pos;
        sead::Vector3f dir;
        if (sub_7100143C64(&dir, &pos))
            m33(pos, &dir);
        else
            m33(pos, nullptr);
        _70 = true;
        if (*mIsEndState_s == 2)
            setFinished();
        else if (*mIsEndState_s == 1)
            mFlags.set(Flag::Changeable);
    } else if (!_70) {
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
    }
}

// NON_MATCHING: float scheduling (the original keeps the squared x / z distances for the second length).
bool ForkASTrgShootArrow::sub_7100143C64(sead::Vector3f* dir, sead::Vector3f* pos) {
    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    sead::Vector3f front;
    m32(&front);
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f to_target{target.x - actor_pos.x, 0, target.z - actor_pos.z};
    const f32 distance = to_target.normalize();
    sead::Vector3f side;
    side.setCross(to_target, sead::Vector3f::ey);
    side.normalize();

    const f32 scale = distance * *mOffsetRateByDist_s + 1.0f;
    f32 min = *mOffsetRangeMin_s * scale;
    if (distance >= 40.0f)
        min = sead::Mathf::max(*mOffsetRangeMinOutOfScreen_s, min);
    f32 max = *mOffsetRangeMax_s;
    if (ksys::sub_7100D8C4F8(mActor->getMtx().getTranslation())) {
        max *= scale;
    } else {
        min = *mOffsetRangeMinOutOfScreen_s;
        max = *mOffsetRangeMaxOutOfScreen_s;
    }
    const f32 offset = sead::GlobalRandom::instance()->getF32Range(min, max);
    const f32 sign = s32((sead::GlobalRandom::instance()->getU32() & 2) - 1);
    const f32 horizontal_distance =
        sead::Vector2f(target.x - actor_pos.x, target.z - actor_pos.z).length();

    pos->x = actor_pos.x + horizontal_distance * front.x + sign * side.x * offset;
    pos->y = target.y + sign * side.y * offset;
    pos->z = actor_pos.z + horizontal_distance * front.z + sign * side.z * offset;

    const sead::Vector3f base = actor_pos + sead::Vector3f(0, 1, 0);
    const f32 height = pos->y - base.y;
    if (height < 0.0f) {
        const f32 length = sead::Vector2f(pos->x - base.x, pos->z - base.z).length();
        if (std::atan2(sead::Mathf::abs(height), length) >= sead::Mathf::deg2rad(30)) {
            *dir = base + front * 2.5f;
            return true;
        }
    }
    return false;
}

void ForkASTrgShootArrow::m32(sead::Vector3f* dir) {
    mActor->getMtx().getBase(*dir, 2);
}

void ForkASTrgShootArrow::m33(const sead::Vector3f& pos, const sead::Vector3f* dir) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->sub_7100016494();
    sub_71005D80FC(mActor, *mWeaponIdx_s, pos, 0, 1.0f, dir, nullptr);
}

}  // namespace uking::action

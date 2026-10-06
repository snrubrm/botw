#include "Game/AI/AI/aiDomesticNormal.h"

#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DomesticNormal::DomesticNormal(const InitArg& arg) : PreyNormal(arg) {}

DomesticNormal::~DomesticNormal() = default;

bool DomesticNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void DomesticNormal::sub_71003653B0() {
    sub_7100364F7C();
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target = _380;
    target.x += sead::GlobalRandom::instance()->getF32Range(-5.0f, 5.0f);
    target.z += sead::GlobalRandom::instance()->getF32Range(-5.0f, 5.0f);
    pack.addVec3(target, "TargetPos", -1);
    changeChild("帰還", &pack);
}

// Whether the player runs towards the animal fast enough to stagger it; `angle` receives the signed angle (degrees)
// between the animal's heading and the direction to the player.
bool DomesticNormal::sub_710036550C(f32* angle) {
    const s32 count = sub_71007A425C(mActor);
    for (s32 i = 0; i < count; ++i) {
        auto* entry = sub_71007A40D0(mActor, i);
        if (!entry || !ksys::act::isPlayerProfile(&entry->_50))
            continue;
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(&entry->_50, &accessor))
            continue;
        const f32 vx = accessor.getVelocity().x - mActor->getVelocity().x;
        const f32 vz = accessor.getVelocity().z - mActor->getVelocity().z;
        const f32 dx = accessor.getActorMtx()(0, 3) - mActor->getMtx()(0, 3);
        const f32 dz = accessor.getActorMtx()(2, 3) - mActor->getMtx()(2, 3);
        const f32 dot = vx * dx + vz * dz;
        const f32 length_squared = dx * dx + dz * dz;
        if (1.0f / std::sqrt(length_squared) * dot < -*mStaggerVelocityThreshold_s) {
            sead::Vector3f front;
            if (auto* controller = mActor->getCharacterController()) {
                front.x = controller->get64().x;
                front.z = controller->get64().z;
            } else {
                mActor->getMtx().getBase(front, 2);
                front.y = 0.0f;
                front.normalize();
            }
            sead::Vector2f dir(dx, dz);
            dir.normalize();
            const f32 cos = front.x * dir.x + front.z * dir.y;
            const f32 degrees = sead::Mathf::rad2deg(std::acos(sead::Mathf::clamp(cos, -1.0f, 1.0f)));
            const f32 sign = front.x * dir.y - front.z * dir.x >= 0.0f ? 1.0f : -1.0f;
            *angle = sign * degrees;
            return true;
        }
    }
    return false;
}

void DomesticNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
}

void DomesticNormal::leave_() {
    PreyNormal::leave_();
}

bool DomesticNormal::m44() {
    return isCurrentChild("逃走") || isCurrentChild("ダメージ逃走") || isCurrentChild("気づき") ||
           isCurrentChild("ふり向き") || isCurrentChild("興味対象発見") ||
           isCurrentChild("ターゲット通知") || isCurrentChild("最後の手段");
}

// NON_MATCHING: Timer store order and register scheduling differ.
void DomesticNormal::calc_() {
    if (!_399) {
        sub_7100364F7C();
        _399 = true;
    }
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished() || child->isFailed()) {
        if (m44()) {
            const f32 minimum = *mWaitFramesAfterRunMin_s;
            const s32 maximum = *mWaitFramesAfterRunMax_s;
            _38c.value = _38c.previous_value =
                minimum + f32(maximum) * sead::GlobalRandom::instance()->getF32();
        } else if (isCurrentChild("帰還")) {
            if (child->isFailed()) {
                ++_398;
                if (_398 >= *mNumFailPathHomeFadeout_s) {
                    sub_7100500B50(false, false, true);
                    changeChild("最後の手段", nullptr);
                } else {
                    sub_71003653B0();
                }
                return;
            }
            sub_71004FCA60();
            return;
        } else if (isCurrentChild("よろけ")) {
            sub_71004FCA60();
            return;
        }
    }
    PreyNormal::calc_();
    if (m44())
        return;
    f32 angle = 0.0f;
    if ((isCurrentChild("よろけ") || mActor->getASList()->x_1(0, 0) == "Wait") &&
        sub_710036550C(&angle)) {
        mActor->getASList()->x_6(11, 0, angle);
        sub_7100500B50(false, false, true);
        changeChild("よろけ", nullptr);
    }
    if (!(_38c.value <= sead::Mathf::epsilon())) {
        _38c.update();
        return;
    }
    const auto position = mActor->getMtx().getTranslation();
    if (isCurrentChild("帰還"))
        return;
    const f32 distance = sead::Vector2f(position.x - _380.x, position.z - _380.z).squaredLength();
    if (distance >= *mDistHomePosFadeout_s * *mDistHomePosFadeout_s) {
        sub_7100500B50(false, false, true);
        changeChild("最後の手段", nullptr);
    } else if (distance >= *mDistUntilReturnToHomePos_s * *mDistUntilReturnToHomePos_s) {
        sub_71003653B0();
    }
}

void DomesticNormal::loadParams_() {
    PreyNormal::loadParams_();
    getStaticParam(&mWaitFramesAfterRunMax_s, "WaitFramesAfterRunMax");
    getStaticParam(&mNumFailPathHomeFadeout_s, "NumFailPathHomeFadeout");
    getStaticParam(&mDistUntilReturnToHomePos_s, "DistUntilReturnToHomePos");
    getStaticParam(&mWaitFramesAfterRunMin_s, "WaitFramesAfterRunMin");
    getStaticParam(&mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mDistHomePosFadeout_s, "DistHomePosFadeout");
    getAITreeVariable(&mDomesticAnimalRailName_a, "DomesticAnimalRailName");
}

}  // namespace uking::ai

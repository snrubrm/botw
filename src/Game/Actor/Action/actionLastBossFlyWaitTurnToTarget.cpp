#include "Game/Actor/Action/actionLastBossFlyWaitTurnToTarget.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cmath>
#include <limits>

namespace uking::action {

LastBossFlyWaitTurnToTarget::LastBossFlyWaitTurnToTarget(const InitArg& arg)
    : LastBossFlyWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
LastBossFlyWaitTurnToTarget::~LastBossFlyWaitTurnToTarget() {
    ;
}

void LastBossFlyWaitTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossFlyWait::enter_(params);
    _ec.value = _ec.prev_value = mActor->getAngVelocity().length();
}

void LastBossFlyWaitTurnToTarget::leave_() {
    LastBossFlyWait::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    _f8 = false;
}

// NON_MATCHING: branch layout of the turn check, the up-vector negation order and the position kept as ints.
void LastBossFlyWaitTurnToTarget::m32(sead::Matrix34f* mtx) {
    sub_710073FA94(&_c8, mActor);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    const sead::Vector3f& gravity = controller->get70();
    sead::Vector3f up = -gravity;
    const f32 gravity_len = gravity.length();
    if (gravity_len > 0.0f)
        up *= 1.0f / gravity_len;
    if (gravity_len < std::numeric_limits<f32>::epsilon())
        up = sead::Vector3f::ey;

    sead::Vector3f to_target = *mTargetPos_d;
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    _ec.lerp(0.16f, 0.16f, 0.016f);
    _ec.updateStats();

    bool turn = *mTurnStartDiffAng_s == 0.0f;
    if (!turn) {
        const f32 limit = _f8 ? *mTurnStartDiffAng_s * 0.1f : *mTurnStartDiffAng_s;
        turn = front.dot(to_target) < std::cos(limit);
    }

    if (turn) {
        sub_710074006C(&_c8, to_target, up, true, *mTurnRate_s, _ec.value, _ec.value * 0.1f);
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
        mActor->getASList()->x_6(9, 0, angle * 57.29578f * axis.y);
        _f8 = true;
        playAS(mTurnASName_s.cstr(), true, 0, 0, -1.0f);
    } else {
        _f8 = false;
        playAS(mWaitAS_s.cstr(), true, 0, 0, -1.0f);
    }

    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    velocity *= 1.0f / 30.0f;
    if (!std::isnan(velocity.x) && !std::isnan(velocity.z) && !std::isnan(velocity.y) &&
        (velocity.x != 0.0f || velocity.z != 0.0f)) {
        auto* vfr = ksys::VFR::instance();
        const f32 frames = f32(vfr->getFrameRate()) * vfr->getRawDeltaTime();
        velocity.y = 0.0f;
        velocity *= frames * 0.98f;
        pos += velocity;
    }
    *mtx = sead::Matrix34f(_c8, pos);
}

void LastBossFlyWaitTurnToTarget::loadParams_() {
    LastBossFlyWait::loadParams_();
    getStaticParam(&mTurnStartDiffAng_s, "TurnStartDiffAng");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mTurnASName_s, "TurnASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::action

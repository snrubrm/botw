#include "Game/AI/Action/actionAnmDrivenHoverBase.h"
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

AnmDrivenHoverBase::AnmDrivenHoverBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDrivenHoverBase::~AnmDrivenHoverBase() = default;

bool AnmDrivenHoverBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmDrivenHoverBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);

    if (mActor->getASList()) {
        if (auto* cc = mActor->getCharacterController()) {
            mCCAccessor.changeMotionType(cc, ksys::act::MotionType::Hover);
            return;
        }
    }
    setFailed();
}

void AnmDrivenHoverBase::leave_() {
    mCCAccessor.resetMotionType(mActor->getCharacterController());
}

void AnmDrivenHoverBase::loadParams_() {
    getStaticParam(&mMoveYLimit_s, "MoveYLimit");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mBaseHeight_d, "BaseHeight");
}

// NON_MATCHING: the sign select is emitted as `mi ? -1 : 1` instead of `ge ? 1 : -1`
void AnmDrivenHoverBase::calc_() {
    auto* as_list = mActor->getASList();
    ksys::phys::CharacterController* controller;
    if (!as_list || !(controller = mActor->getCharacterController())) {
        setFailed();
        return;
    }

    f32 move_y = as_list->sub_710115D2D4().y;
    const f32 diff = mActor->getMtx()(1, 3) - *mBaseHeight_d;
    f32 sign = 1.0f;
    if (diff < 0.0f)
        sign = -1.0f;
    if (sead::Mathf::abs(diff) > *mMoveYLimit_s && move_y * sign > 0.0f)
        move_y *= 0.8f;
    else if (move_y < 0.0f && mActor->get68f())
        move_y *= 0.6f;

    sead::Vector3f velocity = mActor->getVelocity();
    velocity.y = move_y;
    {
        const f32 ratio = *mPosReduceRatio_s;
        velocity.x *= ratio >= 0.0f ?
                          std::pow(ratio, ksys::VFR::instance()->getDeltaFrame()) :
                          -std::pow(-ratio, ksys::VFR::instance()->getDeltaFrame());
    }
    {
        const f32 ratio = *mPosReduceRatio_s;
        velocity.z *= ratio >= 0.0f ?
                          std::pow(ratio, ksys::VFR::instance()->getDeltaFrame()) :
                          -std::pow(-ratio, ksys::VFR::instance()->getDeltaFrame());
    }
    sub_7100737710(controller, velocity);
}

}  // namespace uking::action

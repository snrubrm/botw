#include "Game/AI/Action/actionForkASHoldLegTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASHoldLegTurn::ForkASHoldLegTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASHoldLegTurn::~ForkASHoldLegTurn() = default;

bool ForkASHoldLegTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the argument address `this + 0x48` is computed before `this + 0x60` (swapped x0 / x1)
void ForkASHoldLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsFixBoneWithGround_s && !mRotBaseBoneName_s.isEmpty())
        _60.sub_710070E434(mRotBaseBoneName_s);
    mFlags.set(Flag::Changeable);
}

void ForkASHoldLegTurn::leave_() {
    if (*mIsFixBoneWithGround_s && !mRotBaseBoneName_s.isEmpty())
        _60.sub_710070E4C0();
}

void ForkASHoldLegTurn::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mTargetPosNoUpdateArea_s, "TargetPosNoUpdateArea");
    getStaticParam(&mIsFixBoneWithGround_s, "IsFixBoneWithGround");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkASHoldLegTurn::calc_() {
    sub_710013EE00();
}

// NON_MATCHING: load order (the original loads target.z before target.x and the NoUpdateArea pointer
// after the squares)
void ForkASHoldLegTurn::sub_710013EE00() {
    if (sub_71005DD5B0(mActor, 41, nullptr, 0, 0)) {
        _60.sub_710070E4EC(mRotBaseBoneName_s);
        _178 = *mTargetPos_d;
    }

    const bool is_turning = sub_71005DD798(mActor, 41, nullptr, 0, 0);
    auto* actor = mActor;
    if (is_turning) {
        const f32 dx = actor->getMtx().m[0][3] - mTargetPos_d->x;
        const f32 dz = actor->getMtx().m[2][3] - mTargetPos_d->z;
        if (dx * dx + dz * dz > *mTargetPosNoUpdateArea_s * *mTargetPosNoUpdateArea_s)
            _178 = *mTargetPos_d;
        _60.sub_710070E714();
        _60.sub_710070E7A8(&_178, 0.14f, *mRotSpeed_s, 0.14f);
    } else if (auto* controller = actor->getCharacterController()) {
        sub_7100737C0C(controller, *mStopSpeedRatio_s, -sead::Vector3f::ey);
        sub_7100738660(controller, *mStopRotSpeedRatio_s);
    }
}

}  // namespace uking::action

#include "Game/AI/Action/actionAnmDrivenHoverBase.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void AnmDrivenHoverBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

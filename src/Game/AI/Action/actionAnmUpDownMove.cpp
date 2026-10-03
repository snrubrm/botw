#include "Game/AI/Action/actionAnmUpDownMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

AnmUpDownMove::AnmUpDownMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmUpDownMove::~AnmUpDownMove() = default;

bool AnmUpDownMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmUpDownMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    mFlags.reset(Flag::Changeable);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _54.changeMotionType(cc, ksys::act::MotionType::Hover);
}

void AnmUpDownMove::leave_() {
    _54.resetMotionType(_54.sub_710072ACF8(mActor));
}

void AnmUpDownMove::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void AnmUpDownMove::calc_() {
    ksys::act::ai::Action::calc_();
}

bool AnmUpDownMove::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action

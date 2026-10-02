#include "Game/AI/Action/actionHoverTurn.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HoverTurn::HoverTurn(const InitArg& arg) : TurnBase(arg) {}

HoverTurn::~HoverTurn() = default;

bool HoverTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void HoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    mCCAccessor.changeMotionType(controller, ksys::act::MotionType::Hover);
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), *mIsIgnoreSameAS_s, 0, 0, -1.0f);
}

void HoverTurn::leave_() {
    TurnBase::leave_();
    mCCAccessor.resetMotionType(mActor->getCharacterController());
}

void HoverTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void HoverTurn::calc_() {
    TurnBase::calc_();
}

void HoverTurn::m32(f32 x) {
    if (auto* controller = mActor->getCharacterController())
        sub_71007377D4(controller, x);
}

}  // namespace uking::action

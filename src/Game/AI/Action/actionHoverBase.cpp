#include "Game/AI/Action/actionHoverBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

HoverBase::HoverBase(const InitArg& arg) : FreeMovingAction(arg) {}

bool HoverBase::init_(sead::Heap* heap) {
    return FreeMovingAction::init_(heap);
}

void HoverBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMovingAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void HoverBase::leave_() {
    FreeMovingAction::leave_();
}

void HoverBase::loadParams_() {
    FreeMovingAction::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void HoverBase::calc_() {
    if (auto* controller = mActor->getCharacterController()) {
        sub_71007377D4(controller, *mPosReduceRatio_s);
        sub_7100738660(controller, *mAngReduceRatio_s);
    } else if (auto* body = mActor->getMainBody()) {
        sub_71007379FC(body, *mPosReduceRatio_s);
        sub_7100738898(body, *mAngReduceRatio_s);
    }
}

}  // namespace uking::action

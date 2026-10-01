#include "Game/AI/Action/actionNPCTurnAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

NPCTurnAction::NPCTurnAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnAction::~NPCTurnAction() = default;

void NPCTurnAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTurnAction::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void NPCTurnAction::loadParams_() {
    getStaticParam(&mTurnFrame_s, "TurnFrame");
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NPCTurnAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

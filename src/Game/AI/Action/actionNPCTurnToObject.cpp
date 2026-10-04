#include "Game/AI/Action/actionNPCTurnToObject.h"

namespace uking::action {

NPCTurnToObject::NPCTurnToObject(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnToObject::~NPCTurnToObject() = default;

void NPCTurnToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTurnToObject::leave_() {
    sub_710020A5E4();
}

void NPCTurnToObject::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mActorName_d, "ActorName");
}

void NPCTurnToObject::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionNPCTurnToObjectGreeting.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

NPCTurnToObjectGreeting::NPCTurnToObjectGreeting(const InitArg& arg) : NPCTurnToObject(arg) {}

NPCTurnToObjectGreeting::~NPCTurnToObjectGreeting() = default;

bool NPCTurnToObjectGreeting::init_(sead::Heap* heap) {
    return NPCTurnToObject::init_(heap);
}

void NPCTurnToObjectGreeting::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTurnToObject::enter_(params);
}

void NPCTurnToObjectGreeting::leave_() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        npc->_fe8 &= ~0x40000000u;
    NPCTurnToObject::leave_();
}

void NPCTurnToObjectGreeting::loadParams_() {
    NPCTurnToObject::loadParams_();
    getDynamicParam(&mGreetingType_d, "GreetingType");
}

void NPCTurnToObjectGreeting::calc_() {
    NPCTurnToObject::calc_();
}

}  // namespace uking::action

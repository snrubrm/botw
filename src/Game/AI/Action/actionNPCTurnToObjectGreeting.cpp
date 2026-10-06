#include "Game/AI/Action/actionNPCTurnToObjectGreeting.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCTurnToObjectGreeting::NPCTurnToObjectGreeting(const InitArg& arg) : NPCTurnToObject(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
NPCTurnToObjectGreeting::~NPCTurnToObjectGreeting() {
    ;
}

bool NPCTurnToObjectGreeting::init_(sead::Heap* heap) {
    return NPCTurnToObject::init_(heap);
}

void NPCTurnToObjectGreeting::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTurnToObject::enter_(params);
    if (mActor->getASList()->x_1(0, 0).findIndex("TalkTurn") != -1) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000);
    } else if (mActor->getASList()->x_1(0, 0).findIndex("Sleep") != -1) {
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
            npc->_fe8 |= 0x40000000;
    }
    mActor->getASList()->x_2(0x42, 0xe, false, false);
    if (_40 == 6 || _40 == 1)
        sub_710020ADF0();
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

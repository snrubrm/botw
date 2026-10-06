#include "Game/AI/Action/actionNPCTalkToPlayerAction.h"
#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCTalkToPlayerAction::NPCTalkToPlayerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalkToPlayerAction::~NPCTalkToPlayerAction() = default;

bool NPCTalkToPlayerAction::oneShot_() {
    if (auto* npc = sead::DynamicCast<act::NPCBase>(mActor)) {
        npc->_c70 = 2;
        npc->_b00.copy(mMessageId_d);
        npc->_c18.copy(mASKeyName_d);
    }
    return true;
}

void NPCTalkToPlayerAction::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mASKeyName_d, "ASKeyName");
}

}  // namespace uking::action

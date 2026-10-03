#include "Game/AI/Action/actionSetOwnedHorseAS.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

SetOwnedHorseAS::SetOwnedHorseAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOwnedHorseAS::~SetOwnedHorseAS() = default;

bool SetOwnedHorseAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: regalloc (the original shares x20 between the transceiver id and the result and
// rematerialises the accessor address; ours keeps it in a callee-saved register)
bool SetOwnedHorseAS::oneShot_() {
    auto* mgr = HorseMgr::instance();
    if (!mgr)
        return false;
    bool result = false;
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor)) {
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x380001b),
                        const_cast<char*>(mASName_d.cstr()));
            result = true;
        }
    }
    return result;
}

void SetOwnedHorseAS::loadParams_() {
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::action

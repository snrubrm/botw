#include "Game/AI/aiUnk_7100711020.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

Unk_7100711020::Unk_7100711020(ksys::act::Actor* actor)
    : mActor(actor), _28(actor, 0x8000010), _80(actor, 0x800000f), _d0(actor, 0x8000008) {}

Unk_7100711020::~Unk_7100711020() {
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000f),
                            nullptr, false);
    }
}

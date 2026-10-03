#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

Unk_71025b1808Data::Unk_71025b1808Data()
    : mSender(0x8000040), mOwner(nullptr) {}

Unk_71025b1808Data::Unk_71025b1808Data(ksys::act::Actor* actor)
    : mSender(actor, 0x8000040), mOwner(actor) {}

Unk_71025b1808Data::~Unk_71025b1808Data() = default;

void Unk_71025b1808Data::sub_71006F0354(bool enabled) {
    mSender._18.y(mOwner);
    _3d8 = enabled;
}

void Unk_71025b1808Data::sub_71006F03D0() {
    if (!_3d8)
        return;
    for (auto& entry : mEntries) {
        if (entry.link.hasProcInCalcState() && !entry._10)
            mSender.sub_710070DCC0(&entry.link, true);
    }
}

// NON_MATCHING: same code; the register allocation differs (the original recomputes the address of
// _388's payload link instead of keeping it live across the payload lock, so x21/x22 are swapped).
bool Unk_71025b1808Data::sub_71006F0448(const ksys::Message& message) {
    if (_338.m2(message)) {
        for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
            if (!_338._38.mLink.hasProcInCalcState())
                return true;
            if (it->link == _338._38.mLink)
                return true;
            if (!it->link.hasProcInCalcState()) {
                it->link = _338._38.mLink;
                it->_10 = false;
                return true;
            }
        }
        return false;
    }

    if (!_388.m2(message))
        return false;
    const auto& link = _388._38.mLink;
    for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
        if (it->link == link) {
            it->link.reset();
            it->_10 = false;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: same code; the original merges the three returns through a callee-saved register
// (w19) instead of materialising the constant after the accessor's destructor.
bool Unk_71025b1808Data::sub_71006F0604(const ksys::MessageAck& ack) {
    if (ack.getType() != 0x8000040)
        return false;
    bool handled = false;
    for (auto& entry : mEntries) {
        if (!entry.link.hasProcInCalcState())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&entry.link, &accessor);
        const auto& dest = ack.getDestination();
        const auto* id = accessor.getMessageTransceiverId();
        if (dest.queue_id == id->queue_id && dest.id == id->id) {
            if (ack.isDestinationValid())
                entry._10 = true;
            handled = true;
            break;
        }
    }
    return handled;
}

void Unk_71025b1808Data::sub_71006F0734(const ksys::MessageType& type, void* data) {
    for (auto& entry : mEntries) {
        if (!entry.link.hasProcInCalcState())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&entry.link, &accessor);
        mOwner->sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(), type, data,
                                              false);
    }
}

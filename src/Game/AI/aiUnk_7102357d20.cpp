#include "Game/AI/aiUnk_7102357d20.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

bool Unk_7102357d20::sub_710070DC38(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DCC0(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DD78(accessor, ack);
}

bool Unk_7102357d20::sub_710070DD78(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessage(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE10(const ksys::MesTransceiverId& dest, bool ack) {
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DE98(ksys::act::Actor* actor, bool ack) {
    const auto* dest = actor->getMesTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070DF20(ksys::act::BaseProcLink* link, bool ack) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710070DFD8(accessor, ack);
}

bool Unk_7102357d20::sub_710070DFD8(const ksys::act::ActorLinkConstDataAccess& accessor,
                                    bool ack) {
    const auto* dest = accessor.getMessageTransceiverId();
    _14 = false;
    if (!_8)
        return false;
    return _8->sendMessageOnProcessingThread(*dest, _10, m2(), ack);
}

bool Unk_7102357d20::sub_710070E070(const ksys::MessageAck& ack) {
    if (ack.getType().value != _10.value || ack.getUserData() != m2())
        return false;
    _14 = ack.isDestinationValid() && ack.isSuccess();
    return true;
}

// ---- Senders with JobQueueLock-guarded payloads ----

Unk_710237ecc0::Unk_710237ecc0(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x800001e) {}

Unk_710237ecc0_Payload::Unk_710237ecc0_Payload() = default;

void Unk_710237ecc0_Payload::sub_710070E194(ksys::act::BaseProcLink* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    *out = mLink;
}

void Unk_710237ecc0_Payload::sub_710070E1F8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    mLink.acquire(proc, false);
}

Unk_71023b1608::Unk_71023b1608(ksys::act::Actor* actor) : Unk_7102357d20(actor, 0x800001b) {}

Unk_71023b1608_Payload::Unk_71023b1608_Payload() = default;

void Unk_71023b1608_Payload::sub_710070E374(ksys::act::BaseProcLink* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    *out = mLink;
}

void Unk_71023b1608_Payload::sub_710070E3D8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    mLink.acquire(proc, false);
}

void Unk_71024509d8_Payload::sub_710070E270(Unk_71024509d8_Payload* out) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    out->_4 = _4;
    out->_8 = _8;
}

#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace {
// 2026-10-07: static initializer 0x710066e034 creates this record and registers
// the message ID at +8 for destruction; 0x710066b9b8 copies that ID.
struct Unk_71025c5d60 {
    Unk_71025c5d60() {}
    s32 _0 = 0;
    s32 _4 = 0x8004ef;
    ksys::MesTransceiverId _8;
};
Unk_71025c5d60 sUnk_71025c5d60;
}  // namespace

namespace uking::act {

SiteBoss::Unk_71002cf2ac::~Unk_71002cf2ac() {
    mOwner = nullptr;
    for (s32 i = 0; i < 20; ++i) {
        auto& link = _1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (!accessor.isDeletedOrDeleting())
                accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        link.reset();
        if (_a0[i].isAllocatedOrFailed())
            _a0[i].deleteProc();
        _530[i] = sUnk_71025c5d60._8;
    }
    sub_710066BC04();
}

void SiteBoss::Unk_71002cf2ac::sub_710066DABC(ksys::act::BaseProc* proc, s32 idx) {
    if (proc && !_320[idx].hasProc()) {
        _320[idx].acquire(proc, false);
        return;
    }
    auto& link = _320[idx];
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        link.acquire(proc, false);
    }
}

void SiteBoss::Unk_71002cf2ac::sub_710066C13C(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x800004d), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C518(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x800004e), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C540(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x800004f), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C568(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000050), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C590(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000051), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C5B8(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000052), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C5E0(ksys::act::BaseProcLink* target, int idx,
                                              ksys::map::Rail* rail) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000053), idx, 0, rail);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C60C(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000054), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C634(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000054), idx, 1, nullptr);
    auto* owner = mOwner;
    ksys::MessageType type = ksys::MessageType(0x8000054);
    if (!owner)
        return;
    for (int i = 0; i < 24; ++i) {
        auto& link = _3b0(i);
        if (!link.hasProc())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        owner->sendMessage(*accessor.getMessageTransceiverId(), type, &_710[i], true);
    }
}

void SiteBoss::Unk_71002cf2ac::sub_710066C70C(ksys::act::BaseProcLink* target, int idx, bool flag,
                                              ksys::map::Rail* rail) {
    sub_710066C164(mOwner, target, ksys::MessageType(0x8000055), idx, flag, rail);
}

void SiteBoss::Unk_71002cf2ac::sub_710066CBD4(int idx) {
    sub_710066C164(mOwner, nullptr, ksys::MessageType(0x800005c), idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066CBF8(int idx) {
    auto& link = _1e0[idx];
    if (!link.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void SiteBoss::Unk_71002cf2ac::sub_710066CC64(int idx) {
    auto& link = _1e0[idx];
    if (!link.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

s32 SiteBoss::Unk_71002cf2ac::sub_710066C074() {
    _db0.lock();
    s32 count = 0;
    for (int i = 0; i < 20; ++i) {
        auto& link = _1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            count += accessor.isStateCalc();
        }
    }
    _db0.unlock();
    return count;
}


ksys::act::BaseProcLink* SiteBoss::Unk_71002cf2ac::sub_710066DE24(int idx) {
    return &_3b0[idx];
}

void SiteBoss::Unk_71002cf2ac::sub_710066DB98(ksys::act::BaseProc* proc, int idx) {
    if (proc && !_360.hasProc()) {
        _360.acquire(proc, false);
        return;
    }
    if (!_360.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_360, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    _360.acquire(proc, false);
}


Unk_7100722420::~Unk_7100722420() {
    _240.sub_7100721EFC();
}

void Unk_7100722420::sub_71007224D4() {
    _240.sub_7100721EFC();
}

// NON_MATCHING: the SafeArray iterator uses an element index instead of the original byte offset.
void SiteBoss::Unk_71002cf2ac::sub_710066CD7C(u32 value) {
    _94 = value;
    for (auto& link : _1e0) {
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }
}

bool SiteBoss::Unk_71002cf2ac::sub_710066D9B8(s32 idx) {
    auto& message = mPendingMessages[idx];
    if (message == 0)
        return false;
    auto& payload = _710[idx];
    payload.owner->sendMessage(_530[idx], message, &payload, true);
    message = ksys::MessageType(0);
    return true;
}

}  // namespace uking::act

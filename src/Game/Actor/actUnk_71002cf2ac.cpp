#include <prim/seadScopedLock.h>
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/Map/mapRail.h"
#include "Game/Actor/aiUnk_71007377D4.h"

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
            ksys::act::ActorLinkConstDataAccess accessor;
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

void SiteBoss::Unk_71002cf2ac::sub_710066C028() {
    for (s32 i = 0; i < 20; ++i) {
        if (_a0[i].isAllocatedOrFailed())
            _a0[i].deleteProc();
    }
    _8 = false;
}

// NON_MATCHING: same operations, but we compute the link reference once, so the frame is 0x20 bytes
// smaller and the index/registers differ from the original, which rebuilds it in both blocks.
void SiteBoss::Unk_71002cf2ac::sub_710066DC34(ksys::act::Actor* proc, s32 idx) {
    const s32 i = u32(idx) < 4 ? idx : 0;
    auto& link = _370[i];
    if (proc && !link.hasProc()) {
        link.acquire(proc, false);
        return;
    }
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        link.acquire(proc, false);
    }
}

void SiteBoss::Unk_71002cf2ac::sub_710066DA34(ksys::act::Actor* proc, s32 idx) {
    if (!proc)
        return;
    const s32 i = u32(idx) < 20 ? idx : 0;
    auto& link = _1e0[i];
    if (link.hasProc())
        return;
    link.acquire(proc, false);
    _530[i] = *proc->getMesTransceiverId();
}

void SiteBoss::Unk_71002cf2ac::sub_710066CCD0() {
    for (s32 i = 0; i < 20; ++i) {
        if (_a0[i].isAllocatedOrFailed())
            _a0[i].deleteProc();
    }
    _8 = false;
    for (s32 i = 0; i < 20; ++i) {
        auto& link = _1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }
}

void SiteBoss::Unk_71002cf2ac::sub_710066BC04() {
    for (auto& link : _320) {
        if (!link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (!accessor.isDeletedOrDeleting())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    {
        auto& link = _360;
        if (link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (!accessor.isDeletedOrDeleting())
                accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }

    auto* links = &_3b0[0];
    for (u32 i = 0; i < 24; ++i) {
        auto& link = links[i];
        if (!link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (!accessor.isDeletedOrDeleting())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    for (auto& link : _370) {
        if (!link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (!accessor.isDeletedOrDeleting())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: the loop and the wrap match; the original tests the negated ready flag with
// `eor` + `tbnz`, this build uses `tbz` (one instruction shorter).
void SiteBoss::Unk_71002cf2ac::sub_710066C738(sead::Vector3f* pos, f32 a, f32 b) {
    s32 tries = 20;
    s32 index = 11;
    while (true) {
        const auto& handle = _a0[index];
        const bool ready = handle.isAllocatedOrFailed() && handle.isProcReady();
        if (--tries < 0)
            break;
        if (ready)
            break;
        index = index + 1;
        index = index < 0 ? 19 : (index < 20 ? index : 0);
        if (index == 0)
            index = 1;
    }
    sub_710066C800(pos, index, a, b);
}

void SiteBoss::Unk_71002cf2ac::sub_710066DABC(ksys::act::BaseProc* proc, s32 idx) {
    if (proc && !_320[idx].hasProc()) {
        _320[idx].acquire(proc, false);
        return;
    }
    auto& link = _320[idx];
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        link.acquire(proc, false);
    }
}

bool SiteBoss::Unk_71002cf2ac::sub_710066BFEC(s32 index, const char* name,
                                               ksys::act::InstParamPack* params, bool flag) {
    _98 = flag;
    return sub_710073DB94(name, &_a0[index], params, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
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
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        owner->sendMessage(*accessor.getMessageTransceiverId(), type, &_710[i], true);
    }
}

// NON_MATCHING: same body and calls; our frame is 0x10 bytes larger because the scheduler keeps a
// different set of callee-saved registers (target is kept in a register, owner spilled, and the
// no-rail loop uses a byte offset in the loop-carried register).
// Sends `type` to bound actor `idx` (to every bound actor when idx >= 20). With a rail, the
// payload position is the average of the rail's points.
void SiteBoss::Unk_71002cf2ac::sub_710066C164(ksys::act::Actor* owner,
                                              ksys::act::BaseProcLink* target,
                                              ksys::MessageType type, int idx, u32 flags,
                                              ksys::map::Rail* rail) {
    if (!owner)
        return;

    sead::ScopedLock<sead::JobQueueLock> lock(&_db0);

    sead::Vector3f pos = sead::Vector3f::zero;
    if (rail) {
        const s32 num = rail->getNumPoints();
        if (num > 0) {
            for (s32 i = 0; i < num; ++i)
                pos += rail->getPointTranslate(i);
        }
        pos *= 1.0f / f32(num);

        s32 sent = 0;
        for (s32 i = 0; i < 20; ++i) {
            auto& payload = _710[i];
            payload.owner = owner;
            payload.target = target;
            payload.pos = pos;
            if (_99)
                flags |= 2;
            payload.flags = flags;
            payload.idx = i;
            if (idx >= 20 || idx == i) {
                auto& link = _1e0[i];
                if (link.hasProc()) {
                    if (idx >= 20)
                        payload.idx = sent++;
                    owner->sendMessage(_530[i], type, &payload, true);
                } else if (_a0[i].isAllocatedOrFailed()) {
                    if (idx >= 20)
                        payload.idx = sent++;
                    mPendingMessages[i] = type;
                }
            }
        }
        return;
    }

    const bool all = idx >= 20;
    s32 sent = 0;
    for (s32 i = 0; i < 20; ++i) {
        auto& payload = _710[i];
        payload.owner = owner;
        payload.target = target;
        payload.pos = pos;
        payload.flags = flags;
        payload.idx = i;
        const bool shouldSend = all || idx == i;
        if (!shouldSend)
            continue;
        auto& link = _1e0[i];
        if (link.hasProc()) {
            if (all)
                payload.idx = sent++;
            owner->sendMessage(_530[i], type, &payload, true);
        } else if (_a0[i].isAllocatedOrFailed()) {
            if (all)
                payload.idx = sent++;
            mPendingMessages[i] = type;
        }
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void SiteBoss::Unk_71002cf2ac::sub_710066CC64(int idx) {
    auto& link = _1e0[idx];
    if (!link.hasProc())
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

s32 SiteBoss::Unk_71002cf2ac::sub_710066C074() {
    _db0.lock();
    s32 count = 0;
    for (int i = 0; i < 20; ++i) {
        auto& link = _1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            count += accessor.isStateCalc();
        }
    }
    _db0.unlock();
    return count;
}


// The int argument is unused.
ksys::act::BaseProcLink* SiteBoss::Unk_71002cf2ac::sub_710066DE04(int) {
    return &_360;
}

ksys::act::BaseProcLink* SiteBoss::Unk_71002cf2ac::sub_710066DDEC(int idx) {
    return &_320[idx];
}

ksys::act::BaseProcLink* SiteBoss::Unk_71002cf2ac::sub_710066DE0C(int idx) {
    return &_370[idx];
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
    ksys::act::ActorLinkConstDataAccess accessor;
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

void Unk_7100722420::sub_7100723418(f32 delay) {
    _8 = true;
    _23c = delay;
}

bool Unk_71007237d0::sub_71007237D0(ksys::act::Actor* actor, const sead::SafeString* names, s32 num_parts,
                                    s32 num_values, sead::Heap* heap) {
    mActor = actor;
    _70.tryAllocBuffer(num_parts, heap);
    if (!_70.isBufferReady())
        return false;
    auto* model = actor->getModel();
    if (!model)
        return false;
    for (s32 i = 0; i < num_parts; ++i) {
        if (names[i].isEmpty())
            continue;
        _70[i]._a8.search(model, names[i]);
        _70[i].handle.setName(names[i]);
    }

    _40.tryAllocBuffer(num_values, heap);
    if (!_40.isBufferReady())
        return false;
    _50.tryAllocBuffer(num_values, heap);
    if (!_50.isBufferReady())
        return false;
    _50.fill(-1.0f);
    return true;
}

// NON_MATCHING: the original calls search and then returns true / false; ours tail-calls it.
bool Unk_71007237d0::sub_7100723A84(const sead::SafeString& name) {
    if (!mActor)
        return false;
    auto* model = mActor->getModel();
    if (!model)
        return false;
    return _8.search(model, name);
}

// NON_MATCHING: the SafeArray iterator uses an element index instead of the original byte offset.
void SiteBoss::Unk_71002cf2ac::sub_710066CD7C(u32 value) {
    _94 = value;
    for (s32 i = 0; i < 20; ++i) {
        auto& link = _1e0[i];
        if (link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
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


// NON_MATCHING: the original checks the try counter before the hasProc result and keeps 19 in a second
// register for the first wrap (loop and constant layout only).
s32 SiteBoss::Unk_71002cf2ac::sub_710066DF44(s32 index, s32 step, s32 skip) {
    s32 next = index + step;
    next = next < 0 ? 19 : (next < 20 ? next : 0);
    if (next == skip) {
        next = skip + step;
        next = next < 0 ? 19 : (next < 20 ? next : 0);
    }
    if (!_1e0[next].hasProc()) {
        for (s32 i = 20; i > 0; --i) {
            next += step;
            next = next < 0 ? 19 : (next < 20 ? next : 0);
            if (next == skip) {
                next = skip + step;
                next = next < 0 ? 19 : (next < 20 ? next : 0);
            }
            if (_1e0[next].hasProc())
                break;
        }
    }
    return next;
}

}  // namespace uking::act

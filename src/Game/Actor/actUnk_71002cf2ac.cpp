#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

void SiteBoss::Unk_71002cf2ac::sub_710066C13C(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x800004d, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C518(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x800004e, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C540(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x800004f, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C568(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x8000050, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C590(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x8000051, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C5B8(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x8000052, idx, 0, nullptr);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C5E0(ksys::act::BaseProcLink* target, int idx,
                                              ksys::map::Rail* rail) {
    sub_710066C164(mOwner, target, 0x8000053, idx, 0, rail);
}

void SiteBoss::Unk_71002cf2ac::sub_710066C60C(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x8000054, idx, 0, nullptr);
}

// NON_MATCHING: stack slot of the MessageType local (the known sendMessage MessageType issue)
void SiteBoss::Unk_71002cf2ac::sub_710066C634(ksys::act::BaseProcLink* target, int idx) {
    sub_710066C164(mOwner, target, 0x8000054, idx, 1, nullptr);
    auto* owner = mOwner;
    ksys::MessageType type = 0x8000054;
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
    sub_710066C164(mOwner, target, 0x8000055, idx, flag, rail);
}

void SiteBoss::Unk_71002cf2ac::sub_710066CBD4(int idx) {
    sub_710066C164(mOwner, nullptr, 0x800005c, idx, 0, nullptr);
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


void SiteBoss::Unk_71002cf2ac::sub_710066DB98(ksys::act::BaseProc* proc) {
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


}  // namespace uking::act

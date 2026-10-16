#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/System/VFR.h"

// 0x710071bd3c
Unk_7102451050::Unk_7102451050() = default;

// 0x710071bf08
Unk_7102451050::~Unk_7102451050() = default;

// 0x710071bfe4
void Unk_7102451050::sub_710071BFE4(const InitArg& arg) {
    _8 = arg.unit;
    _14 = arg._8;
    _1c = arg._c;
    if (_8 && arg._e) {
        setFlag(Flag::_0);
        sub_710071C034();
    }
}

// NON_MATCHING: the ring buffer clear is one 64-bit store in the original (our sead clear() stores mSize, then
// mHead: stp)
// 0x710071c1b8
void Unk_7102451050::sub_710071C1B8() {
    if (!_8)
        return;
    resetFlag(Flag::_0);
    if (_8->isFlagOn(Unk_7102450fa8::Flag::_1)) {
        setFlag(Flag::_0);
    } else {
        for (s32 i = 0; i < 9; ++i) {
            if (i == 0)
                continue;
            ksys::act::ActorLinkConstDataAccess accessor;
            if (_8->sub_71007194D4(i + 2, &accessor) && accessor.isStateSleep()) {
                setFlag(Flag::_0);
                break;
            }
        }
    }
    _10 = 1;
    _18 = 0;
    _20.clear();
    _1e = 0;
    _f8.clear();
    _8->resetFlag(Unk_7102450fa8::Flag::_3);
    _8->resetFlag(Unk_7102450fa8::Flag::_4);
    _8->sub_71007199A8();
}

// NON_MATCHING: our sead RingBuffer::popFront returns the request by value (copies it); the original pops without a
// copy
// 0x710071c034
void Unk_7102451050::sub_710071C034() {
    if (!_8)
        return;
    if (!_8->isFlagOn(Unk_7102450fa8::Flag::_4))
        _8->sub_71007199A8();
    if (_10 == 1) {
        s32 sleeping = 0;
        for (s32 i = 0; i < 9; ++i) {
            if (i == 0)
                continue;
            ksys::act::ActorLinkConstDataAccess accessor;
            if (_8->sub_71007194D4(i + 2, &accessor) && accessor.isStateSleep() && ++sleeping >= _1c) {
                _10 = 2;
                break;
            }
        }
    }
    sub_710071C33C();
    if (_10 == 4) {
        while (!_20.empty()) {
            const Request& request = _20.front();
            if (request.type == 3)
                sub_710071C89C(request);
            else if (request.type == 2)
                sub_710071C730(request);
            _20.popFront();
        }
        if (_1e == 0)
            _10 = 5;
    }
    sub_710071C440();
}

// 0x710071c33c
void Unk_7102451050::sub_710071C33C() {
    if (_10 != 2)
        return;
    _18 += ksys::VFR::instance()->getDeltaTime();
    if (isFlagOn(Flag::_0)) {
        _18 = _14;
        resetFlag(Flag::_0);
    } else if (_14 < 0) {
        return;
    }
    if (_18 >= _14) {
        _8->setFlag(Unk_7102450fa8::Flag::_3);
        _10 = 3;
    }
}

// NON_MATCHING: the original keeps an `all done` flag (and + cset) beside the early exit; tried a flag and a loop
// condition form
// 0x710071c440
void Unk_7102451050::sub_710071C440() {
    if (_10 != 5)
        return;
    for (s32 i = 0; i < _f8.size(); ++i) {
        const Member* member = _f8[i];
        if (member->id == -1 || !member->done)
            return;
    }
    _10 = 1;
    _8->resetFlag(Unk_7102450fa8::Flag::_3);
    _8->resetFlag(Unk_7102450fa8::Flag::_4);
    _18 = 0;
    _20.clear();
    _f8.clear();
    _8->_3f0.clear();
}

// NON_MATCHING: the phase cases are laid out the other way round, the position is stored pair-wise and the new
// member is zeroed before its id is set
// 0x710071c730
void Unk_7102451050::sub_710071C730(const Request& request) {
    ksys::act::ActorLinkConstDataAccess leader;
    switch (_8->_3c) {
    case Unk_7102450fa8::Phase::_3:
        _8->sub_71007194D4(1, &leader);
        break;
    case Unk_7102450fa8::Phase::_1:
        _8->sub_71007194D4(2, &leader);
        break;
    default:
        break;
    }
    if (!leader.hasProc())
        return;
    const sead::Vector3f pos = leader.getActorMtx().getTranslation();
    for (s32 i = 0; i < 9; ++i) {
        if (i == 0)
            continue;
        const s32 idx = i + 2;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (_8->sub_71007194D4(idx, &accessor) && accessor.isStateSleep()) {
            auto* member = _f8.emplaceBack();
            if (!member)
                break;
            _8->sub_71007196EC(idx, pos);
            member->id = idx;
            member->done = request._18;
        }
    }
}

// NON_MATCHING: the new member is zeroed before its id is set (Member's initialisers) and the index add is
// scheduled differently
// 0x710071c89c
void Unk_7102451050::sub_710071C89C(const Request& request) {
    for (s32 i = 0; i < 9; ++i) {
        if (i == 0)
            continue;
        const s32 idx = i + 2;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (!_8->sub_71007194D4(idx, &accessor) || !accessor.isStateSleep())
            continue;
        ksys::act::ActorLinkConstDataAccess actor;
        if (!ksys::act::acquireActor(&request.link, &actor))
            continue;
        if (_f8.isFull()) {
            actor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        } else if (auto* member = _f8.emplaceBack()) {
            _8->sub_710071984C(idx, actor.getActorMtx());
            _8->sub_710071A1C0(_8->sub_71007195B0(request.link), idx);
            member->id = idx;
            member->done = request._18;
        }
        return;
    }
}

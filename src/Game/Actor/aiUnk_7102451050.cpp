#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

// NON_MATCHING: scheduling: the original stores _18 .. _1e as one 64-bit value and loads the vtable earlier
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

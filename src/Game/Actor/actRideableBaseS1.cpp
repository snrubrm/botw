#include "Game/Actor/actRideableHorse.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "Game/Actor/actRideable.h"
#include <prim/seadFormatPrint.h>
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::act {

RideableBase::S1::S1() = default;

// NON_MATCHING: the selected saved-name address is retained; field selection and register allocation differ.
void RideableBase::S1::sub_7100E76900(s32 slot, s32 bank, bool force) {
    if (_0->x_7(slot, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        _0->sub_710115B01C(slot, bank, force);
    if (slot != 0 || !(_52 & 0x40))
        return;
    auto& saved = mSavedNames[bank];
    if (!(_52 & 0x80)) {
        const auto& name = _0->x_1(1, bank);
        if (!name.isEmpty() && name != saved)
            return;
    }
    if (_0->x_7(1, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        _0->sub_710115B01C(1, bank, force);
    saved = sead::SafeString::cEmptyString;
}

// 0x7100e7600c: clears / releases animation slot `slot` in `bank`. Releasing slot 0 with the saved-name
// flag of _52 clears the bank's saved name, unless the bank's current AS name differs from it.
void RideableBase::S1::sub_7100E7600C(s32 slot, s32 bank) {
    if (_0->x_7(slot, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        _0->sub_710115B01C(slot, bank, true);
    if (slot != 0 || !(_52 & 0x40))
        return;
    if (!(_52 & 0x80)) {
        const auto& name = _0->x_1(1, bank);
        if (!name.isEmpty() && name != mSavedNames[bank])
            return;
    }
    if (_0->x_7(1, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        _0->sub_710115B01C(1, bank, true);
    mSavedNames[bank] = sead::SafeString::cEmptyString;
}

void RideableBase::S1::sub_7100E761A4(bool clear_gear, bool force) {
    _8 = 0;
    _9 = 0;
    sub_7100E76900(0, 1, force);
    sub_7100E76900(0, 2, force);
    if (clear_gear) {
        _a = 0;
        _b = 0;
    }
    _20 = -1.0f;
    _24 = 1.0f;
    _18 = 0;
    _28 = 0;
    _2c = 0;
    if (_2d == 2) {
        auto* list = _0;
        const s32 bank = _2e;
        const u16 flags = _52;
        list->sub_710115F2EC(0, bank, 1.0f);
        if (flags & 0x40)
            list->sub_710115F2EC(1, bank, 1.0f);
    }
    _2d = 0;
}


// 0x7100e76aa4: requests the (`type`, `gear`) pair with the value the request starts from. Ignored while a
// request for a different pair is still running, and when the pair is already the current one.
void RideableBase::S1::sub_7100E76AA4(UnkGear type, UnkGear gear, f32 value) {
    if (!(_9 == _b && _8 == _a)) {
        if (_c > 0.0f)
            return;
    }
    if (_8 == int(type) && _b == int(gear))
        return;
    _a = int(type);
    _b = int(gear);
    if (_8 != _a || _9 != _b) {
        _10 = value;
        _c = 0.0f;
        return;
    }
    const s8 other_bank = 3 - _2e;
    sub_7100E7600C(0, other_bank);
}

// 0x7100e76bd8 (placeholder name; names inside are guesses): whether the current AS state entry keeps the
// rider's AS inside that entry's gait range. The frame and the rate come from the other bank (3 - _2e); an
// out-of-range frame below the range asks the AS list to move to the range's high value.
bool RideableBase::S1::sub_7100E76BD8(const Unk68* entry, f32 speed) {
    if (_2c != 2)
        return false;
    if (_18 != entry || !_18)
        return false;
    f32 range[2];
    entry->getGaitSpeedRange(range, _9);
    range[0] -= speed;
    range[1] += speed;
    const f32 rate = _0->x_5(0, s8(3 - _2e), &ksys::as::ASList::Unk2::sub_7101163564);
    const f32 frame = _0->x_5(0, s8(3 - _2e), &ksys::as::ASList::Unk2::sub_71011632F8);
    if (range[0] <= frame && frame <= range[1])
        return true;
    if (rate < range[0])
        return _0->sub_710115F0BC(0, s8(3 - _2e), range[1]);
    return false;
}

// NON_MATCHING: the guard is the same fused `fcmp / ccmp / b.eq` but the original branches to its false block
// and falls through to the state test where ours falls through to the false block (ccmp #4 + b.ne).
// 0x7100e76b40: takes an AS state entry as the current animation state when its rate beats `rate`; returns
// false while another entry is still running, and reports through `out` whether the request is over half way.
bool RideableBase::S1::sub_7100E76B40(const Unk68* entry, f32 value, f32 rate, f32 speed, bool* out) {
    const f32 entry_rate = entry->mRate;
    if (_2c == 0 || !(entry_rate > rate))
        return false;
    if (_2c == 2) {
        if (_18 != entry)
            return false;
    } else if (_2c > 2) {
        return false;
    }
    _18 = entry;
    _20 = rate;
    _24 = value;
    _28 = speed;
    if (_2c == 2)
        *out = rate / entry_rate > 0.5f;
    else
        *out = true;
    return true;
}

// NON_MATCHING: bank-count checks are reordered and SafeString assignment is devirtualized.
// 0x7100e74604 (in actRideable.cpp): the AS name of one animal move.
void formatAnimalMoveString(sead::BufferedSafeString* out, int move_type, u32 gear);

// 0x7102603538 (placeholder name): the animal move AS name table (6 move types x 5 gears).
sead::SafeArray<sead::SafeArray<sead::FixedSafeString<32>, 5>, 6> sAnimalMoveNames;

// 0x7100e7449c (placeholder name): fills the animal move AS name table.
// NON_MATCHING: same loop (AnimalMoveType iterator, so the index spills like the original) but the register
// allocation and the second argument (reloaded from the slot here) differ.
void sub_7100E7449C() {
    for (AnimalMoveType::iterator it = AnimalMoveType::begin(); it != AnimalMoveType::end(); ++it) {
        const AnimalMoveType type = *it;
        formatAnimalMoveString(&sAnimalMoveNames[type][0], type, 0);
        formatAnimalMoveString(&sAnimalMoveNames[type][1], type, 1);
        formatAnimalMoveString(&sAnimalMoveNames[type][2], type, 2);
        formatAnimalMoveString(&sAnimalMoveNames[type][3], type, 3);
        formatAnimalMoveString(&sAnimalMoveNames[type][4], type, 4);
    }
}

void RideableBase::S1::sub_7100E747E8(ksys::as::ASList* list) {
    _0 = list;
    if (list->mSlots.size() < 1 || list->mSlots[0]._20.size() < 3 ||
        list->mSlots.size() == 1 || list->mSlots[1]._20.size() != 3)
        _52 &= ~0x40;
    else
        _52 |= 0x40;
    mSavedNames[0] = sead::SafeString::cEmptyString;
    mSavedNames[1] = sead::SafeString::cEmptyString;
    mSavedNames[2] = sead::SafeString::cEmptyString;
}

void RideableBase::S1::sub_7100E770C4(bool force) {
    if ((_52 & 0x400) && !force)
        return;
    _52 = (_52 & ~0x610) | 0x10;
    if (!_40.isEmpty()) {
        _40 = sead::SafeString::cEmptyString;
        _51 = 0;
    }
}

int RideableBase::S1::sub_7100E76CEC() {
    if (_52 & 2)
        return 0;
    if (_0->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C))
        return 0;
    if (_0->x_7(0, _2e, &ksys::as::ASList::Unk2::sub_710002E82C))
        return _2e;
    return 0;
}

void RideableBase::S1::sub_7100E76BBC() {
    _18 = 0;
    _20 = -1.0f;
    _24 = 1.0f;
    _28 = 0;
    _2c = 0;
}

void RideableBase::S1::sub_7100E7878C() {
    if (!_2d)
        _2d = 1;
}

f32 RideableBase::S1::sub_7100E76D6C() {
    if (_0->x_4(0, 0))
        return _0->x_5(0, _2e, &ksys::as::ASList::Unk2::sub_71011632F8);
    return 0.0f;
}

f32 RideableBase::S1::sub_7100E76DC4() {
    if (_0->x_4(0, 0))
        return _0->x_5(0, _2e, &ksys::as::ASList::Unk2::sub_710116323C);
    return 0.0f;
}

f32 RideableBase::S1::sub_7100E76E1C() {
    if (_0->x_4(0, 0))
        return _0->x_5(0, _2e, &ksys::as::ASList::Unk2::sub_7101163160);
    return 1.0f;
}

void RideableBase::S1::sub_7100E787A0() {
    _52 |= 0x20;
}

void RideableBase::S1::sub_7100E78E00() {
    _52 |= 0x80;
}

void RideableBase::S1::sub_7100E786F0(const sead::SafeString& name) {
    int bank;
    if (_9) {
        bank = _2e;
    } else if (_52 & 2) {
        bank = 0;
    } else if (_0->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C)) {
        bank = 0;
    } else if (_0->x_7(0, _2e, &ksys::as::ASList::Unk2::sub_710002E82C)) {
        bank = _2e;
    } else {
        bank = 0;
    }
    sub_7100E76260(name, 0, 0, 0, bank);
}

Unk_7100e7941c::Unk_7100e7941c() = default;

Unk_7100e7941c::~Unk_7100e7941c() {
    if (_0)
        delete _0;
    if (_8)
        delete _8;
    if (_10)
        ksys::phys::QueryContactPointInfo::free(_10);
}

}  // namespace uking::act

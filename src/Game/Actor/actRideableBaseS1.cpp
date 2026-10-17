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
    auto& saved = bank == 1 ? _68 : bank == 2 ? _78 : _58;
    if (!(_52 & 0x80)) {
        const auto& name = _0->x_1(1, bank);
        if (!name.isEmpty() && name != saved)
            return;
    }
    if (_0->x_7(1, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        _0->sub_710115B01C(1, bank, force);
    saved = sead::SafeString::cEmptyString;
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


// NON_MATCHING: bank-count checks are reordered and SafeString assignment is devirtualized.
// 0x7100e74604 (CSV formatAnimalMoveString): the AS name of one animal move (`gear` 0 is the default
// "Wait" name, move type 0 ignores the type name).
// NON_MATCHING: same calls and order but the original keeps a separate StringPrintFormatter stack slot per branch
// (0xd0 frame); ours reuses one (0x90). The original's sead::BufferedSafeStringBase::format is the inline
// PrintFormatter version (see libwork), so the manual formatter is used here.
void formatAnimalMoveString(sead::BufferedSafeString* out, int move_type, u32 gear) {
    if (gear == 0) {
        out->copy(sUnk_7102603110);
    } else if (move_type == 0) {
        sead::StringPrintFormatter formatter(out);
        formatter << "Move_Gear%d";
        formatter, gear;
        formatter.flush();
    } else {
        sead::StringPrintFormatter formatter(out);
        formatter << "Move_%s_Gear%d" << AnimalMoveType::text(move_type);
        formatter, gear;
        formatter.flush();
    }
}

void RideableBase::S1::sub_7100E747E8(ksys::as::ASList* list) {
    _0 = list;
    if (list->mSlots.size() < 1 || list->mSlots[0]._20.size() < 3 ||
        list->mSlots.size() == 1 || list->mSlots[1]._20.size() != 3)
        _52 &= ~0x40;
    else
        _52 |= 0x40;
    _58 = sead::SafeString::cEmptyString;
    _68 = sead::SafeString::cEmptyString;
    _78 = sead::SafeString::cEmptyString;
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

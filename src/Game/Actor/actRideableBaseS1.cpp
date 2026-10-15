#include "Game/Actor/actRideable.h"
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

}  // namespace uking::act

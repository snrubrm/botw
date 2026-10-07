#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::act {

RideableBase::S1::S1() = default;

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

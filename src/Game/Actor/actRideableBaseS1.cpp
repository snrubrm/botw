#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::act {

RideableBase::S1::S1() = default;

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

void RideableBase::S1::sub_7100E78E00() {
    _52 |= 0x80;
}

}  // namespace uking::act

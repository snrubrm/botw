#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace ksys::act {

Unk_7102459df8::~Unk_7102459df8() = default;

void Unk_7102459df8::m5() {
    if (_10)
        _10->sub_71007A5318();
    if (_18)
        _18->sub_710079FE9C();
    if (_20)
        _20->sub_710079F600();
}

bool Unk_7102459df8::m9() {
    if (_20)
        _20->sub_710079F600();
    return true;
}

void Unk_7102459df8::m10() {
    if (_20)
        _20->sub_710079F600();
}

bool Unk_7102459df8::sub_710079CE78() const {
    if (!_10)
        return false;
    return _10->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CE98() const {
    if (!_10)
        return 0;
    return _10->mNum;
}

bool Unk_7102459df8::sub_710079CEB0() const {
    if (!_18)
        return false;
    return _18->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CED0() const {
    if (!_18)
        return 0;
    return _18->mNum;
}

bool Unk_7102459df8::sub_710079CEE8() const {
    if (!_20)
        return false;
    return _20->mNum > 0;
}

s32 Unk_7102459df8::sub_710079CF08() const {
    if (!_20)
        return 0;
    return _20->mNum;
}

bool Unk_7102459df8::sub_710079CF20() const {
    if (!_20)
        return false;
    return _20->_582 != 0;
}

Unk_7102459df8::Unk_7102459e60::Unk1* Unk_7102459df8::sub_710079CF40(int idx) const {
    if (!_10)
        return nullptr;
    return &_10->mEntries[idx];
}

Unk_7102459df8::Unk_7102459e88::Unk1* Unk_7102459df8::sub_710079CF6C(int idx) const {
    if (!_18)
        return nullptr;
    return &_18->mEntries[idx];
}

Unk_7102459df8::Unk_710079d5a0::Unk1* Unk_7102459df8::sub_710079CF98(int idx) const {
    if (!_20)
        return nullptr;
    return &_20->mEntries[idx];
}

}  // namespace ksys::act

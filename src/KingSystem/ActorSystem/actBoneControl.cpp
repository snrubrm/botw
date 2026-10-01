#include "KingSystem/ActorSystem/actBoneControl.h"

namespace ksys::act {

BoneControl::BoneControl() = default;

bool sub_7100D83014(sead::Vector3f* out, const BoneControl* bone_control) {
    if (!bone_control)
        return false;
    auto* unk = bone_control->_0;
    if (!unk)
        return false;
    unk->_10.sub_7100D892C4(out);
    return true;
}

Unk_7100d8557c::Unk_7100d8557c(Actor* actor) : mActor(actor), _10(actor), _e8(actor) {}

void Unk_7100d8557c::sub_7100D8571C(const sead::Vector3f& pos) {
    _10._8 = pos;
    _e8._8 = pos;
}

void Unk_7100d8557c::sub_7100D85750() {
    if (_e8._24 & 1)
        _e8._24 |= 2;
    if (_10._d4 & 1)
        _10._d4 |= 2;
}

void Unk_7100d8557c::sub_7100D85774() {
    _10._d4 &= ~0xc02;
    _e8._24 &= ~0xc02;
}

void Unk_7100d8557c::sub_7100D85794() {
    _10._d4 |= 0x10;
    _e8._24 |= 0x10;
}

void Unk_7100d8557c::sub_7100D857B0() {
    _10._d4 &= ~0x10;
    _e8._24 &= ~0x10;
}

}  // namespace ksys::act

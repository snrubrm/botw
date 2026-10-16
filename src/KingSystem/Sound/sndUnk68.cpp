#include "KingSystem/Sound/sndUnk_7102502138.h"

namespace ksys::snd {

void Unk_7102502138::Unk68::sub_710104DD7C(s32 value) {
    _568 = value;
    _480->sub_71012C5034(value);
}

void Unk_7102502138::Unk68::sub_710104BEF0() {
    if (_56c & 4) {
        sub_710104BF44();
        _56c &= ~4;
    }
    if (_56c & 8) {
        sub_710104C648();
        _56c &= ~8;
    }
}

// NON_MATCHING: the original compares with `current` through an inline byte loop without the two
// assureTermination calls; the form is unknown.
bool Unk_7102502138::Unk68::sub_710104D204(const sead::SafeString& name,
                                           const sead::SafeString& current) const {
    return name == "None" || name == "No_Sound" || name == "Dummy" || name == current;
}

void Unk_7102502138::Unk68::sub_710104DD20(bool flag) {
    _56c = flag ? _56c | 1 : _56c & ~1;
    _480->sub_71012C384C("BaseEquip_Quiver");
}

void Unk_7102502138::Unk68::sub_710104DD88(bool flag) {
    _56c = flag ? _56c | 2 : _56c & ~2;
    _520->sub_71012C384C("BaseEquip_Belt");
    _56c |= 0xc;
}

// NON_MATCHING: the last level choice is a select here (the original branches).
void Unk_7102502138::Unk68::sub_710104DF54(f32 value) {
    s32 level = value > 0.25f ? 0 : value > 0.18f ? 1 : value > 0.1f ? 2 : 3;
    _538->_98->sub_71012C3888(&level);
    _540->_98->sub_71012C3888(&level);
    if (!_15c)
        _160->sub_71012C3888(&level);
    if (!_1fc)
        _200->sub_71012C3888(&level);
}

// NON_MATCHING: the last level choice is a select here (the original branches).
void Unk_7102502138::Unk68::sub_710104E004(f32 value) {
    s32 level = value > 0.25f ? 0 : value > 0.18f ? 1 : value > 0.1f ? 2 : 3;
    _528->_98->sub_71012C3888(&level);
    _530->_98->sub_71012C3888(&level);
    if (!_bc)
        _c0->sub_71012C3888(&level);
}

void Unk_7102502138::Unk68::sub_710104E0A0(void* arg) {
    if (_548)
        _548->_98->sub_71012C38F8(arg);
    if (_550)
        _550->_98->sub_71012C38F8(arg);
    if (_558)
        _558->_98->sub_71012C38F8(arg);
}

void Unk_7102502138::Unk68::sub_710104D398(bool flag) {
    _15c = flag;
    _56c |= 8;
}

void Unk_7102502138::Unk68::sub_710104D620(bool flag) {
    _bc = flag;
    _56c |= 8;
}

void Unk_7102502138::Unk68::sub_710104D834(bool flag) {
    _1fc = flag;
    _56c |= 8;
}

}  // namespace ksys::snd

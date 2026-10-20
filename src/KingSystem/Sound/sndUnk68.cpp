#include "KingSystem/Sound/sndUnk_7102502138.h"

namespace ksys::snd {

bool sub_710104DDF8(const sead::SafeString& name) {
    return name != "Dummy" && name != "None" && name != "No_Sound";
}

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

bool Unk_7102502138::Unk68::sub_710104D204(const sead::SafeString& name,
                                           const sead::SafeString& current) const {
    return name == "None" || name == "No_Sound" || name == "Dummy" || name.startsWith(current);
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

// NON_MATCHING: the store of `level` is sunk to the common branch and lands at sp+8 in the
// original; ours keeps it at x29-4.
void Unk_7102502138::Unk68::sub_710104DF54(f32 value) {
    s32 level = 0;
    if (value <= 0.25f) {
        if (value > 0.18f)
            level = 1;
        else if (value > 0.1f)
            level = 2;
        else
            level = 3;
    }
    _538->_98->sub_71012C3888(&level);
    _540->_98->sub_71012C3888(&level);
    if (!_15c)
        _160->sub_71012C3888(&level);
    if (!_1fc)
        _200->sub_71012C3888(&level);
}

// NON_MATCHING: same store-sinking / stack-slot difference as sub_710104DF54.
void Unk_7102502138::Unk68::sub_710104E004(f32 value) {
    s32 level = 0;
    if (value <= 0.25f) {
        if (value > 0.18f)
            level = 1;
        else if (value > 0.1f)
            level = 2;
        else
            level = 3;
    }
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

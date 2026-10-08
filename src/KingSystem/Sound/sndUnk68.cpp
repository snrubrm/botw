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

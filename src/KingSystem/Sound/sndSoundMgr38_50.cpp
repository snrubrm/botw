#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

// TU 0x71010366e4..0x7101037308 (static initialiser) in the original.

// vtable 0x7102501fd0 (the only one in this TU): D2 0x71010367e0 (empty), D0 0x71010367e4.
Unk_SoundMgr38_50::~Unk_SoundMgr38_50() = default;

void Unk_SoundMgr38_50::sub_71010367E8() {
    _38 = 0;
    _40 = 0;
    _44 = -1;
    _3c = false;
    _48 = 0;
    _80 = 0;
    _84 = 0;
    _50.setValueImmediate(0.0f);
    _68.setValueImmediate(0.0f);
}

void Unk_SoundMgr38_50::sub_7101036840() {
    sub_7101036848(-1);
}

// Empty in the release build.
void Unk_SoundMgr38_50::sub_7101036A68() {}

}  // namespace ksys::snd

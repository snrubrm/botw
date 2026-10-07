#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x710103ae20 (`_GLOBAL__sub_I_sndSoundMgr38.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C104() const {
    return _28;
}

// NON_MATCHING: only the schedule (the original loads both vectors up front and keeps the six results in
// registers before the stores).
void Unk_SoundMgr38_28::sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size) {
    const sead::Vector3f half = *size * 0.5f;
    mBoxMin = *pos - half;
    mBoxMax = half + *pos;
    mBoxCenter = *pos;
    mBoxSize = *size;
}

void Unk_SoundMgr38_28::sub_7101037F5C(u8 value) {
    _344 = value;
}

void Unk_SoundMgr38_28::sub_7101037F64(bool enabled) {
    _328 = enabled;
    if (!enabled) {
        _3c8 = nullptr;
        _3c0 = nullptr;
    }
}

void Unk_SoundMgr38_28::sub_7101037F7C(bool value) {
    _39c = value;
}

}  // namespace ksys::snd

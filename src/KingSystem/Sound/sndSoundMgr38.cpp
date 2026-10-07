#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x710103ae20 (`_GLOBAL__sub_I_sndSoundMgr38.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

void Unk_SoundMgr38_28::sub_7101037F7C(bool value) {
    _39c = value;
}

}  // namespace ksys::snd

#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

// TU 0x71010349dc..0x71010366e4 (static initialiser) in the original.

void Unk_SoundMgr38_48::sub_7101035A50() {
    _1e08.set(1);
    if (_1e08.isOff(2)) {
        sub_7101035888();
        _1dc0 = 1;
    }
}

}  // namespace ksys::snd

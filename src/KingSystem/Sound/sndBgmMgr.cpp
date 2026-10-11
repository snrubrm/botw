#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

void Unk_SoundMgr30::sub_7100FF88A8(s32 fade_type) {
    if (_78)
        _78->sub_7101007AA0(fade_type == 1 ? _50 : 0.0f);
}

void Unk_SoundMgr30::sub_7100FF8AC4(s32 fade_type) {
    if (_78) {
        f32 fade_sec = 0.1f;
        if (fade_type == 1)
            fade_sec = _54;
        else if (fade_type == 2)
            fade_sec = _58;
        _78->sub_7101007A08(fade_sec);
    }
    _88 &= ~4;
}

}  // namespace ksys::snd

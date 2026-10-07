#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_SoundMgra8::~Unk_SoundMgra8() = default;

void Unk_SoundMgra8::sub_710104B404(sead::Heap* heap) {}

void Unk_SoundMgra8::sub_710104B408() {
    if (_48) {
        _49 = false;
        for (auto it = _50.begin(); it != _50.end(); ++it) {
            if (it->sub_710104ACB4()) {
                _49 = true;
                break;
            }
        }
        if (_4a72)
            --_4a72;
    }
}

}  // namespace ksys::snd

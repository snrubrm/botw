#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_710260f130* sub_7100FFD9D0() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f130>(controller);
}

Unk_710260f218* sub_7100FFDA7C() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f218>(controller);
}

void Unk_710260f130::sub_7100FFA1E0(bool value) {
    if (!_92)
        return;
    _91 = value;
    if (value)
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{19});
    else
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{20});
}

}  // namespace ksys::snd

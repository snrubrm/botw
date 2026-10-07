#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::snd {

void SoundMgr::sub_71011FC29C() {
    mDuckingMgr->sub_7101042024(0x23);
    _238 |= 2;
}

void Unk_SoundMgr48::sub_7101055B44() {
    if (_18.isEnabled())
        _18.stop(0.1f, 0.0f);
}

void Unk_710104e5b4::sub_710104F86C() {
    if (evt::Manager::instance()->hasActiveEvent() && !(_2a0 & 4))
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(0x10);
}

void Unk_710104e5b4::sub_710104F8C4(bool suspend) {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0x10, suspend);
}

void Unk_710104e5b4::sub_710104F8E0() {
    if (!(_2a0 & 4))
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(0xf);
}

void Unk_710104e5b4::sub_710104F904() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0xf, false);
}

void Unk_710103b704::sub_710103D418() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(0x1f);
}

f32 Unk_SoundMgr48::sub_7101055E3C() const {
    return 0.2f;
}

bool Unk_SoundMgra8::sub_710104B5DC(u32 idx) const {
    return _4a70 > idx;
}

void Unk_SoundMgra8::sub_710104B554(Unk_SoundInstance* instance) {}

f32 Unk_SoundMgra8::sub_710104B558(ksys::act::Actor* actor) {
    f32 volume = -1.0f;
    if (_48 && _49) {
        for (auto it = _50.begin(); it != _50.end(); ++it) {
            const f32 value = it->sub_710104AC00(actor);
            if (value >= 0.0f) {
                volume = value;
                break;
            }
        }
    }
    return volume;
}

}  // namespace ksys::snd

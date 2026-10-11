#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

void Bgm::m4() {}

void Bgm::m6(f32 fade_sec) {
    if (mActive)
        return;
    m12(fade_sec);
    m8(true);
}

void Bgm::m7(f32 fade_sec) {
    if (mActive) {
        m13(fade_sec);
        m8(false);
    }
}

void Bgm::m8(bool active) {
    mActive = active;
}

bool Bgm::m10() {
    return false;
}

bool Bgm::m11() {
    return false;
}

void Bgm::m12(f32 fade_sec) {}
void Bgm::m13(f32 fade_sec) {}
void Bgm::m14(sead::TextWriter& writer) {}

}  // namespace ksys::snd

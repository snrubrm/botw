#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>

namespace ksys::snd {

Unk_7100ff7444::Unk_7100ff7444() = default;

Unk_7100ff7444::~Unk_7100ff7444() {
    sub_7100FF74D0();
    mEntries.freeBuffer();
}

void Unk_7100ff7444::sub_7100FF75DC(s32 capacity, sead::Heap* heap) {
    mEntries.allocBuffer(capacity, heap, 8);
}

void Unk_7100ff7444::sub_7100FF7830(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mEntries)
        entry.bgm->m6(fade_sec);
}

void Unk_7100ff7444::sub_7100FF78A8(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mEntries)
        entry.bgm->m7(fade_sec);
}

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

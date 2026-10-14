#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>

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

// Defined in this TU: the BGM controllers (sndBgmMgr.cpp, sndBattleDungeonBgm.cpp) call the constructor 0x7100ff7408
// and destructor 0x7100ff7444 out of line.
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

}  // namespace ksys::snd

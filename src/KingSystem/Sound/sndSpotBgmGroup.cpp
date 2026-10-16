#include <aal/aalGroup.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/Actor/Action/actionSpotBgmTriggerAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

// The kind 5 spot BGM (Unk_710260f1a8, 0x7101024a54..): a TU of its own in the original (the spot BGM instance
// functions it calls are not inlined).

namespace ksys::snd {

Unk_710260f1a8::~Unk_710260f1a8() {
    mInstances.freeBuffer();
    _60.freeBuffer();
}

void Unk_710260f1a8::m12(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i])
            instance->sub_710102413C(fade_sec);
    }
}

void Unk_710260f1a8::m13(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i])
            instance->sub_710102418C(fade_sec);
    }
    _28 = 0;
}

void Unk_710260f1a8::sub_71010255D0() {
    _80 = 0;
    if (mGroup)
        mGroup->getParam().setVolume(1.0f);
}

}  // namespace ksys::snd

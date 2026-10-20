#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <new>
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

void Unk_710260f1a8::sub_71010252C0(Unk_SpotBgmInstance* instance, bool started) {
    if (!mInstances.isBufferReady())
        return;
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (!mInstances[i]) {
            instance->_368 = started ? instance->_368 | 1 : instance->_368 & ~1u;
            mInstances[i] = instance;
            break;
        }
    }
}

void Unk_710260f1a8::sub_7101025388(Unk_SpotBgmInstance* instance) {
    if (!mInstances.isBufferReady())
        return;
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (mInstances[i] == instance) {
            instance->sub_7101024280();
            mInstances[i] = nullptr;
            break;
        }
    }
}

void Unk_710260f1a8::sub_71010255D0() {
    _80 = 0;
    if (mGroup)
        mGroup->getParam().setVolume(1.0f);
}

}  // namespace ksys::snd

namespace ksys::snd {

// NON_MATCHING: instance traversal and control forwarding use different loop scheduling.
void Unk_710260f1a8::sub_710102544C(bool entering) {
    if (entering) {
        for (s32 i = 0; i < mInstances.size(); ++i) {
            if (mInstances[i])
                mInstances[i]->sub_7101023EC8();
        }
    } else {
        for (s32 i = 0; i < mInstances.size(); ++i) {
            if (mInstances[i])
                mInstances[i]->sub_71010242C8();
        }
    }
}

}  // namespace ksys::snd

namespace ksys::snd {

void Unk_710260f1a8::sub_7101024AD4(sead::Heap* heap) {
    mInstances.tryAllocBuffer(4, heap);
    mInstances.fill(nullptr);
    auto* positions = new (heap, 8, std::nothrow) PositionRequest[5];
    if (positions)
        _60.setBuffer(5, positions);
    if (auto* groups = aal::SystemAccessor::getGroupMgr())
        mGroup = groups->findGroup("EnvNoisy");
}

}  // namespace ksys::snd

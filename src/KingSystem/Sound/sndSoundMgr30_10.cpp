#include <cstddef>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

// NON_MATCHING: scheduling of the string termination and the member stores after it.
Unk_SoundMgr30_10::Unk_SoundMgr30_10() {
    mHandles.initOffset(offsetof(Unk_SpotBgmHandle, mListNode));
}

Unk_SoundMgr30_10::~Unk_SoundMgr30_10() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
}

void Unk_SoundMgr30_10::init(sead::Heap* heap) {
    _8 = new (heap, 8) Unk_710101E140();
    _8->init(heap);
}

void Unk_SoundMgr30_10::sub_710101D718(Unk_SpotBgmHandle* handle) {
    auto lock = sead::makeScopedLock(mCS);
    if (handle->mListNode.isLinked())
        mHandles.erase(handle);
}

}  // namespace ksys::snd

#include <cstddef>
#include <math/seadVector.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndBgmMgr.h"

namespace ksys::snd {

// TU statics (static initialiser 0x710101d77c); debug values: the category selects the handles whose _178 is set.
static sead::Vector2f sUnk_7102610170{80.0f, 480.0f};
static sead::FixedSafeString<32> sDebugHandleName;

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

void Unk_SoundMgr30_10::sub_710101D5EC(Unk_SpotBgmHandle* handle) {
    auto lock = sead::makeScopedLock(mCS);
    if (handle->mListNode.isLinked())
        return;
    handle->_178 = sDebugHandleName == handle->mCategory;
    mHandles.pushFront(handle);
    _28 = true;
}

void Unk_SoundMgr30_10::sub_710101D718(Unk_SpotBgmHandle* handle) {
    auto lock = sead::makeScopedLock(mCS);
    if (handle->mListNode.isLinked())
        mHandles.erase(handle);
}

}  // namespace ksys::snd

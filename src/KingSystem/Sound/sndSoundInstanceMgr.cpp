#include "KingSystem/Sound/sndMgr.h"
#include <prim/seadScopedLock.h>
#include <new>

namespace ksys::snd {

Unk_SoundMgra8::Unk_SoundMgra8() {
    _49 = false;
    mFreeList.setWork(mPoolStorage, sizeof(Unk_SoundInstance), 16);
    _50.setBuffer(16, mPointerStorage);
    _4a70 = 0;
    _4a72 = 0;
}

// NON_MATCHING: the found instance pointer is retained instead of reloaded.
Unk_SoundInstance* Unk_SoundMgra8::sub_710104B480(s32 id) {
    auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _50.size(); ++i) {
        if (_50.unsafeAt(i)->_48c == id)
            return _50.at(i);
    }
    if (_50.size() >= _50.capacity())
        return nullptr;
    auto* instance = new (mFreeList.alloc()) Unk_SoundInstance(id);
    _50.pushBack(instance);
    return instance;
}

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

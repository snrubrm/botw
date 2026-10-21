// The TU at 0x71012c2b98 .. 0x71012c3070: the emitter allocate callback of Unk_710251af30.
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndSoundAttenuationMgr.h"

namespace ksys::snd {

Unk_710251afc8::Unk_710251afc8() = default;

Unk_710251afc8::~Unk_710251afc8() {
    mEmitters.freeBuffer();
}

void Unk_710251afc8::init(sead::Heap* heap) {
    mEmitters.allocBuffer(400, heap);
}

void Unk_710251afc8::onFreeEmitter(aal::Emitter* emitter) {
    if (!emitter)
        return;

    auto lock = sead::makeScopedLock(mCS);
    for (auto it = mEmitters.robustBegin(), end = mEmitters.robustEnd(); it != end; ++it) {
        if (it->emitter == emitter)
            mEmitters.erase(&*it);
    }
}

}  // namespace ksys::snd

#include "KingSystem/Sound/sndMgr.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSystemAccessor.h>
#include <heap/seadHeap.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

Unk_710105fe78::~Unk_710105fe78() {
    if (_8) {
        _8->freeBuffer();
        delete _8;
    }
}

Unk_SoundMgr48::Unk_SoundMgr48() = default;

Unk_SoundMgr48::~Unk_SoundMgr48() {
    if (_10) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            arbiter->freeEmitter(_10);
            _10 = nullptr;
        }
    }
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
}


void Unk_SoundMgr48::sub_710105590C(sead::Heap* heap) {
    _8 = new (heap, 8) Unk_710105fe78;
    if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
        _10 = arbiter->allocEmitter(nullptr, "Emitter");
        if (_10)
            _10->mSpatialSetting.setPositioned(false);
    }
}

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x710107e7cc) also destroys members or bases
// this class does not declare yet.
Unk_7102504260::~Unk_7102504260() = default;

Unk_7102504470::~Unk_7102504470() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101087a7c) also destroys members or bases
// this class does not declare yet.
Unk_71025046d0::~Unk_71025046d0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101087be4) also destroys members or bases
// this class does not declare yet.
Unk_7102504850::~Unk_7102504850() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101087d00) also destroys members or bases
// this class does not declare yet.
Unk_71025049d0::~Unk_71025049d0() = default;

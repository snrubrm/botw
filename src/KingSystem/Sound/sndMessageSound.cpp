#include "KingSystem/Sound/sndSound.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSettings.h>
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

Unk_71025046d0::~Unk_71025046d0() = default;

Unk_7102504850::~Unk_7102504850() = default;

Unk_71025049d0::~Unk_71025049d0() = default;

// Unk_71025028c0 sits after the Unk_SoundMgr48 functions (0x7101055e48) in the original.
Unk_71025028c0::~Unk_71025028c0() = default;

// NON_MATCHING: clang merges the left / right stores into indexed stores; the original keeps the branches (likely
// named channel members in SpeakerChannelVolume, which lib/aal declares as an array).
void Unk_71025028c0::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device,
                                        s32 index_a, s32 index_b, f32 spread) {
    if (aal::SystemAccessor::getSettings()->mOutputModes[device] == aal::OutputMode::Surround) {
        const f32 rear = _c * ksys::snd::SoundMgr::instance()->sub_71011FC310();
        const f32 front = _8 * spread;
        if (index_b) {
            volume->volume[1] = front;
            volume->volume[3] = rear * spread;
        } else {
            volume->volume[0] = front;
            volume->volume[2] = rear * spread;
        }
    } else if (index_b) {
        volume->volume[1] = spread;
    } else {
        volume->volume[0] = spread;
    }
}

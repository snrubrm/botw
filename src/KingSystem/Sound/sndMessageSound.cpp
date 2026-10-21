#include "KingSystem/Sound/sndSound.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSettings.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSoundSource.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include <aal/aalSystemAccessor.h>
#include <heap/seadHeap.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// NON_MATCHING: the supplier is statically initialized; timing/string store layout differs.
// 0x7101055f00 uses the established timing model and these message-sound globals.
static util::InitTimeInfoEx sMessageSoundInitTimeInfo;
sead::SafeString sVoiceDefault = "VoiceDefault";
sead::SafeString sDemoDialog = "DemoDialog";
Unk_71025028c0 sMessageSpeakerBalance;


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

// NON_MATCHING: string formatting, handle setup and register scheduling differ.
void Unk_SoundMgr48::sub_710105598C(const sead::SafeString& path,
                                   const sead::SafeString& name, s32 suffix) {
    if (!_10)
        return;
    aal::AssetInfo info;
    bool found = false;
    if (suffix <= 0)
        found = _8->sub_7101060D14(&info, path, name);
    if (suffix >= 0 && !found) {
        static sead::FixedSafeString<64> numbered_name;
        numbered_name.format("%s_%d", name.cstr(), suffix);
        found = _8->sub_7101060D14(&info, path, numbered_name);
    }
    if (!found)
        return;
    if (_18.isEnabled())
        _18.stop(0.1f, 0.0f);
    aal::SoundSource::SetupInfo setup{};
    setup.prepare_flags = 3;
    if (auto* groups = aal::SystemAccessor::getGroupMgr())
        setup.sound_group = groups->findSoundGroupOrDefault(sDemoDialog);
    _18 = _10->emit(info, &setup, nullptr);
    sub_7101055B88(&_18, false, 0.0f);
}
// NON_MATCHING: source-state branches and parameter scheduling differ.
void Unk_SoundMgr48::sub_7101055B88(aal::Handle* handle, bool flag, f32 delay) {
    if (!handle->isEnabled())
        return;
    const u8 channels = handle->getAssetInfo()->getChannelNum();
    auto* source = handle->getSoundSource();
    if (source && source->mState != 0 && source->mState != 7) {
        if (channels >= 2) {
            source->setSpeakerBalanceSupplier(&sMessageSpeakerBalance);
        } else {
            source->mSpatialSetting.setPositioned(false);
            source->setInteriorNum(1);
            source->setChannelSpeakerType(0, 0, aal::SpeakerChannel::FrontCenter);
        }
    }
    handle->setVolume(0.708f);
    if (delay > 0.0f)
        handle->setStartDelayTime(delay);
}

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x710107e7cc) also destroys members or bases
// this class does not declare yet.
Unk_7102504260::~Unk_7102504260() = default;

Unk_7102504470::~Unk_7102504470() = default;

void Unk_7102504470::m7(void* vertices, void* indices) {
    mFlags |= 0x80000000;
    mVertices = vertices;
    mIndices = indices;
}

Unk_71025046d0::~Unk_71025046d0() = default;

Unk_7102504850::~Unk_7102504850() = default;

Unk_71025049d0::~Unk_71025049d0() = default;

s32 Unk_7102504850::m8() {
    return _60 * 10;
}

s32 Unk_7102504850::m9() {
    return _60 * 9;
}

s32 Unk_7102504850::m10() {
    return _20 * 20;
}

s32 Unk_7102504850::m11() {
    return mIndexCount * 4;
}

s32 Unk_71025049d0::m8() {
    return _60 * 10;
}

s32 Unk_71025049d0::m9() {
    return _60 * 9;
}

s32 Unk_71025049d0::m10() {
    return _20 * 20;
}

s32 Unk_71025049d0::m11() {
    return mIndexCount * 4;
}

u32 Unk_71025049d0::m28() {
    return _30;
}

u32 Unk_71025049d0::m29() {
    return _34;
}

bool Unk_71025049d0::m30() {
    return _30a8 > 2037;
}

s32 Unk_71025049d0::m31() {
    return 0x800;
}

s32 Unk_71025049d0::m32() {
    return _30a8;
}

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

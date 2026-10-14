#include "KingSystem/Sound/sndBgmMgr.h"
#include <aal/aalArbiter.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSystemAccessor.h>
#include <container/seadPtrArray.h>
#include <xlink2/xlink2EventSLink.h>
#include <algorithm>
#include "KingSystem/Sound/sndMgr.h"

// The sound object entries (0x7100ff6a18..0x7100ff6e2c). Both the Bgm code (0x7100ff62d0) and the BgmMgr code
// (0x7100ff89a0) call these out of line, so they are in a TU of their own.

namespace ksys::snd {

void Unk_710260f248Entry::sub_7100FF6A18(Unk_710260f248* owner, const xlink2::HandleSLink& handle) {
    mOwner = owner;
    mHandle = handle;
    _20 = 1.0;
    _24 = 0.0;
    mVolumes[0] = 1.0;
    mVolumes[1] = 1.0;
    mVolumes[2] = 1.0;
    mVolumes[3] = 1.0;
    _38 = false;
}

void Unk_710260f248Entry::sub_7100FF6A44() {
    mOwner = nullptr;
    mHandle.reset();
}

void Unk_710260f248Entry::sub_7100FF6A50(s32 index, f32 value) {
    if (index >= 0 && index < 4)
        mVolumes[index] = value;
}

void Unk_710260f248Entry::sub_7100FF6A64(f32 fade_sec) {
    if (fade_sec < 0) {
        mHandle.fade();
        return;
    }
    const f32 frames = fade_sec / sub_710105E3A4();
    mHandle.fade(s32(frames + (frames >= 0 ? 0.5f : -0.5f)));
}

// NON_MATCHING: the original keeps a separate `return false` block for a null event (block layout only).
bool Unk_710260f248Entry::sub_7100FF6C1C(Unk_710260f248* owner) {
    bool result = false;
    bool virtualized = false;
    if (mOwner == owner && mHandle.isActive()) {
        mHandle.setVolumeScale(std::max(owner->getVolume() * _20, 0.0f));
        sead::FixedPtrArray<aal::Handle, 2> handles;
        if (mHandle.isActive())
            static_cast<xlink2::EventSLink*>(mHandle.getEvent())->getSoundHandle(&handles);
        for (s32 i = 0; i < handles.size(); ++i) {
            auto* handle = handles.at(i);
            auto* source = handle->getSoundSource();
            if (!source)
                continue;
            const s32 track_num = source->mTrackNum;
            for (s32 track = 0; track < 4 && track < track_num; ++track)
                handle->setTrackVolume(1u << track, mVolumes[track]);
            if (auto* supplier = static_cast<Unk_SoundMgr30_30*>(source->mSpeakerBalanceSupplier))
                supplier->_8 = _24;
            if (source->isVirtualized() && !_50) {
                aal::SystemAccessor::getArbiter()->dumpActiveSoundSource();
                virtualized = true;
            }
        }
        result = true;
    }
    _50 = virtualized;
    return result;
}

bool Unk_710260f248Entry::sub_7100FF6DF4(const Unk_710260f248* owner) const {
    if (mOwner != owner)
        return false;
    return mHandle.isActive();
}

}  // namespace ksys::snd

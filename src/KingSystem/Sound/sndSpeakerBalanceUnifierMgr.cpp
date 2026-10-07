#include <aal/aalShape.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <aal/aalSpeakerBalanceUnifier.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

f32 SpeakerBalanceUnifierMgr::sSizeThresholds[3] = {2.0f, 5.0f, 40.0f};

// NON_MATCHING: the original reads the thresholds through a direct adrp of a file-local table that is not constant (it
// is written elsewhere in its translation unit); a never-written local table gets folded, so it is an external member here
// (GOT access).
void SpeakerBalanceUnifierMgr::sub_7101027D4C(f32 size, aal::Shape* shape) {
    if (!mUnifiers.isBufferReady())
        return;
    s32 idx;
    if (sSizeThresholds[0] >= size)
        idx = 0;
    else if (sSizeThresholds[1] >= size)
        idx = 1;
    else if (sSizeThresholds[2] >= size)
        idx = 2;
    else
        idx = 3;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (auto* unifier = mUnifiers.at(idx))
        unifier->addUnifiable(shape);
}

void SpeakerBalanceUnifierMgr::sub_7101027E0C(aal::Shape* shape) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        if (auto* unifier = mUnifiers.at(i))
            unifier->removeUnifiable(shape);
    }
}

void SpeakerBalanceUnifierMgr::sub_7101027CE8() {
    mHandle.deleteProc();
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        if (auto* unifier = mUnifiers.at(i))
            unifier->clearUnifiable();
    }
    mActor = nullptr;
}

// NON_MATCHING: original local label tables use direct access; the kind argument and label selection
// also have different scheduling. The original kind type remains unknown.
xlink2::HandleSLink SpeakerBalanceUnifierMgr::sub_7101027E90(f32 size, int type,
                                                           aal::Shape* shape) {
    xlink2::HandleSLink handle;
    if (!mActor)
        return handle;
    sead::SafeString* names;
    if (type == 1)
        names = sUnk_7102610618;
    else if (type == 2)
        names = sUnk_7102610658;
    else
        return handle;
    sead::SafeString label;
    s32 index;
    if (sSizeThresholds[0] >= size)
        index = 0;
    else if (sSizeThresholds[1] >= size)
        index = 1;
    else if (sSizeThresholds[2] >= size)
        index = 2;
    else
        index = 3;
    label = names[index];
    if (label.isEmpty())
        return handle;
    handle = eft::searchAndEmitSLink(mActor, label.cstr(), false);
    auto* event = static_cast<xlink2::EventSLink*>(handle.getEvent());
    if (event && event->getCreateId() == handle.getCreateId()) {
        event->resetFlagBit(1);
        if (auto* executor = event->getAliveAssetExecutor()) {
            if (auto* source = executor->getHandle()->getSoundSource()) {
                if (source->mState < 3)
                    source->mSpatialSetting.setShape(shape);
            }
        }
    }
    return handle;
}

}  // namespace ksys::snd

#include "aal/aalActiveSoundLimiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalSoundSourceSortFuncs.h"

namespace aal {

namespace {

/// Cocktail shaker sort: a forward pass moves the elements that `cmp` ranks after their successor to the back, a
/// backward pass moves the elements that `cmp` ranks before their predecessor to the front; the passes only cover
/// the range where the last pass swapped something.
template <typename Compare>
void cocktailSort(sead::PtrArray<SoundSource>* array, Compare cmp) {
    const s32 num = array->size();
    if (num < 2)
        return;

    s32 left = 0;
    s32 right = num - 1;
    s32 last_forward_swap = 0;
    while (true) {
        last_forward_swap = left;
        for (s32 i = left; i < right; ++i) {
            if (cmp((*array)(i), (*array)(i + 1)) >= 1) {
                array->swap(i, i + 1);
                last_forward_swap = i;
            }
        }
        if (left == last_forward_swap)
            return;

        const s32 old_left = left;
        left = last_forward_swap;
        for (s32 i = last_forward_swap; i > old_left; --i) {
            if (cmp((*array)(i), (*array)(i - 1)) < 0) {
                array->swap(i, i - 1);
                left = i;
            }
        }
        if (left == last_forward_swap)
            return;
        right = last_forward_swap;
    }
}

}  // namespace

// 0x7100b832c8
ActiveSoundLimiter::ActiveSoundLimiter() = default;

// 0x7100b832fc
void ActiveSoundLimiter::setup(const Settings& settings) {
    mFlags = settings.mFlags;
    mLimitNum = settings.mLimitNum;
}

// 0x7100b83310
void ActiveSoundLimiter::calcLimit(sead::OffsetList<SoundSource>* sound_sources) {
    if (mLimitNum < 0) {
        // No limit: the sounds are not limited by this limiter any more.
        for (SoundSource& source : *sound_sources) {
            if (_16)
                source.isVirtualized(SoundSource::VirtualizedBy(mVirtualizedBy));
            source.unvirtualize(SoundSource::VirtualizedBy(mVirtualizedBy));
        }
        return;
    }

    if (mLimitNum == 0) {
        // Everything is over the limit.
        for (SoundSource& source : sound_sources->robustRange()) {
            if (source.mSpatialSetting.isUnified())
                continue;
            if (source.canVirtualize()) {
                if (mFlags.mA)
                    source.stop(0.0f, 0.0f);
                else
                    source.virtualize(SoundSource::VirtualizedBy(mVirtualizedBy), DebuggerResult{0x20000});
            }
        }
        return;
    }

    sortSoundSourceList_(sound_sources);

    s32 num = 0;
    for (SoundSource& source : sound_sources->robustRange()) {
        if (source.mSpatialSetting.isUnified())
            continue;
        if (_14 && source.mSpeakerBalanceSupplier)
            continue;

        if (num < mLimitNum) {
            if (_16)
                source.isVirtualized(SoundSource::VirtualizedBy(mVirtualizedBy));
            source.unvirtualize(SoundSource::VirtualizedBy(mVirtualizedBy));
        } else {
            const DebuggerResult result = getDebuggerResultWhenLimit_();
            if (source.canVirtualize()) {
                if (mFlags.mA)
                    source.stop(0.0f, 0.0f);
                else
                    source.virtualize(SoundSource::VirtualizedBy(mVirtualizedBy), result);
            }
        }
        ++num;
    }
}

// 0x7100bb6c08
DebuggerResult ActiveSoundLimiterEarlier::getDebuggerResultWhenLimit_() const {
    return DebuggerResult{0x20002};
}

// NON_MATCHING: the second sort negates the list offset in 32 bits and sign-extends it (the first one negates the
// sign-extended offset).
// 0x7100bb6c10
void ActiveSoundLimiterEarlier::sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        sound_sources->insertionSort(SoundSourceSortFuncs::compareEarlierPriorityIgnoreStopOrVirtual);
    else
        sound_sources->insertionSort(SoundSourceSortFuncs::compareEarlierPriority);
}

// 0x7100bb6fa4
DebuggerResult ActiveSoundLimiterLater::getDebuggerResultWhenLimit_() const {
    return DebuggerResult{0x20003};
}

// NON_MATCHING: the second sort negates the list offset in 32 bits and sign-extends it (the first one negates the
// sign-extended offset).
// 0x7100bb6fb0
void ActiveSoundLimiterLater::sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        sound_sources->insertionSort(SoundSourceSortFuncs::compareLaterPriorityIgnoreStopOrVirtual);
    else
        sound_sources->insertionSort(SoundSourceSortFuncs::compareLaterPriority);
}

// 0x7100bb7344
DebuggerResult ActiveSoundLimiterPriorityEarlier::getDebuggerResultWhenLimit_() const {
    return DebuggerResult{0x20001};
}

// NON_MATCHING: the second sort negates the list offset in 32 bits and sign-extends it (the first one negates the
// sign-extended offset).
// 0x7100bb7350
void ActiveSoundLimiterPriorityEarlier::sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriorityEarlierIgnoreStopOrVirtual);
    else
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriorityEarlier);
}

// 0x7100bb76e4
DebuggerResult ActiveSoundLimiterPriorityLater::getDebuggerResultWhenLimit_() const {
    return DebuggerResult{0x20001};
}

// NON_MATCHING: the second sort negates the list offset in 32 bits and sign-extends it (the first one negates the
// sign-extended offset).
// 0x7100bb76f0
void ActiveSoundLimiterPriorityLater::sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriorityLaterIgnoreStopOrVirtual);
    else
        sound_sources->insertionSort(SoundSourceSortFuncs::comparePriorityLater);
}

// NON_MATCHING: the original keeps the pointer of the array in a register and restarts the scan after each swap (two
// nested loops); here the array is read through the PtrArray again after every comparison.
// 0x7100bb6d64
void ActiveSoundLimiterEarlier::sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        cocktailSort(sound_sources, SoundSourceSortFuncs::compareEarlierPriorityIgnoreStopOrVirtual);
    else
        cocktailSort(sound_sources, SoundSourceSortFuncs::compareEarlierPriority);
}

// NON_MATCHING: the original keeps the pointer of the array in a register and restarts the scan after each swap (two
// nested loops); here the array is read through the PtrArray again after every comparison.
// 0x7100bb7104
void ActiveSoundLimiterLater::sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        cocktailSort(sound_sources, SoundSourceSortFuncs::compareLaterPriorityIgnoreStopOrVirtual);
    else
        cocktailSort(sound_sources, SoundSourceSortFuncs::compareLaterPriority);
}

// NON_MATCHING: the original keeps the pointer of the array in a register and restarts the scan after each swap (two
// nested loops); here the array is read through the PtrArray again after every comparison.
// 0x7100bb74a4
void ActiveSoundLimiterPriorityEarlier::sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        cocktailSort(sound_sources, SoundSourceSortFuncs::comparePriorityEarlierIgnoreStopOrVirtual);
    else
        cocktailSort(sound_sources, SoundSourceSortFuncs::comparePriorityEarlier);
}

// NON_MATCHING: the original keeps the pointer of the array in a register and restarts the scan after each swap (two
// nested loops); here the array is read through the PtrArray again after every comparison.
// 0x7100bb7844
void ActiveSoundLimiterPriorityLater::sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const {
    if (!sound_sources)
        return;
    if (mFlags.mB)
        cocktailSort(sound_sources, SoundSourceSortFuncs::comparePriorityLaterIgnoreStopOrVirtual);
    else
        cocktailSort(sound_sources, SoundSourceSortFuncs::comparePriorityLater);
}

}  // namespace aal

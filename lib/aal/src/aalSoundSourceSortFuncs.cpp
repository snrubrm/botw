#include "aal/aalSoundSourceSortFuncs.h"
#include "aal/aalSoundSource.h"

namespace aal::SoundSourceSortFuncs {

namespace {
constexpr f32 cPriorityScale = 255.0f;

inline s32 getPriority(const SoundSource* source) {
    return static_cast<s32>(source->getAggregatedPriority() * cPriorityScale);
}

inline s32 getPriorityIgnoreStopOrVirtual(const SoundSource* source) {
    if (source->mState >= 6 && source->mState < 8)
        return 0;
    if (source->isVirtualized())
        return 0;
    return getPriority(source);
}
}  // namespace

// 0x7100b83c24
s32 comparePriority(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 lhs_priority = getPriority(lhs);
    return getPriority(rhs) - lhs_priority;
}

// 0x7100b83c84
s32 comparePriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 lhs_priority = getPriorityIgnoreStopOrVirtual(lhs);
    return getPriorityIgnoreStopOrVirtual(rhs) - lhs_priority;
}

// 0x7100b83d4c
s32 compareEarlierPriority(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    if (lhs->mPlayingTime < rhs->mPlayingTime)
        return 1;
    if (lhs->mPlayingTime > rhs->mPlayingTime)
        return -1;
    return comparePriority(lhs, rhs);
}

// 0x7100b83dd0
s32 compareLaterPriority(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    if (lhs->mPlayingTime > rhs->mPlayingTime)
        return 1;
    if (lhs->mPlayingTime < rhs->mPlayingTime)
        return -1;
    return comparePriority(lhs, rhs);
}

// 0x7100b83e54
s32 comparePriorityEarlier(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 result = comparePriority(lhs, rhs);
    if (result != 0)
        return result;
    return lhs->mPlayingTime < rhs->mPlayingTime ? 1 : (lhs->mPlayingTime > rhs->mPlayingTime ? -1 : 0);
}

// 0x7100b83ed4
s32 comparePriorityLater(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 result = comparePriority(lhs, rhs);
    if (result != 0)
        return result;
    return lhs->mPlayingTime > rhs->mPlayingTime ? 1 : (lhs->mPlayingTime < rhs->mPlayingTime ? -1 : 0);
}

// 0x7100b83f54
s32 compareEarlierPriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    if (lhs->mPlayingTime < rhs->mPlayingTime)
        return 1;
    if (lhs->mPlayingTime > rhs->mPlayingTime)
        return -1;
    return comparePriorityIgnoreStopOrVirtual(lhs, rhs);
}

// 0x7100b84040
s32 compareLaterPriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    if (lhs->mPlayingTime > rhs->mPlayingTime)
        return 1;
    if (lhs->mPlayingTime < rhs->mPlayingTime)
        return -1;
    return comparePriorityIgnoreStopOrVirtual(lhs, rhs);
}

// 0x7100b8412c
s32 comparePriorityEarlierIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 result = comparePriorityIgnoreStopOrVirtual(lhs, rhs);
    if (result != 0)
        return result;
    return lhs->mPlayingTime < rhs->mPlayingTime ? 1 : (lhs->mPlayingTime > rhs->mPlayingTime ? -1 : 0);
}

// 0x7100b84214
s32 comparePriorityLaterIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs) {
    if (!lhs || !rhs)
        return 0;
    const s32 result = comparePriorityIgnoreStopOrVirtual(lhs, rhs);
    if (result != 0)
        return result;
    return lhs->mPlayingTime > rhs->mPlayingTime ? 1 : (lhs->mPlayingTime < rhs->mPlayingTime ? -1 : 0);
}

}  // namespace aal::SoundSourceSortFuncs

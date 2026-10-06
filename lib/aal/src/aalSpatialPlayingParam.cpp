#include "aal/aalSpatialCalculator.h"
#include <cfloat>
#include "aal/aalListenerMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b90e70
SpatialPlayingParam::SpatialPlayingParam() : mActivated(false) {
    reset();
}

// 0x7100b90f0c (D1) / 0x7100b90f7c (D0)
SpatialPlayingParam::~SpatialPlayingParam() {
    finalize();
}

// 0x7100b90fb8
void SpatialPlayingParam::initialize(sead::Heap* heap) {
    if (!mListenerParams.isBufferReady()) {
        const s32 num = SystemAccessor::getListenerMgr()->getListenerNum();
        if (num >= 1)
            mListenerParams.tryAllocBuffer(num, heap, 8);
    }
    mActivated = false;
}

// 0x7100b90f4c
void SpatialPlayingParam::finalize() {
    mListenerParams.freeBuffer();
}

// 0x7100b90ea4
void SpatialPlayingParam::reset() {
    _c = FLT_MAX;
    _10 = 1.0f;
    _14 = FLT_MAX;
    mPriorityFactor = 0.0f;
    mNumAggregated = 0;
    for (s32 i = 0; i < mListenerParams.size(); ++i)
        mListenerParams[i] = ListenerParam();
}

// 0x7100b91060
void SpatialPlayingParam::activate() {
    reset();
    mActivated = true;
}

// 0x7100b910d0
void SpatialPlayingParam::aggregate(s32 listener_index, const SpatialCalcResult& result) {
    if (!mListenerParams.isBufferReady() || mNumAggregated >= mListenerParams.size())
        return;

    if (result._8 < _c)
        _c = result._8;
    if (result._c > _10)
        _10 = result._c;
    if (result._10 < _14)
        _14 = result._10;
    if (result.priority_factor > mPriorityFactor)
        mPriorityFactor = result.priority_factor;

    mListenerParams[mNumAggregated].listener_index = listener_index;
    mListenerParams[mNumAggregated].volume = result.volume;
    mListenerParams[mNumAggregated].spread = result.spread;
    mListenerParams[mNumAggregated].dist_2d[0] = result.dist_2d[0];
    mListenerParams[mNumAggregated].angle_idx[0] = result.angle_idx[0];
    mListenerParams[mNumAggregated].dist_2d[1] = result.dist_2d[1];
    mListenerParams[mNumAggregated].angle_idx[1] = result.angle_idx[1];
    ++mNumAggregated;
}

// 0x7100b9121c
s32 SpatialPlayingParam::getListenerIndex(s32 index) const {
    if (mListenerParams.isBufferReady() && index < mListenerParams.size())
        return mListenerParams[index].listener_index;
    return -1;
}

// 0x7100b91254
f32 SpatialPlayingParam::getVolume(s32 index) const {
    if (mListenerParams.isBufferReady() && index < mListenerParams.size())
        return mListenerParams[index].volume;
    return 0.0f;
}

// 0x7100b91280
f32 SpatialPlayingParam::getDist2D(s32 index, s32 listener_idx) const {
    if (mListenerParams.isBufferReady() && index < mListenerParams.size())
        return mListenerParams[index].dist_2d[listener_idx];
    return 0.0f;
}

// 0x7100b912b0
s32 SpatialPlayingParam::getAngleIdx(s32 index, s32 listener_idx) const {
    if (mListenerParams.isBufferReady() && index < mListenerParams.size())
        return mListenerParams[index].angle_idx[listener_idx];
    return 0;
}

// 0x7100b912ec
f32 SpatialPlayingParam::getSpread(s32 index) const {
    if (mListenerParams.isBufferReady() && index < mListenerParams.size())
        return mListenerParams[index].spread;
    return 0.0f;
}
}  // namespace aal

#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>

namespace sead {
class Heap;
}

namespace aal {

class Shape;

/// The spatial calculation result for one listener (0x98 bytes, partially modeled: the fields are the ones
/// SpatialPlayingParam::aggregate reads).
struct SpatialCalcResult {
    u32 _0;
    f32 volume;
    f32 _8;
    f32 _c;
    f32 _10;
    f32 spread;
    f32 priority_factor;
    f32 dist_2d[2];
    s32 angle_idx[2];
    u8 _2c[0x98 - 0x2c];
};
static_assert(sizeof(SpatialCalcResult) == 0x98);

/// Calculates the spatial parameters (distance attenuation, angle, doppler...) of a sound source for each
/// listener, from a SpatialCalculator::Setting.
/// TODO: incomplete. Only the functions that game code calls and the reference count / result count are declared.
class SpatialCalculator {
public:
    using Result = SpatialCalcResult;

    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);

    /// The calculator is shared by the sounds that use it (0x7100b8fe28 / 0x7100b8fe38 / 0x7100b8fe4c).
    void beginReferred();
    void endReferred();
    bool isReferred() const;
    /// 0x7100b8fb00: the number of results of the last calculation (0 if there are none).
    s32 getResultNum() const;
    /// 0x7100b8fab8: nullptr if the index is out of range.
    const Result* getResult(s32 index) const;

private:
    friend class Shape;

    u8 _0[8];
    /// Node in the calculator list of the attached Shape.
    sead::ListNode mShapeListNode;
    u8 _18[0x64 - 0x18];
    s32 mReferredCount;
    u8 _68[0x80 - 0x68];
    /// volatile: the original reads the count again for the bounds check of the result.
    volatile s32 mResultNum;
    u8 _84[4];
    Result* mResults;
};

/// The spatial parameters of a sound that are shared with the playing state: the per-listener results of the
/// spatial calculation, aggregated over the listeners. Member names with a leading underscore are unknown.
class SpatialPlayingParam {
public:
    SpatialPlayingParam();
    virtual ~SpatialPlayingParam();

    void initialize(sead::Heap* heap);
    void finalize();
    void reset();
    void activate();
    void aggregate(s32 listener_index, const SpatialCalcResult& result);

    s32 getListenerIndex(s32 index) const;
    f32 getVolume(s32 index) const;
    f32 getDist2D(s32 index, s32 listener_idx) const;
    s32 getAngleIdx(s32 index, s32 listener_idx) const;
    f32 getSpread(s32 index) const;

private:
    struct ListenerParam {
        s32 listener_index = -1;
        f32 volume = 0.0f;
        f32 dist_2d[2] = {};
        s32 angle_idx[2] = {};
        f32 spread = 0.0f;
    };

    bool mActivated;
    f32 _c;
    f32 _10;
    f32 _14;

public:
    /// Multiplied into the priority of the sound source (the maximum over the results).
    f32 mPriorityFactor;

private:
    s32 mNumAggregated;
    sead::Buffer<ListenerParam> mListenerParams;
};

}  // namespace aal

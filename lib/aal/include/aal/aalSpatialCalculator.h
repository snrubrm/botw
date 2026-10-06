#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {
class Heap;
}

namespace aal {

class Attenuator;
class Cone;
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
    SEAD_RTTI_BASE(SpatialCalculator)
public:
    using Result = SpatialCalcResult;

    /// What the calculation is based on (SpatialSetting keeps one of these at +0x48). Two calculators with the same
    /// setting are shared.
    struct Setting {
        const sead::Matrix34f* actor_matrix;
        const sead::Vector3f* velocity;
        Attenuator* attenuator;
        f32 doppler_factor;
        f32 sound_source_size;
        Shape* shape;
        u16 flags;
        u16 _2a;
        u64 user_param;

        /// 0x7100b8f4ec
        void initialize();
    };
    static_assert(sizeof(Setting) == 0x38);

    SpatialCalculator();
    virtual ~SpatialCalculator();

    /// `index` is the position in the SpatialCalculatorPool, `dirty_counter` its change counter.
    void initialize(s32 index, u32* dirty_counter, sead::Heap* heap);
    void finalize();
    virtual void setup(const Setting& setting);
    virtual void calc(bool force);
    virtual void reset();

    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);

    /// The calculator is shared by the sounds that use it (0x7100b8fe28 / 0x7100b8fe38 / 0x7100b8fe4c).
    void beginReferred();
    void endReferred();
    bool isReferred() const;
    s32 getPoolIndex() const { return mPoolIndex; }
    /// Whether the calculator was set up with exactly this setting (0x7100b8fe5c).
    bool hasSetting(const Setting& setting) const;
    /// 0x7100b8fb00: the number of results of the last calculation (0 if there are none).
    s32 getResultNum() const;
    /// 0x7100b8fab8: nullptr if the index is out of range.
    const Result* getResult(s32 index) const;

private:
    friend class Shape;
    friend class SoundSourceUnifierSource;
    friend class SoundSourceUnifierTarget;

    /// Node in the calculator list of the attached Shape.
    sead::ListNode mShapeListNode;
    u8 _18[0x20 - 0x18];
    Setting mSetting;
    u8 _58[0x64 - 0x58];
    s32 mReferredCount;
    /// The index in the SpatialCalculatorPool.
    s32 mPoolIndex;
    u8 _6c[0x80 - 0x6c];
    /// volatile: the original reads the count again for the bounds check of the result.
    volatile s32 mResultNum;
    u8 _84[4];
    Result* mResults;
    sead::CriticalSection mCS;
    u32 _d0;
    u8 _d4[4];
};
static_assert(sizeof(SpatialCalculator) == 0xd8);

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
    bool isActivated() const { return mActivated; }
    void deactivate() { mActivated = false; }
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

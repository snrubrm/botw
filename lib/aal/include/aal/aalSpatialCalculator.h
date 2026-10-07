#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalDebuggerResult.h"
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {
class Heap;
}

namespace aal {

class Attenuator;
class Cone;
class Listener;
class Shape;

/// The spatial calculation result for one listener (0x98 bytes, partially modeled: the fields are the ones
/// SpatialPlayingParam::aggregate reads).
struct SpatialCalcResult {
    /// Whether the result is used (the sound source aggregates only the valid results).
    bool is_valid;
    /// The volume of the sound for the listener.
    f32 volume;
    f32 _8;
    f32 _c;
    f32 _10;
    f32 spread;
    f32 priority_factor;
    f32 dist_2d[2];
    s32 angle_idx[2];
    sead::Matrix34f _2c;
    sead::Matrix34f _5c;
    f32 _8c;
    f32 _90;
    f32 _94;

    SpatialCalcResult()
        : is_valid(false), volume(1.0f), _8(0.0f), _c(1.0f), _10(0.0f), spread(0.0f), priority_factor(1.0f) {
        _2c = sead::Matrix34f::zero;
        _5c = sead::Matrix34f::zero;
        _8c = 0.0f;
        _90 = 1.0f;
        _94 = 0.0f;
        dist_2d[0] = 0.0f;
        dist_2d[1] = 0.0f;
        angle_idx[0] = 0;
        angle_idx[1] = 0;
    }
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
        /// A bit for each listener that is used for the calculation.
        u16 listener_mask;
        u64 user_param;

        Setting() : flags(0), listener_mask(0) { initialize(); }

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
    /// Calculates the results for the listeners; returns whether the sound has to be virtualized (it is inaudible for
    /// all listeners).
    virtual bool calc(bool force);
    virtual void reset();

    /// Detaches the calculator from its shape; with `reset_position`, also forgets the position/matrix
    /// pointers of the setting. Returns whether a shape was attached.
    bool detachShape(bool reset_position);
    /// 0x7100b8f900: forgets the matrix and velocity pointers of the setting.
    void detachPositioningInfo();

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
    /// 0x7100b8fc8c: calculates the result for one listener; returns whether the sound is audible for it.
    bool calcByListener_(Result* result, const Listener& listener, s32 index, bool force,
                         DebuggerResult* debugger_result);

    friend class Shape;
    friend class SoundSourceUnifierSource;
    friend class SoundSourceUnifierTarget;
    friend class SoundSource;

    /// Node in the calculator list of the attached Shape.
    sead::ListNode mShapeListNode;
    bool mInitialized;
    u8 _19[0x20 - 0x19];
    Setting mSetting;
    Cone* mCone;
    /// Whether the last calculation found that the sound has to be virtualized.
    u8 mLastResult;
    u8 _61[0x64 - 0x61];
    s32 mReferredCount;
    /// The index in the SpatialCalculatorPool.
    s32 mPoolIndex;
    u8 _6c[0x70 - 0x6c];
    /// The change counter of the pool: the calculation is repeated when it has changed.
    u32* mDirtyCounter;
    u32 mLastDirtyCounter;
    u8 _7c[0x80 - 0x7c];
    /// volatile: the original reads the count again for the bounds check of the result.
    volatile s32 mResultNum;
    u8 _84[4];
    Result* mResults;
    sead::CriticalSection mCS;
    DebuggerResult mDebuggerResult;
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

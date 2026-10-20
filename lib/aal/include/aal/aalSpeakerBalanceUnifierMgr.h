#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalDeviceType.h"
#include "aal/aalSpeakerChannelVolume.h"

namespace sead {
class Heap;
}

namespace aal {

class SpeakerBalanceUnifier;
class Interior;
enum class SpeakerBalanceMode : u32;

// The native table calculators write one five-channel entry through this type.
struct UnifierSpeakerBalanceData {
    UnifierSpeakerBalanceData() : mBalance{} {}
    using ChannelBalance = sead::SafeArray<u8, 5>;
    ChannelBalance mBalance;
};
static_assert(sizeof(UnifierSpeakerBalanceData) == 5);

/// Speaker balances indexed by device, interior, spread and direction.
class UnifierSpeakerBalanceTable {
public:
    UnifierSpeakerBalanceTable();
    ~UnifierSpeakerBalanceTable();

    void initialize(sead::Heap* heap);
    void makeTable();
    // Inline-only in the original; name describes the per-device count at +0x14.
    s32 getCurrentInteriorNum(DeviceType device) const { return mCurrentInteriorNum[device]; }
    f32 getTotalVolumeMax(DeviceType device, s32 interior) const;
    /// The speaker balance of the direction as a float in 0..255 (the first five channels).
    void getSpeakerBalanceU8Range(SpeakerChannelVolume* volume, s32 angle, DeviceType device, s32 interior) const;
    void getSpeakerBalanceU8RangeWithSpread(SpeakerChannelVolume* volume, s32 angle, DeviceType device, s32 interior,
                                            f32 spread) const;

private:
    struct AngleSection {
        u32 lower;
        u32 upper;
    };
    static_assert(sizeof(AngleSection) == 8);
    void calcSpeakerBalance_(UnifierSpeakerBalanceData*, const Interior&, u32, SpeakerBalanceMode);
    void calcSpeakerBalanceStereo_(UnifierSpeakerBalanceData*, u32, SpeakerBalanceMode);
    void calcSpeakerBalanceSpread_(UnifierSpeakerBalanceData*, const Interior&, u32, f32,
                                   SpeakerBalanceMode);
    void calcSpeakerBalanceSpreadStereo_(UnifierSpeakerBalanceData*, u32, f32, SpeakerBalanceMode);
    void calcSpread_(f32*, f32*, const AngleSection&, const AngleSection*, f32,
                     SpeakerBalanceMode) const;
    using InteriorData = sead::SafeArray<sead::SafeArray<UnifierSpeakerBalanceData, 64>, 48>;
    static_assert(sizeof(InteriorData) == 0x3c00);
    InteriorData** mData;
    /// The maximum of the total volume of each direction, for each interior.
    f32* mTotalVolumeMax[DeviceType::size()];
    s32 mInteriorNum;
    s32 mCurrentInteriorNum[DeviceType::size()];
};

/// Manages the speaker balance unifiers: they are created at initialization and handed out (allocSpeakerBalanceUnifier)
/// and taken back (freeSpeakerBalanceUnifier) by the sound source unifiers.
/// TODO: incomplete (the constructor, initialize, setupInteriorSize and the unknown members are not decompiled).
class SpeakerBalanceUnifierMgr : public sead::hostio::Node {
public:
    struct InitializeArg {
        /// The number of speaker balance unifiers.
        s32 unifier_num;
    };

    SpeakerBalanceUnifierMgr();
    virtual ~SpeakerBalanceUnifierMgr();


    void finalize();
    void initialize(const InitializeArg& arg, sead::Heap* heap);
    /// Sets the interior size of the unifier areas from the current interior.
    void setupInteriorSize();
    // Inline-only in the original; names describe fields read by B937CC.
    UnifierSpeakerBalanceTable* getTable() const { return mTable; }
    f32 getInteriorSize(s32 interior) const { return mInteriorSizes[interior]; }
    u8 getEnabledDeviceMask() const { return _50; }
    void calc();
    void setupUnifierSpeakerBalanceTable();
    void setRegisterCullingDistance(f32 distance);
    SpeakerBalanceUnifier* allocSpeakerBalanceUnifier(const sead::SafeString& name, sead::Heap* heap);
    void freeSpeakerBalanceUnifier(SpeakerBalanceUnifier* unifier);

    struct Pair {
        f32 first;
        f32 second;
    };
    struct Quad {
        f32 values[4];
    };

private:
    bool mInitialized;
    /// All the unifiers.
    sead::PtrArray<SpeakerBalanceUnifier> mUnifiers;
    /// The unifiers that are in use.
    sead::OffsetList<SpeakerBalanceUnifier> mActiveUnifiers;
    UnifierSpeakerBalanceTable* mTable;
    /// The interior size of each interior.
    f32* mInteriorSizes;
    s32 mInteriorNum;
    f32 mRegisterCullingDistance;
    u8 _50;
    sead::CriticalSection mCS;
    bool _98;
    Pair _9c;
    Quad _a4;
    u8 _b4;
    sead::FixedSafeString<32> mName;
    u64 mCalcBeginTick;
    u64 mCalcTicks;
    u32 _100;
};

}  // namespace aal

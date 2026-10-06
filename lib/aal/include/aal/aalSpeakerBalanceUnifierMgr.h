#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalDeviceType.h"

namespace sead {
class Heap;
}

namespace aal {

class SpeakerBalanceUnifier;

/// The speaker balances of the sixty four directions around a listener for each interior (0x3c00 bytes each, not
/// modeled).
struct UnifierSpeakerBalanceData {
    UnifierSpeakerBalanceData() : _0{} {}

    u8 _0[0x3c00];
};

/// The table of the speaker balances of the unifiers: one UnifierSpeakerBalanceData for each interior of each device.
/// TODO: incomplete (makeTable and the calcSpeakerBalance functions are not decompiled, 0x7100b94830 declared only).
class UnifierSpeakerBalanceTable {
public:
    UnifierSpeakerBalanceTable();
    ~UnifierSpeakerBalanceTable();

    void initialize(sead::Heap* heap);
    void makeTable();
    f32 getTotalVolumeMax(DeviceType device, s32 interior) const;

private:
    UnifierSpeakerBalanceData** mData;
    /// The maximum of the total volume of each direction, for each interior.
    f32* mTotalVolumeMax[DeviceType::size()];
    s32 mInteriorNum;
    s32 mCurrentInteriorNum;
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

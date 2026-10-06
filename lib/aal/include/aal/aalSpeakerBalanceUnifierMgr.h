#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace sead {
class Heap;
}

namespace aal {

class SpeakerBalanceUnifier;

/// The table of the speaker balances of the unifiers. TODO: not modeled (0x18 bytes; the constructor, destructor,
/// initialize and makeTable are 0x7100b946d4 / 0x7100b946dc / 0x7100b94738 / 0x7100b94830, declared only).
class UnifierSpeakerBalanceTable {
public:
    UnifierSpeakerBalanceTable();
    ~UnifierSpeakerBalanceTable();

    void initialize(sead::Heap* heap);
    void makeTable();

private:
    u8 _0[0x18];
};

/// Manages the speaker balance unifiers: they are created at initialization and handed out (allocSpeakerBalanceUnifier)
/// and taken back (freeSpeakerBalanceUnifier) by the sound source unifiers.
/// TODO: incomplete (the constructor, initialize, setupInteriorSize and the unknown members are not decompiled).
class SpeakerBalanceUnifierMgr {
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
    u8 _98[0xf0 - 0x98];
    u64 mCalcBeginTick;
    u64 mCalcTicks;
    u8 _100[8];
};

}  // namespace aal

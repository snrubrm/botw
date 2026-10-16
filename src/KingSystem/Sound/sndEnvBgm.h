#pragma once

#include <prim/seadSafeString.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <xlink2/xlink2PropertyDefinition.h>

namespace ksys::snd {

class Unk_EnvBgmNode;

// Placeholder (vtable 0x71024fdb00; derived from Unk_71024fc7f8 without RTTI of its own): the environment BGM handle
// (one per EnvBgmInfo::EnvTimeEnum, held by Unk_71025ce350). Its init 0x7101004a54 (declared only) builds the node
// graph below from EnvBgmInfo ("Part0_A0", "Part0", ..., "Part3").
class Unk_71024fdb00 : public Unk_71024fc7f8 {
public:
    ~Unk_71024fdb00() override;

    // 0x7101005ab8
    void hm14() override {}
    // 0x7101005abc (declared only; 684 B)
    void hm15() override;

    // 0x7101005874 (declared only; 580 B): plays the part `name` with the given volume and pan, at once when
    // `wait_count` is 0, else queued in a free entry of mEntries (placeholder name; argument order is a guess).
    void sub_7101005874(const sead::SafeString& name, s32 wait_count, u8 part, f32 volume, f32 pan);

    // A part queued by sub_7101005874 (0xb0 bytes).
    struct Entry {
        sead::FixedSafeString<128> name;
        s32 wait_count = 0;
        s32 wait_count_init = 0;
        f32 volume = 1.0;
        f32 pan = 0.0;
        u8 part = 0;
    };

    u32 mTimeType;
    EnvBgmInfo* mInfo;
    sead::PtrArray<xlink2::PropertyDefinition> mProperties;
    u32 mBpm;
    f32 mBeatSec;
    u8 _1a8[0x1ac - 0x1a8];
    bool _1ac;
    u8 _1ad[0x1b4 - 0x1ad];
    // Index of the branch taken by Unk_71024fdd28 (0..2).
    s32 _1b4;
    s32 _1b8;
    // 0..15; Unk_71024fdbe8::start multiplies the wait count by 2 or 3 for some values.
    u32 _1bc;
    sead::Buffer<Entry> mEntries;
    // The node machines of parts 0 to 3.
    Unk_71024fdde8* mPartMachines[4];
    sead::PtrArray<Unk_EnvBgmNode> mNodes;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fdb00, 0x200);

// Placeholder base of the environment BGM nodes (no vtable of its own is emitted: slots 0-2 and 4 are defined by each
// node). Slots 3 and 5 are the shared empty functions 0x7101006960 / 0x7101006964.
class Unk_EnvBgmNode {
public:
    explicit Unk_EnvBgmNode(Unk_71024fdb00* owner) : mOwner(owner) {}
    virtual ~Unk_EnvBgmNode() = default;

    // True when the node is finished and the machine may move on (placeholder name).
    virtual bool isDone() = 0;
    virtual Unk_EnvBgmNode* getNext() = 0;
    virtual void setNext(Unk_EnvBgmNode* next) = 0;
    virtual void setBranch(Unk_EnvBgmNode* next, s32 index) {}
    virtual void start() = 0;
    virtual void m5() {}

protected:
    bool _8 = false;
    Unk_71024fdb00* mOwner;
};

// vtable 0x71024fdb98 (constructor 0x7101005d68, 0xd8 bytes): plays a part after a fixed wait count.
class Unk_71024fdb98 : public Unk_EnvBgmNode {
public:
    Unk_71024fdb98(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                   const agl::utl::Parameter<u32>* wait_count, const MusicInfo::MinMax<f32>* volume,
                   const MusicInfo::MinMax<f32>* pan);

    bool isDone() override { return true; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x7101005f44
    void start() override {
        f32 volume = mVolume->mMin.ref();
        const f32 volume_max = mVolume->mMax.ref();
        f32 pan = mPan->mMin.ref();
        const f32 pan_max = mPan->mMax.ref();
        if (volume < volume_max)
            volume = sead::GlobalRandom::instance()->getF32Range(volume, volume_max);
        if (pan < pan_max)
            pan = sead::GlobalRandom::instance()->getF32Range(pan, pan_max);
        mOwner->sub_7101005874(mName, mWaitCount->ref(), mPart, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    u8 mPart;
    const agl::utl::Parameter<u32>* mWaitCount;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

// vtable 0x71024fdbe8 (constructor 0x7101006038, 0xc8 bytes): plays a part after a wait count derived from the
// owner's beat state.
class Unk_71024fdbe8 : public Unk_EnvBgmNode {
public:
    Unk_71024fdbe8(Unk_71024fdb00* owner, const sead::SafeString& name,
                   const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan);

    bool isDone() override { return true; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x7101006204
    // NON_MATCHING: the original computes the name address before the switch (the wait count is probably an inline
    // owner helper evaluated as the second argument; it has no other copy, so it is not added).
    void start() override {
        f32 volume = mVolume->mMin.ref();
        const f32 volume_max = mVolume->mMax.ref();
        f32 pan = mPan->mMin.ref();
        const f32 pan_max = mPan->mMax.ref();
        if (volume < volume_max)
            volume = sead::GlobalRandom::instance()->getF32Range(volume, volume_max);
        if (pan < pan_max)
            pan = sead::GlobalRandom::instance()->getF32Range(pan, pan_max);
        s32 wait_count;
        switch (mOwner->_1bc) {
        case 0:
        case 1:
        case 2:
        case 6:
        case 10:
        case 11:
        case 12:
        case 13:
            wait_count = mOwner->_1b8;
            break;
        case 3:
        case 4:
        case 5:
        case 7:
        case 8:
        case 9:
        case 14:
            wait_count = mOwner->_1b8 * 2;
            break;
        case 15:
            wait_count = mOwner->_1b8 * 3;
            break;
        default:
            wait_count = mOwner->_1b8;
            break;
        }
        mOwner->sub_7101005874(mName, wait_count, false, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

// vtable 0x71024fdc38 (constructor 0x7101006310, 0xe0 bytes): plays a part, then waits the same count before it is
// done.
class Unk_71024fdc38 : public Unk_EnvBgmNode {
public:
    Unk_71024fdc38(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                   const agl::utl::Parameter<u32>* wait_count, const MusicInfo::MinMax<f32>* volume,
                   const MusicInfo::MinMax<f32>* pan);

    // 0x71010064f0
    // NON_MATCHING: the original returns false as a 64-bit zero (mov x0, xzr).
    bool isDone() override {
        if (mCounter != 0) {
            --mCounter;
            return false;
        }
        return true;
    }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x7101006514
    void start() override {
        mCounter = mWaitCount->ref();
        f32 volume = mVolume->mMin.ref();
        const f32 volume_max = mVolume->mMax.ref();
        f32 pan = mPan->mMin.ref();
        const f32 pan_max = mPan->mMax.ref();
        if (volume < volume_max)
            volume = sead::GlobalRandom::instance()->getF32Range(volume, volume_max);
        if (pan < pan_max)
            pan = sead::GlobalRandom::instance()->getF32Range(pan, pan_max);
        mOwner->sub_7101005874(mName, mCounter, mPart, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    u8 mPart;
    const agl::utl::Parameter<u32>* mWaitCount;
    s32 mCounter = 0;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

// vtable 0x71024fdc88 (constructor 0x71010065e8, 0xe8 bytes): like Unk_71024fdc38 with a random wait count
// (base * rate in [min, max]).
class Unk_71024fdc88 : public Unk_EnvBgmNode {
public:
    Unk_71024fdc88(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                   const agl::utl::Parameter<u32>* wait_count_base,
                   const MusicInfo::MinMax<u32>* wait_count_rate, const MusicInfo::MinMax<f32>* volume,
                   const MusicInfo::MinMax<f32>* pan);

    // 0x71010067d4
    // NON_MATCHING: the original returns false as a 64-bit zero (mov x0, xzr).
    bool isDone() override {
        if (mCounter != 0) {
            --mCounter;
            return false;
        }
        return true;
    }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x71010067f8
    void start() override {
        const u32 min = mWaitCountRate->mMin.ref();
        const u32 max = mWaitCountRate->mMax.ref();
        mCounter = sead::GlobalRandom::instance()->getS32Range(min, max + 1) * mWaitCountBase->ref();
        f32 volume = mVolume->mMin.ref();
        const f32 volume_max = mVolume->mMax.ref();
        f32 pan = mPan->mMin.ref();
        const f32 pan_max = mPan->mMax.ref();
        if (volume < volume_max)
            volume = sead::GlobalRandom::instance()->getF32Range(volume, volume_max);
        if (pan < pan_max)
            pan = sead::GlobalRandom::instance()->getF32Range(pan, pan_max);
        mOwner->sub_7101005874(mName, mCounter, mPart, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    u8 mPart;
    const agl::utl::Parameter<u32>* mWaitCountBase;
    const MusicInfo::MinMax<u32>* mWaitCountRate;
    s32 mCounter = 0;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

}  // namespace ksys::snd

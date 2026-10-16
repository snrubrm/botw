#pragma once

#include <prim/seadSafeString.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

class Unk_EnvBgmNode;

// Placeholder (vtable 0x71024fdb00; derived from Unk_SpotBgmHandle without RTTI of its own): the environment BGM
// handle. Its init 0x7101004a54 (declared only) builds the node graph below from EnvBgmInfo ("Part0_A0", "Part0",
// ..., "Part3"). Only the fields used by the nodes are declared.
class Unk_71024fdb00 : public Unk_SpotBgmHandle {
public:
    // 0x7101005874 (declared only; 580 B): plays the part `name` with the given volume and pan, at once when
    // `wait_count` is 0, else queued in the free entry of `_1c0` (placeholder name; argument order is a guess).
    void sub_7101005874(const sead::SafeString& name, s32 wait_count, bool flag, f32 volume, f32 pan);

    u8 _180[0x188 - 0x180];
    EnvBgmInfo* mInfo;
    u8 _190[0x1ac - 0x190];
    bool _1ac;
    u8 _1ad[0x1b4 - 0x1ad];
    // Index of the branch taken by Unk_71024fdd28 (0..2).
    s32 _1b4;
    s32 _1b8;
    // 0..15; Unk_71024fdbe8::start multiplies the wait count by 2 or 3 for some values.
    u32 _1bc;
};

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
    Unk_71024fdb98(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
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
        mOwner->sub_7101005874(mName, mWaitCount->ref(), mFlag, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    bool mFlag;
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
    Unk_71024fdc38(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
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
        mOwner->sub_7101005874(mName, mCounter, mFlag, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    bool mFlag;
    const agl::utl::Parameter<u32>* mWaitCount;
    s32 mCounter = 0;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

// vtable 0x71024fdc88 (constructor 0x71010065e8, 0xe8 bytes): like Unk_71024fdc38 with a random wait count
// (base * rate in [min, max]).
class Unk_71024fdc88 : public Unk_EnvBgmNode {
public:
    Unk_71024fdc88(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
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
        mOwner->sub_7101005874(mName, mCounter, mFlag, volume, pan);
    }

private:
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    bool mFlag;
    const agl::utl::Parameter<u32>* mWaitCountBase;
    const MusicInfo::MinMax<u32>* mWaitCountRate;
    s32 mCounter = 0;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

}  // namespace ksys::snd

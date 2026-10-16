#pragma once

#include <prim/seadSafeString.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <xlink2/xlink2PropertyDefinition.h>

namespace ksys::snd {

class Unk_EnvBgmNode;

// Placeholder (vtable 0x71024fdb00; derived from Unk_71024fc7f8 without RTTI of its own): the environment BGM handle
// (one per EnvBgmInfo::EnvTimeEnum, held by Unk_71025ce350). Its init 0x7101004a54 (declared only) builds the node
// graph below from EnvBgmInfo ("Part0_A0", "Part0", ..., "Part3").
// 0x7101006e6c (declared only; placeholder name): the text function of the second property's value enum. Its
// text is ",A0,A1,...,B6,C0" (an empty first name), which SEAD_ENUM cannot produce.
const char* sub_7101006E6C(int idx);

class Unk_71024fdb00 : public Unk_71024fc7f8 {
public:
    // Inlined into Unk_71025ce350::sub_710100454C (0x710100454c), which creates the day / night handles.
    Unk_71024fdb00() : Unk_71024fc7f8(Unk_710260f248Type::_0) {}
    ~Unk_71024fdb00() override;

    // 0x7101005ab8
    void hm14() override {}
    // 0x7101005abc (declared only; 684 B)
    void hm15() override;

    // 0x7101004a54: creates the xlink2 properties and the node graph of the four parts (placeholder name).
    void sub_7101004A54(sead::Heap* heap, EnvBgmInfo::EnvTimeEnum type, EnvBgmInfo* info);
    // 0x7101005698: resets the section and part properties, the counters and the four part machines.
    void sub_7101005698();

    // The xlink2 property names (text 0x7101006b14) and the values of the first property (0x7101006cc0); the
    // second property's 16 value names come from 0x7101006e6c (sub_7101006E6C).
    SEAD_ENUM(PropertyType,区間,パート0のID)
    SEAD_ENUM(Section,A,B,C)

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

    u32 mTimeType = 0;
    EnvBgmInfo* mInfo = nullptr;
    sead::PtrArray<xlink2::PropertyDefinition> mProperties;
    u32 mBpm = 0;
    f32 mBeatSec = 0;
    u32 _1a8 = 0;
    bool _1ac = true;
    u8 _1ad[0x1b0 - 0x1ad];
    u32 _1b0 = 0;
    // The branch taken by Unk_71024fdd28.
    Section _1b4;
    s32 _1b8 = 0;
    // 0..15; Unk_71024fdbe8::start multiplies the wait count by 2 or 3 for some values.
    u32 _1bc = 0;
    sead::Buffer<Entry> mEntries;
    // The node machines of parts 0 to 3.
    Unk_71024fdde8* mPartMachines[4]{};
    sead::PtrArray<Unk_EnvBgmNode> mNodes;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fdb00, 0x200);

// Placeholder base of the environment and field battle BGM nodes (each node keeps its owner at +0x10; no vtable of its own is emitted: slots 0-2 and 4 are defined by each
// node). Slots 3 and 5 are the shared empty functions 0x7101006960 / 0x7101006964.
class Unk_EnvBgmNode {
public:
    Unk_EnvBgmNode() = default;
    virtual ~Unk_EnvBgmNode() = default;

    // True when the node is finished and the machine may move on (placeholder name).
    virtual bool isDone() = 0;
    virtual Unk_EnvBgmNode* getNext() = 0;
    virtual void setNext(Unk_EnvBgmNode* next) = 0;
    virtual void setBranch(Unk_EnvBgmNode* next, s32 index) {}
    virtual void start() = 0;
    virtual void m5() {}

protected:
    // Unk_71024fdde8 (the node machine) sets and clears this flag (0x7101014320 / 0x7101014450).
    friend struct Unk_71024fdde8;

    bool _8 = false;
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
    Unk_71024fdb00* mOwner;
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
    Unk_71024fdb00* mOwner;
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
    Unk_71024fdb00* mOwner;
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
    Unk_71024fdb00* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    sead::FixedSafeString<128> mName;
    u8 mPart;
    const agl::utl::Parameter<u32>* mWaitCountBase;
    const MusicInfo::MinMax<u32>* mWaitCountRate;
    s32 mCounter = 0;
    const MusicInfo::MinMax<f32>* mVolume;
    const MusicInfo::MinMax<f32>* mPan;
};

// vtable 0x71024fdcd8 (0x28 bytes; constructed only in sub_7101004A54): done once the owner's beat state changes.
class Unk_71024fdcd8 : public Unk_EnvBgmNode {
public:
    explicit Unk_71024fdcd8(Unk_71024fdb00* owner) : mOwner(owner) {}

    // 0x7101006020
    bool isDone() override { return mBeatState != mOwner->_1bc; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x7101006010
    void start() override { mBeatState = mOwner->_1bc; }

private:
    Unk_71024fdb00* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    u32 mBeatState = 0;
};

// vtable 0x71024fdd28 (0x30 bytes; constructed only in sub_7101004A54): branches on the owner's section.
class Unk_71024fdd28 : public Unk_EnvBgmNode {
public:
    explicit Unk_71024fdd28(Unk_71024fdb00* owner) : mOwner(owner) {}

    bool isDone() override { return true; }
    // 0x71010068fc
    Unk_EnvBgmNode* getNext() override {
        const auto section = mOwner->_1b4;
        return mBranches[section];
    }
    void setNext(Unk_EnvBgmNode* next) override {}
    // 0x7101006928
    void setBranch(Unk_EnvBgmNode* next, s32 index) override { mBranches[index] = next; }
    void start() override {}

private:
    Unk_71024fdb00* mOwner;
    sead::SafeArray<Unk_EnvBgmNode*, 3> mBranches;
};

}  // namespace ksys::snd

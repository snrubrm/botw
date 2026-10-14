#pragma once

#include <basis/seadTypes.h>
#include <aal/aalTimedFader.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadObjList.h>
#include <prim/seadDelegate.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

#include <aal/aalAssetInfo.h>
#include <aal/aalHandle.h>
#include <aal/aalISpeakerBalanceSupplier.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <xlink2/xlink2HandleSLink.h>

namespace xlink2 {
class Locator;
class PropertyDefinition;
class UserInstanceSLink;
}  // namespace xlink2

class Unk_SpotBgmHandle;

namespace sead {
class TextWriter;
}

namespace uking::action {
class SoundOcclusionTagAction;
}

class Unk_7102500a00;
class Unk_71024fefe8;
class Unk_71024feae8;
class Unk_71024fe368;
class Unk_71024fd6c8;
class Unk_71024fd948;

namespace ksys::snd {

class Unk_710260f248;

// Placeholder: the entries of Unk_710260f248::mEntries (0x58 bytes, list node at +0x40; a buffer of them sits at
// Unk_SoundMgr30 +0x20, 0x7100ff89a0 returns a free one). The f048 code at 0x7100ff62d0 calls 0x7100ff6df4 out of
// line, so the methods are defined in sndBgmMgr.cpp rather than with the Bgm code.
class Unk_710260f248Entry {
public:
    // 0x7100ff6df4: whether the entry belongs to `owner` and its handle is still valid.
    bool sub_7100FF6DF4(const Unk_710260f248* owner) const;
    // 0x7100ff6a50: stores `value` in the float array at +0x28 (index 0..3).
    void sub_7100FF6A50(s32 index, f32 value);
    // 0x7100ff6a64 (declared only)
    void sub_7100FF6A64(f32 fade_sec);
    // 0x7100ff6c1c (declared only): per-frame update for `owner`; false when the entry is finished.
    bool sub_7100FF6C1C(Unk_710260f248* owner);
    // 0x7100ff6a44: releases the entry.
    void sub_7100FF6A44();
    // 0x7100ff6a18: takes over the emitted handle for `owner`.
    void sub_7100FF6A18(Unk_710260f248* owner, const xlink2::HandleSLink& handle);

    u8 _0[8];
    Unk_710260f248* mOwner;
    xlink2::HandleSLink mHandle;
    f32 _20;
    u32 _24;
    f32 mVolumes[4];
    bool _38;
    sead::ListNode mNode;
    // Set when the last update found a virtualized sound (it dumps the active sound sources once).
    bool _50;
    u8 _51[7];
};

// Argument of Unk_710260f248::m3 (callers unknown): only the handle pointer at +0x8 is read.
struct Unk_710260f248M3Arg {
    u8 _0[8];
    aal::Handle* handle;
};

// Placeholder: the 0x20-byte speaker balance suppliers in the buffer at Unk_SoundMgr30 +0x30 (0x7100ff8a24 returns the
// first one whose handle at +0x10 is inactive). Declared only.
class Unk_SoundMgr30_30 : public aal::ISpeakerBalanceSupplier {
public:
    // Set from Unk_710260f248Entry::_24 by 0x7100ff6c1c.
    u32 _8;
    // 0x7100ff8c74 (76 B): copies the handle and reads a byte of its asset info into `_c`.
    void sub_7100FF8C74(const aal::Handle& handle);
};

// Placeholder (vtable 0x7102502950; D1 0x7101056bc8, readAssetInfo 0x7101056cac): the asset info reader at +0x68 of
// Unk_710260f248. The D1 frees a buffer of 0x50-byte res::Handle objects (`_8` count, `_10` pointer).
struct Unk_SoundMgr30_80;

class Unk_7102502950 : public aal::IAssetInfoReadable {
public:
    // 0x7101057258 (declared only; 712 B): loads the asset info for `name`; true when done.
    bool sub_7101057258(const sead::SafeString& name, Unk_SoundMgr30_80* arg);
    bool readAssetInfo(aal::AssetInfo* asset_info, const sead::SafeString& name, bool flag) override;
    virtual ~Unk_7102502950();

    s32 _8 = 0;
    void* _10 = nullptr;
    // Bit 0 makes the owner pass this reader to its xlink2 user instance (0x7101020988).
    u8 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502950, 0x20);

// Type of an Unk_710260f248 (stored at +0xd0; the code tests 0, 1, 2 and 3). The constructors receive it as a
// four-byte class in a full register (0x710101d7f8 masks it with 0xffffffff). Enumerator names are unknown.
SEAD_ENUM(Unk_710260f248Type, _0, _1, _2, _3)

// RTTI root typeInfo 0x710260f248 (vtable 0x7102500850, 14 slots, constructor 0x71010203ac, 0xe8 bytes): a sound
// object with a name, an xlink2 SLink user instance and a list of playing entries (Unk_SoundMgr30 registers these
// with ObjList functions 0x7100ff8b24 / 0x7100ff8b94). Base of Unk_SpotBgmHandle.
class Unk_710260f248 {
public:
    // Virtual names: `hmN` is slot N (the trivial slots' meaning is unknown); `hm` avoids clashing with Bgm's mN in
    // the classes that derive from both.
    explicit Unk_710260f248(Unk_710260f248Type type);

    // 0x7100ff6628 / 0x7100ff6630 / 0x7100ff6634 (inline bodies emitted in the Bgm TU).
    virtual bool hm0() { return false; }
    virtual void hm1() {}
    virtual bool hm2() { return false; }
    // 0x7101020c90: lets the first free speaker balance supplier of Unk_SoundMgr30 control the sound of `arg`.
    virtual void hm3(const Unk_710260f248M3Arg& arg);
    virtual void hm4() {}
    virtual bool hm5() { return false; }

    SEAD_RTTI_BASE(Unk_710260f248)

    virtual ~Unk_710260f248();
    // 0x710102052c: copies `name`, reads the music definition and creates the xlink2 user instance.
    virtual void init(sead::Heap* heap, const sead::SafeString& name,
                     const sead::PtrArray<const xlink2::PropertyDefinition>* properties);
    // 0x7101020898
    virtual void calc();
    // 0x7101020e40
    virtual f32 getVolume() { return _a0 * _a4 * _a8.getValue(); }
    // 0x7100ff6808
    virtual const sead::SafeString* getName() { return &mName; }

    // 0x71010209fc: emits the asset `name` and returns its new entry (or null).
    Unk_710260f248Entry* sub_71010209FC(const sead::SafeString& name);
    // 0x7101020a88: emits `locator` and adds an entry for the handle.
    Unk_710260f248Entry* sub_7101020A88(const xlink2::Locator& locator);
    // 0x7101020b40 (declared only; needs the user header of xlink2::ResourceAccessor): emits the first call table.
    Unk_710260f248Entry* sub_7101020B40();
    // 0x7101020988: for type 2, loads the asset info of the name (Unk_71025ce380's m4 slot 0x7100ff6544 forwards
    // its second argument here, so Bgm::m4 probably takes the heap).
    void sub_7101020988(sead::Heap* heap);
    // 0x7101020bb0: restarts the fader at 0 and moves it to 1 in `fade_sec` (nothing for 0).
    void sub_7101020BB0(f32 fade_sec);
    // 0x7101020cec (declared only): whether the object has finished (type 3, or its asset reader is done).
    bool sub_7101020CEC();
    // 0x7101020c08: fades out the entries that belong to this object.
    void sub_7101020C08(f32 fade_sec);

    sead::FixedSafeString<64> mName;
    xlink2::UserInstanceSLink* mUserInstance = nullptr;
    Unk_7102502950 _68;
    sead::OffsetList<Unk_710260f248Entry> mEntries;
    f32 _a0 = 1.0;
    f32 _a4 = 1.0;
    aal::TimedFader _a8{1.0, aal::FadeCurveType(1), 1.0};
    Unk_710260f248Type mType;
    u8 _d4 = 0;
    u64 _d8 = 0;
    u64 _e0 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f248, 0xe8);

}  // namespace ksys::snd

// typeInfo 0x710260f238 (vtable 0x7102500670, constructor 0x710101d7f8, 0xe8 + 0x98 bytes): a BGM handle. The spot BGM
// instance (+0x8) and the Bgm children (+0x10, through Unk_71024fc7f8) contain one.
class Unk_SpotBgmHandle : public ksys::snd::Unk_710260f248 {
    SEAD_RTTI_OVERRIDE(Unk_SpotBgmHandle, ksys::snd::Unk_710260f248)
public:
    explicit Unk_SpotBgmHandle(ksys::snd::Unk_710260f248Type type);
    ~Unk_SpotBgmHandle() override;
    void init(sead::Heap* heap, const sead::SafeString& name,
             const sead::PtrArray<const xlink2::PropertyDefinition>* properties) override;
    void calc() override;
    // 0x7100ff67ec
    f32 getVolume() override { return _138.getValue() * Unk_710260f248::getVolume(); }

    // 0x710101d9d8 / 0x710101d9f4 / 0x710101da34 (declared only): start / stop (with a fade) / reset the state `_124`.
    void sub_710101D9D8();
    void sub_710101D9F4(f32 fade_sec);
    void sub_710101DA34();
    // 0x710101d9a4
    void sub_710101D9A4();
    // 0x710101d970 (52 B)
    void sub_710101D970();

    sead::FixedSafeString<32> mCategory;
    s32 mPriority = 0;
    // State (0..5; 3 and 4 are playing).
    u32 _124 = 0;
    u64 _128 = 0;
    u64 _130 = 0;
    aal::TimedFader _138{1.0, aal::FadeCurveType(1), 1.0};
    // [1] is the playing time (0x710101da4c adds the frame time to it in states 3 and 4).
    f32 _160[2]{};
    u64 _168 = 0;
    u64 _170 = 0;
    bool _178 = false;
    bool _179 = true;
    bool _17a = false;
    u32 _17c = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_SpotBgmHandle, 0x180);

namespace ksys::snd {

// The base at +0x10 of the Bgm children (Unk_71025ce380): Unk_SpotBgmHandle plus three virtuals. It has no vtable or
// RTTI of its own in the original; its slots 14..16 come from the children's secondary vtables (e.g. 0x71024fc7f8 in
// Unk_710260f048's, 0x7102500cb0 + 0x40 in Unk_SpotBgmInstance's): every child overrides 14 and 15, 16 is the empty
// 0x7100ff6810.
class Unk_71024fc7f8 : public Unk_SpotBgmHandle {
public:
    using Unk_SpotBgmHandle::Unk_SpotBgmHandle;
    virtual void hm14() = 0;
    virtual void hm15() = 0;
    virtual void hm16() {}
};
KSYS_CHECK_SIZE_NX150(Unk_71024fc7f8, 0x180);

// Placeholder name (`SoundMgr::_30->_78`, see sub_7100FFD784; the BGM interface used by the EventBgm* actions). Only the
// methods those actions call are declared (declaration only).
class Unk_SoundMgr30_78 {
public:
    // 0x71010078a0 (100 B): starts the BGM `name`.
    void sub_71010078A0(const sead::SafeString& name);
    // 0x7101007904 (92 B): stops the BGM `name` with a fade of `fade_sec` seconds.
    void sub_7101007904(f32 fade_sec, const sead::SafeString& name);
    // 0x7101007960 / 0x7101007b44 (declared only)
    void sub_7101007960(f32 fade_sec);
    void sub_7101007A08(f32 fade_sec);
    void sub_7101007AA0(f32 fade_sec);
    void sub_7101007B44();
    bool sub_7101007C14();
    bool sub_7101007C90();
    // 0x710100748c (declared only; 192 B): per-frame update.
    void sub_710100748C();
};

// The kind of a BGM (Bgm::_c). A four-byte enum wrapper: sub_7100FF7920 / sub_7100FF7C74 and the controller BGM
// callbacks spill and reload it like SEAD_ENUM values, and a zero kind is passed as `mov x1, xzr`. Enumerator names are
// unknown; the controllers use kinds 0..35.
SEAD_ENUM(BgmKind, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35)

class MusicInfo;
class HorseBgmInfo;
class AssassinSeniorBgmInfo;
class MazeForestBgmInfo;
class BigMazeBgmInfo;

// Placeholder (D1 0x710103ab10, declared only): a 4-byte object holding a ducker index (SoundMgr::DuckerType value;
// its destructor releases the ducker entry in SoundMgr +0x80). Members of the Bgm children (fd448: 10, fec18: 11).
class Unk_710103AB10 {
public:
    explicit Unk_710103AB10(s32 type) : mType(type) {}
    ~Unk_710103AB10();

    s32 mType;
};

// Which Remains (Divine Beast) boss BGM an Unk_71024fd448 plays; the names come from its name table at 0x71024fd578
// ("RemainsWindBossBgm", "RemainsFireBossBgm", "RemainsElecBossBgm", "RemainsWaterBossBgm").
SEAD_ENUM(RemainsBossBgmType, Wind, Fire, Elec, Water)

// The argument of allocBgm (0x7100ff6e2c, which switches on `kind` and passes it on to the constructors).
struct BgmInitArg {
    BgmKind kind;
    Unk_710260f248Type handle_type;
    sead::Heap* heap;
};

// Index of the music info table of Unk_SoundMgr30_18 (the factory 0x710101b84c creates 0 EnvBgmInfo, 1 HorseBgmInfo,
// 3 SpotBgmInfo, ...). Spilled and reloaded like a SEAD_ENUM; enumerator names are unknown.
SEAD_ENUM(MusicInfoType, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26)

// RTTI root at 0x71025ce360; primary vtable at 0x71024fc8a0.
class Bgm {
public:
    explicit Bgm(BgmKind kind) : _c(kind) {}
    virtual ~Bgm() = default;
    SEAD_RTTI_BASE(Bgm)

    // Unk_71025ce380's and Unk_710260f2a8's overrides pass the heap on to Unk_710260f248::sub_7101020988.
    virtual void m4(sead::Heap* heap);
    virtual void m5() = 0;
    virtual void m6(f32 fade_sec);
    virtual void m7(f32 fade_sec);
    virtual void m8(bool active);
    virtual bool m9() = 0;
    virtual bool m10();
    virtual bool m11();
    virtual void m12(f32 fade_sec);
    virtual void m13(f32 fade_sec);
    virtual void m14(sead::TextWriter& writer);

    BgmKind getKind() const { return _c; }

protected:
    friend class Unk_710260f160;

    bool mActive = false;
    u8 _9[3];
    BgmKind _c;
};
KSYS_CHECK_SIZE_NX150(Bgm, 0x10);

// Intermediate BGM RTTI typeInfo 0x71025ce380, derived from Bgm.
class Unk_71025ce380 : public Bgm, public Unk_71024fc7f8 {
    SEAD_RTTI_OVERRIDE(Unk_71025ce380, Bgm)
public:
    explicit Unk_71025ce380(const BgmInitArg& arg) : Bgm(arg.kind), Unk_71024fc7f8(arg.handle_type) {}

    // 0x7100ff653c (CSV snd::BgmCastle::m4; shared by the children's vtables)
    void m4(sead::Heap* heap) override { sub_7101020988(heap); }
    // 0x7100ff6544 (CSV snd::BgmCastle::m6; shared by the children's vtables)
    void m6(f32 fade_sec) override {
        if (mActive)
            return;
        sub_7101020BB0(fade_sec);
        m12(fade_sec);
        m8(true);
    }
    // 0x7100ff6610 (CSV snd::BgmCastle::m9; shared by the children's vtables)
    bool m9() override { return mEntries.size() == 0; }
};

// RTTI typeInfo 0x710260f278, derived from Unk_71025ce380 (sub_7100FFDD38 casts BGM kind 2 to it).
// The horse BGM ("HorseBgm"; 0x1f0 bytes, constructor 0x7101012918).
class Unk_710260f278 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f278, Unk_71025ce380)
public:
    explicit Unk_710260f278(const BgmInitArg& arg);
    ~Unk_710260f278() override;

    // 0x7101012a14 (declared only; 376 B)
    void m5() override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    // Overrides of Unk_71024fc7f8's slots 14 / 15 (primary slots 15 / 16): 0x7101012bbc / 0x7101012cd8, declared
    // only.
    void hm14() override;
    void hm15() override;

    HorseBgmInfo* mInfo = nullptr;
    u32 _198 = 0;
    u8 _19c = 0;
    u64 _1a0 = 0;
    u64 _1a8 = 0;
    u32 _1b0 = 0;
    u64 _1b8 = 0;
    aal::TimedFader _1c0{0.0, aal::FadeCurveType::Linear, 1.0};
    bool _1e8 = false;
};

// RTTI typeInfo 0x710260f2a8, derived from Bgm (sub_7100FFE094 casts BGM kind 15 to it).
// The dragon BGM (BGM kind 15; 0x68 bytes, constructor 0x71010010fc). It owns two heap-allocated BGM handles.
class Unk_710260f2a8 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_710260f2a8, Bgm)
public:
    explicit Unk_710260f2a8(const BgmInitArg& arg);
    ~Unk_710260f2a8() override;

    // 0x7101001818 / 0x7101001478 / 0x7101001770 / 0x71010016f8 / 0x71010018b4 (declared only)
    void m4(sead::Heap* heap) override;
    void m5() override;
    bool m9() override;
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override;

    // 0x7101001194 (declared only; 508 B): called at the end of the constructor.
    void sub_7101001194(const BgmInitArg& arg);

    u64 _10 = 0;
    // Indexed by DragonBgmInfo::DragonEnum (DragonBgm, GrudgeDragonBgm).
    sead::SafeArray<Unk_SpotBgmHandle*, 2> mHandles{};
    Unk_SpotBgmHandle* _28 = nullptr;
    u32 _30 = 0;
    u32 _34 = 0;
    aal::SimpleTimedFader _38{1.0};
    u64 _50 = 0;
    bool _58 = false;
    f32 _5c = 800.0;
    bool _60 = true;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f2a8, 0x68);

// RTTI typeInfo 0x71025ce350, derived from Bgm (sub_7100FFDC80 casts BGM kind 0 to it).
class Unk_71025ce350 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71025ce350, Bgm)
    friend class uking::action::SoundOcclusionTagAction;

    u8 _10[0x3c - 0x10];
    bool _3c;
    u8 _3d;
    bool _3e;
    u8 _3f;
};
KSYS_CHECK_SIZE_NX150(Unk_71025ce350, 0x40);

// RTTI typeInfo 0x710260f288, derived from Unk_71025ce380 (sub_7100FFDDF0 casts BGM kind 6 to it).
// The maze forest BGM ("MazeForestBgm"; 0x1d8 bytes, constructor 0x7101013c50).
class Unk_710260f288 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f288, Unk_71025ce380)
public:
    explicit Unk_710260f288(const BgmInitArg& arg);

    void m13(f32 fade_sec) override;
    // 0x7101013d20 (declared only; 512 B): follows the env palette and runs the state machine.
    void m5() override;
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    void hm15() override {}

private:
    MazeForestBgmInfo* mInfo = nullptr;
    s32 mState = 0;
    f32 mTimer = 0;
    aal::TimedFader mFader{0.0, aal::FadeCurveType::Linear, 1.0};
    bool _1c8 = false;
    f32 _1cc = 0;
    bool _1d0 = false;
    f32 _1d4 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f288, 0x1d8);

// RTTI typeInfo 0x710260f048, derived from Unk_71025ce380 (sub_7100FFDFDC casts BGM kind 14 to it).
class Unk_710260f048 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f048, Unk_71025ce380)
public:
    // The assassin boss BGM ("AssassinBossBgm"; 0x1c0 bytes, constructor 0x7100ff6060; was Unk_7100ffdfdc in
    // Game/AI/aiUnk_7100FFDFDC.h).
    explicit Unk_710260f048(const BgmInitArg& arg);

    void m5() override;
    bool m10() override;
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    void hm15() override;

    // 0x7100ff61bc (4 B, empty; CSV nullsub_4300)
    void sub_7100FF61BC();
    void sub_7100FF61C0();
    // 0x7100ff61f8: fades the "main" track in (to battle) or out (to the demo).
    void sub_7100FF61F8(bool battle);
    void sub_7100FF6220();
    void sub_7100FF6268();

private:
    AssassinSeniorBgmInfo* mInfo;
    s32 mState = 0;
    u16 mStopTimer = 0;
    aal::SimpleTimedFader mMainFader{1.0};
    Unk_710260f248Entry* mMainEntry;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f048, 0x1c0);

// RTTI typeInfo 0x710260f1a8, derived from Bgm (sub_7100FFE14C casts BGM kind 5 to it).
class Unk_710260f1a8 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_710260f1a8, Bgm)
};

// Four-byte practice-state argument, passed by reference to sub_71010267A8.
struct Unk_71010267A8 {
    s32 value;
};
// GuardianMini practice BGM RTTI typeInfo 0x710260f228 ("DungeonTutorialBgm"; 0x1b0 bytes, constructor 0x7101026544).
// Its D1 slot points at the identical 0x71010032f0.
class Unk_710260f228 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f228, Unk_71025ce380)
public:
    explicit Unk_710260f228(const BgmInitArg& arg);

    bool m10() override;
    void m5() override {}
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    // 0x7101026924 (declared only; 240 B)
    void m14(sead::TextWriter& writer) override;
    void hm14() override;
    // 0x710102661c (declared only; 388 B)
    void hm15() override;

    // Plays the lesson track for `state` (0: "Lesson1") or records it for later (state 2).
    void sub_71010267A8(const Unk_71010267A8& state);
    // 0x7101026888 (called by Unk_710260f218::m10).
    void sub_7101026888();

private:
    MusicInfo* mInfo = nullptr;
    s32 mState = 0;
    s32 _19c = 0;
    Unk_71010267A8 mLesson{0};
    Unk_710260f248Entry* mEntry = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f228, 0x1b0);

// Placeholder name (ctor 0x71010073f4, constructed by the BgmMgr's init 0xff7f14): a list of BGM objects (their list node
// is at +0x190) guarded by a critical section.
class Unk_71010073f4 {
public:
    // 0x71010073f4
    Unk_71010073f4();
    // 0x7101007440 (D1) / 0x7101007454 (D0)
    virtual ~Unk_71010073f4();

private:
    sead::OffsetList<Bgm> mList;
    sead::CriticalSection mCS;
};

// Placeholder name (`SoundMgr::_30->_10`, see sub_7100FFD754): the manager the spot BGM handles register with.
struct Unk_SoundMgr30_10 {
    // 0x710101d5ec (declared only; 300 B) / 0x710101d718 (declared only; 96 B)
    void sub_710101D5EC(Unk_SpotBgmHandle* handle);
    void sub_710101D718(Unk_SpotBgmHandle* handle);
    // 0x710101cfec (declared only; 1536 B): per-frame update.
    void sub_710101CFEC();
};

// Four-byte state argument of sub_7100FF7BE0; the real enum name is unknown.
struct Unk_7100FF7BE0 {
    s32 value;
};

class Unk_7100ff7444 {
public:
    Unk_7100ff7444();
    ~Unk_7100ff7444();
    void sub_7100FF74D0();
    void sub_7100FF75DC(s32 capacity, sead::Heap* heap);
    void sub_7100FF7698();
    void sub_7100FF7830(f32 fade_sec);
    void sub_7100FF78A8(f32 fade_sec);
    // 0x7100ff7920 (184 B, CSV name snd::changeBgm): adds a reference to the entry of `kind`, or allocates the BGM.
    void sub_7100FF7920(BgmKind kind, sead::Heap* heap);
    void sub_7100FF7BE0(Unk_7100FF7BE0 state);
    Bgm* sub_7100FF7C74(BgmKind kind);

private:
    // FF79D8 constructs 0x10-byte values in the 0x20-byte ObjList nodes.
    struct Entry {
        Bgm* bgm;
        u32 refs;
    };
    sead::ObjList<Entry> mEntries;

public:
    // Callbacks invoked by sub_7100FF7698 (_30) with each BGM; the controllers point them at their delegate members
    // in their m4 (f160 sets both).
    sead::IDelegate1<Bgm*>* _30 = nullptr;
    sead::IDelegate1<Bgm*>* _38 = nullptr;

private:
    sead::CriticalSection mCS;
    bool _80 = false;
    bool _81 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7100ff7444, 0x88);

// Argument of the controller virtual m8 (a pointer in the original). The consumers 0x7100ff9dcc / 0x7100ffbb24 read
// the first dword, a dword at +4, a halfword at +8 and a dword at +0xc; 0x710100215c copies all 16 bytes.
struct Unk_BgmControllerM8Arg {
    u32 _0;
    s32 _4;
    u16 _8;
    u8 _a[2];
    u32 _c;
};
KSYS_CHECK_SIZE_NX150(Unk_BgmControllerM8Arg, 0x10);

// Kind of BGM controller created by 0x7100ff8464 (CSV sound::x_1; it stores it at +0x40). That switch spills and
// reloads the four-byte enum wrapper, and the Unk_710260f150 constructor receives it in a full register. Enumerator
// names are unknown; the switch covers 1..11.
SEAD_ENUM(BgmControllerType, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)

// Slot of the BGM tables of Unk_71024fe948 (0..5; spilled and range-checked like a SEAD_ENUM). Names unknown.
SEAD_ENUM(Unk_71024fe948Slot, _0, _1, _2, _3, _4, _5)

// Placeholder (vtable 0x71024fe948, three slots, no RTTI): the 0x88-byte object at +0x90 of Unk_710260f0c0 and
// Unk_710260f198 (constructor 0x710100d5bc).
class Unk_71024fe948 {
public:
    Unk_71024fe948();
    virtual ~Unk_71024fe948();
    virtual void m2();

    // 0x710100d604
    void sub_710100D604(sead::Heap* heap);
    // 0x710100d694
    void sub_710100D694();
    // 0x710100d874 (declared only): stores `bgm` in the table at +0x20 and, if it is set, gives it the value of the
    // table at +0x50 (at its +0x190).
    void sub_710100D874(Unk_71024fe948Slot slot, Unk_71025ce380* bgm);
    // 0x710100d860: clears _1c and _8 when _8 is set.
    void sub_710100D860();

    bool _8;
    u8 _9[3];
    // Copied from the controller m9 argument by Unk_710260f0c0::m9.
    u32 _c;
    s32 _10;
    u16 _14;
    u8 _16[2];
    u32 _18;
    u8 _1c[0x88 - 0x1c];
};
KSYS_CHECK_SIZE_NX150(Unk_71024fe948, 0x88);

// The RTTI root of the BGM controller family (vtable 0x71024fca78). `_8` is common to the family: the helpers
// sub_7100FFDD38 etc. call `_48->_8.sub_7100FF7C74()` on the base pointer without a cast. The controllers derive from
// it directly (their checkDerivedRuntimeTypeInfo tests their own typeInfo and then this class's).
class Unk_71024fca78 {
public:
    // Inline: the Unk_710260f0c0 destructor (0x7100ff9338, in the sndBgmMgr.cpp TU) and the controller D0s (in
    // sndBattleDungeonBgm.cpp) all inline it.
    virtual ~Unk_71024fca78() = default;
    SEAD_RTTI_BASE(Unk_71024fca78)

    // Slots 4-7 are pure in the original vtable; 8-12 have empty or `return nullptr` default bodies.
    virtual void m4(sead::Heap* heap) = 0;
    virtual void m5() = 0;
    virtual void m6(f32 fade_sec) = 0;
    virtual void m7(f32 fade_sec) = 0;
    virtual void m8(const Unk_BgmControllerM8Arg& arg) {}
    virtual void m9(const Unk_BgmControllerM8Arg& arg) {}
    virtual void m10() {}
    virtual void* m11() { return nullptr; }
    virtual void m12() {}

    Unk_7100ff7444 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fca78, 0x90);

// RTTI typeInfo 0x710260f130, SoundMgr::_30->_48.
class Unk_710260f130 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f130, Unk_71024fca78)
public:
    Unk_710260f130();

    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    void m10() override;
    void m12() override {}

    void sub_7100FF9CC8(Bgm* bgm);
    void sub_7100FF9F0C();
    void sub_7100FF9FA8();
    void sub_7100FFA0C4();
    void sub_7100FFA1E0(bool value);

    bool _90 = false;
    bool _91 = false;
    bool _92 = true;
    sead::Delegate1<Unk_710260f130, Bgm*> _98{this, &Unk_710260f130::sub_7100FF9CC8};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f130, 0xb8);
Unk_710260f130* sub_7100FFD9D0();

// RTTI typeInfo 0x710260f198, a BGM controller (sub_7100FFD7CC casts SoundMgr::_30->_48 to it).
class Unk_710260f198 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f198, Unk_71024fca78)
public:
    // 0x7100ffaf20 (declared only; 0x130 bytes, created by Unk_SoundMgr30::sub_7100FF8464 for type 1).
    Unk_710260f198();
    // Own slots of vtable 0x71024fcdb0 (D2 0x7100ffb368, m4 0x7100ffb438 ... m12 0x7100ffbf40); declared only.
    ~Unk_710260f198() override;
    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    void m9(const Unk_BgmControllerM8Arg& arg) override;
    void m10() override;
    void* m11() override;
    void m12() override;

    u8 _90[0x130 - 0x90];
};
KSYS_CHECK_SIZE_NX150(Unk_710260f198, 0x130);
Unk_710260f198* sub_7100FFD7CC();

// RTTI typeInfo 0x710260f1f8, a BGM controller (sub_7100FFD878 casts SoundMgr::_30->_48 to it).
class Unk_710260f1f8 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f1f8, Unk_71024fca78)
public:
    explicit Unk_710260f1f8(BgmControllerType type);

    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    void m12() override {}

    void sub_7100FFC1C8(Bgm* bgm);

    bool _90 = false;
    // 0..3, set from the controller types 6..9; m4 maps it to the BGM kinds 22, 24, 23, 25.
    s32 _94 = 0;
    sead::Delegate1<Unk_710260f1f8, Bgm*> _98{this, &Unk_710260f1f8::sub_7100FFC1C8};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f1f8, 0xb8);
Unk_710260f1f8* sub_7100FFD878();

// RTTI typeInfo 0x710260f150, a BGM controller (sub_7100FFD924 casts SoundMgr::_30->_48 to it).
class Unk_710260f150 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f150, Unk_71024fca78)
public:
    explicit Unk_710260f150(BgmControllerType type);

    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    void m12() override {}

    void sub_7100FFA46C(Bgm* bgm);
    void sub_7100FFA610();
    void sub_7100FFA72C();

    bool _90 = false;
    bool _91;
    sead::Delegate1<Unk_710260f150, Bgm*> _98{this, &Unk_710260f150::sub_7100FFA46C};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f150, 0xb8);
Unk_710260f150* sub_7100FFD924();

// RTTI typeInfo 0x710260f0c0, a BGM controller (sub_7100FFDB28 casts SoundMgr::_30->_48 to it).
class Unk_710260f0c0 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f0c0, Unk_71024fca78)
public:
    Unk_710260f0c0();
    ~Unk_710260f0c0() override;

    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    // 0x7100ff9690 / 0x7100ff978c / 0x7100ff97b8: declared only (they need the layouts of the BGMs at _a8 / _b0
    // and of _90).
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    void m9(const Unk_BgmControllerM8Arg& arg) override;
    void m10() override;
    void m12() override {}

    // Delegate callbacks (0x7100ff8f34 / 0x7100ff92bc): declared only; they pass a kind enum to
    // Unk_71024fe948::sub_710100D874.
    void sub_7100FF8F34(Bgm* bgm);
    void sub_7100FF92BC(Bgm* bgm);
    // Called by uking::act::Guardian with its +0x60 value and whether its +0x15b0 / +0x15b0-like pointer is null.
    void sub_7100FF9810(s32 id, bool use_a0);
    void sub_7100FF9830(s32 id, bool use_a0);
    void sub_7100FF9850(s32 a, bool b, s32 id, bool use_a0);
    void sub_7100FF987C(bool a, s32 id, bool use_a0);
    // Called by uking::action::SceneBgmCtrlAction::oneShot_.
    void sub_7100FF98A4();

    Unk_71024fe948* _90 = nullptr;
    // Set by sub_7100FF8F34 from the BGM kinds 16, 17, 3, 18 and 20.
    ::Unk_71024fefe8* _98 = nullptr;
    ::Unk_71024feae8* _a0 = nullptr;
    ::Unk_71024fe368* _a8 = nullptr;
    ::Unk_71024fd6c8* _b0 = nullptr;
    ::Unk_71024fd948* _b8 = nullptr;
    f32 _c0 = 0;
    u8 _c4 = 0;
    sead::Delegate1<Unk_710260f0c0, Bgm*> _c8{this, &Unk_710260f0c0::sub_7100FF8F34};
    sead::Delegate1<Unk_710260f0c0, Bgm*> _e8{this, &Unk_710260f0c0::sub_7100FF92BC};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f0c0, 0x108);
Unk_710260f0c0* sub_7100FFDB28();

// RTTI typeInfo 0x710260f160, a BGM controller (sub_7100FFDBD4 casts SoundMgr::_30->_48 to it).
class Unk_710260f160 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f160, Unk_71024fca78)
public:
    Unk_710260f160();

    // m4-m6 (0x7100ffab6c / 0x7100ffabfc / 0x7100ffac7c) also query the object at SoundMgr+0xc8 (vtable
    // 0x710246be38, slot 9); declared only until that class exists.
    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override {}
    void m12() override {}

    void sub_7100FFAAB0(Bgm* bgm);
    void sub_7100FFAB58(Bgm* bgm);

    bool _90 = false;
    bool _91 = false;
    sead::Delegate1<Unk_710260f160, Bgm*> _98{this, &Unk_710260f160::sub_7100FFAAB0};
    sead::Delegate1<Unk_710260f160, Bgm*> _b8{this, &Unk_710260f160::sub_7100FFAB58};
    // The kind 34 BGM, set by sub_7100FFAAB0 when it is a ::Unk_7102500a00.
    ::Unk_7102500a00* _d8 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f160, 0xe0);
Unk_710260f160* sub_7100FFDBD4();

// RTTI typeInfo 0x710260f218; the GuardianMini practice BGM controller.
// Its remaining layout is not modeled yet.
class Unk_710260f218 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f218, Unk_71024fca78)
public:
    Unk_710260f218();

    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    void m8(const Unk_BgmControllerM8Arg& arg) override {}
    void m10() override;
    void m12() override {}

    void sub_7100FFC5C8(Bgm* bgm);
    void sub_7100FFC758();
    void sub_7100FFC7F4();
    void sub_7100FFC894();
    void sub_7100FFC934();
    void sub_7100FFC9D4();
    void sub_7100FFCA70();

    bool _90 = false;
    sead::Delegate1<Unk_710260f218, Bgm*> _98{this, &Unk_710260f218::sub_7100FFC5C8};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f218, 0xb8);
Unk_710260f218* sub_7100FFDA7C();

// 0x7100ffdd38 / 0x7100ffe094 (placeholder names): BGM kind 2 / 15 of the controller at SoundMgr::_30->_48, cast to its
// class (null if there is none). The controller is read without null checks on SoundMgr and _30.
Unk_710260f278* sub_7100FFDD38();
Unk_710260f2a8* sub_7100FFE094();
Unk_71025ce350* sub_7100FFDC80();
Unk_710260f288* sub_7100FFDDF0();
Unk_710260f048* sub_7100FFDFDC();
Unk_710260f1a8* sub_7100FFE14C();

// Placeholders (types unknown): SoundMgr::_30->_8 / _18 (returned by sub_7100FFD73C / sub_7100FFD76C).
class MusicDefinition;
// SoundMgr::_30->_18: one music info object per MusicInfoType (created by 0x710101b84c).
struct Unk_SoundMgr30_18 {
    // inline-only in the original; name is a guess (the Bgm constructors 0x7101012918, ... index the table with a
    // spilled enum whose stack slot is shared with later temporaries).
    MusicInfo* getInfo(MusicInfoType type) const { return mInfos[type]; }

    u8 _0[8];
    sead::SafeArray<MusicInfo*, 27> mInfos;
};

// Placeholder name (SoundMgr::_30): the BGM side of the sound manager.
struct Unk_SoundMgr30 {
    // 0x7100ff8464 (CSV sound::x_1): creates the BGM controller for `type` at _48 and initializes it.
    void sub_7100FF8464(sead::Heap* heap, BgmControllerType type);
    // 0x7100ff8804 (declared only; 164 B): called by SoundMgr::sub_71011FC288.
    void sub_7100FF8804();
    void sub_7100FF85E0();
    void sub_7100FF8684(s32 fade_type);
    // 0x7100ff8730: deletes the controller and resets the controller type.
    void sub_7100FF8730();
    void sub_7100FF8780(s32 fade_type);
    void sub_7100FF88A8(s32 fade_type);
    void sub_7100FF8AC4(s32 fade_type);
    // 0x7100ff88d0: per-frame update; drops the finished sound objects.
    void sub_7100FF88D0();
    // 0x7100ff8b24 / 0x7100ff8b94: add / remove a sound object from the ObjList at +0x90.
    void sub_7100FF8B24(Unk_710260f248* obj);
    void sub_7100FF8B94(Unk_710260f248* obj);
    // 0x7100ff8a24 (declared only)
    Unk_SoundMgr30_30* sub_7100FF8A24();
    // 0x7100ff89a0: a free entry of the pool at +0x20 (reset), or null.
    Unk_710260f248Entry* sub_7100FF89A0();

    u8 _0[0x8];
    /* 0x08 */ MusicDefinition* _8;
    /* 0x10 */ Unk_SoundMgr30_10* _10;
    /* 0x18 */ Unk_SoundMgr30_18* _18;
    // Pool of the sound object entries (0x7100ff89a0 hands out the unlinked ones).
    /* 0x20 */ sead::Buffer<Unk_710260f248Entry> mEntryPool;
    // A buffer of the 0x20-byte speaker balance suppliers (count, pointer; 0x7100ff8a24).
    /* 0x30 */ u8 _30[0x10];
    /* 0x40 */ BgmControllerType _40;
    u8 _44[4];
    /* 0x48 */ Unk_71024fca78* _48;
    // Native constructor FF7D08 and fade controls independently establish these floats.
    f32 _50;
    f32 _54;
    f32 _58;
    u8 _5c[4];
    /* 0x60 */ aal::SimpleTimedFader _60;
    /* 0x78 */ Unk_SoundMgr30_78* _78;
    /* 0x80 */ Unk_SoundMgr30_80* _80;
    u8 _88;
    // Skips the controller / _78 / _10 / fader updates in 0x7100ff88d0.
    bool _89;
    u8 _8a[6];
    // The sound objects being updated (0x7100ff88d0 removes the finished ones).
    sead::ObjList<Unk_710260f248*> mObjects;
};

// 0x7100ffd71c (32 B): `SoundMgr::instance()->_30`, or null without a SoundMgr. Placeholder name.
Unk_SoundMgr30* sub_7100FFD71C();
// 0x7100ffd73c / 0x7100ffd76c (24 B): `SoundMgr::instance()->_30->_8` / `->_18`. Placeholder names.
MusicDefinition* sub_7100FFD73C();
Unk_SoundMgr30_18* sub_7100FFD76C();

// 0x7100ffd754 (24 B): `SoundMgr::instance()->_30->_10`.
Unk_SoundMgr30_10* sub_7100FFD754();

struct Unk_SoundMgr30_240 {
    // 0x71012be0a4 (400 B) / 0x71012be234 (96 B), declared only: register / unregister a sound object.
    void sub_71012BE0A4(Unk_710260f248* obj);
    void sub_71012BE234(Unk_710260f248* obj);
};
// 0x7100fff124 (24 B): `SoundMgr::instance()->_30->_240` (no null checks). Placeholder name; declared only.
Unk_SoundMgr30_240* sub_7100FFF124();

// 0x7100ffd784 (24 B): `SoundMgr::instance()->_30->_78`.
Unk_SoundMgr30_78* sub_7100FFD784();

}  // namespace ksys::snd

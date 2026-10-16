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
#include <thread/seadSpinLock.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"

#include <aal/aalAssetInfo.h>
#include <aal/aalHandle.h>
#include <aal/aalISpeakerBalanceSupplier.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadHeap.h>
#include <xlink2/xlink2HandleSLink.h>

namespace aal {
class Group;
}  // namespace aal

namespace ksys::res {
class Handle;
}  // namespace ksys::res

namespace xlink2 {
class Locator;
class PropertyDefinition;
class UserInstanceSLink;
}  // namespace xlink2

class Unk_SpotBgmHandle;
class Unk_SpotBgmInstance;

namespace sead {
class TextWriter;
}

class Unk_7102500a00;
class Unk_71024fefe8;
class Unk_71024fe808;
class Unk_71024feae8;
class Unk_71024fe368;
class Unk_71024fee78;
class Unk_71024fec18;
class Unk_71024fed48;
class Unk_71024fd448;
class Unk_71024fd6c8;
class Unk_71024fd948;

namespace ksys::snd {

class DragonBgmInfo;
class TemperatureBgmInfo;

class Unk_710260f248;
class Unk_EnvBgmNode;

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
    // Pan (-1..1); passed to the speaker balance supplier.
    f32 mPan;
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
    // The pan, set from Unk_710260f248Entry::mPan by 0x7100ff6c1c.
    f32 _8;
    // 0x7100ff8c74 (76 B): copies the handle and reads a byte of its asset info into `_c`.
    void sub_7100FF8C74(const aal::Handle& handle);
    // Declared only (address unknown).
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override;

    /* 0x0c */ u32 _c;
    /* 0x10 */ aal::Handle mHandle;
};

// Placeholder (vtable 0x7102502950; D1 0x7101056bc8, readAssetInfo 0x7101056cac): the asset info reader at +0x68 of
// Unk_710260f248. The D1 frees a buffer of 0x50-byte res::Handle objects (`_8` count, `_10` pointer).

class Unk_7102502950 : public aal::IAssetInfoReadable {
public:
    // 0x7101057258 (declared only; 712 B): loads the asset info for `name`; true when done.
    bool sub_7101057258(const sead::SafeString& name, sead::Heap* heap);
    bool readAssetInfo(aal::AssetInfo* asset_info, const sead::SafeString& name, bool flag) override;
    // 0x7101056bc8
    virtual ~Unk_7102502950();

    // The loaded asset info resources (0x50-byte res::Handle objects).
    sead::Buffer<res::Handle> mHandles;
    // Bit 0 makes the owner pass this reader to its xlink2 user instance (0x7101020988).
    u8 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102502950, 0x20);

// Placeholder (vtable 0x71024fdde8: D1 0x71010073ac (empty), D0 0x71010073b0; 0x20 bytes): created by the field battle
// BGM's init 0x71010099f0 (stored at +0x248): a small state machine over the BGM's node objects (`_8` the first node,
// `_10` the current one, `_18` running). Declared only.
struct Unk_71024fdde8 {
    // Defined (empty) in sndEnvBgm.cpp, the TU of its vtable.
    virtual ~Unk_71024fdde8();

    // 0x7101014300: makes `_8` the current node and sets `_18`, once.
    void start();
    // 0x7101014320 (declared only): runs the current node and follows the chain.
    void sub_7101014320();
    // 0x7101014450: clears the started flag of the current node and goes back to the first one.
    void reset();
    // 0x7101014468: true when there is no first node, or the first node is current and not started.
    bool isAtStartMaybe() const;

    Unk_EnvBgmNode* _8 = nullptr;
    Unk_EnvBgmNode* _10 = nullptr;
    u8 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fdde8, 0x20);

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
                     const sead::PtrArray<xlink2::PropertyDefinition>* properties);
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
             const sead::PtrArray<xlink2::PropertyDefinition>* properties) override;
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
    // Link in Unk_SoundMgr30_10's handle list (0x710101d5ec / 0x710101d718).
    sead::ListNode mListNode;
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
    // 0x7100ff6810 (empty); the field battle BGM's override (0x710100b9bc) reads the argument.
    virtual void hm16(s32 arg) {}
};
KSYS_CHECK_SIZE_NX150(Unk_71024fc7f8, 0x180);

// RTTI root typeInfo 0x71025ce3b0 (vtable 0x710246d118: only the destructor pair is filled in; the original's RTTI slots
// look pure). The base of the named BGM objects kept by Unk_71010073f4.
class Unk_71025ce3b0 {
public:
    virtual ~Unk_71025ce3b0() = default;
    SEAD_RTTI_BASE(Unk_71025ce3b0)
};

struct BgmInitArg;
class EventBgmRemainsElecBattleInfo;
class EventBgmRemainsFireBattleInfo;

// The named BGM objects kept by Unk_71010073f4 (node at +0x190), created by bgmStuff 0x7100ffee14. Has no RTTI of its
// own: the generic object Unk_710260ecf8 and the Remains battle BGMs (Unk_71025ce3a0) derive from it with
// Unk_71025ce3b0 as their RTTI parent (EventBgmStartAndKeepAction fails for objects that are not Unk_710260ecf8).
// Its inline virtuals are emitted next to the first vtable that uses them (update 0x7101008120, getName 0x7101008124,
// m6 0x71010097d8, m7 0x7101008da0, m8 0x7101008da4).
class NamedBgm : public Unk_71025ce3b0, public Unk_71024fc7f8 {
public:
    // The derived constructors pass BgmInitArg::handle_type (read before the first vtable store).
    explicit NamedBgm(Unk_710260f248Type type) : Unk_71024fc7f8(type) {}

    // The RTTI of the list items is Unk_71025ce3b0's (the handle base has its own).
    using Unk_71025ce3b0::checkDerivedRuntimeTypeInfo;
    using Unk_71025ce3b0::getRuntimeTypeInfo;

    virtual void update() {}
    // Thunk 0x71010082fc.
    const sead::SafeString* getName() override { return &mName; }
    // Called with true when the BGM is started.
    virtual void m6(bool started) {}
    virtual void m7() {}
    // Called once after the object is created.
    virtual bool m8() { return false; }

    bool mStarted = false;
    bool _189 = true;
    s32 mRefCount = 0;
    sead::ListNode mListNode;
};
KSYS_CHECK_SIZE_NX150(NamedBgm, 0x1a0);

// RTTI typeInfo 0x710260ecf8 (vtable 0x71024fe268, 0x1a0 bytes, created by bgmStuff 0x7100ffee14 for names without a
// dedicated class).
class Unk_710260ecf8 : public NamedBgm {
    SEAD_RTTI_OVERRIDE(Unk_710260ecf8, Unk_71025ce3b0)
public:
    // Inlined in bgmStuff 0x7100ffee14 (defined there).
    Unk_710260ecf8(const BgmInitArg& arg, const sead::SafeString& name);
    // 0x7101008738 (D1, shared with the Remains classes) / 0x7101009688 (D0)
    ~Unk_710260ecf8() override;

    // 0x71010094f4 / 0x71010095e8 (thunks 0x7101009574 / 0x7101009638)
    void hm14() override;
    void hm15() override;
};
KSYS_CHECK_SIZE_NX150(Unk_710260ecf8, 0x1a0);

// RTTI typeInfo 0x71025ce3a0 (no vtable of its own; checkDerivedRuntimeTypeInfo 0x7101008304): the base of the four
// Remains (Divine Beast) battle BGMs. While the BGM plays it holds a ducking request of kind `mDuckingKind`.
class Unk_71025ce3a0 : public NamedBgm {
    SEAD_RTTI_OVERRIDE(Unk_71025ce3a0, Unk_71025ce3b0)
public:
    Unk_71025ce3a0(Unk_710260f248Type type, s32 ducking_kind) : NamedBgm(type), mDuckingKind(ducking_kind) {}

    // 0x710100812c
    void m6(bool started) override;
    // The water BGM's (0x7101008b04 / 0x7101008bf8); the same code as Unk_710260ecf8's.
    void hm14() override;
    void hm15() override;

    s32 mDuckingKind;
};
KSYS_CHECK_SIZE_NX150(Unk_71025ce3a0, 0x1a8);

// RTTI typeInfo 0x710260f2c8 (vtable 0x71024fde28, 0x1f0 bytes, constructor 0x7101007d14): "RemainsElecBattleBgm".
// The music has two parts (entry volumes 1 and 2) faded by the storm and wake boarding states.
class Unk_710260f2c8 : public Unk_71025ce3a0 {
    SEAD_RTTI_OVERRIDE(Unk_710260f2c8, Unk_71025ce3a0)
public:
    explicit Unk_710260f2c8(const BgmInitArg& arg);
    ~Unk_710260f2c8() override;

    // 0x710100800c
    void m7() override {}
    // 0x7101008150
    bool m8() override { return true; }
    // 0x7101007e1c / 0x7101007ee8 (thunks 0x7101007ee0 / 0x7101008004)
    void hm14() override;
    void hm15() override;

    EventBgmRemainsElecBattleInfo* mInfo;
    Unk_710260f248Entry* mEntry = nullptr;
    aal::SimpleTimedFader mStormFader{0.0};
    aal::SimpleTimedFader mWakeBoardingFader{0.0};
    bool _1e8 = false;
    bool _1e9 = false;
    bool _1ea = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f2c8, 0x1f0);

// RTTI typeInfo 0x71025ce390 (vtable 0x71024fdf28, 0x1b8 bytes, constructor 0x71010083d0): "RemainsFireBattleBgm".
class Unk_71025ce390 : public Unk_71025ce3a0 {
    SEAD_RTTI_OVERRIDE(Unk_71025ce390, Unk_71025ce3a0)
public:
    explicit Unk_71025ce390(const BgmInitArg& arg);
    ~Unk_71025ce390() override;

    // 0x7101008734
    void m7() override {}
    // 0x7101008848
    bool m8() override { return true; }
    // 0x7101008534 / 0x71010085f4 (thunks 0x7101008594 / 0x7101008694)
    void hm14() override;
    void hm15() override;

    // 0x71010084b4: the alert cues (EventBgmCtrlAction "RemainsFireBattleBgm_Alert" / "_Alert2").
    void sub_71010084B4(bool alert);

    EventBgmRemainsFireBattleInfo* mInfo;
    // Countdown (seconds) before the "B" asset is emitted.
    f32 mWaitTimer = 0.0;
    bool _1b4 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71025ce390, 0x1b8);

// RTTI typeInfo 0x710260f848 (vtable 0x71024fe028, 0x1a8 bytes, constructor 0x7101008a4c): "RemainsWaterBattleBgm".
class Unk_710260f848 : public Unk_71025ce3a0 {
    SEAD_RTTI_OVERRIDE(Unk_710260f848, Unk_71025ce3a0)
public:
    explicit Unk_710260f848(const BgmInitArg& arg);
    ~Unk_710260f848() override;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f848, 0x1a8);

// RTTI typeInfo 0x710260f2b8 (vtable 0x71024fe128, 0x1c8 bytes, constructor 0x7101008f50): "RemainsWindBattleBgm".
class Unk_710260f2b8 : public Unk_71025ce3a0 {
    SEAD_RTTI_OVERRIDE(Unk_710260f2b8, Unk_71025ce3a0)
public:
    explicit Unk_710260f2b8(const BgmInitArg& arg);
    ~Unk_710260f2b8() override;

    // 0x7101009234
    void m7() override {}
    // 0x71010090d4 / 0x7101009158 (thunks 0x7101009118 / 0x71010091c4)
    void hm14() override;
    void hm15() override;
    // 0x7101009018 / 0x7101009348: fade the handle in / out (placeholder names).
    virtual void fadeInMaybe(f32 fade_sec);
    virtual void fadeOutMaybe(f32 fade_sec);

    // 0x7101009040: the jump cue (EventBgmCtrlAction "RemainsWindBattleBgm_Jump").
    void sub_7101009040();

    // In the tail padding of Unk_71025ce3a0 (+0x1a4).
    bool mJumped = false;
    Unk_710260f248Entry* mEntry = nullptr;
    aal::SimpleTimedFader mFader{1.0};
};
KSYS_CHECK_SIZE_NX150(Unk_710260f2b8, 0x1c8);

// 0x7100ffe204 / 0x7100ffe39c: the wind / fire Remains battle BGM in the named BGM list, or null.
Unk_710260f2b8* sub_7100FFE204();
Unk_71025ce390* sub_7100FFE39C();
// 0x7100ffe7a4 (declared only; 664 B): the BGM of kind 22..25 picked by the Unk_710260f1f8 controller's _94, else kind
// 34 under another controller, cast to Unk_7102500a00.
Unk_7102500a00* sub_7100FFE7A4();
// 0x7100ffea3c: the BGM of kind 26 of the controller at SoundMgr::_30->_48, cast to Unk_71024fee78.
Unk_71024fee78* sub_7100FFEA3C();
// 0x7100ffe468 / 0x7100ffe6ec: the BGM of kind 32 / 31 of that controller, cast to Unk_71024fec18 (Ganon beast) /
// Unk_71024fed48 (Ganon).
Unk_71024fec18* sub_7100FFE468();
Unk_71024fed48* sub_7100FFE6EC();

// 0x7100ffee14 (declared only): creates the BGM object for `name` (dedicated classes for four names).
NamedBgm* bgmStuff(const sead::SafeString& name, sead::Heap* heap);
// 0x7100fff0e4: releases the handle of `bgm` and deletes it.
void sub_7100FFF0E4(NamedBgm* bgm);


// The kind of a BGM (Bgm::_c). A four-byte enum wrapper: sub_7100FF7920 / sub_7100FF7C74 and the controller BGM
// callbacks spill and reload it like SEAD_ENUM values, and a zero kind is passed as `mov x1, xzr`. Enumerator names are
// unknown; the controllers use kinds 0..35.
SEAD_ENUM(BgmKind, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35)

class MusicInfo;
class CastleBgmInfo;
class HorseBgmInfo;
class AssassinSeniorBgmInfo;
class MazeForestBgmInfo;
class BigMazeBgmInfo;
class DungeonBattleBgmInfo;
class DungeonNormalBgmInfo;
class GuardianFixedBgmInfo;
class GuardianBgmInfo;
class GanonGrudgeBattleBgmInfo;
class DungeonRewardBgmInfo;
class GanonBeastBgmInfo;
class FieldBattleBgmInfo;
class TutorialDungeonBattleBgmInfo;

// Placeholder (D1 0x710103ab10, declared only): a 4-byte object holding a ducker index (SoundMgr::DuckerType value;
// its destructor releases the ducker entry in SoundMgr +0x80). Members of the Bgm children (fd448: 10, fec18: 11).
// Unk_710103AB10 (a message sound ducking request) is defined in sndSound.h.

// Which Remains (Divine Beast) boss BGM an Unk_71024fd448 plays; the names come from its name table at 0x71024fd578
// ("RemainsWindBossBgm", "RemainsFireBossBgm", "RemainsElecBossBgm", "RemainsWaterBossBgm").
SEAD_ENUM(RemainsBossBgmType, Wind, Fire, Elec, Water)
// 0x7100ffebe0: calls Unk_71024fd448::sub_7101000514 on the Remains boss BGM of `type` (kinds 27..30).
void sub_7100FFEBE0(const RemainsBossBgmType& type);
// 0x7100ffecb0: calls Unk_71024fd448::sub_71010007B4 (stop) on the Remains boss BGM of `type`.
void sub_7100FFECB0(const RemainsBossBgmType& type);

// The argument of allocBgm (0x7100ff6e2c, which switches on `kind` and passes it on to the constructors).
struct BgmInitArg {
    BgmKind kind;
    Unk_710260f248Type handle_type;
    sead::Heap* heap;
};
class Bgm;
// 0x7100ff6e2c (declared only; 1500 B)
Bgm* allocBgm(const BgmInitArg& arg);

// Index of the music info table of Unk_SoundMgr30_18 (the factory 0x710101b84c creates one info per type). Names
// from the SEAD_ENUM text at 0x7101e246f5 (text function 0x710101caa8; a space before each comma).
// clang-format off
SEAD_ENUM(MusicInfoType,EnvBgm ,HorseBgm ,TemperatureBgm ,SpotBgm ,MazeForestBgm ,CastleBgm ,BigMazeBgm ,AnimalMasterBgm ,FieldBattleBgm ,GolemBgm ,GiantBgm ,SandwormBgm ,AssassinSeniorBgm ,GuardianBgm ,GuardianFixedBgm ,DragonBgm ,GanonGrudgeBattleBgm ,EventBgmRemainsElecBattle ,EventBgmRemainsFireBattle ,DungeonNormalBgm ,DungeonRewardBgm ,DungeonBattleBgm ,RemainsNormalBgm ,TutorialDungeonBattleBgm ,GanonBeastBgm ,FinalTrialBossBattleBgm ,EnvPaletteReactiveBgm)
// clang-format on

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
    s32 _1a0 = 0;
    u32 _1a4 = 0;
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

    // 0x7101001194: called at the end of the constructor; creates the two handles (Unk_71024fd3a0).
    void sub_7101001194(const BgmInitArg& arg);
    // 0x7101001808 (declared only; placeholder name): sets _60 (DragonReleaseGrudgeForDemo::calc_ clears it).
    void sub_7101001808(bool on);

    // The states of _34 (enum text "停止中,再生中,フェードアウト中,怨念切替停止": stopped, playing, fading out,
    // stopped for the grudge switch; text_ is 0x7101001d24).
    // clang-format off
    SEAD_ENUM(State,停止中,再生中,フェードアウト中,怨念切替停止)
    // clang-format on

    // The DragonBgm music info (set by sub_7101001194).
    DragonBgmInfo* _10 = nullptr;
    // Indexed by DragonBgmInfo::DragonEnum (DragonBgm, GrudgeDragonBgm).
    sead::SafeArray<Unk_SpotBgmHandle*, 2> mHandles{};
    Unk_SpotBgmHandle* _28 = nullptr;
    u32 _30 = 0;
    u32 _34 = 0;
    aal::SimpleTimedFader _38{1.0};
    // The play / stop wait counters (m14).
    f32 _50 = 0;
    f32 _54 = 0;
    bool _58 = false;
    f32 _5c = 800.0;
    bool _60 = true;
};
KSYS_CHECK_SIZE_NX150(Unk_710260f2a8, 0x68);

class Unk_71024fdb00;
class Unk_EnvBgmNode;

// RTTI typeInfo 0x71025ce350, derived from Bgm (sub_7100FFDC80 casts BGM kind 0 to it): the environment BGM
// (EnvBgmInfo; constructor 0x7101003df4, defined in sndEnvBgm.cpp with its day and night handles).
class Unk_71025ce350 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71025ce350, Bgm)
    friend class SoundOcclusionTagAction;

public:
    explicit Unk_71025ce350(const BgmInitArg& arg);
    ~Unk_71025ce350() override;

    // 0x7101003fb8 (declared only; 1428 B)
    void m5() override;
    // 0x7101006b0c
    bool m9() override { return true; }
    // 0x7101004858: starts both handles and picks the day or night part from the world time.
    void m12(f32 fade_sec) override;
    // 0x710100496c
    void m13(f32 fade_sec) override;
    // 0x7101005734
    void m14(sead::TextWriter& writer) override {}

    // 0x710100454c (declared only; 536 B): switches between the day and night handles.
    void sub_710100454C();

private:
    EnvBgmInfo* mInfo = nullptr;
    // Indexed by EnvBgmInfo::EnvTimeEnum.
    sead::SafeArray<Unk_71024fdb00*, 2> mHandles{};
    bool _28 = true;
    u32 _2c = 0;
    // The EnvBgmInfo::EnvTimeEnum value of the playing part.
    s32 mTimeType = 0;
    u32 _34 = 0;
    u32 _38 = 0;
    bool _3c = false;
    u8 _3d = 0;
    bool _3e = false;
    u8 _3f = 0;
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
    // 0x7101013fe0 (called by SceneBgmCtrlAction::oneShot_): plays the "GetLost" entry while _124 is 3 or 4.
    void playGetLostMaybe();
    // 0x7101013f70 (declared only; called by WarpSafeTagRoot::calc_ with the mist on / off): fades the BGM.
    void sub_7101013F70(bool on);

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
public:
    // 0x71010252c0 / 0x7101025388 (declared only): add / remove a spot BGM instance (`started`: the controller runs).
    void sub_71010252C0(Unk_SpotBgmInstance* instance, bool started);
    void sub_7101025388(Unk_SpotBgmInstance* instance);
    // 0x71010255d0: clears _80 and resets the volume of mGroup to 1.
    void sub_71010255D0();

    ~Unk_710260f1a8() override;
    // 0x7101024cc0 (declared only)
    void m5() override;
    bool m9() override { return true; }
    void m14(sead::TextWriter& writer) override {}
    // 0x71010251a4 / 0x7101025230: fade in / out every instance (under mLock).
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;

    /* 0x10 */ sead::Buffer<Unk_SpotBgmInstance*> mInstances;
    u8 _20[0x28 - 0x20];
    /* 0x28 */ u64 _28;
    /* 0x30 */ sead::SpinLock mLock;
    u8 _40[0x60 - 0x40];
    /* 0x60 */ sead::Buffer<void*> _60;
    u8 _70[0x78 - 0x70];
    // The "EnvNoisy" group (0x7101024ad4).
    /* 0x78 */ aal::Group* mGroup;
    /* 0x80 */ f32 _80;
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
    // 0x7101026924: prints the state when the debug flag sUnk_7102610448 is set.
    void m14(sead::TextWriter& writer) override;
    void hm14() override;
    void hm15() override;

    // Plays the lesson track for `state` (0: "Lesson1") or records it for later (state 2).
    void sub_71010267A8(const Unk_71010267A8& state);
    // 0x7101026888 (called by Unk_710260f218::m10).
    void sub_7101026888();

    // The states of mState (enum text "停止,再生,変更待ち,アウトロ待ち,アウトロ"; text_ is 0x7101026d10) and the
    // lessons of mLesson (enum text "cLesson1 , cLesson2 , cLesson3 , cLesson4"; text_ is 0x71010270a4).
    // clang-format off
    SEAD_ENUM(State,停止,再生,変更待ち,アウトロ待ち,アウトロ)
    SEAD_ENUM(Lesson,cLesson1 , cLesson2 , cLesson3 , cLesson4)
    // clang-format on

private:
    TutorialDungeonBattleBgmInfo* mInfo = nullptr;
    s32 mState = 0;
    f32 mTimer = 0;
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

    // 0x710100748c: updates the BGMs and deletes the ones that are not started, have no entries and are not held.
    void update();
    // 0x710100760c: the BGM named `name`, or null.
    NamedBgm* find(const sead::SafeString& name);
    // 0x7101007760: holds the BGM `name`, creating it on `heap` if needed. Returns false if it could not be created.
    bool hold(const sead::SafeString& name, sead::Heap* heap);
    // 0x7101007818: whether the BGM `name` is finished (true when it does not exist).
    bool isFinished(const sead::SafeString& name);
    // 0x710100754c (declared only; CSV bgmStuff_0): looks up the BGM `name` under the lock (called by
    // Unk_710105abc0::sub_710105B0F0 before it loads the Demo143 resources).
    u32 sub_710100754C(const sead::SafeString& name);
    // 0x710100787c: releases a hold taken with hold().
    void release(const sead::SafeString& name);
    // 0x71010078a0 (100 B): starts the BGM `name`.
    void sub_71010078A0(const sead::SafeString& name);
    // 0x7101007904 (92 B): stops the BGM `name` with a fade of `fade_sec` seconds.
    void sub_7101007904(f32 fade_sec, const sead::SafeString& name);
    // declared only
    void sub_7101007960(f32 fade_sec);
    void sub_7101007A08(f32 fade_sec);
    void sub_7101007AA0(f32 fade_sec);
    void sub_7101007B44();
    bool sub_7101007C14();
    bool sub_7101007C90();

private:
    sead::OffsetList<NamedBgm> mList;
    sead::CriticalSection mCS;
};

// Placeholder name (`SoundMgr::_30->_10`, see sub_7100FFD754): the manager the spot BGM handles register with.
// Placeholder (constructor 0x710101e140, init 0x710101e758, 0x3e0 bytes; deleted through slot 1): created by
// Unk_SoundMgr30_10::init. Declared only.
class Unk_710101E140 {
public:
    Unk_710101E140();
    virtual ~Unk_710101E140();
    void init(sead::Heap* heap);

    u8 _8[0x3e0 - 0x8];
};

// TU 0x710101ce5c..0x710101d77c (static initialiser) in the original: sndSoundMgr30_10.cpp.
struct Unk_SoundMgr30_10 {
    // 0x710101ce5c. Created by Unk_SoundMgr30::sub_7100FF8338 (0xd0 bytes).
    Unk_SoundMgr30_10();
    // Deleted through slot 1 by Unk_SoundMgr30's destructor.
    virtual ~Unk_SoundMgr30_10();
    // 0x710101cfa4: creates the 0x3e0-byte object at _8 on `heap` and initializes it.
    void init(sead::Heap* heap);
    // 0x710101d5ec adds the handle to mHandles (front) unless linked.
    void sub_710101D5EC(Unk_SpotBgmHandle* handle);
    // 0x710101d718: removes the handle from mHandles if it is linked.
    void sub_710101D718(Unk_SpotBgmHandle* handle);
    // 0x710101cfec (declared only; 1536 B): per-frame update.
    void sub_710101CFEC();

    /* 0x08 */ Unk_710101E140* _8 = nullptr;
    /* 0x10 */ sead::OffsetList<Unk_SpotBgmHandle> mHandles;
    /* 0x28 */ bool _28 = false;
    /* 0x30 */ sead::CriticalSection mCS;
    /* 0x70 */ u32 _70 = 0;
    /* 0x78 */ sead::FixedSafeString<32> _78;
    /* 0xb0 */ u32 _b0 = 0;
    // Returned by Unk_SoundMgr30::sub_7100FF8774.
    /* 0xb4 */ u32 _b4 = 0;
    /* 0xb8 */ void* _b8 = nullptr;
    /* 0xc0 */ void* _c0 = nullptr;
    /* 0xc8 */ bool _c8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr30_10, 0xd0);



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
    void sub_7100FF7BE0(BgmKind kind);
    Bgm* sub_7100FF7C74(BgmKind kind);

private:
    // FF79D8 constructs 0x10-byte values in the 0x20-byte ObjList nodes.
    struct Entry {
        Bgm* bgm = nullptr;
        u32 refs = 0;
    };

    // inline-only in the original; name is a guess. Evidence: sub_7100FF7920, sub_7100FF7BE0 and sub_7100FF7C74
    // repeat this search (the key is copied to the stack after the lock, the result tested for null).
    Entry* findEntry(BgmKind kind) {
        for (auto& entry : mEntries) {
            if (int(entry.bgm->getKind()) == int(kind))
                return &entry;
        }
        return nullptr;
    }
    // 0x7100ff79d8 (CSV callAllocBgm): allocates the BGM for `arg` and adds an entry for it.
    Entry* sub_7100FF79D8(const BgmInitArg& arg);

    sead::ObjList<Entry> mEntries;

public:
    // Callbacks invoked by sub_7100FF7698 (_30) with each BGM; the controllers point them at their delegate members
    // in their m4 (f160 sets both).
    sead::IDelegate1<Bgm*>* _30 = nullptr;
    sead::IDelegate1<Bgm*>* _38 = nullptr;

private:
    sead::CriticalSection mCS;

public:
    // Read by sub_7100FFED80 / sub_7100FFEDC8.
    bool _80 = false;
    bool _81 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7100ff7444, 0x88);

// Argument of the controller virtual m8 (a pointer in the original). The consumers 0x7100ff9dcc / 0x7100ffbb24 read
// the first dword, a dword at +4, a halfword at +8 and a dword at +0xc; 0x710100215c copies all 16 bytes.
struct Unk_BgmControllerM8Arg {
    // The field battle BGM compares it (signed) with FieldBattleBgmInfo's Tension_Skip* values.
    s32 _0;
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

// Placeholder (vtable 0x71024fe958: D1 0x710100d5fc, D0 0x710100d600, slot 2 0x710100d8b4; 0x88 bytes): the boss
// BGM table of the spot BGM controller (Unk_710260f198::_90). Defined in sndPriestBossBgm.cpp (its TU).
class Unk_71024fe958 {
public:
    // Index of the boss BGM table (1..3: Golem, Giant, Sandworm; spilled like a SEAD_ENUM). Names unknown.
    SEAD_ENUM(Index, _0, _1, _2, _3, _4, _5)

    // 0x710100d5bc
    Unk_71024fe958();
    virtual ~Unk_71024fe958();
    // 0x710100d8b4
    virtual void m2();

    // 0x710100d604: takes the music infos of the Golem, Giant and Sandworm BGMs.
    void init(sead::Heap* heap);
    // 0x710100d694 (declared only; 460 B)
    void sub_710100D694();
    // 0x710100d860: clears _1c and _8.
    // 0x710100d874: stores the BGM and gives it the matching info.
    void sub_710100D874(Index idx, Unk_71024fe808* bgm);
    void sub_710100D860();

    /* 0x08 */ bool _8 = false;
    /* 0x0c */ u32 _c = 0;
    /* 0x10 */ u32 _10 = 0;
    /* 0x14 */ u16 _14 = 0;
    /* 0x18 */ u32 _18 = 0;
    /* 0x1c */ u32 _1c = 0;
    /* 0x20 */ sead::SafeArray<Unk_71024fe808*, 6> mBgms{};
    /* 0x50 */ sead::SafeArray<MusicInfo*, 6> mInfos{};
    u8 _80[8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024fe958, 0x88);

// RTTI typeInfo 0x710260f198, a BGM controller (sub_7100FFD7CC casts SoundMgr::_30->_48 to it): the spot BGM
// controller (BGM kinds 0, 1, 4, 2, 5). Its TU is 0x7100ffaf20..0x7100ffc100 (static initialiser): sndSpotBgmController.cpp.
class Unk_710260f198 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f198, Unk_71024fca78)
public:
    // 0x7100ffaf20 (0x130 bytes, created by Unk_SoundMgr30::sub_7100FF8464 for type 1).
    Unk_710260f198();
    // vtable 0x71024fcdb0 (D2 0x7100ffb368, ..., m12 0x7100ffbf40).
    ~Unk_710260f198() override;
    void m4(sead::Heap* heap) override;
    void m5() override;
    void m6(f32 fade_sec) override;
    void m7(f32 fade_sec) override;
    // 0x7100ffba00: passes the argument to the field battle BGM (kind 3) and its count to the castle BGM (kind 10).
    void m8(const Unk_BgmControllerM8Arg& arg) override;
    // 0x7100ffbb24: copies the argument into the boss BGM table.
    void m9(const Unk_BgmControllerM8Arg& arg) override;
    // 0x7100ffbb50: marks the field battle BGM (kind 3).
    void m10() override;
    void* m11() override { return _a8; }
    void m12() override {}

    // 0x7100ffafbc / 0x7100ffb2d4: the BGM delegates (keep / forget a created / deleted BGM).
    void sub_7100FFAFBC(Bgm* bgm);
    void sub_7100FFB2D4(Bgm* bgm);
    // 0x7100ffbd44 / 0x7100ffbdc0 / 0x7100ffbe0c / 0x7100ffbe38: as Unk_710260f0c0's entry functions, on the kind 17
    // (Unk_71024feae8, `use_a0`) or kind 16 (Unk_71024fefe8) BGM; the first one also allocates that BGM.
    void sub_7100FFBD44(s32 id, bool use_a0);
    void sub_7100FFBDC0(s32 id, bool use_a0);
    void sub_7100FFBE0C(s32 a, bool b, s32 id, bool use_a0);
    void sub_7100FFBE38(bool a, s32 id, bool use_a0);
    // 0x7100ffbbe4 (SpotBgmTriggerAction::enter_) / 0x7100ffbca0 (leave_): declared only.
    void sub_7100FFBBE4(Unk_SpotBgmInstance* instance);
    void sub_7100FFBCA0(Unk_SpotBgmInstance* instance);
    // 0x7100ffbea8 (declared only; lane1 s46): sets the byte at +0x20 of the child 4 (KokkoAngry::~KokkoAngry passes
    // false).
    void sub_7100FFBEA8(bool value);
    // 0x7100ffb5b0 / 0x7100ffb7e8 (declared only; m5's update steps).
    void sub_7100FFB5B0();
    void sub_7100FFB7E8();

    /* 0x90 */ Unk_71024fe958* mBossBgms = nullptr;
    /* 0x98 */ Unk_71024fefe8* _98 = nullptr;
    /* 0xa0 */ Unk_71024feae8* _a0 = nullptr;
    /* 0xa8 */ void* _a8;
    // 0x7100ffb7e8: 0 = no source volume, 1 = following the source, 2 = source lost (timer _b4 running).
    /* 0xb0 */ u32 _b0 = 0;
    /* 0xb4 */ f32 _b4 = 0.0f;
    /* 0xb8 */ aal::Group* mGroup = nullptr;
    /* 0xc0 */ aal::Handle _c0;
    /* 0xd0 */ aal::SimpleTimedFader _d0{0.0f};
    /* 0xe8 */ f32 _e8 = 1.0f;
    // Bit 0: started (m6 / m7); bit 2: cleared by m5 / m6 after a fade request.
    /* 0xec */ u8 _ec = 0;
    /* 0xf0 */ sead::Delegate1<Unk_710260f198, Bgm*> _f0{this, &Unk_710260f198::sub_7100FFAFBC};
    /* 0x110 */ sead::Delegate1<Unk_710260f198, Bgm*> _110{this, &Unk_710260f198::sub_7100FFB2D4};
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
    // 0..3, set from the controller types 6..9; m4 maps it to the BGM kinds 22, 24, 23, 25. A four-byte enum wrapper:
    // sub_7100FFE7A4 copies it to the stack and reloads it before switching (enumerator names unknown).
    SEAD_ENUM(Kind, _0, _1, _2, _3)
    Kind _94;
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
    // Called by SceneBgmCtrlAction::oneShot_.
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
// 0x7100ffed80 / 0x7100ffedc8 (placeholder names): `_8._80` / `_8._81` of the controller at SoundMgr::_30->_48
// (false if SoundMgr, _30 or the controller is null).
bool sub_7100FFED80();
bool sub_7100FFEDC8();
// 0x7100ffee10 (placeholder name; CSV nullsub_4329): empty in the release build. AdvanceTime::enter_ calls it before
// changing the time of day.
void sub_7100FFEE10();

// Placeholders (types unknown): SoundMgr::_30->_8 / _18 (returned by sub_7100FFD73C / sub_7100FFD76C).
class MusicDefinition;
// SoundMgr::_30->_18: one music info object per MusicInfoType (created by 0x710101b84c).
struct Unk_SoundMgr30_18 {
    // inline-only in the original; name is a guess (the Bgm constructors 0x7101012918, ... index the table with a
    // spilled enum whose stack slot is shared with later temporaries).
    MusicInfo* getInfo(MusicInfoType type) const { return mInfos[type]; }
    // inline-only in the original; name is a guess (init 0x710101b79c spills the type for the store like getInfo).
    void setInfo(MusicInfoType type, MusicInfo* info) { mInfos[type] = info; }

    // vtable 0x71024fc950: D1 0x7100ff8c08 (empty), D0 0x7100ff8c0c.
    virtual ~Unk_SoundMgr30_18();
    // 0x710101b79c: creates and initializes the 27 music infos.
    void init(sead::Heap* heap);
    // 0x710101b84c: creates the music info object of `type` (the original call does not set x0).
    MusicInfo* createInfo(sead::Heap* heap, MusicInfoType type);

    sead::SafeArray<MusicInfo*, 27> mInfos{};
};

struct Unk_SoundMgr30_240;

// Placeholder name (SoundMgr::_30; CSV snd::BgmMgr::ctor / init): the BGM side of the sound manager (vtable
// 0x71024fc918: D1 0x7100ff7e1c, D0 0x7100ff7ef0, 0x7100ff8338).
struct Unk_SoundMgr30 {
    Unk_SoundMgr30();
    virtual ~Unk_SoundMgr30();
    // 0x7100ff8338: loads the music definition (Sound/Music/MusicList.bmscdef) and creates _10 and _18 on `heap`.
    virtual void sub_7100FF8338(sead::Heap* heap);

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
    // 0x7100ff8a24: a speaker balance supplier whose handle is inactive, or null.
    Unk_SoundMgr30_30* sub_7100FF8A24();
    // 0x7100ff8774 (placeholder name): _10->_b4.
    u32 sub_7100FF8774() const;
    // 0x7100ff8aa0 / 0x7100ff8aac / 0x7100ff8ab8 (placeholder names): the tunables sUnk_71024FC940 (true),
    // sUnk_71024FC944 (0.894) and sUnk_71024FC948 (0.448); `this` is not read.
    bool sub_7100FF8AA0() const;
    f32 sub_7100FF8AAC() const;
    f32 sub_7100FF8AB8() const;
    // 0x7100ff89a0: a free entry of the pool at +0x20 (reset), or null.
    Unk_710260f248Entry* sub_7100FF89A0();

    /* 0x08 */ MusicDefinition* _8 = nullptr;
    /* 0x10 */ Unk_SoundMgr30_10* _10 = nullptr;
    /* 0x18 */ Unk_SoundMgr30_18* _18 = nullptr;
    // Pool of the sound object entries (0x7100ff89a0 hands out the unlinked ones).
    /* 0x20 */ sead::Buffer<Unk_710260f248Entry> mEntryPool;
    // The speaker balance suppliers (0x7100ff8a24 hands out the ones whose handle is inactive).
    /* 0x30 */ sead::Buffer<Unk_SoundMgr30_30> mSpeakerBalanceSuppliers;
    /* 0x40 */ BgmControllerType _40;
    /* 0x48 */ Unk_71024fca78* _48 = nullptr;
    // Native constructor FF7D08 and fade controls independently establish these floats.
    f32 _50 = 2.0;
    f32 _54 = 2.2;
    f32 _58 = 1.0;
    /* 0x60 */ aal::SimpleTimedFader _60{0.0};
    /* 0x78 */ Unk_71010073f4* _78 = nullptr;
    // The ExpHeap created by init (0x7100ff7f14); destroyed by the destructor.
    /* 0x80 */ sead::Heap* mHeap = nullptr;
    u8 _88 = 0;
    // Skips the controller / _78 / _10 / fader updates in 0x7100ff88d0.
    bool _89 = false;
    // The sound objects being updated (0x7100ff88d0 removes the finished ones).
    sead::FixedObjList<Unk_710260f248*, 16> mObjects;
    /* 0x240 */ Unk_SoundMgr30_240* _240 = nullptr;
    u16 _248 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_SoundMgr30, 0x250);

// 0x7100ffd71c (32 B): `SoundMgr::instance()->_30`, or null without a SoundMgr. Placeholder name.
Unk_SoundMgr30* sub_7100FFD71C();
// 0x7100ffd73c / 0x7100ffd76c (24 B): `SoundMgr::instance()->_30->_8` / `->_18`. Placeholder names.
MusicDefinition* sub_7100FFD73C();
Unk_SoundMgr30_18* sub_7100FFD76C();

// 0x7100ffd754 (24 B): `SoundMgr::instance()->_30->_10`.
Unk_SoundMgr30_10* sub_7100FFD754();

struct Unk_SoundMgr30_240 {
    // Deleted through slot 1 by Unk_SoundMgr30's destructor (declared only).
    virtual ~Unk_SoundMgr30_240();
    // 0x71012be0a4 (400 B) / 0x71012be234 (96 B), declared only: register / unregister a sound object.
    void sub_71012BE0A4(Unk_710260f248* obj);
    void sub_71012BE234(Unk_710260f248* obj);
};
// 0x7100fff124 (24 B): `SoundMgr::instance()->_30->_240` (no null checks). Placeholder name.
Unk_SoundMgr30_240* sub_7100FFF124();

// 0x7100ffd784 (24 B): `SoundMgr::instance()->_30->_78`.
Unk_71010073f4* sub_7100FFD784();

}  // namespace ksys::snd

// vtable 0x71024ff268 (17 slots): the castle BGM ("CastleBgm"; constructor 0x710101320c, 0x210 bytes; its TU
// 0x710101320c..0x7101013c4c is sndBgmCastle.cpp).
class Unk_71024ff268 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024ff268, ksys::snd::Unk_71025ce380)
public:
    explicit Unk_71024ff268(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024ff268() override;
    // 0x710101330c (CSV snd::BgmCastle::m5; declared only, 900 B)
    void m5() override;
    bool m10() override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    void hm15() override;

    // Applies the two faders to the volumes of the "Castle" entry's three parts (inlined into hm14 / hm15).
    void updateEntryVolumes() {
        if (!mEntry || !mEntry->sub_7100FF6DF4(this))
            return;
        const f32 inside = _1d0.getValue();
        mEntry->sub_7100FF6A50(0, 1.0f - inside);
        mEntry->sub_7100FF6A50(1, inside);
        mEntry->sub_7100FF6A50(2, _1f0.getValue());
    }

    ksys::snd::CastleBgmInfo* mInfo = nullptr;
    // Play state (0 stopped, 1 playing, 2 waiting to fade out, 3 fading out) driven by _1a8.
    u32 _198 = 0;
    // Inside mix state (0 outside, 1 waiting, 2 fading in, 3 inside, 4 fading out).
    u32 _19c = 0;
    ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
    bool _1a8 = false;
    f32 _1ac = 0;
    f32 _1b0 = 0;
    aal::SimpleTimedFader _1b8{1.0};
    aal::SimpleTimedFader _1d0{0.0};
    // Battle request count and battle part state (0 off, 1 fading in, 2 on, 3 fading out).
    s32 _1e8 = 0;
    u32 _1ec = 0;
    aal::SimpleTimedFader _1f0{0.0};
    f32 _208 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024ff268, 0x210);

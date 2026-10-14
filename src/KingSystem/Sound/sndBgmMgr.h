#pragma once

#include <basis/seadTypes.h>
#include <aal/aalTimedFader.h>
#include <container/seadOffsetList.h>
#include <container/seadObjList.h>
#include <prim/seadDelegate.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

struct Unk_SpotBgmHandle;

namespace sead {
class TextWriter;
}

namespace uking::action {
class SoundOcclusionTagAction;
}

class Unk_7102500a00;

namespace ksys::snd {

// Placeholder name (`SoundMgr::_30->_78`, see sub_7100FFD784; the BGM interface used by the EventBgm* actions). Only the
// methods those actions call are declared (declaration only).
class Unk_SoundMgr30_78 {
public:
    // 0x71010078a0 (100 B): starts the BGM `name`.
    void sub_71010078A0(const sead::SafeString& name);
    // 0x7101007904 (92 B): stops the BGM `name` with a fade of `fade_sec` seconds.
    void sub_7101007904(f32 fade_sec, const sead::SafeString& name);
    void sub_7101007A08(f32 fade_sec);
    void sub_7101007AA0(f32 fade_sec);
    bool sub_7101007C14();
    bool sub_7101007C90();
};

// RTTI root at 0x71025ce360; primary vtable at 0x71024fc8a0.
class Bgm {
public:
    virtual ~Bgm() = default;
    SEAD_RTTI_BASE(Bgm)

    virtual void m4();
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

protected:
    friend class Unk_710260f160;

    bool mActive;
    u8 _9[3];
    s32 _c;
};
KSYS_CHECK_SIZE_NX150(Bgm, 0x10);

// Intermediate BGM RTTI typeInfo 0x71025ce380, derived from Bgm.
class Unk_71025ce380 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71025ce380, Bgm)
};

// RTTI typeInfo 0x710260f278, derived from Unk_71025ce380 (sub_7100FFDD38 casts BGM kind 2 to it).
class Unk_710260f278 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f278, Unk_71025ce380)
};

// RTTI typeInfo 0x710260f2a8, derived from Bgm (sub_7100FFE094 casts BGM kind 15 to it).
class Unk_710260f2a8 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_710260f2a8, Bgm)
};

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
class Unk_710260f288 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f288, Unk_71025ce380)
};

// RTTI typeInfo 0x710260f048, derived from Unk_71025ce380 (sub_7100FFDFDC casts BGM kind 14 to it).
class Unk_710260f048 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f048, Unk_71025ce380)
public:
    // The assassin boss BGM (was Unk_7100ffdfdc in Game/AI/aiUnk_7100FFDFDC.h).
    // 0x7100ff61bc (4 B, empty; CSV nullsub_4300)
    void sub_7100FF61BC();
    void sub_7100FF61C0();
    void sub_7100FF6220();
    void sub_7100FF6268();
};

// RTTI typeInfo 0x710260f1a8, derived from Bgm (sub_7100FFE14C casts BGM kind 5 to it).
class Unk_710260f1a8 : public Bgm {
    SEAD_RTTI_OVERRIDE(Unk_710260f1a8, Bgm)
};

// Four-byte practice-state argument, passed by reference to sub_71010267A8.
struct Unk_71010267A8 {
    s32 value;
};
// GuardianMini practice BGM RTTI typeInfo 0x710260f228.
class Unk_710260f228 : public Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710260f228, Unk_71025ce380)
public:
    void sub_71010267A8(const Unk_71010267A8& state);
    // 0x7101026888 (called by Unk_710260f218::m10).
    void sub_7101026888();
};

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
    void sub_7100FF7920(s32 kind, sead::Heap* heap);
    void sub_7100FF7BE0(Unk_7100FF7BE0 state);
    Bgm* sub_7100FF7C74(s32 kind);

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

// The RTTI root of the BGM controller family (vtable 0x71024fca78). `_8` is common to the family: the helpers
// sub_7100FFDD38 etc. call `_48->_8.sub_7100FF7C74()` on the base pointer without a cast. The controllers derive from
// it directly (their checkDerivedRuntimeTypeInfo tests their own typeInfo and then this class's).
class Unk_71024fca78 {
public:
    virtual ~Unk_71024fca78();
    SEAD_RTTI_BASE(Unk_71024fca78)

    // Slots 4-7 are pure in the original vtable; 8-12 have empty or `return nullptr` default bodies.
    virtual void m4(sead::Heap* heap) = 0;
    virtual void m5() = 0;
    virtual void m6(f32 fade_sec) = 0;
    virtual void m7(f32 fade_sec) = 0;
    virtual void m8(const Unk_BgmControllerM8Arg& arg) {}
    virtual void m9() {}
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
};
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
};
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
struct Unk_SoundMgr30_8;
struct Unk_SoundMgr30_18;

// Placeholder name (SoundMgr::_30): the BGM side of the sound manager.
struct Unk_SoundMgr30 {
    // 0x7100ff8804 (declared only; 164 B): called by SoundMgr::sub_71011FC288.
    void sub_7100FF8804();
    void sub_7100FF85E0();
    void sub_7100FF8684(s32 fade_type);
    void sub_7100FF8780(s32 fade_type);
    void sub_7100FF88A8(s32 fade_type);
    void sub_7100FF8AC4(s32 fade_type);

    u8 _0[0x8];
    /* 0x08 */ Unk_SoundMgr30_8* _8;
    /* 0x10 */ Unk_SoundMgr30_10* _10;
    /* 0x18 */ Unk_SoundMgr30_18* _18;
    u8 _20[0x28];
    /* 0x48 */ Unk_71024fca78* _48;
    // Native constructor FF7D08 and fade controls independently establish these floats.
    f32 _50;
    f32 _54;
    f32 _58;
    u8 _5c[4];
    /* 0x60 */ aal::SimpleTimedFader _60;
    /* 0x78 */ Unk_SoundMgr30_78* _78;
    u8 _80[8];
    u8 _88;
    u8 _89[7];
};

// 0x7100ffd71c (32 B): `SoundMgr::instance()->_30`, or null without a SoundMgr. Placeholder name.
Unk_SoundMgr30* sub_7100FFD71C();
// 0x7100ffd73c / 0x7100ffd76c (24 B): `SoundMgr::instance()->_30->_8` / `->_18`. Placeholder names.
Unk_SoundMgr30_8* sub_7100FFD73C();
Unk_SoundMgr30_18* sub_7100FFD76C();

// 0x7100ffd754 (24 B): `SoundMgr::instance()->_30->_10`.
Unk_SoundMgr30_10* sub_7100FFD754();

// 0x7100ffd784 (24 B): `SoundMgr::instance()->_30->_78`.
Unk_SoundMgr30_78* sub_7100FFD784();

}  // namespace ksys::snd

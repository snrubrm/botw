#pragma once

#include <basis/seadTypes.h>
#include <aal/aalTimedFader.h>
#include <container/seadOffsetList.h>
#include <prim/seadSafeString.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>

struct Unk_SpotBgmHandle;

namespace ksys::snd {

// Placeholder name (`SoundMgr::_30->_78`, see sub_7100FFD784; the BGM interface used by the EventBgm* actions). Only the
// methods those actions call are declared (declaration only).
class Unk_SoundMgr30_78 {
public:
    // 0x71010078a0 (100 B): starts the BGM `name`.
    void sub_71010078A0(const sead::SafeString& name);
    // 0x7101007904 (92 B): stops the BGM `name` with a fade of `fade_sec` seconds.
    void sub_7101007904(f32 fade_sec, const sead::SafeString& name);
};

// CSV Bgm RTTI root (typeInfo 0x71025ce360). The remaining interface and layout are not modeled.
class Bgm {
public:
    virtual ~Bgm();
    SEAD_RTTI_BASE(Bgm)
};

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
};

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
    void sub_7100FF7BE0(Unk_7100FF7BE0 state);
    Bgm* sub_7100FF7C74(s32 kind);
    u8 _0[0x88];
};

// The RTTI root of the BGM controller family (vtable 0x71024fca78). `_8` is common to the family: the helpers
// sub_7100FFDD38 etc. call `_48->_8.sub_7100FF7C74()` on the base pointer without a cast.
class Unk_71024fca78 {
public:
    virtual ~Unk_71024fca78();
    SEAD_RTTI_BASE(Unk_71024fca78)

    Unk_7100ff7444 _8;
};

// RTTI typeInfo 0x710260f130, SoundMgr::_30->_48.
class Unk_710260f130 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f130, Unk_71024fca78)
public:
    void sub_7100FFA1E0(bool value);
    bool _90;
    bool _91;
    bool _92;
};
Unk_710260f130* sub_7100FFD9D0();

// RTTI typeInfo 0x710260f198, a BGM controller (sub_7100FFD7CC casts SoundMgr::_30->_48 to it).
class Unk_710260f198 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f198, Unk_71024fca78)
};
Unk_710260f198* sub_7100FFD7CC();

// RTTI typeInfo 0x710260f1f8, a BGM controller (sub_7100FFD878 casts SoundMgr::_30->_48 to it).
class Unk_710260f1f8 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f1f8, Unk_71024fca78)
};
Unk_710260f1f8* sub_7100FFD878();

// RTTI typeInfo 0x710260f150, a BGM controller (sub_7100FFD924 casts SoundMgr::_30->_48 to it).
class Unk_710260f150 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f150, Unk_71024fca78)
};
Unk_710260f150* sub_7100FFD924();

// RTTI typeInfo 0x710260f0c0, a BGM controller (sub_7100FFDB28 casts SoundMgr::_30->_48 to it).
class Unk_710260f0c0 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f0c0, Unk_71024fca78)
};
Unk_710260f0c0* sub_7100FFDB28();

// RTTI typeInfo 0x710260f160, a BGM controller (sub_7100FFDBD4 casts SoundMgr::_30->_48 to it).
class Unk_710260f160 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f160, Unk_71024fca78)
};
Unk_710260f160* sub_7100FFDBD4();

// RTTI typeInfo 0x710260f218; the GuardianMini practice BGM controller.
// Its remaining layout is not modeled yet.
class Unk_710260f218 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f218, Unk_71024fca78)
public:
    void sub_7100FFC7F4();
    void sub_7100FFC894();
    void sub_7100FFC934();
};
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

    u8 _0[0x8];
    /* 0x08 */ Unk_SoundMgr30_8* _8;
    /* 0x10 */ Unk_SoundMgr30_10* _10;
    /* 0x18 */ Unk_SoundMgr30_18* _18;
    u8 _20[0x28];
    /* 0x48 */ Unk_71024fca78* _48;
    u8 _50[0x10];
    /* 0x60 */ aal::SimpleTimedFader _60;
    /* 0x78 */ Unk_SoundMgr30_78* _78;
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

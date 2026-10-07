#pragma once

#include <basis/seadTypes.h>
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

// The RTTI root of the BGM controller family (vtable 0x71024fca78).
class Unk_71024fca78 {
public:
    virtual ~Unk_71024fca78();
    SEAD_RTTI_BASE(Unk_71024fca78)
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

// RTTI typeInfo 0x710260f130, SoundMgr::_30->_48.
class Unk_710260f130 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f130, Unk_71024fca78)
public:
    void sub_7100FFA1E0(bool value);
    Unk_7100ff7444 _8;
    bool _90;
    bool _91;
    bool _92;
};
Unk_710260f130* sub_7100FFD9D0();

// RTTI typeInfo 0x710260f218; the GuardianMini practice BGM controller.
// Its remaining layout is not modeled yet.
class Unk_710260f218 : public Unk_71024fca78 {
    SEAD_RTTI_OVERRIDE(Unk_710260f218, Unk_71024fca78)
public:
    void sub_7100FFC7F4();
    void sub_7100FFC894();
    void sub_7100FFC934();
    Unk_7100ff7444 _8;
};
Unk_710260f218* sub_7100FFDA7C();

// Placeholder name (SoundMgr::_30): the BGM side of the sound manager.
struct Unk_SoundMgr30 {
    // 0x7100ff8804 (declared only; 164 B): called by SoundMgr::sub_71011FC288.
    void sub_7100FF8804();

    u8 _0[0x10];
    /* 0x10 */ Unk_SoundMgr30_10* _10;
    u8 _18[0x30];
    /* 0x48 */ Unk_71024fca78* _48;
    u8 _50[0x28];
    /* 0x78 */ Unk_SoundMgr30_78* _78;
};

// 0x7100ffd754 (24 B): `SoundMgr::instance()->_30->_10`.
Unk_SoundMgr30_10* sub_7100FFD754();

// 0x7100ffd784 (24 B): `SoundMgr::instance()->_30->_78`.
Unk_SoundMgr30_78* sub_7100FFD784();

}  // namespace ksys::snd

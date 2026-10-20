#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace gsys { class Model; }
namespace ksys { class OverlayArena; }

// Terrain editor RTTI root, vtable 0x71024f13f0.
class Unk_71024f13f0 {
    SEAD_RTTI_BASE(Unk_71024f13f0)
public:
    virtual ~Unk_71024f13f0();
};

// Editor base vtable 0x7102504260; constructor 0x710107e724.
class Unk_7102504260 : public Unk_71024f13f0 {
    SEAD_RTTI_OVERRIDE(Unk_7102504260, Unk_71024f13f0)
public:
    Unk_7102504260();
    ~Unk_7102504260() override;
    void sub_710107E900(gsys::Model* model, bool visible);
    // Six terrain callers pass their editor base at +0x20; false in this release.
    bool sub_710107EC48() const;
    // 0x710107ed78 / 0x710107ed84: the hostio names. Slots 4 / 5 of the class vtable (the original
    // class is the terrain editor; the strings are "Terrain" and "地形編集").
    virtual const char* getName() const { return "Terrain"; }
    virtual const char* getJpName() const { return "地形編集"; }
    virtual void m6();
    virtual bool m7() { return false; }
    virtual void m8();
    virtual bool m9();
    virtual void m10();
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13() {}
    virtual void m14() {}
    virtual void m15() {}
    virtual void m16() {}
    virtual void m17() {}
    virtual void m18() {}

    // Constructor 0x710107e724 writes through +0x2d8. The controller/debug state
    // at +0x38 / +0x48 retains opaque storage until its lifetime is modelled.
    u8 _8[0x2c0 - 0x8];
    // Terrain image request arenas (absolute +0x2e0 / +0x2e8 in Terrain).
    ksys::OverlayArena* mTerrainArena;
    ksys::OverlayArena* mSteraArena;
    u64 _2d0;
    u64 _2d8;
};
KSYS_CHECK_SIZE_NX150(Unk_7102504260, 0x2e0);

// Secondary Terrain interface at +0x20, vtable 0x710250fb18.
class Unk_710250fb18 : public Unk_7102504260 {
    SEAD_RTTI_OVERRIDE(Unk_710250fb18, Unk_7102504260)
public:
    ~Unk_710250fb18() override;
    virtual void m19() {}
    virtual void m20();
    virtual bool m21() { return false; }
    virtual void m22() {}
    virtual void m23() {}
    bool m9() override { return false; }
    void m10() override {}
    void m14() override {}
    void m16() override {}
    void m17() override {}
    void m18() override {}
};

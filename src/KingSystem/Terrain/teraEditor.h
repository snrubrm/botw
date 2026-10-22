#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/System/GameTool.h"
#include "KingSystem/Utils/Types.h"

namespace gsys { class Model; }
namespace ksys { class OverlayArena; }

// Editor base vtable 0x7102504260; constructor 0x710107e724. The constructor stores the hostio::Node
// vtable (0x7102504340) at +0x38, after the base's tail padding.
class Unk_7102504260 : public Unk_71024f13f0, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(Unk_7102504260, Unk_71024f13f0)
public:
    Unk_7102504260();
    ~Unk_7102504260() override;
    void sub_710107E900(gsys::Model* model, bool visible);
    // Six terrain callers pass their editor base at +0x20; false in this release.
    bool sub_710107EC48() const;
    // 0x710107ed78 / 0x710107ed84: the hostio names. Slots 4 / 5 of the class vtable (the original
    // class is the terrain editor; the strings are "Terrain" and "地形編集").
    const char* getName() const override { return "Terrain"; }
    const char* getJpName() const override { return "地形編集"; }
    void m6() override;
    bool m9() override;
    void m10() override;
    virtual void m17() {}
    virtual void m18() {}
    // Slots 19 - 23 are pure in this class (the original vtable has nulls there); Terrain overrides all five.
    virtual void m19() = 0;
    virtual void m20(f32 delta) = 0;
    virtual bool m21() = 0;
    virtual void m22() = 0;
    virtual void m23() = 0;

    // Constructor 0x710107e724 writes through +0x2d8. The controller/debug state
    // at +0x48 retains opaque storage until its lifetime is modelled.
    // 0x40: the constructor stores 2; m6 copies it to the SeadController's _1ec.
    u32 _40 = 2;
    u8 _44[0x2c0 - 0x44];
    // Terrain image request arenas (absolute +0x2e0 / +0x2e8 in Terrain).
    ksys::OverlayArena* mTerrainArena;
    ksys::OverlayArena* mSteraArena;
    u64 _2d0;
    u64 _2d8;
};
KSYS_CHECK_SIZE_NX150(Unk_7102504260, 0x2e0);

// Secondary Terrain interface at +0x20, vtable 0x710250fb18. It has no RTTI of its own (Terrain's
// checkDerivedRuntimeTypeInfo goes from Terrain straight to Unk_7102504260), and Terrain overrides all
// of its new slots, so its own vtable is never emitted.
class Unk_710250fb18 : public Unk_7102504260 {
public:
    void m19() override {}
    void m20(f32 delta) override;
    bool m21() override { return false; }
    void m22() override {}
    void m23() override {}
};

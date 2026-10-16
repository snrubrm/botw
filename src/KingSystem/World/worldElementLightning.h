#pragma once

#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/Chemical/chmElement.h"
#include "KingSystem/Utils/Types.h"

// vtable 0x710251f5c8: the lightning shockwave element (constructor inlined into
// Unk_71024dd490::sub_71012FE4B4; destructors 0x71012fde74 / 0x71012fdebc).
class ElementLightningShockwave : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(ElementLightningShockwave, Unk_7102518688)
public:
    ~ElementLightningShockwave() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override {}

    /* 0x48 */ ksys::phys::RigidBody* mRigidBody2;
    /* 0x50 */ ElementLightningCreateArg mArg;
};
KSYS_CHECK_SIZE_NX150(ElementLightningShockwave, 0x60);

// vtable 0x710251f710: the lightning fire element (constructor inlined into
// Unk_71024dd490::sub_71012FE6E0; destructors 0x71012fe10c / 0x71012fe154).
class ElementLightningFire : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(ElementLightningFire, Unk_7102518688)
public:
    ~ElementLightningFire() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override {}
    // Own overrides in the original (vtable 0x710251f710 slots 36-38 point to 0x71010c6ca0 / ca4 / cac).
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    /* 0x48 */ ksys::phys::RigidBody* mRigidBody2;
    /* 0x50 */ ElementLightningCreateArg mArg;
};
KSYS_CHECK_SIZE_NX150(ElementLightningFire, 0x60);

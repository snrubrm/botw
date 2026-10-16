#pragma once

#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include <container/seadPtrArray.h>

#include <prim/seadRuntimeTypeInfo.h>
#include <nn/ui2d/TextureInfo.h>
#include "Game/Actor/aiUnk_71025afb58.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/gameStageBinder.h"
#include "Game/gameUnkRttiClasses.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/Chemical/chmElement.h"
#include "KingSystem/Event/evtS7.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Resource/resResourceJpg.h"
#include "KingSystem/System/Controller.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include <aal/aalSpatialCalculator.h>
#include <gsys/gsysIModelProcedural.h>
#include <gsys/gsysModelUnit.h>
#include <common/aglDrawContext.h>
#include <common/aglGPUMemBlock.h>
#include "Game/gameUnk_71024739f8.h"
#include "controller/seadControllerAddon.h"
#include "framework/seadSingleScreenMethodTreeMgr.h"
#include "framework/seadTaskParameter.h"
#include "resource/seadArchiveRes.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <aal/aalAuxBusDataSerialCtrl.h>
#include "framework/nx/seadGameFrameworkNx.h"
#include "framework/seadCalculateTask.h"
#include "framework/seadTask.h"
#include "framework/seadTaskBase.h"
#include "Game/Actor/actUnk_7102366570.h"
#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include <aal/aalISpeakerBalanceSupplier.h>

namespace aal {
class Shape;
}

// Placeholder classes generated from the vtables of the original (genskel.py in the botw-tools scratch). Each class
// is named after the address of its vtable and declares only what the vtable shows: the sead RTTI pair with the
// parent named by the Derive<Parent> vtable its RTTI getter loads, the destructor and, for slots past the parent's,
// bare-return bodies where the original slot is a bare return (other new slots are declared only). The destructor is
// defined in the source file of the class's address neighbours (the key function there emits the vtable and RTTI).
// Members are not known yet; destructors that destroy members in the original are marked NON_MATCHING.

// vtable 0x710238b148 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710238b148 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_710238b148, Unk_71025afb58)
public:
    ~Unk_710238b148() override;
};

// vtable 0x710247faf0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247faf0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_710247faf0, uking::ui::Unk_7102474e38)
public:
    ~Unk_710247faf0() override;
    void m5() override {}
};

// vtable 0x710247fbc0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247fbc0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_710247fbc0, uking::ui::Unk_7102474e38)
public:
    ~Unk_710247fbc0() override;
    void m5() override {}
};

// vtable 0x71024826c0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024826c0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024826c0, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024826c0() override;
    void m5() override {}
};

// vtable 0x7102482790 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102482790 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_7102482790, uking::ui::Unk_7102474e38)
public:
    ~Unk_7102482790() override;
};

// vtable 0x71024855a8 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024855a8 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024855a8, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024855a8() override;
};

// vtable 0x71024975d0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024975d0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024975d0, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024975d0() override;
};

// vtable 0x71024dcf48 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024dcf48 : public Unk_71024dcf80 {
    SEAD_RTTI_OVERRIDE(Unk_71024dcf48, Unk_71024dcf80)
public:
    ~Unk_71024dcf48() override;
};

// vtable 0x71024f13f0 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024f13f0 {
    SEAD_RTTI_BASE(Unk_71024f13f0)
public:
    virtual ~Unk_71024f13f0();
};

// vtable 0x7102519378 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519378 {
    SEAD_RTTI_BASE(Unk_7102519378)
public:
    virtual ~Unk_7102519378();
    virtual void m4() {}
};

// vtable 0x7102357ab0 (10 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102357ab0 : public uking::act::Unk_710244eaa0 {
    SEAD_RTTI_OVERRIDE(Unk_7102357ab0, uking::act::Unk_710244eaa0)
public:
    ~Unk_7102357ab0() override;

    // 0x710001ba54 / 0x710001ba90: the RootNode / SpineNode bone names from the rider's HorseRider GParam object
    // (empty string without one).
    const sead::SafeString& getRootNodeName() const;
    const sead::SafeString& getSpineNodeName() const;
};

// vtable 0x7102450fe0 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102450fe0 {
    SEAD_RTTI_BASE(Unk_7102450fe0)
public:
    virtual ~Unk_7102450fe0();
    virtual void* m4() { return nullptr; }
    virtual void m5();
    virtual void m6();
    virtual void m7() {}
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102451c48 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102451c48 : public uking::act::DamageCallback {
    SEAD_RTTI_OVERRIDE(Unk_7102451c48, uking::act::DamageCallback)
public:
    ~Unk_7102451c48() override;
};

// vtable 0x710245bf30 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710245bf30 {
    SEAD_RTTI_BASE(Unk_710245bf30)
public:
    virtual ~Unk_710245bf30();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x710245c368 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_710245c368 : public uking::StageArg {
    SEAD_RTTI_OVERRIDE(Unk_710245c368, uking::StageArg)
public:
    ~Unk_710245c368() override;
};

// vtable 0x710246cb78 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710246cb78 : public ksys::evt::S7 {
    SEAD_RTTI_OVERRIDE(Unk_710246cb78, ksys::evt::S7)
public:
    ~Unk_710246cb78() override;
};

// vtable 0x710246d1e8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710246d1e8 {
    SEAD_RTTI_BASE(Unk_710246d1e8)
public:
    virtual ~Unk_710246d1e8();
};

// vtable 0x71024742f0 (35 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024742f0 {
    SEAD_RTTI_BASE(Unk_71024742f0)
public:
    virtual ~Unk_71024742f0();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9() {}
    virtual bool m10() { return false; }
    virtual void m11();
    virtual void m12();
    virtual void m13() {}
    virtual bool m14() { return false; }
    virtual void m15();
    virtual void m16();
    virtual void m17() {}
    virtual bool m18() { return false; }
    virtual void m19();
    virtual void m20();
    virtual void m21() {}
    virtual bool m22() { return false; }
    virtual void m23() {}
    virtual void m24();
    virtual void m25() {}
    virtual bool m26() { return false; }
    virtual void m27();
    virtual void m28();
    virtual void m29() {}
    virtual bool m30() { return false; }
    virtual void m31();
    virtual void m32() {}
    virtual void m33() {}
    virtual bool m34() { return false; }
};

// vtable 0x7102474fd8 (6 slots); placeholder generated from the vtable (genskel.py).
// ScreenPauseMenuInfo's destructor destroys two objects of this family (0x130 bytes each, at 0x36e0 / 0x3810).
// The original destructor is inline (its D2 copy 0x71009479c4 sits in Unk_71024750c8's TU and both vtables use it;
// D0 0x71009453bc is in another TU); it is defined out of line here so that the vtable (and RTTI rows) stay emitted.
class Unk_7102474fd8 {
    SEAD_RTTI_BASE(Unk_7102474fd8)
public:
    virtual ~Unk_7102474fd8();
    virtual void m4();
    virtual s32 m5() { return 0; }

    u8 _8[0x60 - 0x8];
    /* 0x60 */ sead::PtrArrayImpl _60;
};

// vtable 0x7102475050 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475050 : public Unk_7102474fd8 {
    SEAD_RTTI_OVERRIDE(Unk_7102475050, Unk_7102474fd8)
public:
    ~Unk_7102475050() override;
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    s32 m5() override { return 5; }
};

// vtable 0x71024750c8 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024750c8 : public Unk_7102474fd8 {
    SEAD_RTTI_OVERRIDE(Unk_71024750c8, Unk_7102474fd8)
public:
    ~Unk_71024750c8() override;
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11() {}
    virtual void m12() {}
    s32 m5() override { return 10; }
};

// vtable 0x71024756f0 (33 slots): a map marker like Unk_71024755d8 (same layout; defined in uiMapMarker.cpp).
class Unk_71024756f0 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_71024756f0, uking::ui::Unk_71024754c0)
public:
    ~Unk_71024756f0() override;
    void m9() override;
    void m11() override;
    void m12() override;
    void m21() override;
    void m29(uking::ui::Unk_710095192c* entry) override;
    void m31() override;
    void m32() override;
    // 0x7100952c00 (CSV unnamed; not decompiled): called at the end of m29 (as Unk_71024755d8::sub_71009520D4)
    void sub_7100952C00();

    sead::SafeString _68;
    ksys::gdt::FlagHandle _78;
    ksys::gdt::FlagHandle _7c;
    ksys::gdt::FlagHandle _80;
    ksys::gdt::FlagHandle _84;
};
static_assert(sizeof(Unk_71024756f0) == 0x88);

// vtable 0x7102475920 (33 slots): a map marker with a name and one bool flag handle (defined in uiMapMarker.cpp).
class Unk_7102475920 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475920, uking::ui::Unk_71024754c0)
public:
    ~Unk_7102475920() override;
    void m9() override;
    void m21() override;
    void m29(uking::ui::Unk_710095192c* entry) override;
    void m31() override;
    void m32() override;
    // 0x7100953b50 (CSV unnamed; not decompiled): called at the end of m29
    void sub_7100953B50();

    sead::SafeString _68;
    ksys::gdt::FlagHandle _78;
};

// vtable 0x7102475a38 (33 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475a38 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475a38, uking::ui::Unk_71024754c0)
public:
    ~Unk_7102475a38() override;
};

// vtable 0x7102475b50 (33 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475b50 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475b50, uking::ui::Unk_71024754c0)
public:
    ~Unk_7102475b50() override;
};

// vtable 0x7102475e68 (29 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475e68 : public uking::ui::UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102475e68, uking::ui::UiSubsys1Entry)
public:
    ~Unk_7102475e68() override;

    u8 _50[0x7c - 0x50];
    /* 0x7c */ s32 _7c;  // 0 / 1 select the frame of Unk_7102478ab0's animator
};

// vtable 0x71024795a8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024795a8 : public uking::ui::Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024795a8, uking::ui::Unk_71025d9170)
public:
    ~Unk_71024795a8() override;
};

// vtable 0x7102479640 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102479640 : public uking::ui::Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479640, uking::ui::Unk_71025d9170)
public:
    ~Unk_7102479640() override;
};

// vtable 0x71024796d8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024796d8 : public uking::ui::Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_71024796d8, uking::ui::Unk_71025d9170)
public:
    ~Unk_71024796d8() override;
};

// vtable 0x7102479770 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102479770 : public uking::ui::Unk_71025d9170 {
    SEAD_RTTI_OVERRIDE(Unk_7102479770, uking::ui::Unk_71025d9170)
public:
    ~Unk_7102479770() override;
};

// vtable 0x710247e8c0 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710247e8c0 : public ksys::res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_710247e8c0, ksys::res::Resource)
public:
    // 0x71009ca980 (CSV unnamed)
    Unk_710247e8c0();
    ~Unk_710247e8c0() override;
    s32 getLoadDataAlignment() const override { return 8192; }

    // A UI texture resource (the item icons, e.g. UI/StockItem/*.bitemico): the parse step (0x71009caa34) sets up
    // the texture from the g3d resource file and stores its size in mTexInfo.
    /* 0x38 */ nn::ui2d::ExternalTextureInfo mTexInfo;
    /* 0x50 */ void* _50 = nullptr;  // nn::g3d::ResFile
    /* 0x58 */ bool _58 = false;
};

// vtable 0x710247e960 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247e960 : public ksys::res::Context {
    SEAD_RTTI_OVERRIDE(Unk_710247e960, ksys::res::Context)
public:
    ~Unk_710247e960() override;
};

// vtable 0x710247e990 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247e990 : public ksys::TaskData {
    SEAD_RTTI_OVERRIDE(Unk_710247e990, ksys::TaskData)
public:
    ~Unk_710247e990() override;
};

// vtable 0x710247ec28 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247ec28 : public ksys::res::ResourceJpg {
    SEAD_RTTI_OVERRIDE(Unk_710247ec28, ksys::res::ResourceJpg)
public:
    ~Unk_710247ec28() override;

protected:
    // Native table 247EC28 overrides the JPEG denominator query with 9CD4A8.
    u32 sub_71009CD408() override { return 1; }
};

// vtable 0x710247ed28 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710247ed28 : public ksys::res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_710247ed28, ksys::res::Resource)
public:
    Unk_710247ed28();
    ~Unk_710247ed28() override;
    // Native resource and factory alignment queries both return 0x2000.
    static constexpr size_t cLoadDataAlignment = 0x2000;
    s32 getLoadDataAlignment() const override;
    bool m2_() override;

protected:
    void doCreate_(u8* data, u32 size, sead::Heap* heap) override;
    void onDestroy_() override;

    // Complete 9CE1C8/A80F20 producers and A816D8 texture-info consumer.
    nn::ui2d::ExternalTextureInfo _38;
    nn::g3d::ResFile* _50 = nullptr;
    bool _58 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710247ed28, 0x60);

// vtable 0x710247edc8 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710247edc8 : public ksys::res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_710247edc8, ksys::res::Resource)
public:
    Unk_710247edc8();
    ~Unk_710247edc8() override;
    // Native resource and factory alignment queries both return 0x2000.
    static constexpr size_t cLoadDataAlignment = 0x2000;
    s32 getLoadDataAlignment() const override;
    bool m2_() override;

protected:
    void doCreate_(u8* data, u32 size, sead::Heap* heap) override;
    void onDestroy_() override;

    // Complete 9CE54C/A80D08 producers and A816D8/9A4DDC consumers.
    nn::ui2d::ExternalTextureInfo _38;
    nn::g3d::ResFile* _50 = nullptr;
    bool _58 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710247edc8, 0x60);

// vtable 0x7102496f70 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102496f70 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_7102496f70, uking::ui::Unk_7102474e38)
public:
    ~Unk_7102496f70() override;
};

// vtable 0x71024993a0 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024993a0 {
    SEAD_RTTI_BASE(Unk_71024993a0)
public:
    virtual ~Unk_71024993a0();
    virtual void m4() {}
    virtual void m5() {}
};

// vtable 0x71024993e0 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024993e0 : public Unk_71024993a0 {
    SEAD_RTTI_OVERRIDE(Unk_71024993e0, Unk_71024993a0)
public:
    ~Unk_71024993e0() override;
};

// vtable 0x7102499a28 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102499a28 : public Unk_71024993a0 {
    SEAD_RTTI_OVERRIDE(Unk_7102499a28, Unk_71024993a0)
public:
    ~Unk_7102499a28() override;
};

// vtable 0x7102499ad8 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102499ad8 {
    SEAD_RTTI_BASE(Unk_7102499ad8)
public:
    virtual ~Unk_7102499ad8();
    virtual void m4() {}
    virtual void m5() {}
};

// vtable 0x7102499b18 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102499b18 : public Unk_7102499ad8 {
    SEAD_RTTI_OVERRIDE(Unk_7102499b18, Unk_7102499ad8)
public:
    ~Unk_7102499b18() override;
};

// vtable 0x710249a160 (6 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249a160 : public Unk_7102499ad8 {
    SEAD_RTTI_OVERRIDE(Unk_710249a160, Unk_7102499ad8)
public:
    ~Unk_710249a160() override;
};

// vtable 0x710249c338 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c338 : public uking::Unk_710246d448 {
    SEAD_RTTI_OVERRIDE(Unk_710249c338, uking::Unk_710246d448)
public:
    ~Unk_710249c338() override;
};

// vtable 0x710249c5e8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c5e8 {
    SEAD_RTTI_BASE(Unk_710249c5e8)
public:
    virtual ~Unk_710249c5e8();
};

// vtable 0x710249c5b8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c5b8 : public Unk_710249c5e8 {
    SEAD_RTTI_OVERRIDE(Unk_710249c5b8, Unk_710249c5e8)
public:
    ~Unk_710249c5b8() override;
};

// vtable 0x71024ca688 (84 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024ca688 : public gsys::ModelUnit {
    SEAD_RTTI_OVERRIDE(Unk_71024ca688, gsys::ModelUnit)
public:
    ~Unk_71024ca688() override;
};

// vtable 0x71024cffe8 (84 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024cffe8 : public gsys::ModelUnit {
    SEAD_RTTI_OVERRIDE(Unk_71024cffe8, gsys::ModelUnit)
public:
    ~Unk_71024cffe8() override;
};

// vtable 0x71024f1358 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024f1358 {
    SEAD_RTTI_BASE(Unk_71024f1358)
public:
    virtual ~Unk_71024f1358();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual s32 m9() { return 1; }
    virtual void m10() {}
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13() {}
    virtual void m14();
    virtual void m15() {}
    virtual void m16() {}
};

// vtable 0x71024f4720 (84 slots); placeholder generated from the vtable (genskel.py).
// Uses gsys::IModelProcedural's RTTI functions (slots 0 and 1 are 0x7100c1444c / 0x7100c14518).
class Unk_71024f4720 : public gsys::IModelProcedural {
public:
    ~Unk_71024f4720() override;
};

// vtable 0x7102519e58 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519e58 {
    SEAD_RTTI_BASE(Unk_7102519e58)
public:
    virtual ~Unk_7102519e58();
};

// vtable 0x71024f7180 (7 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024f7180 : public Unk_7102519e58 {
    SEAD_RTTI_OVERRIDE(Unk_71024f7180, Unk_7102519e58)
public:
    ~Unk_71024f7180() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
};

// vtable 0x7102502978 (15 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_7102502978 : public ksys::res::Resource {
    SEAD_RTTI_OVERRIDE(Unk_7102502978, ksys::res::Resource)
public:
    ~Unk_7102502978() override;
    // 0x7101057588: copies `name` into the file name string at +0x48 and passes it to the
    // aal::AudioResource at +0x40 (setFilename). Called by snd::Unk_710251b6f0::sub_71012CD614.
    void sub_7101057588(const sead::SafeString& name);
    s32 getLoadDataAlignment() const override { return 128; }
    bool needsParse() const override { return true; }
};

// vtable 0x7102504260 (19 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_7102504260 : public Unk_71024f13f0 {
    SEAD_RTTI_OVERRIDE(Unk_7102504260, Unk_71024f13f0)
public:
    ~Unk_7102504260() override;
    virtual void m4();
    virtual void m5();
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
};

// vtable 0x7102504470 (8 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102504470 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_7102504470, Unk_710251d230)
public:
    ~Unk_7102504470() override;
    virtual void m7();
};

// vtable 0x71025046d0 (8 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_71025046d0 : public Unk_7102504470 {
    SEAD_RTTI_OVERRIDE(Unk_71025046d0, Unk_7102504470)
public:
    ~Unk_71025046d0() override;
};

// vtable 0x7102504850 (46 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_7102504850 : public Unk_71025046d0 {
    SEAD_RTTI_OVERRIDE(Unk_7102504850, Unk_71025046d0)
public:
    ~Unk_7102504850() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual s32 m12() { return 20; }
    virtual s32 m13() { return 4; }
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual s32 m19() { return 4; }
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual bool m23() { return false; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39() {}
    virtual void m40();
    virtual void m41() {}
    virtual void m42();
    virtual void m43();
    virtual void m44() {}
    virtual void m45() {}
};

// vtable 0x71025049d0 (46 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_71025049d0 : public Unk_71025046d0 {
    SEAD_RTTI_OVERRIDE(Unk_71025049d0, Unk_71025046d0)
public:
    ~Unk_71025049d0() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual s32 m12() { return 20; }
    virtual s32 m13() { return 4; }
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual s32 m19() { return 4; }
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual bool m23() { return false; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39() {}
    virtual void m40();
    virtual void m41() {}
    virtual void m42();
    virtual void m43();
    virtual void m44() {}
    virtual void m45() {}
};

// lane1 s95: the request passed to Unk_71024dd490::sub_71010C760C.
struct Unk_710250c118Arg {
    u32 _0;
    u32 _4;
    ksys::phys::RigidBody* body;
};

// vtable 0x710250c118 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250c118 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250c118, Unk_7102518688)
public:
    // lane1 s95: a "chemi_fire" element; built by Unk_71024dd490::sub_71010C760C.
    Unk_710250c118(const Unk_710250c118Arg& arg, sead::Heap* heap);
    ~Unk_710250c118() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override {}
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    // lane1 s91: m29 copies mArg._4 to the holder's _1a and adds the rigid body to the world.
    u8 _48[0x50 - 0x48];
    Unk_710250c118Arg mArg;
};

// lane1 s95: the request passed to Unk_71024dd490::sub_71010C77F4.
struct Unk_710250c280Arg {
    f32 _0;
    sead::Vector3f _4;
    ksys::phys::RigidBody* body;
};

// vtable 0x710250c280 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250c280 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250c280, Unk_7102518688)
public:
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    // lane1 s95: a "directional_wind" element; built by Unk_71024dd490::sub_71010C77F4.
    Unk_710250c280(const Unk_710250c280Arg& arg, sead::Heap* heap);
    ~Unk_710250c280() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}
    bool m18() override { return true; }
    f32 m20(ksys::act::Chemical* chemical) override { return 0.0f; }

    // lane1 s91: m29 / m35 copy mArg._0 / _4 to the holder's _3c / _1c.
    u8 _48[0x50 - 0x48];
    Unk_710250c280Arg mArg;
};

// lane1 s95: the request passed to Unk_71024dd490::sub_71010C79DC.
struct Unk_710250c3e8Arg {
    ksys::phys::RigidBody* body;
    f32 _8;
    f32 _c;
    f32 _10;
    u32 _14;
};

// vtable 0x710250c3e8 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250c3e8 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250c3e8, Unk_7102518688)
public:
    // lane1 s95: a "directional_wind" element with an "Updraft" capsule sound shape; built by
    // Unk_71024dd490::sub_71010C79DC.
    Unk_710250c3e8(const Unk_710250c3e8Arg& arg, sead::Heap* heap);
    ~Unk_710250c3e8() override;
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}
    bool m18() override { return true; }

    // 0x71010c5154 / 0x71010c53d8 (placeholder names, declared only): called from m33 / m35; they use the
    // effect and sound handles.
    void sub_71010C5154();
    void sub_71010C53D8();

    u8 _48[0x50 - 0x48];
    /* 0x50 */ Unk_710250c3e8Arg mArg;
    /* 0x68 */ bool _68 = false;
    /* 0x69 */ bool _69 = false;
    /* 0x70 */ xlink2::HandleELink _70;
    /* 0x80 */ xlink2::HandleSLink _80;
    /* 0x90 */ aal::Shape* _90 = nullptr;
    /* 0x98 */ f32 _98 = 0.0f;
};

// vtable 0x710250c550 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250c550 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250c550, Unk_7102518688)
public:
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    // lane1 s95: the "radial_wind" element; built by Unk_71024dd490::sub_71010C7BE0 (ctor inlined there).
    Unk_710250c550(ksys::phys::RigidBody* const& body, sead::Heap* heap);
    ~Unk_710250c550() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override {}
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    // lane1 s91: m29 adds this rigid body to the world.
    u8 _48[0x50 - 0x48];
    ksys::phys::RigidBody* _50;
    // lane1 s95: m14 pulls towards the centre _58 with strength _64 inside radius _68.
    sead::Vector3f _58;
    f32 _64;
    f32 _68;
    u8 _6c[0x70 - 0x6c];
};

// vtable 0x710250c6d8 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250c6d8 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250c6d8, Unk_7102518688)
public:
    // lane1 s95: a "chemi_fire" element on a rigid body; built by Unk_71024dd490::sub_71010C7DB8.
    Unk_710250c6d8(ksys::phys::RigidBody* const& body, sead::Heap* heap);
    ~Unk_710250c6d8() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    // lane1 s91: m29 adds this rigid body to the world.
    u8 _48[0x50 - 0x48];
    ksys::phys::RigidBody* _50;
};

// lane1 s95: the request passed to Unk_71024dd490::sub_71010F1D1C.
struct Unk_710250d3e8Arg {
    u32 _0;
    f32 _4;
    u8 _8[0x18 - 0x8];
    ksys::phys::RigidBody* body;
};

// vtable 0x710250d3e8 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250d3e8 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710250d3e8, Unk_7102518688)
public:
    // lane1 s95: a "directional_wind" element; built by Unk_71024dd490::sub_71010F1D1C.
    Unk_710250d3e8(const Unk_710250d3e8Arg& arg, sead::Heap* heap);
    ~Unk_710250d3e8() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}
    bool m18() override { return true; }

    // lane1 s91: m29 / m35 copy mArg._4 to the holder's _3c; m33 stores its first flag in _69.
    Unk_710250d3e8Arg mArg;
    bool _68 = false;
    bool _69 = false;
};

// vtable 0x710250db28 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250db28 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250db28, Unk_710250dcd8)
public:
    ~Unk_710250db28() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual s32 m10() { return 1; }
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
};

// vtable 0x710250dbc8 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dbc8 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dbc8, Unk_710250dcd8)
public:
    ~Unk_710250dbc8() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual s32 m10() { return 1; }
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
};

// vtable 0x710250dc50 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dc50 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dc50, Unk_710250dcd8)
public:
    ~Unk_710250dc50() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual s32 m10() { return 1; }
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
};

// vtable 0x710250dd60 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dd60 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dd60, Unk_710250dcd8)
public:
    ~Unk_710250dd60() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual s32 m10() { return 1; }
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
};

// vtable 0x710250e490 (9 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250e490 {
    SEAD_RTTI_BASE(Unk_710250e490)
public:
    virtual ~Unk_710250e490();
    virtual void m4();
    virtual void m5() {}
    virtual bool m6() { return false; }
    virtual void m7() {}
    virtual void m8() {}
};

// vtable 0x710250fb18 (24 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
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

// vtable 0x710250fdf8 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250fdf8 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_710250fdf8, Unk_710251d230)
public:
    ~Unk_710250fdf8() override;
    virtual void m7() {}
    virtual s32 m8() { return 918; }
    virtual s32 m9() { return 2808; }
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102513630 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102513630 {
    SEAD_RTTI_BASE(Unk_7102513630)
public:
    virtual ~Unk_7102513630();
    virtual void m4();
    virtual void m5();
    virtual void m6() {}
    virtual void m7();
    virtual void m8();
    virtual s32 m9() { return 1; }
    virtual void m10() {}
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13() {}
    virtual void m14() {}
    virtual void m15() {}
    virtual void m16();
};

// vtable 0x7102516b30 (84 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102516b30 : public Unk_71024f4720 {
    SEAD_RTTI_OVERRIDE(Unk_7102516b30, Unk_71024f4720)
public:
    ~Unk_7102516b30() override;
};

// vtable 0x7102516f88 (11 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102516f88 : public ksys::act::ActorBind {
    SEAD_RTTI_OVERRIDE(Unk_7102516f88, ksys::act::ActorBind)
public:
    ~Unk_7102516f88() override;
};

// vtable 0x7102517ab0 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102517ab0 : public Unk_71024dcf48 {
    SEAD_RTTI_OVERRIDE(Unk_7102517ab0, Unk_71024dcf48)
public:
    ~Unk_7102517ab0() override;
    virtual void m4();
};

// vtable 0x71025193e8 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025193e8 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_71025193e8, Unk_7102519378)
public:
    ~Unk_71025193e8() override;
    virtual bool m5() { return false; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
};

// vtable 0x7102519460 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519460 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519460, Unk_7102519378)
public:
    ~Unk_7102519460() override;
    virtual s32 m5() { return 1; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x71025194d0 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025194d0 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_71025194d0, Unk_7102519378)
public:
    ~Unk_71025194d0() override;
    virtual s32 m5() { return 2; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102519540 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519540 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519540, Unk_7102519378)
public:
    ~Unk_7102519540() override;
    virtual s32 m5() { return 3; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x71025195b0 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025195b0 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_71025195b0, Unk_7102519378)
public:
    ~Unk_71025195b0() override;
    virtual s32 m5() { return 4; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102519620 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519620 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519620, Unk_7102519378)
public:
    ~Unk_7102519620() override;
    virtual s32 m5() { return 5; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102519690 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519690 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519690, Unk_7102519378)
public:
    ~Unk_7102519690() override;
    virtual s32 m5() { return 6; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
};

// vtable 0x7102519708 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519708 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519708, Unk_7102519378)
public:
    ~Unk_7102519708() override;
    virtual s32 m5() { return 7; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102519778 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519778 : public Unk_7102519378 {
    SEAD_RTTI_OVERRIDE(Unk_7102519778, Unk_7102519378)
public:
    ~Unk_7102519778() override;
    virtual s32 m5() { return 8; }
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
};

// vtable 0x7102519a68 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102519a68 {
    SEAD_RTTI_BASE(Unk_7102519a68)
public:
    virtual ~Unk_7102519a68();
};

// vtable 0x710251ba58 (10 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251ba58 : public aal::SpatialCalculator {
    SEAD_RTTI_OVERRIDE(Unk_710251ba58, aal::SpatialCalculator)
public:
    ~Unk_710251ba58() override;
};

// vtable 0x710251bb98 (8 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251bb98 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_710251bb98, Unk_710251d230)
public:
    ~Unk_710251bb98() override;
    virtual void m7();
};

// vtable 0x710251bf80 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251bf80 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251bf80, Unk_710251bb98)
public:
    ~Unk_710251bf80() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 2; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual bool m29() { return false; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c0b8 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c0b8 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c0b8, Unk_710251bb98)
public:
    ~Unk_710251c0b8() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 1; }
    virtual s32 m15() { return 37; }
    virtual bool m16() { return false; }
    virtual bool m17() { return false; }
    virtual void m18();
    virtual s32 m19() { return 2817; }
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 7; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual s32 m36() { return 1; }
};

// vtable 0x710251c1f0 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c1f0 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c1f0, Unk_710251bb98)
public:
    ~Unk_710251c1f0() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 1; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c328 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c328 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c328, Unk_710251bb98)
public:
    ~Unk_710251c328() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 2; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c460 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c460 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c460, Unk_710251bb98)
public:
    ~Unk_710251c460() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 3; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c598 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c598 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c598, Unk_710251bb98)
public:
    ~Unk_710251c598() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 4; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c6d0 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c6d0 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c6d0, Unk_710251bb98)
public:
    ~Unk_710251c6d0() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 5; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c808 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c808 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c808, Unk_710251bb98)
public:
    ~Unk_710251c808() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 6; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251c940 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251c940 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251c940, Unk_710251bb98)
public:
    ~Unk_710251c940() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 8; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251ca78 (37 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251ca78 : public Unk_710251bb98 {
    SEAD_RTTI_OVERRIDE(Unk_710251ca78, Unk_710251bb98)
public:
    ~Unk_710251ca78() override;
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual s32 m13() { return 2; }
    virtual s32 m14() { return 3; }
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual s32 m20() { return 2; }
    virtual void m21();
    virtual void m22();
    virtual s32 m23() { return 6; }
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual s32 m29() { return 9; }
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34() {}
    virtual void m35() {}
    virtual void m36();
};

// vtable 0x710251cbf0 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251cbf0 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710251cbf0, Unk_7102518688)
public:
    // lane1 s95: the "grass_fire" element; built by Unk_71024dd490::sub_71012DF1A0.
    Unk_710251cbf0(void* arg, sead::Heap* heap);
    f32 m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    ~Unk_710251cbf0() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}
    f32 m19(ksys::act::Chemical* chemical) override { return 1.0f; }

    // lane1 s95: only the initial values from the ctor are known.
    void* _48;
    ksys::phys::RigidBody* _50 = nullptr;
    s32 _58 = -1;
    void* _60 = nullptr;
    u32 _68 = 0;
};

// vtable 0x710251cd38 (39 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251cd38 : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(Unk_710251cd38, Unk_7102518688)
public:
    // lane1 s95: the "grass_fire_warm" element; built by Unk_71024dd490::sub_71012DF384.
    Unk_710251cd38(void* arg, sead::Heap* heap);
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    ~Unk_710251cd38() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    // lane1 s91: _50 is a sphere rigid body (m35 sets its radius from the floats at _48 + 0x30 / 0x34).
    void* _48;
    ksys::phys::RigidBody* _50 = nullptr;
};

// vtable 0x710251cf40 (10 slots); placeholder generated from the vtable (genskel.py).
// Placeholder name (ctor 0x71011595fc, declaration only): a GPU memory block and a draw context with a small
// header; Unk_710251cf40 holds two of them.
struct Unk_71011595fc {
    Unk_71011595fc();

    u8 _0;
    u8 _1[0x8 - 0x1];
    u32 _8;
    u64 _10;
    u32 _18;
    agl::GPUMemBlock<u8> _20;
    agl::DrawContext _58;
};
KSYS_CHECK_SIZE_NX150(Unk_71011595fc, 0x208);

class Unk_710251cf40 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_710251cf40, Unk_710251d230)
public:
    ~Unk_710251cf40() override;
    virtual void m7() {}
    virtual void m8();
    virtual void m9();

    u8 _8[0xd8 - 0x8];
    Unk_71011595fc _d8;
    Unk_71011595fc _2e0;
};
KSYS_CHECK_SIZE_NX150(Unk_710251cf40, 0x4e8);

// vtable 0x710251d160 (14 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251d160 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_710251d160, Unk_710251d230)
public:
    ~Unk_710251d160() override;
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
};

// vtable 0x710251f878 (85 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251f878 : public Unk_71024f4720 {
    SEAD_RTTI_OVERRIDE(Unk_710251f878, Unk_71024f4720)
public:
    ~Unk_710251f878() override;
};

// vtable 0x710252e4b8 (9 slots); placeholder generated from the vtable (genskel.py).
class Unk_710252e4b8 : public sead::Controller {
    SEAD_RTTI_OVERRIDE(Unk_710252e4b8, sead::Controller)
public:
    ~Unk_710252e4b8() override;
};

// vtable 0x710235a160 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710235a160 : public sead::ControllerAddon {
    SEAD_RTTI_OVERRIDE(Unk_710235a160, sead::ControllerAddon)
public:
    ~Unk_710235a160() override;
};

// vtable 0x710235a368 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710235a368 : public sead::ControllerAddon {
    SEAD_RTTI_OVERRIDE(Unk_710235a368, sead::ControllerAddon)
public:
    ~Unk_710235a368() override;
};

// vtable 0x710245b8a8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710245b8a8 : public sead::TaskParameter {
    SEAD_RTTI_OVERRIDE(Unk_710245b8a8, sead::TaskParameter)
public:
    virtual ~Unk_710245b8a8();
};

// typeinfo 0x71025d0530; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025d0530 {
    SEAD_RTTI_BASE(Unk_71025d0530)
public:
    virtual ~Unk_71025d0530() = default;
};

// vtable 0x710246c410 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710246c410 : public Unk_71025d0530 {
    SEAD_RTTI_OVERRIDE(Unk_710246c410, Unk_71025d0530)
public:
    ~Unk_710246c410() override;
};

// vtable 0x710246d140 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_710246d140 : public uking::Unk_71024739f8 {
    SEAD_RTTI_OVERRIDE(Unk_710246d140, uking::Unk_71024739f8)
public:
    ~Unk_710246d140() override;
};

// vtable 0x710246d258 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_710246d258 : public uking::Unk_71024739f8 {
    SEAD_RTTI_OVERRIDE(Unk_710246d258, uking::Unk_71024739f8)
public:
    ~Unk_710246d258() override;
};

// typeinfo 0x71025d9ad8; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025d9ad8 {
    SEAD_RTTI_BASE(Unk_71025d9ad8)
public:
    virtual ~Unk_71025d9ad8() = default;
};

// vtable 0x710247b2c8 (11 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247b2c8 : public Unk_71025d9ad8 {
    SEAD_RTTI_OVERRIDE(Unk_710247b2c8, Unk_71025d9ad8)
public:
    ~Unk_710247b2c8() override;
    virtual void m4();
    virtual void m5();
    virtual void m6() {}
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
};

// typeinfo 0x71025b1218; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025b1218 {
    SEAD_RTTI_BASE(Unk_71025b1218)
public:
    virtual ~Unk_71025b1218() = default;
};

// vtable 0x710249c558 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c558 : public Unk_71025b1218 {
    SEAD_RTTI_OVERRIDE(Unk_710249c558, Unk_71025b1218)
public:
    ~Unk_710249c558() override;
};

// vtable 0x710249c588 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c588 : public Unk_71025b1218 {
    SEAD_RTTI_OVERRIDE(Unk_710249c588, Unk_71025b1218)
public:
    ~Unk_710249c588() override;
};

// vtable 0x710249d608 (15 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710249d608 : public sead::ArchiveRes {
    SEAD_RTTI_OVERRIDE(Unk_710249d608, sead::ArchiveRes)
public:
    ~Unk_710249d608() override;
    s32 getLoadDataAlignment() const override { return 64; }
};

// typeinfo 0x71025f89a8; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025f89a8 {
    SEAD_RTTI_BASE(Unk_71025f89a8)
public:
    virtual ~Unk_71025f89a8() = default;
};

// vtable 0x71024bd4f0 (20 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024bd4f0 : public Unk_71025f89a8 {
    SEAD_RTTI_OVERRIDE(Unk_71024bd4f0, Unk_71025f89a8)
public:
    ~Unk_71024bd4f0() override;
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
};

// typeinfo 0x71025d0328; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025d0328 {
    SEAD_RTTI_BASE(Unk_71025d0328)
public:
    virtual ~Unk_71025d0328() = default;
};

// vtable 0x71024bf6f8 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024bf6f8 : public Unk_71025d0328 {
    SEAD_RTTI_OVERRIDE(Unk_71024bf6f8, Unk_71025d0328)
public:
    ~Unk_71024bf6f8() override;
    virtual void m4();
};

// typeinfo 0x71025f9c60; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025f9c60 {
    SEAD_RTTI_BASE(Unk_71025f9c60)
public:
    virtual ~Unk_71025f9c60() = default;
};

// vtable 0x71024bfe10 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024bfe10 : public Unk_71025f9c60 {
    SEAD_RTTI_OVERRIDE(Unk_71024bfe10, Unk_71025f9c60)
public:
    ~Unk_71024bfe10() override;
    virtual void m4();
};

// typeinfo 0x71025fffa8; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025fffa8 {
    SEAD_RTTI_BASE(Unk_71025fffa8)
public:
    virtual ~Unk_71025fffa8() = default;
};

// vtable 0x71024d8fa8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024d8fa8 : public Unk_71025fffa8 {
    SEAD_RTTI_OVERRIDE(Unk_71024d8fa8, Unk_71025fffa8)
public:
    ~Unk_71024d8fa8() override;
};

// vtable 0x71024d8ff0 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024d8ff0 : public Unk_71025fffa8 {
    SEAD_RTTI_OVERRIDE(Unk_71024d8ff0, Unk_71025fffa8)
public:
    ~Unk_71024d8ff0() override;
};

// vtable 0x71024eb480 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024eb480 : public Unk_71025d0530 {
    SEAD_RTTI_OVERRIDE(Unk_71024eb480, Unk_71025d0530)
public:
    ~Unk_71024eb480() override;
};

// typeinfo 0x710260dda0; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_710260dda0 {
    SEAD_RTTI_BASE(Unk_710260dda0)
public:
    virtual ~Unk_710260dda0() = default;
};

// vtable 0x71024f6670 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024f6670 : public Unk_710260dda0 {
    SEAD_RTTI_OVERRIDE(Unk_71024f6670, Unk_710260dda0)
public:
    ~Unk_71024f6670() override;
};

// vtable 0x710252e510 (7 slots); placeholder generated from the vtable (genskel.py).
class Unk_710252e510 : public Unk_71024bf6f8 {
    SEAD_RTTI_OVERRIDE(Unk_710252e510, Unk_71024bf6f8)
public:
    ~Unk_710252e510() override;
    virtual void m5();
    virtual void m6();
};

// vtable 0x71024f9e58 (7 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_71024f9e58 : public Unk_710252e510 {
    SEAD_RTTI_OVERRIDE(Unk_71024f9e58, Unk_710252e510)
public:
    ~Unk_71024f9e58() override;
};

// vtable 0x710250b7c0 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250b7c0 : public Unk_71025d0530 {
    SEAD_RTTI_OVERRIDE(Unk_710250b7c0, Unk_71025d0530)
public:
    ~Unk_710250b7c0() override;
};

// typeinfo 0x71026205b8; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71026205b8 : public Unk_710251d230 {
    SEAD_RTTI_OVERRIDE(Unk_71026205b8, Unk_710251d230)
public:
    ~Unk_71026205b8() override = default;
};

// vtable 0x710251d0e0 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710251d0e0 : public Unk_71026205b8 {
    SEAD_RTTI_OVERRIDE(Unk_710251d0e0, Unk_71026205b8)
public:
    ~Unk_710251d0e0() override;
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
};

// vtable 0x710250f758 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710250f758 : public Unk_710251d0e0 {
    SEAD_RTTI_OVERRIDE(Unk_710250f758, Unk_710251d0e0)
public:
    ~Unk_710250f758() override;
};

// vtable 0x710251d010 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710251d010 : public Unk_710251d0e0 {
    SEAD_RTTI_OVERRIDE(Unk_710251d010, Unk_710251d0e0)
public:
    ~Unk_710251d010() override;
};

// vtable 0x710250f7d8 (14 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710250f7d8 : public Unk_710251d010 {
    SEAD_RTTI_OVERRIDE(Unk_710250f7d8, Unk_710251d010)
public:
    ~Unk_710250f7d8() override;
};

// vtable 0x71025138e8 (20 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025138e8 : public Unk_71024bd4f0 {
    SEAD_RTTI_OVERRIDE(Unk_71025138e8, Unk_71024bd4f0)
public:
    ~Unk_71025138e8() override;
    void m5() override {}
};

// vtable 0x7102513d70 (8 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102513d70 : public sead::SingleScreenMethodTreeMgr {
    SEAD_RTTI_OVERRIDE(Unk_7102513d70, sead::SingleScreenMethodTreeMgr)
public:
    ~Unk_7102513d70() override;
};

// typeinfo 0x71025f64e8; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71025f64e8 {
    SEAD_RTTI_BASE(Unk_71025f64e8)
public:
    virtual ~Unk_71025f64e8() = default;
};

// typeinfo 0x7102652580; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_7102652580 : public Unk_71025f64e8 {
    SEAD_RTTI_OVERRIDE(Unk_7102652580, Unk_71025f64e8)
public:
    ~Unk_7102652580() override = default;
};

// typeinfo 0x7102652570; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_7102652570 : public Unk_7102652580 {
    SEAD_RTTI_OVERRIDE(Unk_7102652570, Unk_7102652580)
public:
    ~Unk_7102652570() override = default;
};

// typeinfo 0x7102652590; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_7102652590 : public Unk_7102652570 {
    SEAD_RTTI_OVERRIDE(Unk_7102652590, Unk_7102652570)
public:
    ~Unk_7102652590() override = default;
};

// typeinfo 0x71026525a0; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71026525a0 : public Unk_7102652590 {
    SEAD_RTTI_OVERRIDE(Unk_71026525a0, Unk_7102652590)
public:
    ~Unk_71026525a0() override = default;
};

// vtable 0x7102514540 (18 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_7102514540 : public Unk_71026525a0 {
    SEAD_RTTI_OVERRIDE(Unk_7102514540, Unk_71026525a0)
public:
    ~Unk_7102514540() override;
    virtual void m4();
    virtual void m5() {}
    virtual void m6() {}
    virtual void m7() {}
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
};

// typeinfo 0x71026529f0; the original has no vtable for this class (an abstract base: only its RTTI
// checks remain). Placeholder generated from its children (genskel.py).
class Unk_71026529f0 {
    SEAD_RTTI_BASE(Unk_71026529f0)
public:
    virtual ~Unk_71026529f0() = default;
};

// vtable 0x7102515058 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102515058 : public Unk_71026529f0 {
    SEAD_RTTI_OVERRIDE(Unk_7102515058, Unk_71026529f0)
public:
    ~Unk_7102515058() override;
};

// vtable 0x710251cfa0 (12 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251cfa0 : public Unk_71026205b8 {
    SEAD_RTTI_OVERRIDE(Unk_710251cfa0, Unk_71026205b8)
public:
    ~Unk_710251cfa0() override;
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    void m5() override {}
};

// vtable 0x710252e558 (5 slots); placeholder generated from the vtable (genskel.py).
class Unk_710252e558 : public Unk_71025d0328 {
    SEAD_RTTI_OVERRIDE(Unk_710252e558, Unk_71025d0328)
public:
    ~Unk_710252e558() override;
    virtual void m4();
};

// vtable 0x710252e590 (7 slots); placeholder generated from the vtable (genskel.py).
class Unk_710252e590 : public Unk_71024bf6f8 {
    SEAD_RTTI_OVERRIDE(Unk_710252e590, Unk_71024bf6f8)
public:
    ~Unk_710252e590() override;
    virtual void m5() {}
    virtual void m6() {}
};

// vtable 0x7102531eb0 (9 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102531eb0 : public Unk_710250e490 {
    SEAD_RTTI_OVERRIDE(Unk_7102531eb0, Unk_710250e490)
public:
    ~Unk_7102531eb0() override;
    bool m6() override { return false; }
};

// vtable 0x7102531f08 (9 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102531f08 : public Unk_710250e490 {
    SEAD_RTTI_OVERRIDE(Unk_7102531f08, Unk_710250e490)
public:
    ~Unk_7102531f08() override;
};

// vtable 0x7102531f60 (9 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102531f60 : public Unk_710250e490 {
    SEAD_RTTI_OVERRIDE(Unk_7102531f60, Unk_710250e490)
public:
    ~Unk_7102531f60() override;
};

// vtable 0x710245b7a0 (24 slots); placeholder generated from the vtable (genskel.py).
class Unk_710245b7a0 : public sead::Task {
    SEAD_RTTI_OVERRIDE(Unk_710245b7a0, sead::Task)
public:
    ~Unk_710245b7a0() override;
    void enter() override {}
};

// vtable 0x710249c630 (10 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c630 : public ksys::res::EntryFactoryBase {
    SEAD_RTTI_OVERRIDE(Unk_710249c630, ksys::res::EntryFactoryBase)
public:
    ~Unk_710249c630() override;
    u32 getResourceSize() const override { return 96; }
    u32 getLoadDataAlignment() const override { return 8192; }
};

// vtable 0x710249ce90 (127 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710249ce90 : public uking::ui::Screen {
    SEAD_RTTI_OVERRIDE(Unk_710249ce90, uking::ui::Screen)
public:
    ~Unk_710249ce90() override;
};

// vtable 0x71024cfdf8 (22 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024cfdf8 : public sead::TaskBase {
    SEAD_RTTI_OVERRIDE(Unk_71024cfdf8, sead::TaskBase)
public:
    ~Unk_71024cfdf8() override;
};

// vtable 0x71024d9160 (148 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024d9160 : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(Unk_71024d9160, ksys::act::Actor)
public:
    ~Unk_71024d9160() override;
};

// vtable 0x71024de2f0 (148 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024de2f0 : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(Unk_71024de2f0, ksys::act::Actor)
public:
    ~Unk_71024de2f0() override;
    bool shouldUnload(s32* a1) override { return false; }
};

// vtable 0x71024de830 (43 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024de830 : public sead::GameFrameworkNx {
    SEAD_RTTI_OVERRIDE(Unk_71024de830, sead::GameFrameworkNx)
public:
    ~Unk_71024de830() override;
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40() {}
    virtual void m41();
    virtual void m42();
};

// vtable 0x71024f6f70 (10 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024f6f70 : public ksys::res::EntryFactoryBase {
    SEAD_RTTI_OVERRIDE(Unk_71024f6f70, ksys::res::EntryFactoryBase)
public:
    ~Unk_71024f6f70() override;
    u32 getResourceSize() const override { return 72; }
    u32 getLoadDataAlignment() const override { return 4; }
};

// vtable 0x71024fd0a8 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fd0a8 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71024fd0a8, ksys::snd::Bgm)
public:
    ~Unk_71024fd0a8() override;
    void m14(sead::TextWriter& writer) override {}
};

// vtable 0x71024fd188 (17 slots); placeholder generated from the vtable (genskel.py).
// The big maze BGM ("BigMazeBgm"; 0x1d0 bytes, constructor 0x7100fff1fc).
class Unk_71024fd188 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd188, ksys::snd::Unk_71025ce380)
public:
    explicit Unk_71024fd188(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fd188() override;
    void hm14() override;
    void hm15() override {}

    ksys::snd::BigMazeBgmInfo* mInfo = nullptr;
    u64 _198 = 0;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd188, 0x1d0);

// vtable 0x71024fd318 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fd318 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71024fd318, ksys::snd::Bgm)
public:
    ~Unk_71024fd318() override;
    void m14(sead::TextWriter& writer) override {}
};

// vtable 0x71024fd448 (17 slots); placeholder generated from the vtable (genskel.py).
// The Remains (Divine Beast) boss BGM (BGM kinds 27..30; 0x1b0 bytes, constructor 0x7101000254).
class Unk_71024fd448 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd448, ksys::snd::Unk_71025ce380)
public:
    explicit Unk_71024fd448(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fd448() override;
    // 0x710100064c / 0x7101000b00 (declared only)
    void hm14() override;
    void hm15() override;

    // Full native lookups and member bodies establish this existing BGM owner.
    void sub_71010003A4();
    void sub_7101000838(f32 value);

    u32 _190 = 0;
    u64 _198 = 0;
    ksys::snd::Unk_710103AB10 _1a0{10};
    ksys::snd::RemainsBossBgmType mType;
    u32 _1a8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd448, 0x1b0);

// vtable 0x71024fd6c8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fd6c8 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd6c8, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fd6c8() override;
    // Called by the BGM controllers (ksys::snd::Unk_710260f130 / Unk_710260f150) on their kind 18 BGM.
    void sub_710100215C(const ksys::snd::Unk_BgmControllerM8Arg& arg);
    void sub_7101002194();
    // 0x7101002274 (declared only: in our TU layout Unk_710260f130::sub_7100FF9F0C would inline it): sets bit 3 of
    // _1f4 and _1ec to the info's PlayWaitSec.
    void sub_7101002274();
    // 0x7101002244: in state 3 / 4 with _160[1] above the info's VolumeNormal.
    bool m10() override;
    void m14(sead::TextWriter& writer) override {}
    // 0x7101002290 (declared only)
    void hm14() override;
    void hm15() override;

    explicit Unk_71024fd6c8(const ksys::snd::BgmInitArg& arg);

    ksys::snd::DungeonBattleBgmInfo* mInfo = nullptr;
    s32 mState = 0;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
    u32 _1d0;
    u64 _1d8 = 0;
    u64 _1e0 = 0;
    u32 _1e8 = 0;
    f32 _1ec = 0;
    s32 _1f0 = -1;
    // ksys::snd::Unk_710260f0c0::sub_7100FF8F34 sets bit 0x10.
    u8 _1f4 = 7;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd6c8, 0x1f8);

// vtable 0x71024fd808 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fd808 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd808, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fd808() override;
    // Called by the BGM controllers on their kind 19 BGM.
    void sub_71010029B8();
    void sub_71010029CC();
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    // 0x7101002a24 (declared only; 772 B)
    void hm15() override;

    // The dungeon BGM ("DungeonNormalBgm"; 0x1c0 bytes, constructor 0x7101002850).
    explicit Unk_71024fd808(const ksys::snd::BgmInitArg& arg);

    ksys::snd::MusicInfo* mInfo = nullptr;
    f32 _198 = 0;
    u32 _19c = 0;
    u32 _1a0 = 0;
    u16 _1a4 = 0;
    u16 _1a6 = 0;
    u16 _1a8 = 0;
    u16 _1aa = 0;
    u16 _1ac = 0;
    u64 _1b0 = 0;
    f32 _1b8 = 0;
    u32 _1bc = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd808, 0x1c0);

// vtable 0x71024fd948 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fd948 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd948, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fd948() override;
    // Called by the BGM controllers on their kind 20 BGM.
    void sub_71010038AC();
    void sub_71010038C0();
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    // 0x710100390c (declared only; 360 B)
    void hm15() override;

    // The dungeon reward BGM ("DungeonRewardBgm"; 0x1b8 bytes, constructor 0x7101003750).
    explicit Unk_71024fd948(const ksys::snd::BgmInitArg& arg);

    ksys::snd::MusicInfo* mInfo = nullptr;
    f32 _198 = 0;
    u32 _19c = 0;
    u32 _1a0 = 0;
    u32 _1a4 = 0;
    u32 _1a8 = 0;
    f32 _1ac = 0;
    u32 _1b0 = 0;
    bool _1b4 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd948, 0x1b8);

// vtable 0x71024fe368 (19 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fe368 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fe368, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fe368() override;
    void m14(sead::TextWriter& writer) override {}
    // 0x710100b30c (declared only): called by ksys::snd::Unk_710260f0c0::m8 on its kind 3 BGM.
    void sub_710100B30C(const ksys::snd::Unk_BgmControllerM8Arg& arg);

    u8 _190[0x224 - 0x190];
    // Set by ksys::snd::Unk_710260f0c0::m10.
    bool _224;
};

// vtable 0x71024fe808 (19 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fe808 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fe808, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fe808() override;
};

// vtable 0x71024fe970 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fe970 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fe970, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fe970() override;
    // 0x710100e124 (declaration only): requests the signed state, queuing it during a transition.
    void sub_710100E124(const s32& state);
    void m14(sead::TextWriter& writer) override {}
};

// vtable 0x71024feae8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024feae8 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024feae8, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024feae8() override;
    // Called by ksys::snd::Unk_710260f0c0 on its kind 17 BGM.
    void sub_710100F798();
    void sub_710100F860();
    void sub_710100F8B0(bool value);
    void sub_710100F900(bool flag, s32 value);
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    void hm15() override;

    // The fixed guardian BGM ("GuardianFixedBgm"; 0x200 bytes, constructor 0x710100f2a8).
    explicit Unk_71024feae8(const ksys::snd::BgmInitArg& arg);

    struct Entry {
        u32 _0 = 0;
        u16 _4 = 0;
    };

    ksys::snd::MusicInfo* mInfo = nullptr;
    s32 mState = 0;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    sead::Buffer<Entry> mEntries;
    u32 _1d8 = 0;
    u32 _1dc = 0;
    u32 _1e0 = 0;
    u32 _1e4 = 0;
    u32 _1e8 = 0;
    ksys::snd::Unk_710260f248Entry* mMainEntry = nullptr;
    s32 _1f8 = -1;
};
KSYS_CHECK_SIZE_NX150(Unk_71024feae8, 0x200);

// vtable 0x71024fec18 (17 slots); placeholder generated from the vtable (genskel.py).
// The Ganon beast BGM ("GanonBeastBgm"; 0x1b8 bytes, constructor 0x710100fcf8).
class Unk_71024fec18 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fec18, ksys::snd::Unk_71025ce380)
public:
    explicit Unk_71024fec18(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fec18() override;
    // 0x710100fff4 / 0x710101011c (declared only)
    void hm14() override;
    void hm15() override;

    ksys::snd::MusicInfo* mInfo = nullptr;
    u64 _198 = 0;
    u32 _1a0;
    u32 _1a4 = 0;
    u64 _1a8 = 0;
    ksys::snd::Unk_710103AB10 _1b0{11};
};
KSYS_CHECK_SIZE_NX150(Unk_71024fec18, 0x1b8);

// vtable 0x71024fed48 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fed48 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fed48, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fed48() override;
};

// vtable 0x71024fee78 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fee78 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fee78, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fee78() override;
    // 0x710101157c: stores the first dword of `arg` at +0x1d0 (called by Unk_710260f1f8::m8 on its kind 26 BGM).
    void sub_710101157C(const ksys::snd::Unk_BgmControllerM8Arg& arg);
};

// vtable 0x71024fefe8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fefe8 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fefe8, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fefe8() override;
    // Called by ksys::snd::Unk_710260f0c0 on its kind 16 BGM.
    void sub_71010121D8();
    void sub_71010122A0();
    void sub_71010122F0(bool value);
    void sub_7101012340(s32 value, bool flag);
    void m14(sead::TextWriter& writer) override {}
    // 0x71010123ac / 0x71010124f4 (declared only)
    void hm14() override;
    void hm15() override;

    // 64 entries allocated by the constructor 0x7101011b90 (same zeroing loop as Unk_71024feae8's).
    struct Entry {
        u32 _0 = 0;
        u16 _4 = 0;
    };

    ksys::snd::MusicInfo* mInfo;
    s32 mState;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    sead::Buffer<Entry> mEntries;
    // Not declared yet: fields up to 0x200, a FixedSafeString<8>-based object at 0x200 and fields to 0x240.
    u8 _1d8[0x240 - 0x1d8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024fefe8, 0x240);

// vtable 0x71024ff268: the castle BGM, declared in KingSystem/Sound/sndBgmMgr.h.
// vtable 0x71025008d0 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025008d0 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71025008d0, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71025008d0() override;
};

// vtable 0x7102500a00 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102500a00 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_7102500a00, ksys::snd::Unk_71025ce380)
public:
    ~Unk_7102500a00() override;
    void m14(sead::TextWriter& writer) override {}
};

// vtable 0x7102500e08 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102500e08 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_7102500e08, ksys::snd::Bgm)
public:
    ~Unk_7102500e08() override;
    void m14(sead::TextWriter& writer) override {}
};

// vtable 0x7102502640 (18 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102502640 : public aal::AuxBusDataSerialCtrl {
    SEAD_RTTI_OVERRIDE(Unk_7102502640, aal::AuxBusDataSerialCtrl)
public:
    ~Unk_7102502640() override;
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15() {}
    virtual void m16();
    virtual void m17() {}
};

// vtable 0x7102502b50 (10 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102502b50 : public ksys::res::EntryFactoryBase {
    SEAD_RTTI_OVERRIDE(Unk_7102502b50, ksys::res::EntryFactoryBase)
public:
    ~Unk_7102502b50() override;
    u32 getResourceSize() const override { return 176; }
    u32 getLoadDataAlignment() const override { return 128; }
};

// vtable 0x71025136c8 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71025136c8 : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE(Unk_71025136c8, sead::CalculateTask)
public:
    ~Unk_71025136c8() override;
    void enter() override {}
    void exit() override {}
    void calc() override {}
};

// vtable 0x7102513c38 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102513c38 : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE(Unk_7102513c38, sead::CalculateTask)
public:
    ~Unk_7102513c38() override;
    void enter() override {}
    void exit() override {}
    void calc() override {}
};

// vtable 0x710251ab30 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251ab30 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_710251ab30, ksys::snd::Unk_71025ce380)
public:
    ~Unk_710251ab30() override;
};

// vtable 0x710251b5c0 (18 slots); placeholder generated from the vtable (genskel.py).
class Unk_710251b5c0 : public Unk_7102502640 {
    SEAD_RTTI_OVERRIDE(Unk_710251b5c0, Unk_7102502640)
public:
    ~Unk_710251b5c0() override;
    void m15() override {}
};

// vtable 0x7102366538 (5 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses Unk_7102366570's RTTI functions.
class Unk_7102366538 : public Unk_7102366570 {
public:
    ~Unk_7102366538() override;
};

// vtable 0x71024c0140 (26 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses sead::TaskBase's RTTI functions.
class Unk_71024c0140 : public sead::TaskBase {
public:
    ~Unk_71024c0140() override;
};

// vtable 0x71024c0220 (5 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses sead::TaskBase's RTTI functions.
class Unk_71024c0220 : public sead::TaskBase {
public:
    ~Unk_71024c0220() override;
};

// vtable 0x71024fc990 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_71024fc990 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_71024fc990() override;
};

// vtable 0x7102501910 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501910 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501910() override;
};

// vtable 0x7102501980 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501980 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501980() override;
};

// vtable 0x7102501f10 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501f10 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501f10() override;
};

// vtable 0x71025028c0 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_71025028c0 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_71025028c0() override;
};

// vtable 0x71025159b0 (15 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses ksys::phys::TerrainHeightFieldRigidBody's RTTI functions.
class Unk_71025159b0 : public ksys::phys::TerrainHeightFieldRigidBody {
public:
    ~Unk_71025159b0() override;
};

// vtable 0x710251b810 (13 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_710251b810 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_710251b810() override;
};

// vtable 0x710251b888 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_710251b888 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_710251b888() override;
};

// vtable 0x710251b900 (13 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_710251b900 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_710251b900() override;
};

// vtable 0x710251b978 (13 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_710251b978 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_710251b978() override;
};

// vtable 0x710251b9f0 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_710251b9f0 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_710251b9f0() override;
};

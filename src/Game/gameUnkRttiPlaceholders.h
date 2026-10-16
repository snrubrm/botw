#pragma once

#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <container/seadTList.h>
#include "KingSystem/Terrain/teraResourceNode.h"

#include <prim/seadRuntimeTypeInfo.h>
#include <nn/ui2d/TextureInfo.h>
#include "Game/Actor/aiUnk_71025afb58.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiTexSlots.h"
#include "Game/UI/uiTimer.h"
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
#include "KingSystem/Camera/camUnk_71025136c8.h"
#include <aal/aalSpatialCalculator.h>
#include <aal/aalSpeakerChannelVolume.h>
#include <aal/aalDeviceType.h>
#include <container/seadSafeArray.h>
#include <thread/seadAtomic.h>
#include "KingSystem/GameData/gdtFlagHandle.h"
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
#include "KingSystem/Physics/Ragdoll/physUnk_7102519b90.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include <aal/aalAuxBusDataSerialCtrl.h>
#include "framework/nx/seadGameFrameworkNx.h"
#include "framework/seadCalculateTask.h"
#include "framework/seadTask.h"
#include "framework/seadTaskBase.h"
#include "Game/Actor/actUnk_7102366570.h"
#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include <aal/aalISpeakerBalanceSupplier.h>
#include <aal/aalMarkerController.h>

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
    void m7() override;
    void m14() override;

    /* 0x48 */ uking::ui::Unk_71009cb0c8 _48;
    // zeroed by the constructor (inlined in ScreenAppPictureBookEntry::createUnits, 0x71009d6d8c; 0x380 bytes)
    /* 0x330 */ u64 _330 = 0;
    /* 0x338 */ u64 _338 = 0;
    /* 0x340 */ bool _340 = false;
    /* 0x341 */ bool _341 = false;
    /* 0x348 */ u64 _348 = 0;
    /* 0x350 */ u64 _350 = 0;
    /* 0x358 */ u64 _358 = 0;
    /* 0x360 */ u64 _360 = 0;
    /* 0x368 */ u64 _368 = 0;
    /* 0x370 */ u64 _370 = 0;
    /* 0x378 */ u64 _378 = 0;
};

// vtable 0x710247fbc0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247fbc0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_710247fbc0, uking::ui::Unk_7102474e38)
public:
    ~Unk_710247fbc0() override;
    void m5() override {}
    void m7() override;

    /* 0x48 */ uking::ui::Unk_71009cb0c8 _48;
    // zeroed by the constructor (inlined in ScreenAppPictureBookEntry::createUnits, 0x71009d6f6c; 0x358 bytes)
    /* 0x330 */ u64 _330 = 0;
    /* 0x338 */ u64 _338 = 0;
    /* 0x340 */ bool _340 = false;
    /* 0x341 */ bool _341 = false;
    /* 0x348 */ u64 _348 = 0;
    /* 0x350 */ u64 _350 = 0;
};

// vtable 0x71024826c0 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024826c0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024826c0, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024826c0() override;
    void m5() override {}
    void m8() override;
    void m14() override;

    /* 0x48 */ uking::ui::Unk_71009cb0c8 _48;
    // zeroed by the constructor (inlined in ScreenAppPictureBookEntry::createUnits, 0x71009fb528; 0x350 bytes)
    /* 0x330 */ void* _330 = nullptr;
    /* 0x338 */ void* _338 = nullptr;
    /* 0x340 */ void* _340 = nullptr;
    /* 0x348 */ void* _348 = nullptr;
};

// vtable 0x7102482790 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102482790 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_7102482790, uking::ui::Unk_7102474e38)
public:
    ~Unk_7102482790() override;

    /* 0x48 */ uking::ui::Unk_71009cb0c8 _48;
    // zeroed by the constructor with two memsets (inlined in ScreenAppPictureBookEntry::createUnits, 0x71009fb6fc;
    // 0x4f0 bytes)
    /* 0x330 */ u8 _330[0x147]{};
    /* 0x478 */ u64 _478[15]{};
};

// vtable 0x71024855a8 (23 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024855a8 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024855a8, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024855a8() override;

    /* 0x48 */ uking::ui::Unk_7102509148 _48;
};

// vtable 0x71024975d0 (23 slots); placeholder generated from the vtable (genskel.py).
// A shop list entry with a texture slot set (uiScreenSmall2.cpp).
class Unk_71024975d0 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_71024975d0, uking::ui::Unk_7102474e38)
public:
    ~Unk_71024975d0() override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m13() override;
    void m14() override;
    void m15(eui::AnimButton* button) override;
    void m19(eui::AnimButton* button) override;
    // 0x7100a4d41c (CSV unnamed; not decompiled)
    void sub_7100A4D41C();

    // 0x48 .. 0x78 are zeroed by the constructor (inlined in ScreenAppPictureBookEntry::createUnits, 0x7100a4e6ac)
    /* 0x48 */ u64 _48 = 0;
    /* 0x50 */ u64 _50 = 0;
    /* 0x58 */ u64 _58 = 0;
    /* 0x60 */ u64 _60 = 0;
    /* 0x68 */ u64 _68 = 0;
    /* 0x70 */ u64 _70 = 0;
    /* 0x78 */ u64 _78 = 0;
    /* 0x80 */ uking::ui::UiTexSlots _80;
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

namespace eui {
class Animator;
class CapturePane;
class LayoutEx;
class TraceGaugeControl;
}  // namespace eui

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

    // 0x7100945364 (inlined into the ScreenMainScreen3D / ScreenPauseMenuInfo constructors as well)
    Unk_7102474fd8();
    // 0x710094581c (declared only; 796 bytes): a state function stored in _a0
    void sub_710094581C();
    // 0x7100945c98 (placeholder name): closes the layout if it is open or opening; with `a1`, also when it is not
    // closed
    void sub_7100945C98(bool a1);
    // 0x7100945db8 (placeholder name): resets the TU's gauge flags (unless sub_7100AA8F30 holds), flags the capture
    // panes of an open layout, runs the state function _a0 and clears _9d / _9e
    void sub_7100945DB8();
    // 0x7100945ea4 (placeholder name): follows the trace gauge: stores its speed in _98 while it is not tracing,
    // otherwise stops tracing at _98 (or once it has caught up)
    void sub_7100945EA4();
    // 0x7100945d70 (placeholder name): sets the trace gauge's tracing speed to its _50
    void sub_7100945D70();
    // 0x7100945d98 (placeholder name): the trace gauge's _6c flag (false without one)
    bool sub_7100945D98() const;
    // 0x7100946604 / 0x710094661c (placeholder names): set the alpha / uniform scale of the layout's root pane
    void sub_7100946604(u8 alpha);
    void sub_710094661C(f32 scale);
    // 0x7100946664 (placeholder name): stops the _50 animator at its maximum (`max`) or minimum
    void sub_7100946664(bool max);
    // 0x7100946898 / 0x71009468ac (placeholder names): play the _28 / _58 animator
    void sub_7100946898();
    void sub_71009468AC();
    // 0x7100945d84 (placeholder name): sets the trace gauge's _6c flag
    void sub_7100945D84(bool value);
    // 0x7100946864 (placeholder name): 1 + the number of whole 1000s above 1000 in _8c
    s32 sub_7100946864() const;
    // 0x71009468e0 (placeholder name): stops the _58 animator at `frame`
    void sub_71009468E0(f32 frame);

    // Layout from the constructor (0x8 .. 0x80 zeroed as one block) and the gauge updates 0x7100945f78 /
    // 0x7100946318 (placeholder types: the slots used are eui::Animator / TraceGaugeControl virtuals).
    /* 0x08 */ eui::LayoutEx* _8 = nullptr;
    /* 0x10 */ eui::TraceGaugeControl* _10 = nullptr;
    /* 0x18 */ eui::Animator* _18 = nullptr;
    /* 0x20 */ eui::Animator* _20 = nullptr;
    /* 0x28 */ eui::Animator* _28 = nullptr;
    /* 0x30 */ eui::Animator* _30 = nullptr;
    /* 0x38 */ eui::Animator* _38 = nullptr;
    /* 0x40 */ eui::Animator* _40 = nullptr;
    /* 0x48 */ eui::Animator* _48 = nullptr;
    /* 0x50 */ eui::Animator* _50 = nullptr;
    /* 0x58 */ eui::Animator* _58 = nullptr;
    // capture panes whose _db flag sub_7100945DB8 sets
    /* 0x60 */ sead::PtrArray<eui::CapturePane> _60;
    /* 0x70 */ void* _70 = nullptr;
    /* 0x78 */ void* _78 = nullptr;
    /* 0x80 */ f32 _80 = 1.0f;
    /* 0x84 */ bool _84 = false;
    /* 0x88 */ f32 _88 = 0;
    /* 0x8c */ f32 _8c = 0;
    /* 0x90 */ f32 _90 = 0;
    /* 0x94 */ f32 _94 = 0;
    // the value the trace gauge catches up to (sub_7100945EA4)
    /* 0x98 */ f32 _98 = 0;
    /* 0x9c */ bool _9c = false;
    /* 0x9d */ bool _9d = false;
    /* 0x9e */ bool _9e = false;
    // a member function pointer (Unk_7102475050::m12 compares it with sub_710094581C)
    /* 0xa0 */ void (Unk_7102474fd8::*_a0)() = nullptr;
    /* 0xb0 */ void* _b0 = nullptr;
};

// 0x71009452c4 (placeholder name): the gauge flag sUnk_71025d64ec of the gauge TU
bool sub_71009452C4();

// Placeholder: the common base of Unk_7102475050 and Unk_71024750c8. Both vtables have the slots m6 .. m12 after the
// base's six, and the gauge helpers 0x7100945f78 / 0x7100946740 (in the base's TU) call m6 .. m9 and m12 on `this`;
// it has no RTTI of its own (both derived classes check Unk_7102474fd8 directly) and no vtable of its own in the
// original (abstract).
class Unk_7102474fd8Gauge : public Unk_7102474fd8 {
public:
    virtual f32 m6() = 0;
    virtual f32 m7() = 0;
    virtual f32 m8() = 0;
    virtual f32 m9(f32 value) = 0;
    virtual bool m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;

    // 0x7100945f78 (placeholder name): takes the new gauge value (m7), moves the gauge animation and the trace
    // gauge, then updates the extra animators
    void sub_7100945F78();
    // 0x71009461b8 (placeholder name): with m10, opens the layout (also when the remote bomb / camera rune state
    // says so) after refreshing the gauge; otherwise closes it
    void sub_71009461B8();
    // 0x7100946318 (declared only; 304 bytes): sets the animators _50 / _40 / _20 from the player's state
    void sub_7100946318();
    // 0x710094574c / 0x71009457b4 (placeholder names): set the trace gauge's tracing speed / _50 from `value`
    // (scaled against m8 by uking::ui::sub_7100AA8FCC)
    void sub_710094574C(f32 value);
    void sub_71009457B4(f32 value);
    // 0x7100946740 (placeholder name): opens the layout (and with `update`, refreshes the gauge first) if it is
    // closed or closing; with `a1` also when it is not open
    void sub_7100946740(bool a1, bool update);
};

// vtable 0x7102475050 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475050 : public Unk_7102474fd8Gauge {
    SEAD_RTTI_OVERRIDE(Unk_7102475050, Unk_7102474fd8)
public:
    ~Unk_7102475050() override;
    // 0x71009468f0: also creates the "Born" (stopped at min) / "Dead" (stopped at max) animators and ends the timer
    void m4() override;
    // the gauge values from the UI Manager (uking::ui::sub_7100A9B6D0 / sub_7100A9B6F0)
    f32 m6() override;
    f32 m7() override;
    // 3000 (the default limit set by uking::ui::sub_7100945320)
    f32 m8() override;
    // (value - 1000) / 2000 clamped to [0, 1]
    f32 m9(f32 value) override;
    // 0x71009469b4 (not decompiled)
    bool m10() override;
    // 0x7100946a5c (placeholder name): whether the timer _c8 is still running
    bool sub_7100946A5C() const;
    // 0x7100946688: restarts the timer while the value changes; plays _30 once the value is stable
    void m11() override;
    // 0x71009467d8: closes the layout once the value is stable and the state is sub_710094581C
    void m12() override;
    s32 m5() override { return 5; }

    /* 0xb8 */ eui::Animator* _b8;
    /* 0xc0 */ eui::Animator* _c0;
    /* 0xc8 */ uking::ui::UiTimer _c8;
};

// vtable 0x71024750c8 (13 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024750c8 : public Unk_7102474fd8Gauge {
    SEAD_RTTI_OVERRIDE(Unk_71024750c8, Unk_7102474fd8)
public:
    ~Unk_71024750c8() override;
    // 0x7100947244: also stops _40 at its minimum and drops it
    void m4() override;
    // the gauge value from the UI Manager (uking::ui::sub_7100A9B710)
    f32 m6() override;
    // 1000 or 2000 depending on m6() (0 while it is not positive)
    f32 m7() override;
    // 2000 (the default limit set by uking::ui::sub_7100945344)
    f32 m8() override;
    // how many 1000 steps _8c is above 1000 (the parameter is unused)
    f32 m9(f32 value) override;
    // 0x7100947318 (not decompiled)
    bool m10() override;
    void m11() override {}
    void m12() override {}
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

// vtable 0x7102475a38 (33 slots): a map marker with an actor link, a name and two bool flag handles (defined in
// uiMapMarker.cpp).
class Unk_7102475a38 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475a38, uking::ui::Unk_71024754c0)
public:
    ~Unk_7102475a38() override;
    void m9() override;
    void m11() override;
    void m12() override;
    void m21() override;
    void m31() override;
    void m32() override;

    ksys::act::BaseProcLink _68;
    sead::SafeString _78;
    ksys::gdt::FlagHandle _88;
    ksys::gdt::FlagHandle _8c;
    // m11 / m12: the marker is shown while bit 19 of _3c equals this (compared with 0, so not a bool)
    u8 _90;
    bool _91;
};

// vtable 0x7102475b50 (33 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475b50 : public uking::ui::Unk_71024754c0 {
    SEAD_RTTI_OVERRIDE(Unk_7102475b50, uking::ui::Unk_71024754c0)
public:
    ~Unk_7102475b50() override;
    void m9() override;
    void m21() override;
    void m29(uking::ui::Unk_710095192c* entry) override;
    void m31() override;
    void m32() override;
    // 0x71009552fc (CSV unnamed; not decompiled): called at the end of m29
    void sub_71009552FC();

    // Same layout and overrides as Unk_7102475920 (defined in uiMapMarker.cpp).
    sead::SafeString _68;
    ksys::gdt::FlagHandle _78;
};

// vtable 0x7102475e68 (29 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102475e68 : public uking::ui::UiSubsys1Entry {
    SEAD_RTTI_OVERRIDE(Unk_7102475e68, uking::ui::UiSubsys1Entry)
public:
    ~Unk_7102475e68() override;
    void m11() override;
    void m12() override;
    void m14() override;
    void m16() override;

    /* 0x50 */ bool _50;
    /* 0x54 */ s32 _54;
    /* 0x58 */ s32 _58;  // 1: use _70 / _60, else _64 / _5c while _54 is 0 (m14 / m16)
    /* 0x5c */ s32 _5c;
    /* 0x60 */ s32 _60;
    /* 0x64 */ sead::Vector3f _64;
    /* 0x70 */ sead::Vector3f _70;
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
    // 0x71009cab84: whether doCreate_ has set up the texture
    bool m2_() override;
    // 0x71009caad4: releases the g3d resource file
    void onDestroy_() override;

    // A UI texture resource (the item icons, e.g. UI/StockItem/*.bitemico): the parse step (0x71009caa34) sets up
    // the texture from the g3d resource file and stores its size in mTexInfo.
    /* 0x38 */ nn::ui2d::ExternalTextureInfo mTexInfo;
    /* 0x50 */ nn::g3d::ResFile* _50 = nullptr;
    /* 0x58 */ bool _58 = false;
};

// vtable 0x710247e960 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247e960 : public ksys::res::Context {
    SEAD_RTTI_OVERRIDE(Unk_710247e960, ksys::res::Context)
public:
    ~Unk_710247e960() override;

    sead::FixedSafeString<64> _8;
    sead::FixedSafeString<64> _60;
    sead::SafeString _b8;
    s32 _c8;
    u16 _cc;
    s32 _d0;
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
// A shop list entry with a button and a texture slot set (uiScreenSlot4.cpp).
class Unk_7102496f70 : public uking::ui::Unk_7102474e38 {
    SEAD_RTTI_OVERRIDE(Unk_7102496f70, uking::ui::Unk_7102474e38)
public:
    ~Unk_7102496f70() override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m13() override;
    void m14() override;
    void m15(eui::AnimButton* button) override;
    void m19(eui::AnimButton* button) override;
    // 0x7100a4b7f8 (CSV unnamed; not decompiled)
    void sub_7100A4B7F8();

    /* 0x48 */ uking::ui::ScreenButton_7100989968 _48;
    /* 0xd8 */ uking::ui::UiTexSlots _d8;
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

    u8 _200[0x408 - 0x200];
    /* 0x408 */ uking::ui::Unk_710249c3b0 _408;
    u8 _410[0x440 - 0x410];
    /* 0x440 */ uking::ui::Unk_710249c3d0 _440;
    /* 0x468 */ uking::ui::Unk_710249c3f0 _468;
};

// vtable 0x710249c5e8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c5e8 {
    SEAD_RTTI_BASE(Unk_710249c5e8)
public:
    virtual ~Unk_710249c5e8();

    s64 _8;
    void* _10;
    void* _18;
    s32 _20;
};

// vtable 0x710249c5b8 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c5b8 : public Unk_710249c5e8 {
    SEAD_RTTI_OVERRIDE(Unk_710249c5b8, Unk_710249c5e8)
public:
    ~Unk_710249c5b8() override;

    void* _28;
    s32 _30;
    s32 _34;
    bool _38;
    s32 _3c;
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
    // 0x7101087a48 (D1; the CSV had it as an nn::nex destructor): destroys the lock, then the
    // Unk_710251d230 base (Unk_7102504470's destructor is trivial).
    ~Unk_71025046d0() override;

    // Not modelled yet (base data or this class's first fields).
    u8 _8[0x68 - 0x8];
    sead::CriticalSection mCS;
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
// The list node is a base: 0x7101108564 converts a new object to it with a null check, and the
// constructor builds it before the vtable store.
class Unk_710250db28 : public Unk_710250dcd8, public sead::TListNode<Unk_710250db28*> {
    SEAD_RTTI_OVERRIDE(Unk_710250db28, Unk_710250dcd8)
public:
    // 0x710110cbcc
    Unk_710250db28();
    struct InitArg {
        u32 index;
        u32 size;
    };
    // 0x710110cc34
    void init(const InitArg& arg);

    ~Unk_710250db28() override;
    s32 m4() override;
    s32 m5() override;
    s32 m6() override;
    s32 m7() override;
    u16 m8() override;
    u32 m9() override;
    s32 m10() override { return 1; }
    void m13(void* unused, const void* src, u32 size) override;

    // inline-only in the original; name is a guess. m4 - m8 all build the key as one word
    // (3 | index << 16), as a value returned in a register.
    ksys::tera::ImageTypeMaybe getImageType() const {
        ksys::tera::ImageTypeMaybe type;
        type.type = 3;
        type.index = mIndex;
        return type;
    }

    // Bit-fields: init 0x710110cc34 stores both bytes as one halfword.
    u16 mSize : 8;
    u16 mIndex : 8;
};

// vtable 0x710250dbc8 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dbc8 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dbc8, Unk_710250dcd8)
public:
    // 0x710110cfd0
    Unk_710250dbc8();
    // 0x710110d034
    void init(const ksys::tera::ImageSizeMaybe& size);

    ~Unk_710250dbc8() override;
    s32 m4() override;
    s32 m5() override;
    s32 m6() override;
    s32 m7() override;
    u16 m8() override;
    u32 m9() override;
    s32 m10() override { return 1; }
    void m13(void* unused, const void* src, u32 size) override;

    // inline-only in the original; name is a guess (as Unk_710250db28::getImageType).
    ksys::tera::ImageTypeMaybe getImageType() const {
        ksys::tera::ImageTypeMaybe type;
        type.type = 2;
        type.index = 0;
        return type;
    }

    ksys::tera::ImageSizeMaybe mSize = ksys::tera::ImageSizeMaybe(10);
    u8 _24 = 0;
};

// vtable 0x710250dc50 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dc50 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dc50, Unk_710250dcd8)
public:
    // 0x710110d8b8 (does nothing)
    void init(const sead::SafeString& name) {}
    // 0x710110d860
    Unk_710250dc50();
    ~Unk_710250dc50() override;
    s32 m4() override;
    s32 m5() override;
    s32 m6() override;
    s32 m7() override;
    u16 m8() override;
    u32 m9() override;
    s32 m10() override { return 1; }
    void m13(void* unused, const void* src, u32 size) override;
};

// vtable 0x710250dd60 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_710250dd60 : public Unk_710250dcd8 {
    SEAD_RTTI_OVERRIDE(Unk_710250dd60, Unk_710250dcd8)
public:
    // 0x710110e154
    void init(const ksys::tera::ImageSizeMaybe& size);
    // 0x710110e0f4
    Unk_710250dd60();
    ~Unk_710250dd60() override;
    s32 m4() override;
    s32 m5() override;
    s32 m6() override;
    s32 m7() override;
    u16 m8() override;
    u32 m9() override;
    s32 m10() override { return 1; }
    void m13(void* unused, const void* src, u32 size) override;

    ksys::tera::ImageSizeMaybe mSize = ksys::tera::ImageSizeMaybe(10);
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

    // Layout from the ctor at 0x71011ece14 (getName 0x71011ed3cc returns "PlacementNavi"). The dtor also
    // destroys a ksys::SeadController at 0x48 and restores the vtable of Unk_71024f13f0 (base not declared yet).
    u64 _8 = 0;
    u64 _10 = 0;
    u64 _18 = 0;
    u64 _20 = 0;
    void* _28 = nullptr;  // points to _48
    u32 _30 = 5;
    // Written by OpenWorldStage::calc (camera direction, lane1).
    sead::Vector3f _34{0, 0, 1};
    u64 _40 = 0;
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
    // 0x71012da6bc (Unk_710251bf80's destructor is an alias of it): frees the five buffers.
    ~Unk_710251bb98() override;
    virtual void m7();

    // Not modelled yet (the base's data or this class's first fields).
    u8 _8[0x38 - 0x8];
    // Five buffers freed by the destructor (element types unknown; trivially destructible).
    sead::Buffer<u8> _38;
    sead::Buffer<u8> _48;
    sead::Buffer<u8> _58;
    sead::Buffer<u8> _68;
    sead::Buffer<u8> _78;
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
// Its D2 0x71012ff93c ends with ~IModelProcedural: a direct subclass (its RTTI type is
// RuntimeTypeInfo::Derive<gsys::IModelProcedural>, shared with ksys::act::ClusteredRenderer).
class Unk_710251f878 : public gsys::IModelProcedural {
    SEAD_RTTI_OVERRIDE(Unk_710251f878, gsys::IModelProcedural)
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
    virtual void* m10();

    // 0x71009b2c38 / 0x71009b2db4 / 0x71009b7414 (CSV unnamed; not decompiled)
    void sub_71009B2C38();
    void sub_71009B2DB4();
    void sub_71009B7414();

    u8 _8[0x18 - 0x8];
    /* 0x18 */ uking::ui::ScreenAppPictureBookUnk* _18;
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

    sead::FixedSafeString<64> _8;
    s32 _60;
};

// vtable 0x710249c588 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710249c588 : public Unk_71025b1218 {
    SEAD_RTTI_OVERRIDE(Unk_710249c588, Unk_71025b1218)
public:
    ~Unk_710249c588() override;

    sead::FixedSafeString<64> _8;
    s32 _60;
};

// vtable 0x710249d608 (15 slots); placeholder generated from the vtable (genskel.py).
// checkDerivedRuntimeTypeInfo does not match yet: the original calls checkDerivedRuntimeTypeInfoStatic out of
// line, so its parent chain is deeper than the one declared here.
class Unk_710249d608 : public sead::ArchiveRes {
    SEAD_RTTI_OVERRIDE(Unk_710249d608, sead::ArchiveRes)
public:
    ~Unk_710249d608() override;
    s32 getLoadDataAlignment() const override { return 64; }

protected:
    const void* getFileImpl_(const sead::SafeString& file_path,
                             sead::ArchiveRes::FileInfo* file_info) SEAD_ARCHIVERES_CONST_TOKEN override;
    const void* getFileFastImpl_(s32 entry_id,
                                 sead::ArchiveRes::FileInfo* file_info) SEAD_ARCHIVERES_CONST_TOKEN override;
    s32 convertPathToEntryIDImpl_(const sead::SafeString& file_path) SEAD_ARCHIVERES_CONST_TOKEN override;
    bool setCurrentDirectoryImpl_(const sead::SafeString&) override;
    bool openDirectoryImpl_(sead::HandleBuffer* handle,
                            const sead::SafeString& path) SEAD_ARCHIVERES_CONST_TOKEN override;
    bool closeDirectoryImpl_(sead::HandleBuffer* handle) SEAD_ARCHIVERES_CONST_TOKEN override;
    u32 readDirectoryImpl_(sead::HandleBuffer* handle, sead::DirectoryEntry* entries,
                           u32 num) SEAD_ARCHIVERES_CONST_TOKEN override;
    bool prepareArchive_(const void* archive) override;
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
    // 0x7100a806c0: as EntryFactory<T>::newResource_ (this class is laid out like EntryFactory<Unk_710247e8c0>)
    sead::DirectResource* newResource_(sead::Heap* heap_, s32 alignment) override;

    /* 0x80 */ Unk_710247e8c0 mResource;
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
// This is res::EntryFactory<phys::Unk_7102519b90> (the "hknm2" factory; HavokAI::init 0x7100f80f38 creates it
// with (1.0, 0xb28) and registers it). Kept as a placeholder until HavokAI::init is decompiled (it is the
// only place that instantiates the template).
class Unk_71024f6f70 : public ksys::res::EntryFactoryBase {
    SEAD_RTTI_OVERRIDE(Unk_71024f6f70, ksys::res::EntryFactoryBase)
public:
    ~Unk_71024f6f70() override;
    u32 getResourceSize() const override { return 72; }
    u32 getLoadDataAlignment() const override { return 4; }
    sead::DirectResource* newResource_(sead::Heap* heap_, s32 alignment) override;

    ksys::phys::Unk_7102519b90 mResource;
};

// vtable 0x71024fd0a8 (15 slots); placeholder generated from the vtable (genskel.py).
// The animal master BGM's handles (vtable 0x71024fd010, 0x188 bytes; Unk_SpotBgmHandle's RTTI and D1, two extra
// empty slots 0x7100ffd654 / 0x7100ffd658). Declared only.
class Unk_71024fd010 : public Unk_SpotBgmHandle {
public:
    using Unk_SpotBgmHandle::Unk_SpotBgmHandle;
    // 0x7100ffd630 (D0; D1 is Unk_SpotBgmHandle's)
    ~Unk_71024fd010() override;
    // 0x7100ffd654 / 0x7100ffd658 (empty)
    virtual void m16() {}
    virtual void m17() {}

    /* 0x180 */ u32 _180;
};

// The animal master BGM (kind 4; "AnimalMaster_Appearance" flag).
class Unk_71024fd0a8 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71024fd0a8, ksys::snd::Bgm)
public:
    // 0x7100ffccf8
    explicit Unk_71024fd0a8(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fd0a8() override;
    // 0x7100ffcd88 (declared only; 700 B): creates the two handles.
    void init(const ksys::snd::BgmInitArg& arg);
    // 0x7100ffd1a0 (declared only)
    void m5() override;
    bool m9() override { return true; }
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}

    /* 0x10 */ Unk_71024fd010* _10 = nullptr;
    /* 0x18 */ Unk_71024fd010* _18 = nullptr;
    // Set by Unk_710260f198::sub_7100FFBEA8 (BGM kind 4).
    /* 0x20 */ bool _20 = false;
    /* 0x24 */ ksys::gdt::FlagHandle mAppearanceFlag = ksys::gdt::InvalidHandle;
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
    // 0x7100fff73c
    void m13(f32 fade_sec) override;
    // 0x7100fff4e4 (CSV giantMazeBGMDebug): prints the state when the debug flag sUnk_710260F33C is set.
    void m14(sead::TextWriter& writer) override;

    // The states of _198 (enum text "停止,本体再生中,フェードアウト"; text_ is 0x7100fff908).
    // clang-format off
    SEAD_ENUM(State,停止,本体再生中,フェードアウト)
    // clang-format on

    ksys::snd::BigMazeBgmInfo* mInfo = nullptr;
    u32 _198 = 0;
    // The play wait counter (m14).
    f32 _19c = 0;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd188, 0x1d0);

// vtable 0x71024fd318 (15 slots); placeholder generated from the vtable (genskel.py).
// The Blood Moon BGM's handle (vtable 0x71024fd3a0; Unk_SpotBgmHandle's RTTI). Placeholder; constructor not
// decompiled.
class Unk_71024fd3a0 : public Unk_SpotBgmHandle {
public:
    using Unk_SpotBgmHandle::Unk_SpotBgmHandle;
    // 0x71010001f0 / 0x71010001f4
    ~Unk_71024fd3a0() override;
    // 0x7101000218: emits the asset named by _180.
    virtual void m14() { sub_71010209FC(_180); }
    // 0x7101000220 / 0x7101000224 (empty)
    virtual void m15() {}
    virtual void m16() {}

    // 0x7101022dec (placeholder name): init with `name`, then stores the asset name `asset` in _180.
    void sub_7101022DEC(sead::Heap* heap, const sead::SafeString& name, const sead::SafeString& asset);

    // The constructor inlined in Unk_710260f2a8::sub_7101001194 builds a 32-character buffer here (0x1b8 bytes).
    /* 0x180 */ sead::FixedSafeString<32> _180;
};
KSYS_CHECK_SIZE_NX150(Unk_71024fd3a0, 0x1b8);

// The concentration (Blood Moon) BGM: one handle (vtable 0x71024fd3a0) and the ducker cBloody.
class Unk_71024fd318 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_71024fd318, ksys::snd::Bgm)
public:
    ~Unk_71024fd318() override;
    // 0x7100fffcf0 (placeholder name): creates the "OmenOfBloodyMoonBgm" handle (asset "Omen").
    void sub_7100FFFCF0(const ksys::snd::BgmInitArg& arg);
    // 0x7100fffe88 (declared only)
    void m5() override;
    bool m9() override;
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}

    /* 0x10 */ Unk_71024fd3a0* _10;
    /* 0x18 */ f32 _18;
    /* 0x1c */ u32 _1c;
};

// vtable 0x71024fd448 (17 slots); placeholder generated from the vtable (genskel.py).
// The Remains (Divine Beast) boss BGM (BGM kinds 27..30; 0x1b0 bytes, constructor 0x7101000254).
class Unk_71024fd448 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fd448, ksys::snd::Unk_71025ce380)
public:
    explicit Unk_71024fd448(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fd448() override;
    // 0x7101000360: runs the message sound ducking while _190 is set.
    void m5() override;
    bool m10() override;
    // 0x7101000374: restarts the BGM after a stop (state 3 -> 1, 4 -> 2).
    void m12(f32 fade_sec) override;
    // 0x710100064c / 0x7101000b00 (declared only)
    void hm14() override;
    void hm15() override;
    // 0x7101000ab8: stops the BGM (state 1 -> 3, 2 -> 4, else 0) and the message ducking.
    void m13(f32 fade_sec) override;
    // 0x71010007b4: stops the BGM in 3 s like m13, releases the ducker request at Unk_710104e5b4 +0x294 and resets
    // the FX mode.
    void sub_71010007B4();
    // 0x71010008a8: prints the state when the debug flag sUnk_710260F3F8 is set.
    void m14(sead::TextWriter& writer) override;

    // The states of _190 (enum text "停止,前半再生中,後半再生中,前半中断中,後半中断中", as Unk_71024fed48::State;
    // text_ is 0x7101000d10).
    // clang-format off
    SEAD_ENUM(State,停止,前半再生中,後半再生中,前半中断中,後半中断中)
    // clang-format on

    // Full native lookups and member bodies establish this existing BGM owner.
    void sub_71010003A4();
    void sub_7101000838(f32 value);
    // 0x7101000514: called by ksys::snd::sub_7100FFEBE0 (BgmCtrlBehavior::enter); stops the BGM in 1 s, the
    // ducking and the ducker request (with hold) and resets the FX mode.
    void sub_7101000514();
    // 0x7101000598: unless playing, starts the second half and requests the ducker; the FX mode is 2 for the Wind
    // and Fire bosses inside a "Remains" map, else 1.
    void sub_7101000598();

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
    bool m11() override;
    void m13(f32 fade_sec) override;
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
    // 0x7101002924: starts the BGM once the title delay has passed (state 2) or when it is idle.
    void m5() override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    // 0x7101002a24 (declared only; 772 B)
    void hm15() override;

    // The dungeon BGM ("DungeonNormalBgm"; 0x1c0 bytes, constructor 0x7101002850).
    explicit Unk_71024fd808(const ksys::snd::BgmInitArg& arg);

    // The music parts (enum text "Arp,Strings,Bass,Lead"; text_ is 0x71010035a4).
    // clang-format off
    SEAD_ENUM(Part,Arp,Strings,Bass,Lead)
    // clang-format on
    // 0x7101003198: picks two random parts (Bass + Strings, Bass + Arp or Strings + Arp), starts them when the
    // asset info is loaded and marks them in _1ac.
    void sub_7101003198();

    ksys::snd::DungeonNormalBgmInfo* mInfo = nullptr;
    f32 _198 = 0;
    u32 _19c = 0;
    u32 _1a0 = 0;
    u16 _1a4 = 0;
    u16 _1a6 = 0;
    u16 _1a8 = 0;
    u16 _1aa = 0;
    // Bit flags of the started parts (bit = Part index).
    u8 _1ac = 0;
    u8 _1ad = 0;
    u32 _1b0 = 0;
    f32 _1b4 = 0;
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
    // 0x7101003820: as Unk_71024fd808::m5.
    void m5() override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    void hm14() override;
    // 0x710100390c (declared only; 360 B)
    void hm15() override;

    // The dungeon reward BGM ("DungeonRewardBgm"; 0x1b8 bytes, constructor 0x7101003750).
    explicit Unk_71024fd948(const ksys::snd::BgmInitArg& arg);

    ksys::snd::DungeonRewardBgmInfo* mInfo = nullptr;
    f32 _198 = 0;
    u32 _19c = 0;
    u32 _1a0 = 0;
    u32 _1a4 = 0;
    f32 _1a8 = 0;
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
    // 0x710100b30c: called by ksys::snd::Unk_710260f0c0::m8 on its kind 3 BGM.
    void sub_710100B30C(const ksys::snd::Unk_BgmControllerM8Arg& arg);

    // The field battle BGM (MusicInfoType 8 info, FieldBattleBgmInfo). lane3 s86.
    // 0x710100b320: playing (handle state 3 or 4) for longer than FeelPlayingSec.
    bool m10() override;
    // 0x710100bf2c
    bool m11() override { return mState == 2; }
    // 0x710100b2b8
    void m13(f32 fade_sec) override;
    // 0x710100b234 (copy for the handle base 0x710100b278): forwards the volume to the second handle.
    void calc() override;
    // 0x710100b350 (copy for the handle base 0x710100b3cc): resets the state and starts the node machine.
    void hm14() override;
    // 0x710100b44c (declared only; 916 B; the handle base copy is 0x710100b9b4).
    void hm15() override;
    // 0x710100b9bc (copy for the handle base 0x710100b9d8)
    void hm16(s32 arg) override;
    // 0x710100b7e0: fills the first free entry (_98 == -1) with `name`, `value` and `flag` (placeholder name).
    void sub_710100B7E0(const sead::SafeString& name, s32 value, bool flag);
    // 0x71010099f0 (tail of the constructor 0x710100992c): creates the xlink2 properties, the second handle, the
    // entries and the node graph (lane3 s88).
    void sub_71010099F0(const ksys::snd::BgmInitArg& arg);

    // The xlink2 property names (text 0x710100c0b8) and the values of the three properties (0x710100c44c,
    // 0x710100c5f8, 0x710100c7a4).
    SEAD_ENUM(PropertyType,区間,調,調内タイプ)
    SEAD_ENUM(Section,Easy,Middle,Hard)
    SEAD_ENUM(Key,調0,調1,調2)
    SEAD_ENUM(KeyType,A,B)
    // The parts started by the Unk_71024fe618 nodes (text 0x710100ca70).
    SEAD_ENUM(Part,Easy1,Easy2,Easy3,Easy4,Easy5,Easy6,Middle0,Middle1,Middle2,Hard0,Hard1,QuickIntro)

    /* 0x190 */ ksys::snd::FieldBattleBgmInfo* mInfo;
    /* 0x198 */ sead::PtrArray<xlink2::PropertyDefinition> mProperties;
    /* 0x1a8 */ s32 mState;
    /* 0x1b0 */ aal::TimedFader _1b0;
    /* 0x1d8 */ ksys::snd::Unk_BgmControllerM8Arg _1d8;
    /* 0x1e8 */ u32 _1e8;
    // Half a beat in seconds (hm14: 60 / Bpm / 2).
    /* 0x1ec */ f32 mHalfBeatSec;
    /* 0x1f0 */ u32 _1f0;
    /* 0x1f4 */ u32 _1f4;
    /* 0x1f8 */ u8 _1f8;
    // Four entries (allocated by the init function 0x71010099f0).
    struct Entry {
        sead::FixedSafeString<128> name;
        s32 _98 = -1;
        bool _9c = false;
    };
    /* 0x200 */ sead::Buffer<Entry> mEntries4;
    // A second sound object (0xe8 bytes) created by the init function 0x71010099f0.
    /* 0x210 */ ksys::snd::Unk_710260f248* mSubHandle;
    /* 0x218 */ u32 _218;
    /* 0x21c */ u32 _21c;
    /* 0x220 */ u32 _220;
    // Set by ksys::snd::Unk_710260f0c0::m10.
    bool _224;
    /* 0x228 */ s32 _228;
    /* 0x230 */ void* _230;
    // The values of the xlink2 properties (PropertyType order).
    /* 0x238 */ Section mSection;
    /* 0x23c */ Key mKey;
    /* 0x240 */ KeyType mKeyType;
    // The Part of the last started part node.
    /* 0x244 */ s32 mPart;
    /* 0x248 */ ksys::snd::Unk_71024fdde8* _248;
    /* 0x250 */ sead::PtrArray<ksys::snd::Unk_EnvBgmNode> mNodes;
    /* 0x260 */ ksys::snd::Unk_EnvBgmNode* _260;
    /* 0x268 */ ksys::snd::Unk_EnvBgmNode* _268;
    /* 0x270 */ u32 _270;
    /* 0x274 */ bool _274;
};

// vtable 0x71024fe808 (19 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fe808 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fe808, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fe808() override;
    // 0x710100cf20 (declared only; 408 B)
    void m5() override;
    // 0x710100d2a0: playing (handle state 3 or 4) for at least FeelPlayingSec.
    bool m10() override;
    // 0x710100d3fc
    bool m11() override { return mState == 3; }
    // 0x710100d278
    void m13(f32 fade_sec) override;
    // 0x710100cf14 (placeholder name): initialises the handle without xlink2 properties.
    virtual void initHandle(sead::Heap* heap, const sead::SafeString& name) {
        Unk_SpotBgmHandle::init(heap, name, nullptr);
    }
    // 0x710100d2d0 (copy for the handle base 0x710100d2e0): plays "main".
    void hm14() override;
    // 0x710100d40c (copy for the handle base 0x710100d5b8)
    void hm15() override {}
    // 0x710100d410
    virtual void m18() {}

    // Set by Unk_71024fe958::sub_710100D874 (the Golem / Giant / Sandworm BGM info, a BossBgmInfo).
    /* 0x190 */ ksys::snd::MusicInfo* mInfo;
    /* 0x198 */ s32 mState;
};

// vtable 0x71024fe970 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fe970 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fe970, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fe970() override;
    // 0x710100e124 (declaration only): requests the signed state, queuing it during a transition.
    void sub_710100E124(const s32& state);
    bool m10() override;
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    // 0x710100e664 (copy for the handle base 0x710100e804): bit 1 of mFlags is set while the asset is not
    // ready; once it is, sub_710100E6A8 runs.
    void hm14() override;
    // 0x710100e84c (declared only; 620 B; handle base thunk 0x710100eab8).
    void hm15() override;
    // 0x710100e6a8 (declared only).
    void sub_710100E6A8();
    // 0x710100e0c4: marks the BGM playing (clears bit 8) and starts it.
    void sub_710100E0C4();
    // 0x710100e108: sets bit 2 of mFlags and the flags _1e1 / _229.
    void sub_710100E108();
    // 0x710100ead8 (declared only): handles a marker of the playing level.
    void sub_710100EAD8(const aal::MarkerController::MarkerCallbackInfo& info);
    // 0x710100eac0: the marker callback set by sub_710100E6A8.
    static void markerCallback(const aal::MarkerController::MarkerCallbackInfo& info, void* user);

    u8 _190[0x198 - 0x190];
    /* 0x198 */ s32 _198;
    /* 0x19c */ s32 _19c;
    // Placeholder (0x48 bytes): a playing level entry with its fader; two at 0x1a0 / 0x1e8 (constructor
    // 0x710100dd4c).
    struct Slot {
        Slot();

        // inline-only in the original; name is a guess (the same sequence runs on both slots in 0x710100e6a8).
        void reset() {
            if (mEntry) {
                mEntry->sub_7100FF6A64(0.0f);
                mEntry = nullptr;
            }
            mFader.setValueImmediate(0.0f);
            _30 = -1;
            _34 = -1;
            _3c = 0;
            _40 = true;
        }
        // 0x710100d9fc (declared only): takes `entry` and sets its stream region callback.
        void sub_710100D9FC(ksys::snd::Unk_710260f248Entry* entry);
        // 0x710100db1c (declared only)
        void sub_710100DB1C(f32 value);

        ksys::snd::Unk_710260f248Entry* mEntry;
        aal::TimedFader mFader;
        s32 _30;
        s32 _34;
        s32 _38;
        s32 _3c;
        bool _40;
        // Set by sub_710100E108.
        bool _41;
        s32 _44;
    };
    static_assert(sizeof(Slot) == 0x48);

    /* 0x1a0 */ Slot _1a0;
    /* 0x1e8 */ Slot _1e8;
    u8 _230[0x238 - 0x230];
    // States queued by sub_710100E124 during a transition (freed by the destructor 0x710100df48).
    /* 0x238 */ sead::RingBuffer<s32> mStateQueue;
    u8 _250[0x288 - 0x250];
    // Bit 0: playing; bits 3..6: transition states (0x710100f0c0); bit 8 set on start / stop.
    /* 0x288 */ u16 mFlags;
};

// vtable 0x71024feae8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024feae8 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024feae8, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024feae8() override;
    // Called by ksys::snd::Unk_710260f0c0 on its kind 17 BGM.
    // 0x710100f798 (declared only): under the lock at _1d8, takes a free entry for `id` unless it has one.
    void sub_710100F798(s32 id);
    // 0x710100f860 / 0x710100f8b0 / 0x710100f900: clear / set _4 / set _5 of the entry of `id`.
    void sub_710100F860(s32 id);
    void sub_710100F8B0(bool value, s32 id);
    void sub_710100F900(bool value, s32 id);
    void m14(sead::TextWriter& writer) override {}
    bool m10() override;
    bool m11() override;
    void m13(f32 fade_sec) override;
    void hm14() override;
    void hm15() override;

    // The fixed guardian BGM ("GuardianFixedBgm"; 0x200 bytes, constructor 0x710100f2a8).
    explicit Unk_71024feae8(const ksys::snd::BgmInitArg& arg);

    struct Entry {
        s32 id = 0;
        bool _4 = false;
        bool _5 = false;
    };

    ksys::snd::GuardianFixedBgmInfo* mInfo = nullptr;
    s32 mState = 0;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    sead::Buffer<Entry> mEntries;
    // Spin lock of mEntries (0x710100f798).
    sead::Atomic<s32> mEntriesLock = 0;
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
    void m5() override;
    bool m10() override;
    void m12(f32 fade_sec) override;
    // 0x71010104ac: stops the BGM and the message ducking.
    void m13(f32 fade_sec) override;
    // 0x71010101ec: like m13, then clears the state, releases the ducker request at Unk_710104e5b4 +0x294 (with
    // hold) and resets the FX mode.
    void sub_71010101EC(f32 fade_sec);
    // 0x7101010250: prints the state when the debug flag sUnk_710260FAE4 is set.
    void m14(sead::TextWriter& writer) override;
    // 0x710100fff4: starts the entry of the current level once it exists (state 1 -> playing).
    void hm14() override;
    // 0x710101011c: after the delay _1a0 in state 2, fades out the current entry and starts the level _1a4.
    void hm15() override;

    // The levels (enum text "Level1,Level2,Level3"; text_ is 0x71010106dc).
    // clang-format off
    SEAD_ENUM(Level,Level1,Level2,Level3)
    // The states of _198 (enum text "停止,再生,変更待ち": stopped, playing, waiting for a change; text_ is
    // 0x7101010888).
    SEAD_ENUM(State,停止,再生,変更待ち)
    // clang-format on

    // 0x710100fe0c: switches to the level `*level` (0 restarts with the start delay and requests the ducker).
    void sub_710100FE0C(const Level* level);
    // 0x710100ff38: unless the current entry plays, waits the retry delay for level 0 and requests the ducker.
    void sub_710100FF38();
    // inline-only in the original; name is a guess (the same sequence ends 0x710100fe0c and 0x710100ff38).
    inline void startWaitDucking();


    ksys::snd::GanonBeastBgmInfo* mInfo = nullptr;
    u32 _198 = 0;
    f32 _19c = 0;
    f32 _1a0;
    u32 _1a4 = 0;
    ksys::snd::Unk_710260f248Entry* _1a8 = nullptr;
    ksys::snd::Unk_710103AB10 _1b0{11};
};
KSYS_CHECK_SIZE_NX150(Unk_71024fec18, 0x1b8);

// vtable 0x71024fed48 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fed48 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fed48, ksys::snd::Unk_71025ce380)
public:
    // 0x7101010a68: the Ganon BGM ("GanonBgm").
    explicit Unk_71024fed48(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fed48() override;
    bool m10() override;
    // 0x7101010af0: restarts the BGM after a stop (state 3 -> 1, 4 -> 2).
    void m12(f32 fade_sec) override;
    // 0x7101010e74: stops the BGM (state 1 -> 3, 2 -> 4, else 0).
    void m13(f32 fade_sec) override;
    // 0x7101010e70
    void m5() override {}
    // 0x7101010ba8 (copy for the handle base 0x7101010bf8): plays "former" (state 1) or "latter" (state 2).
    void hm14() override;
    // 0x7101010eb8 (copy for the handle base 0x7101011060)
    void hm15() override {}
    // 0x7101010b84: unless playing (state 1 or 2), starts the second half.
    void sub_7101010B84();
    // 0x7101010b20: unless playing (state 1 or 2), starts the first half, requests the ducker at
    // Unk_710104e5b4 +0x294 and sets the FX mode 1.
    void sub_7101010B20();
    // 0x7101010c58: stops the BGM like m13, releases the ducker at Unk_710104e5b4 +0x294 (with hold) and resets
    // the FX mode.
    void sub_7101010C58(f32 fade_sec);
    // 0x7101010cd0: prints the state when the debug flag sUnk_710260FBB8 is set.
    void m14(sead::TextWriter& writer) override;

    // The states of mState (enum text "停止,前半再生中,後半再生中,前半中断中,後半中断中": stopped, playing the first /
    // second half, first / second half interrupted; text_ is 0x7101011064).
    // clang-format off
    SEAD_ENUM(State,停止,前半再生中,後半再生中,前半中断中,後半中断中)
    // clang-format on

    /* 0x190 */ u32 mState = 0;
    /* 0x198 */ ksys::snd::Unk_710260f248Entry* mEntry;
};

// vtable 0x71024fee78 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fee78 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fee78, ksys::snd::Unk_71025ce380)
public:
    // 0x7101011274: the Ganon grudge battle BGM ("GanonGrudgeBattleBgm").
    explicit Unk_71024fee78(const ksys::snd::BgmInitArg& arg);
    ~Unk_71024fee78() override;
    // 0x710101157c: stores the first dword of `arg` at +0x1d0 (called by Unk_710260f1f8::m8 on its kind 26 BGM).
    void sub_710101157C(const ksys::snd::Unk_BgmControllerM8Arg& arg);
    // 0x7101011380: starts the BGM when a battle begins, fades it out after it ends and stops it once faded out.
    void m5() override;
    bool m10() override;
    bool m11() override;
    void m13(f32 fade_sec) override;
    // 0x7101011480 (copy for the handle base 0x71010114e4): plays the main part and fades it in.
    void hm14() override;
    // 0x7101011544 (copy for the handle base 0x7101011548)
    void hm15() override {}
    // 0x7101011588: prints the state when the debug flag sUnk_710260FCA8 is set.
    void m14(sead::TextWriter& writer) override;

    // The states of mState (enum text "停止,本体再生中,フェードアウト": stopped, playing the main part, fading out;
    // text_ is 0x7101011980).
    // clang-format off
    SEAD_ENUM(State,停止,本体再生中,フェードアウト)
    // clang-format on

    /* 0x190 */ ksys::snd::GanonGrudgeBattleBgmInfo* mInfo;
    /* 0x198 */ s32 mState = 0;
    /* 0x1a0 */ aal::TimedFader _1a0{1.0, aal::FadeCurveType(0), 1.0};
    /* 0x1c8 */ ksys::snd::Unk_710260f248Entry* mEntry = nullptr;
    // Set by sub_710101157C (Unk_BgmControllerM8Arg::_0; m14 shows "in battle" when it is positive).
    /* 0x1d0 */ s32 _1d0 = 0;
    // Bit 1: set by uking::behavior::BgmCtrlBehavior::enter; the constructor sets it from
    // Unk_710246be38::m5 (SoundMgr::_c8).
    /* 0x1d4 */ u8 _1d4 = 0;
};

// vtable 0x71024fefe8 (17 slots); placeholder generated from the vtable (genskel.py).
class Unk_71024fefe8 : public ksys::snd::Unk_71025ce380 {
    SEAD_RTTI_OVERRIDE(Unk_71024fefe8, ksys::snd::Unk_71025ce380)
public:
    ~Unk_71024fefe8() override;
    // Called by ksys::snd::Unk_710260f0c0 on its kind 16 BGM.
    // 0x71010121d8 (declared only): as Unk_71024feae8::sub_710100F798.
    void sub_71010121D8(s32 id);
    // 0x71010122a0 / 0x71010122f0: clear / set _4 of the entry of `id`.
    void sub_71010122A0(s32 id);
    void sub_71010122F0(bool value, s32 id);
    // 0x7101012340: raises _1ec to `value`, sets _1f0 if `flag`, and sets _5 of the entry of `id` to `flag`.
    void sub_7101012340(s32 value, bool flag, s32 id);
    bool m10() override;
    bool m11() override;
    // 0x710101214c: stops the handle and resets the play state.
    void m13(f32 fade_sec) override;
    void m14(sead::TextWriter& writer) override {}
    // 0x71010123ac / 0x71010124f4 (declared only)
    void hm14() override;
    void hm15() override;

    // 64 entries allocated by the constructor 0x7101011b90 (same zeroing loop as Unk_71024feae8's).
    struct Entry {
        s32 id = 0;
        bool _4 = false;
        bool _5 = false;
    };

    ksys::snd::GuardianBgmInfo* mInfo;
    s32 mState;
    aal::TimedFader _1a0{1.0, aal::FadeCurveType::Linear, 1.0};
    sead::Buffer<Entry> mEntries;
    // Not declared yet: fields up to 0x200, a FixedSafeString<8>-based object at 0x200 and fields to 0x240.
    // Spin lock of mEntries (0x71010121d8).
    /* 0x1d8 */ sead::Atomic<s32> mEntriesLock;
    // 0x1dc..0x1e8 and 0x1f4..0x228 are reset by m13 (0x710101214c); meanings unknown.
    /* 0x1dc */ u32 _1dc;
    /* 0x1e0 */ u8 _1e0;
    /* 0x1e1 */ u8 _1e1;
    /* 0x1e2 */ u8 _1e2;
    /* 0x1e3 */ u8 _1e3;
    /* 0x1e4 */ u32 _1e4;
    /* 0x1e8 */ u8 _1e8;
    /* 0x1ec */ s32 _1ec;
    /* 0x1f0 */ bool _1f0;
    /* 0x1f4 */ u32 _1f4;
    u8 _1f8[0x1fc - 0x1f8];
    /* 0x1fc */ s32 _1fc;
    /* 0x200 */ sead::FixedSafeString<8> _200;
    /* 0x220 */ u64 _220;
    u8 _228[0x240 - 0x228];
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
    // 0x7101021db8: frees the faders and the part names, then the handle base.
    ~Unk_7102500a00() override;
    // 0x7101022668
    void m5() override {}
    // 0x7101021eec (declared only)
    void m12(f32 fade_sec) override;
    // 0x710102266c
    void m13(f32 fade_sec) override { sub_710101D9F4(fade_sec); }
    void m14(sead::TextWriter& writer) override {}
    // 0x7101022108 / 0x71010221e8 (declared only; handle base thunks 0x71010221e0 / 0x710102257c).
    void hm14() override;
    void hm15() override;

    /* 0x190 */ ksys::snd::MusicInfo* mInfo;
    /* 0x198 */ s32 _198;
    /* 0x19c */ s32 _19c;
    /* 0x1a0 */ s32 _1a0;
    /* 0x1a4 */ s32 _1a4;
    // One fader per part (_19c - 1 of them; constructor 0x7101021b10).
    /* 0x1a8 */ sead::Buffer<aal::TimedFader> mFaders;
    /* 0x1b8 */ ksys::snd::Unk_710260f248Entry* _1b8;
    // "B%d" part names, one per fader.
    /* 0x1c0 */ sead::Buffer<sead::FixedSafeString<8>*> mPartNames;
    u8 _1d0[0x1e0 - 0x1d0];
    /* 0x1e0 */ aal::TimedFader _1e0;
    u8 _208[0x20c - 0x208];
    // Bit 1 is set by uking::behavior::BgmCtrlBehavior::enter.
    /* 0x20c */ u8 _20c;
};

// vtable 0x7102500e08 (15 slots); placeholder generated from the vtable (genskel.py).
class Unk_7102500e08 : public ksys::snd::Bgm {
    SEAD_RTTI_OVERRIDE(Unk_7102500e08, ksys::snd::Bgm)
public:
    // 0x7101025764
    explicit Unk_7102500e08(const ksys::snd::BgmInitArg& arg);
    // 0x7101025acc: stops and deletes the three handles.
    ~Unk_7102500e08() override;
    void m14(sead::TextWriter& writer) override {}
    // 0x7101025bf0: stores the ignited level at the player (_88, _3c) and updates the three handles.
    void m5() override;
    // 0x710102653c
    bool m9() override { return true; }
    // 0x7101025fe0 / 0x7101026068
    void m12(f32 fade_sec) override;
    void m13(f32 fade_sec) override;
    // 0x7101025ca4 (declaration only; placeholder name): updates the handle of `type`.
    void sub_7101025CA4(ksys::snd::TemperatureBgmInfo::TemperatureEnum type);

    // 0x7101025840 (placeholder name; end of the constructor 0x7101025764): creates one handle per
    // TemperatureEnum value ("Bgm_TemperatureCold" / "Hot" / "Burn") and gets the TemperatureBgm music info.
    void sub_7101025840(const ksys::snd::BgmInitArg& arg);

    /* 0x10 */ ksys::snd::TemperatureBgmInfo* mInfo = nullptr;
    // Indexed by TemperatureBgmInfo::TemperatureEnum (as are the arrays below).
    /* 0x18 */ sead::SafeArray<Unk_SpotBgmHandle*, 3> mHandles;
    /* 0x30 */ sead::SafeArray<u32, 3> _30{};
    /* 0x3c */ bool _3c = false;
    /* 0x40 */ sead::SafeArray<aal::SimpleTimedFader, 3> mFaders{
        {aal::SimpleTimedFader{1.0f}, aal::SimpleTimedFader{1.0f}, aal::SimpleTimedFader{1.0f}}};
    // The ignited level at the player (world::Manager::getIgnitedLevel).
    /* 0x88 */ s32 _88 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102500e08, 0x90);

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

// vtable 0x71025136c8: moved to KingSystem/Camera/camUnk_71025136c8.h (camera manager task).

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
    // 0x7100ff8e90 (empty)
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override {}
    // 0x7100ff8cc0: pans by _8 when _c is 1; on a surround output with the BGM manager's tunable set, also
    // feeds the rear channels.
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                            s32 index_b, f32 spread) override;

    /* 0x08 */ f32 _8;
    /* 0x0c */ s32 _c;
};

// vtable 0x7102501910 (11 slots); placeholder generated from the vtable (genskel.py).
// Speaker balance suppliers of the SoundMgr38 forest sound TU (0x710102c1d8..0x71010349dc): a volume per
// index and fixed reductions (slot 4 is an empty override, 0x7101030c70 / 0x7101030c74 / 0x71010349d8).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501910 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501910() override;
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override {}
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                            s32 index_b, f32 spread) override;
    f32 getEnvFxReduction() const override { return mEnvFxReduction; }
    f32 getFilterReduction() const override { return mFilterReduction; }
    f32 getPriorityReduction() const override { return mPriorityReduction; }
    f32 getLpf() const override { return mLpf; }

    // Per device (DeviceType has one value) and index.
    sead::SafeArray<sead::SafeArray<aal::SpeakerChannelVolume, 2>, 1> mVolumes;
    u8 _38[0x50 - 0x38];
    f32 mEnvFxReduction;
    f32 mFilterReduction;
    f32 mPriorityReduction;
    f32 mLpf;
};

// vtable 0x7102501980 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501980 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501980() override;
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override {}
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                            s32 index_b, f32 spread) override;
    f32 getEnvFxReduction() const override { return mEnvFxReduction; }
    f32 getFilterReduction() const override { return mFilterReduction; }
    f32 getPriorityReduction() const override { return mPriorityReduction; }
    f32 getLpf() const override { return mLpf; }

    // Per device (DeviceType has one value) and index.
    sead::SafeArray<sead::SafeArray<aal::SpeakerChannelVolume, 2>, 1> mVolumes;
    f32 mEnvFxReduction;
    f32 mFilterReduction;
    f32 mPriorityReduction;
    f32 mLpf;
};

// vtable 0x7102501f10 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_7102501f10 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_7102501f10() override;
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override {}
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                            s32 index_b, f32 spread) override;
    f32 getEnvFxReduction() const override { return mEnvFxReduction; }
    f32 getFilterReduction() const override { return mFilterReduction; }
    f32 getPriorityReduction() const override { return mPriorityReduction; }
    f32 getLpf() const override { return mLpf; }

    // Per device (DeviceType has one value) and index.
    sead::SafeArray<sead::SafeArray<aal::SpeakerChannelVolume, 2>, 1> mVolumes;
    f32 mEnvFxReduction;
    f32 mFilterReduction;
    f32 mPriorityReduction;
    f32 mLpf;
};

// vtable 0x71025028c0 (11 slots); placeholder generated from the vtable (genskel.py).
// No RTTI of its own: the vtable reuses aal::ISpeakerBalanceSupplier's RTTI functions.
class Unk_71025028c0 : public aal::ISpeakerBalanceSupplier {
public:
    ~Unk_71025028c0() override;
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index,
                            f32 spread) override {}
    // 0x7101055e50: front volume (_8) and, in surround mode, rear volume (_c, scaled by SoundMgr::sub_71011FC310)
    // on the left (index 0) or right side.
    void calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                            s32 index_b, f32 spread) override;

    f32 _8;
    f32 _c;
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

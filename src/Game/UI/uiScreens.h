#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadObjArray.h>
#include <container/seadObjList.h>
#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <math/seadBoundBox.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadEnum.h>
#include <math/seadVector.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadAtomic.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiControlBase.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiTimer.h"
#include "Game/UI/uiGauge.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/DebugBoard.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiPictureEx.h"
#include "Game/UI/euiUIController.h"
#include "Game/UI/uiButtonEventQueue.h"
#include "Game/UI/uiArchiveHandle.h"
#include "Game/UI/uiShopItemElement.h"
#include "Game/UI/uiTexSlots.h"
#include "Game/UI/uiTextureLoad.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiNormalMap.h"
#include <common/aglRenderBuffer.h>
#include <common/aglTextureData.h>
#include <xlink2/xlink2HandleSLink.h>
#include <driver/aglNVNsampler.h>
#include <driver/aglNVNtexture.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Utils/StateMachine.h"
#include "Game/UI/uiScreenChildMessage.h"
#include "Game/UI/uiUtils.h"
#include <controller/seadControllerBase.h>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace eui {
class Animator;
class CapturePane;
class PartsEx;
class TraceGaugeControl;
}

namespace sead {
class Thread;
}

namespace ksys {
class ManagedTaskHandle;
class SeadController;
}

namespace ksys::qst {
struct Quest;
}

namespace ksys::act {
class Actor;
}

namespace ksys::res {
class Handle;
}

class Unk_710247e960;

namespace uking {
// 0x71025cb0eb (defined in gameScene.cpp)
extern bool sForceEnableGlidingSurfingRupee;
}  // namespace uking

namespace uking::ui {
class Unk_71025d6578;

class TagProcessor;
class ScreenEx;
class UiSubsys1;
class Unk_7102477110;
class Unk_710247bcb8;
class Unk_710247e0c8;
class Unk_710247c368;
class Unk_710247dc90;
struct CookingInfo;

// The game's UI screen classes (CSV: ScreenBase / Screen / ScreenEx / Screen<Name>, IDA placeholder
// names; the namespace is a guess). The chain eui::Screen <- ScreenBase <- Screen <- ScreenEx <-
// Screen<Name> is established by the RTTI (the leaf classes' checkDerivedRuntimeTypeInfo compares
// against four typeinfo statics and their Derive<> typeinfo is Derive<ScreenEx>). The layouts are
// not modelled yet: only what the facade functions in uiScreenFacade.cpp use is declared.

class ScreenBase : public eui::Screen {
public:
    ScreenBase();
    SEAD_RTTI_OVERRIDE(ScreenBase, eui::Screen)

    // 0x71010a9d9c (CSV ScreenBase::doInitialize_)
    void doInitialize_(sead::Heap* heap) override;
    // 0x71010a9f70 (CSV ScreenBase::doSetupDrawInfo_): perspective instead of Screen's orthographic projection
    void doSetupDrawInfo_() override;
    // 0x71010a9f58
    void* getSlink2ResourceList_(xlink2::UserInstanceSLink* link) const override;
    // 0x71010a9f44 (CSV ScreenBase::getAnimationStep_)
    f32 getAnimationStep_() const override;
    const char* getArchiveName_() const override;
    const char* replacePartsLayoutName(const char*, eui::PartsEx*, eui::LayoutEx*) override;

    // 0x71010a9da0 (CSV ScreenBase::updateButton_; the game's Screen overrides it again and forwards to this one)
    void updateButton_() override;
    // 0x71010a9eb8
    void registerController_() override;
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;
    nn::ui2d::ResourceAccessor* doCreateResourceAccessor_(sead::Heap* heap) override;
    // 0x71010a9b44 (placeholder name): empty; called with `true` by ScreenChangeController::m98 and Screen::doInitialize
    void sub_71010A9B44(bool flag);
};

// Base class of the screens' child components (elements of Screen::mChildren at 0x250), with 81 virtual slots.
// ScreenChildEx extends it to 105 slots. Slots 43-52 are the ones Screen::m117 - m126 call. The first slots belong to
// eui::ControlBase in the original (0 / 4); slots 2 / 3 are the destructor. Most default implementations are empty or
// forward to another slot of the same object (the argument types of the forwarded slots are unknown).
class ScreenChild : public eui::ControlBase {
public:
    NN_RUNTIME_TYPEINFO(eui::ControlBase)
    // 0x71010a8e30 / 0x71010a8e80 (placeholder names): request opening / closing (states 1 / 3 and 2 / 4 in _104);
    // false if the child cannot (no _110 / _118, or already in the other transition)
    virtual bool m5(bool a1);
    virtual bool m6(bool a1);
    virtual bool m7(bool immediate);
    virtual bool m8(bool immediate);
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual s32 m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23(void* a1);
    // Complete initialization chain 10AB2DC -> 9B06A8 -> 10A90C4 passes the heap to slot 24.
    virtual void m24(sead::Heap* heap);
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
    virtual void m35(void* a1);
    virtual void m36(void* a1);
    virtual void m37(void* a1);
    virtual void m38(void* a1);
    virtual void m39(void* a1);
    virtual void m40(void* a1);
    virtual void m41(void* a1);
    virtual void m42(void* a1);
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53(void* a1);
    virtual void m54(sead::Heap* heap);
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61(void* a1);
    virtual void m62(void* a1);
    virtual void m63(void* a1);
    virtual void m64(void* a1);
    virtual void m65(void* a1);
    virtual void m66(void* a1);
    virtual void m67(void* a1);
    virtual void m68(void* a1);
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73(bool instant);
    virtual bool m74();
    virtual void m75();
    virtual void m76();
    virtual void m77(bool instant);
    virtual bool m78();
    virtual void m79();
    virtual void m80();

    // 0x71010a9000 / 0x71010a9008 / 0x71010a9014 / 0x71010a9064 / 0x71010a90b4 (placeholder names): helpers that
    // forward to the owning screen _120 (child group size, button by tag, controller hold / trigger test while the
    // screen accepts input (_292 bit 6), animation step)
    s32 sub_71010A9000(s32 group) const;
    eui::ButtonBase* sub_71010A9008(s32 tag) const;
    bool sub_71010A9014(u32 mask) const;
    bool sub_71010A9064(u32 mask) const;
    f32 sub_71010A90B4() const;


    // 0x71010a8cec (CSV ksys::ui::Control::ctor; declared only): builds the message transceiver at 0x38, the state
    // machine at 0x80 and the receiver at 0xa8 / adapter at 0xc8, then mName = the layout's root pane name and
    // mLayout = layout
    explicit ScreenChild(eui::LayoutEx* layout);
    // NON_MATCHING: the implicit deleting destructor (0x71010a94e8) computes this + 0xc8 before the vtable stores
    // instead of after the getDispatcher call (scheduling only).

    /* 0x28 */ nn::util::IntrusiveListNode _28;
    /* 0x38 */ Unk_7102474a28<ScreenChild> mTransceiver;  // the state machine is at 0x80, the receiver at 0xa8, its adapter at 0xc8
    ksys::StateMachine& getStateMachine() { return mTransceiver.mReceiver.mMachine; }
    // 0x7100a48628 (CSV unnamed): sends a debug board message of `type` with `user` data through the 0x1e0 transceiver
    void sub_7100A48628(const ksys::MessageType* type, void* user);

    /* 0x100 */ u8 _100 = 0;  // lifecycle event flags, cleared by the update method
    /* 0x104 */ s32 _104 = 0;  // open / close state (7: ScreenMainScreen::sub_7100A1A460 checks it)
    /* 0x108 */ bool _108 = true;  // m55 runs only while set
    /* 0x109 */ bool _109 = false;
    /* 0x110 */ eui::Animator* _110 = nullptr;
    /* 0x118 */ eui::Animator* _118 = nullptr;
    /* 0x120 */ Screen* _120 = nullptr;
};
static_assert(sizeof(ScreenChild) == 0x128);

// The class between ScreenChild and the concrete child classes (guess: the name; the RTTI chain of the leaf classes
// is ControlBase <- ScreenChild-sized class <- this one <- leaf, e.g. the static at 0x71009865a8; ScreenEx::m144 -
// m153 cast their children to it before forwarding the child slots 95 - 104). Its GetRuntimeTypeInfoStatic is
// the out-of-line function at 0x710096a9c4.
class ScreenChildEx : public ScreenChild {
public:
    NN_RUNTIME_TYPEINFO(ScreenChild)
    // 0x71009b0618 (27 leaf constructors call it, e.g. 0x7100931d6c / 0x71009d7198)
    explicit ScreenChildEx(eui::LayoutEx* layout);
    void m54(sead::Heap* heap) override;
    ScreenChildEx* sub_71009B064C(s32 group, s32 index);

    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85(void* a1);
    virtual void m86(void* a1);
    virtual void m87(void* a1, void* a2);
    virtual void m88(void* a1, void* a2);
    virtual void m89(void* a1, void* a2);
    virtual void m90(void* a1, void* a2);
    virtual void m91(void* a1, void* a2);
    virtual void m92(void* a1, void* a2);
    virtual void m93(void* a1, void* a2);
    virtual void m94(void* a1, void* a2);
    virtual void m95(void* a1);
    virtual void m96(void* a1);
    virtual void m97(void* a1, void* a2);
    virtual void m98(void* a1, void* a2);
    virtual void m99(void* a1, void* a2);
    virtual void m100(void* a1, void* a2);
    virtual void m101(void* a1, void* a2);
    virtual void m102(void* a1, void* a2);
    virtual void m103(void* a1, void* a2);
    virtual void m104(void* a1, void* a2);

    /* 0x128 */ ScreenEx* _128;  // Unk_710247af10::m110 calls eui::Screen::sub_7100BEB70C on it
};
static_assert(sizeof(ScreenChildEx) == 0x130);

// ScreenChildEx children made by the control creators below (placeholder classes named after their vtables; the
// constructors are not decompiled, only their sizes are known).
// sub_7100A233EC creates it (0x1f0 bytes, ctor 0x71009b0818).
class Unk_710247a6d8 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247a6d8(eui::LayoutEx* layout);
    // 0x71009b0f3c: stops _138 at its end (true) or start (false)
    void sub_71009B0F3C(bool on);
    // 0x71009b0f60: stops _140 at its start (true); otherwise at its end, resets _130 and closes the _1d8 layout
    void sub_71009B0F60(bool on);
    // 0x71009b0eec: stops _130 at frame `frame`; closes the _1d8 layout unless the frame is 2
    void sub_71009B0EEC(u32 frame);
    // 0x71009b0fcc: fills the weapon modifier display from a pouch item
    void sub_71009B0FCC(const PouchItem* item);
    // 0x71009b0c24: sets the gauge _150 and clears its byte at 0x6c
    void sub_71009B0C24(eui::TraceGaugeControl* gauge);
    // 0x71009b10ec: sets the gauge to `value` out of 120 and closes the _190 layout
    void sub_71009B10EC(s32 value);
    // 0x71009b1024: forwards to _158.sub_71009B26A0
    void sub_71009B1024();
    // 0x71009b102c: fills the armor effect display from a pouch item
    void sub_71009B102C(const PouchItem* item);
    // 0x71009b1148 (placeholder name): sets the gauge speed from the food's value out of 120 and fills the
    // cooking info display
    void sub_71009B1148(const CookingInfo& info);
    /* 0x130 */ eui::Animator* _130 = nullptr;
    /* 0x138 */ eui::Animator* _138 = nullptr;
    /* 0x140 */ eui::Animator* _140 = nullptr;
    /* 0x148 */ void* _148 = nullptr;
    /* 0x150 */ eui::TraceGaugeControl* _150 = nullptr;
    /* 0x158 */ Unk_710247ade8 _158;
    /* 0x190 */ Unk_710247ada8 _190;
    /* 0x1c8 */ void* _1c8 = nullptr;
    /* 0x1d0 */ void* _1d0 = nullptr;
    /* 0x1d8 */ Unk_710247dc70 _1d8;
};
static_assert(sizeof(Unk_710247a6d8) == 0x1f0);

// sub_7100A2C3D8 creates it (0x130 bytes, ctor 0x71009b17a4).
class Unk_710247aa50 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247aa50(eui::LayoutEx* layout);
};
static_assert(sizeof(Unk_710247aa50) == 0x130);

// sub_7100A2C4D4 creates it (0x170 bytes, ctor 0x71009bc268).
class Unk_710247b960 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247b960(eui::LayoutEx* layout);
    ~Unk_710247b960() override;
    void m24(sead::Heap* heap) override;
    // 9BC874 hides the child and clears its effect selection/progress.
    void sub_71009BC874();
    /* 0x130 */ eui::Animator* _130 = nullptr;
    /* 0x138 */ eui::Animator* _138 = nullptr;
    // 9BC468 allocates three state animators; the destructor frees their pointer buffer.
    /* 0x140 */ sead::PtrArray<eui::Animator> _140;
    /* 0x150 */ Unk_71024774c8 _150;
    /* 0x168 */ s32 _168 = -1;
    /* 0x16c */ s32 _16c = 0;
};
static_assert(sizeof(Unk_710247b960) == 0x170);

// sub_7100A33134 creates it (0xd98 bytes, ctor 0x71009af944).
class Unk_710247a028 : public ScreenChildEx {
public:
    explicit Unk_710247a028(eui::LayoutEx* layout);
    u8 _130[0xd98 - 0x130];
};
static_assert(sizeof(Unk_710247a028) == 0xd98);

// sub_7100A513A4 creates it (0x1e8 bytes, ctor 0x71009c1edc).
class Unk_710247ca18 : public ScreenChildEx {
public:
    explicit Unk_710247ca18(eui::LayoutEx* layout);
    // 0x71009c28d0: stops _130 at its start and _138 at frame 0
    void sub_71009C28D0();
    // 0x71009c20f0: sets the gauge _170 and clears its byte at 0x6c
    void sub_71009C20F0(eui::TraceGaugeControl* gauge);
    // 0x71009c21f0 / 0x71009c2274 / 0x71009c22f8: show `name` in the T_Name_00 / detail widgets.
    void sub_71009C21F0(const sead::SafeString& name);
    void sub_71009C2274(const sead::SafeString& name);
    void sub_71009C22F8(const sead::SafeString& name);
    // 0x71009c2420: shows `name` and the equipped item name in the name / detail widgets.
    void sub_71009C2420(const sead::SafeString& name, const sead::SafeString& equipped, bool flag);
    // 0x71009c2718: shows the food / elixir item `name`; true when the gauge was set.
    bool sub_71009C2718(const sead::SafeString& name);
    // 0x71009c2828: shows the cooking info in the effect / duration widgets.
    void sub_71009C2828(const CookingInfo& cook);
    // 0x71009c25a0: shows the armor next-rank name and the item name in the name / detail widgets.
    void sub_71009C25A0(const sead::SafeString& a, const sead::SafeString& b, bool equipped,
                        bool flag);
    /* 0x130 */ eui::Animator* _130 = nullptr;
    /* 0x138 */ eui::Animator* _138 = nullptr;
    u8 _140[0x170 - 0x140];
    /* 0x170 */ eui::TraceGaugeControl* _170 = nullptr;
    /* 0x178 */ Unk_710247ade8 _178;
    u8 _1b0[0x1e8 - 0x1b0];
};
static_assert(sizeof(Unk_710247ca18) == 0x1e8);

// sub_7100A5159C creates it (0x140 bytes, ctor 0x71009c2a40).
class Unk_710247cd70 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247cd70(eui::LayoutEx* layout);
    /* 0x130 */ void* _130 = nullptr;
    /* 0x138 */ s32 _138 = -1;
};
static_assert(sizeof(Unk_710247cd70) == 0x140);



// A state of Unk_710247af10's state machine (a plain StateBase object; uiScreenChildStates.h).
extern const ksys::StateBase sUnk_71025d9960;

// 0x71009de2b8 (uiPaneCasts.cpp)
ScreenChildEx* sub_71009DE2B8(eui::ControlBase* control);

// The secondary RxOnly/TxOnly handlers are at0x108/0x110. Screen introduces its
// handleMessage override at primary slot111; ScreenEx overrides that same slot.

struct ChildControlCreatorEntry;

// 0x71010b6638 (placeholder name; declared only): drives a parts layout's open / close / loop animators between two
// progress values
void sub_71010B6638(eui::Animator* open, eui::Animator* close, eui::Animator* loop, f32 from, f32 to);

class Screen : public ScreenBase, public ksys::ActorMessageTransceiver::IHandler {
public:
    // 0x71010aa3b0 (CSV Screen::ctor; declared only)
    Screen();
    ~Screen() override;
    SEAD_RTTI_OVERRIDE(Screen, ScreenBase)
    // The screen's state machine is mTransceiver.mReceiver.mMachine at 0x160 (the leaf classes' own virtual slots
    // 154+ are the callbacks of its states).
    ksys::StateMachine& getStateMachine() { return mTransceiver.mReceiver.mMachine; }
    // 0x7100a48628 (CSV unnamed): sends a debug board message of `type` with `user` data through the 0x1e0 transceiver
    void sub_7100A48628(const ksys::MessageType* type, void* user);
    const ksys::StateMachine& getStateMachine() const { return mTransceiver.mReceiver.mMachine; }

    /* 0x118 */ Unk_7102474a28<Screen> mTransceiver;
    /* 0x1e0 */ ksys::ActorMessageTransceiver _1e0;
    /* 0x238 */ nn::util::IntrusiveList<ScreenChild, nn::util::IntrusiveListMemberNodeTraits<ScreenChild, &ScreenChild::_28>>
        mChildList;  // owned: the destructor deletes every child in it
    /* 0x248 */ void* _248 = nullptr;
    /* 0x250 */ sead::PtrArray<ScreenChild> mChildren;
    /* 0x260 */ sead::Buffer<s32> mChildGroupSizes;  // the number of children of each group (the groups are consecutive in mChildren)
    /* 0x270 */ f32 _270 = -1.0f;
    // animators reset by ScreenAppCamera::sub_71009D9AD8
    /* 0x278 */ sead::PtrArray<eui::Animator> _278;
    /* 0x288 */ eui::Animator* _288 = nullptr;
    /* 0x290 */ u8 _290 = 0;
    u8 _291 = 0;
    /* 0x292 */ u16 _292 = 0;
    /* 0x294 */ u8 _294 = 0xff;  // 1: ScreenSystemWindow00::m98 / m99 leave the button group's flag 2 clear
    u8 _295 = 0;
    // the "SunLight" animators of the layout and its parts layouts (sub_71010AB490)
    /* 0x298 */ sead::FixedPtrArray<eui::Animator, 10> _298;
    /* 0x2f8 */ f32 _2f8 = 0;  // the last frame applied to the _298 animators (doUpdate_WorldMgrStuff)
    // Ends at 0x2fc: the members of ScreenMainDungeon start there (tail padding of the non-POD base).

    void open(s32 option) override;
    void close(s32 option) override;
    void update() override;
    // 0x71010aa7a0 (CSV Screen::x_0): the child with index `index` of the group `group` (null if out of range)
    ScreenChild* getChild(s32 group, s32 index);
    // 0x71010ab66c (CSV Screen::doUpdate_WorldMgrStuff): sets the _298 animators to the EnvMgr's mExposure frame
    // (clamped to the first animator's frame range)
    void doUpdate_WorldMgrStuff();
    // 0x71010aa868 / 0x71010aa8d0 / 0x71010aa910 (placeholder names): the size of the child group; suspend / resume the
    // screen's button group (flag 2 of its word at 0x38 is saved in bit 7 of _292 and bit 8 of _292 marks the suspension)
    s32 sub_71010AA868(s32 group) const;
    void sub_71010AA8D0();
    void sub_71010AA910();
    // 0x71010aa894 (placeholder name; 19 callers): releases the active cursor node's button while the box cursor is on
    void sub_71010AA894();
    // 0x71010abaa8 / 0x71010abb68 / 0x71010abc28 / 0x71010abce8 / 0x71010abda8 / 0x71010abe68 / 0x71010abf28
    // (placeholder names): out-of-line copies of doButtonOnEnd_ .. doButtonCancelEnd_ that ButtonEventQueue::Update calls
    // 0x71010ab97c (placeholder name): the body of doButtonOnStart_ (0x71010ab978 only forwards to it)
    void sub_71010AB97C(eui::AnimButton* button);
    void sub_71010ABAA8(eui::AnimButton* button);
    void sub_71010ABB68(eui::AnimButton* button);
    void sub_71010ABC28(eui::AnimButton* button);
    void sub_71010ABCE8(eui::AnimButton* button);
    void sub_71010ABDA8(eui::AnimButton* button);
    void sub_71010ABE68(eui::AnimButton* button);
    void sub_71010ABF28(eui::AnimButton* button);
    // 0x71010abf8c (placeholder name; declared only, 2108 bytes): called by the doBuildLayout_ overrides with the
    // creator's child-control table after the layout is built
    void sub_71010ABF8C(const sead::Buffer<const ChildControlCreatorEntry>* entries);
    // 0x71010ab490 (placeholder name): collects the "SunLight" animator of `layout` and of its parts layouts
    // (recursively) into _298, stopped at their start
    void sub_71010AB490(eui::LayoutEx* layout);
    // 0x71010ac7c8 (placeholder name): the number of layouts in `layout`'s tree (itself and its parts layouts) that
    // have an animation `name`
    s32 sub_71010AC7C8(eui::LayoutEx* layout, const sead::SafeString& name);
    // 0x71010ac920 (placeholder name): appends the animator `name` of every layout in `layout`'s tree to `animators`
    void sub_71010AC920(sead::PtrArray<eui::Animator>* animators, eui::LayoutEx* layout, const sead::SafeString& name);
    // 0x71010aa9d0 (placeholder name; 107 callers): `DynamicCast<ksys::SeadController>(mUIController->getController())`
    ksys::SeadController* sub_71010AA9D0();
    // inline-only in the original; name is a guess: the `(_292 & 0x40) && controller && isTrig(mask)` test repeats in
    // ScreenMessageTips::m94 (three times, the mask loaded before the controller call), ScreenPauseMenuMantan::m94,
    // ScreenPauseMenuEiketsu::m94 and ScreenChild::sub_71010A9064
    bool isTrigMaybe(u32 mask) {
        return (_292 & 0x40) && sub_71010AA9D0() && mUIController && mUIController->isTrig(mask);
    }

    // Overrides of the eui::Screen callbacks (CSV Screen::doAfterBuildLayout etc.)
    void doAfterBuildLayout_(sead::Heap* heap) override;
    void doInitialize_(sead::Heap* heap) override;
    void doUpdate_() override;
    void doOpenStart_() override;
    void doOpenEnd_() override;
    void doCloseStart_() override;
    void doCloseEnd_() override;
    void updateButton_() override;
    void updateControl_() override;
    void updateAnimator_() override;
    // The button callbacks call the Screen slots 102-109 and the children's slots 61-68 (ScreenEx overrides all of them).
    void doButtonOnStart_(eui::AnimButton* button) override;
    void doButtonOnEnd_(eui::AnimButton* button) override;
    void doButtonOffStart_(eui::AnimButton* button) override;
    void doButtonOffEnd_(eui::AnimButton* button) override;
    void doButtonDownStart_(eui::AnimButton* button) override;
    void doButtonDownEnd_(eui::AnimButton* button) override;
    void doButtonCancelStart_(eui::AnimButton* button) override;
    void doButtonCancelEnd_(eui::AnimButton* button) override;

    // New virtual slots of Screen (CSV Screen::mNN; the number is the vtable slot, 69-126). Only the trivial
    // ones have known signatures.
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual s32 m72();
    virtual void m73(f32 value);
    // 0x71010aaaac: like m75 for the screen layout, or for each animator of _278 (one frame later)
    virtual void m74(f32 progress);
    // 0x71010aac10: calls m76 when `progress` passes _270, then hands the open / close / loop animators of the parts
    // layout `name` to sub_71010B6638
    virtual void m75(f32 progress, const sead::SafeString& name);
    virtual void m76();
    // 0x71010aacc0: looks up the animation `anim` (field +0x30 helper) and stores it at +0x288.
    virtual void m77(const sead::SafeString& anim);
    virtual void m78(f32 frame);
    virtual void m79();
    virtual void m80(bool visible);
    virtual s32 m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void m92(sead::Heap*);
    virtual void m93(sead::Heap*);
    virtual void m94();
    virtual void m95();
    virtual void m96();  // open(1)
    virtual void m97();  // close(-1)
    virtual void m98();
    virtual void m99();
    virtual void m100();
    virtual void m101();
    virtual void m102(eui::AnimButton*);
    virtual void m103(eui::AnimButton*);
    virtual void m104(eui::AnimButton*);
    virtual void m105(eui::AnimButton*);
    virtual void m106(eui::AnimButton*);
    virtual void m107(eui::AnimButton*);
    virtual void m108(eui::AnimButton*);
    virtual void m109(eui::AnimButton*);
    virtual void m110();
    int handleMessage(const ksys::Message* message) override;
    virtual void m112(sead::Heap* heap);
    virtual void m113();
    virtual void m114(sead::Heap* heap);
    virtual void m115();
    virtual void m116();
    virtual void m117();
    virtual void m118();
    virtual void m119();
    virtual void m120();
    virtual void m121();
    virtual void m122();
    virtual void m123();
    virtual void m124();
    virtual void m125();
    virtual void m126();
};

// Class of the per-button units of a ScreenEx (elements of ScreenEx::mButtonUnits, one per eui::AnimButton; vtable
// 0x7102474e38 with 23 slots and sead RTTI, base of many of the UI helper classes; only the button notification slots
// 15-22 are known). The sub_ functions are out-of-line forwarders to the slots (0x7100939ef8 - 0x7100939f4c).
class ScreenEx;
struct ScreenAppPictureBookUnk;
class Unk_7102474f10;
struct PictureBookItem;

class Unk_7102474e38 {
public:
    SEAD_RTTI_BASE(Unk_7102474e38)
    virtual ~Unk_7102474e38();
    virtual void m4(sead::Heap*);
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
    virtual void m15(eui::AnimButton* button);
    virtual void m16(eui::AnimButton* button);
    virtual void m17(eui::AnimButton* button);
    virtual void m18(eui::AnimButton* button);
    virtual void m19(eui::AnimButton* button);
    virtual void m20(eui::AnimButton* button);
    virtual void m21(eui::AnimButton* button);
    virtual void m22(eui::AnimButton* button);

    ScreenEx* sub_7100939C5C() const;
    s32 sub_7100939C68() const;
    s32 sub_7100939C78() const;
    bool sub_7100939CA0() const;
    void sub_7100939EF8(eui::AnimButton* button);
    void sub_7100939F04(eui::AnimButton* button);
    void sub_7100939F10(eui::AnimButton* button);
    void sub_7100939F1C(eui::AnimButton* button);
    void sub_7100939F28(eui::AnimButton* button);
    void sub_7100939F34(eui::AnimButton* button);
    void sub_7100939F40(eui::AnimButton* button);
    void sub_7100939F4C(eui::AnimButton* button);

    // 0x7100939bd8: the constructor; the destructor at939c18 resets the same state.
    Unk_7102474e38();

    /* 0x08 */ eui::LayoutEx* _8{};
    /* 0x10 */ eui::AnimButton* _10{};
    /* 0x18 */ Unk_7102474f10* _18{};
    /* 0x20 */ ScreenAppPictureBookUnk* _20{};
    /* 0x28 */ eui::BoxCursorNode* _28{};
    /* 0x30 */ s32 _30{};
    /* 0x34 */ sead::Vector2f _34 = sead::Vector2f::zero;
    /* 0x3c */ s32 _3c = -1;
    /* 0x40 */ s32 _40 = -1;
    /* 0x44 */ s32 _44 = -1;
};

// An item of ScreenEx's button helper (placeholder; no RTTI: vtable slots D1 = nullsub 0x92f36c, D0 = delete
// 0x92f370). 0x92f374 (1.2 KB, not decompiled) updates it.
// Vtable 0x7102474690; created by Unk_71024746b0::initialize (0xb8 bytes).
class Unk_71024746b0Item {
public:
    virtual ~Unk_71024746b0Item() = default;
    // 0x710092f374 (declared only)
    void sub_710092F374(bool a1);

    /* 0x08 */ Screen* mScreen{};
    /* 0x10 */ eui::PartsEx* mParts{};
    /* 0x18 */ u32 _18{};
    /* 0x1c */ u8 _1c{};
    /* 0x20 */ sead::Vector2f _20 = sead::ControllerBase::cInvalidPointer;
    /* 0x28 */ sead::Vector2f _28 = sead::ControllerBase::cInvalidPointer;
    /* 0x30 */ sead::Vector2f _30 = sead::ControllerBase::cInvalidPointer;
    /* 0x38 */ sead::Vector2f _38 = sead::ControllerBase::cInvalidPointer;
    /* 0x40 */ sead::Vector2f _40 = sead::ControllerBase::cInvalidPointer;
    /* 0x48 */ sead::Vector2f _48 = sead::ControllerBase::cInvalidPointer;
    /* 0x50 */ f32 _50 = 100.0f;
    /* 0x54 */ f32 _54 = 10.0f;
    /* 0x58 */ sead::Vector2f _58 = sead::ControllerBase::cInvalidPointer;
    /* 0x60 */ sead::Vector2f _60 = sead::ControllerBase::cInvalidPointer;
    /* 0x68 */ u64 _68{};
    /* 0x70 */ f32 _70 = 1.0f;
    /* 0x74 */ s32 _74{};
    /* 0x78 */ u64 _78{};
    /* 0x80 */ s32 _80 = 4;
    /* 0x84 */ s32 _84{};
    /* 0x88 */ f32 _88 = 0.2f;
    /* 0x8c */ f32 _8c = 0.1f;
    /* 0x90 */ u16 _90{};
    /* 0x94 */ sead::BoundBox2f _94;
    /* 0xa4 */ u16 _a4{};
    /* 0xa6 */ u8 _a6{};
    /* 0xa8 */ s32 _a8{};
    /* 0xac */ f32 _ac = 10.0f;
    /* 0xb0 */ f32 _b0 = 10.0f;
};
static_assert(sizeof(Unk_71024746b0Item) == 0xb8);

// The pane path of each button of a screen (ScreenEx::m143; five path levels per button).
struct ButtonPanePath {
    WidgetPathEntry entries[5];
};

// 0x71025d5bc0 (placeholder name): table of 0x58-byte records read by sub_7100931D40 (capacity 145).
struct Unk_71025D5BC0Entry {
    u8 _0[0x58];
};
KSYS_VISIBILITY_HIDDEN extern sead::Buffer<Unk_71025D5BC0Entry> sUnk_71025D5BC0;
// 0x7100931d40 (placeholder name): record `index` of sUnk_71025D5BC0 (sead::Buffer clamping)
Unk_71025D5BC0Entry* sub_7100931D40(s32 index);

// ScreenEx's helper at+0x330. The constructor0x92fc8c and destructor0x92fcb4 prove
// size0x38, heap+8, Screen*+0x10, config+0x18, item buffer+0x20 (a sead::Buffer of pointers) and boolean+0x30.
class Unk_71024746b0 {
public:
    Unk_71024746b0();
    virtual ~Unk_71024746b0();

    void setHeap(sead::Heap* heap);
    void initialize(Screen* screen, eui::LayoutEx* layout, const sead::Buffer<ButtonPanePath>* config);
    void update();
    // 0x71009301f4 (placeholder name): the item `index` (null when there is no buffer or the index is out of range)
    Unk_71024746b0Item* sub_71009301F4(s32 index);

    /* 0x08 */ sead::Heap* mHeap{};
    /* 0x10 */ Screen* mScreen{};
    /* 0x18 */ const sead::Buffer<ButtonPanePath>* mConfig{};
    /* 0x20 */ sead::Buffer<Unk_71024746b0Item*> mItems;
    /* 0x30 */ bool _30 = true;
};
static_assert(sizeof(Unk_71024746b0) == 0x38);

class ScreenEx : public Screen {
public:
    ScreenEx();
    ~ScreenEx() override;
    SEAD_RTTI_OVERRIDE(ScreenEx, Screen)

    // Overrides of the eui::Screen button callbacks
    void doButtonOnStart_(eui::AnimButton* button) override;
    void doButtonOnEnd_(eui::AnimButton* button) override;
    void doButtonOffStart_(eui::AnimButton* button) override;
    void doButtonOffEnd_(eui::AnimButton* button) override;
    void doButtonDownStart_(eui::AnimButton* button) override;
    void doButtonDownEnd_(eui::AnimButton* button) override;
    void doButtonCancelStart_(eui::AnimButton* button) override;
    void doButtonCancelEnd_(eui::AnimButton* button) override;

    int handleMessage(const ksys::Message* message) override;
    void m112(sead::Heap* heap) override;
    void m113() override;
    void m114(sead::Heap* heap) override;
    void m115() override;
    eui::UIController* doCreateUIController_(sead::Heap* heap) override;
    void registerController_() override;

    // Placeholder for the real data (0x300 ...; the leaf classes' members start at 0x3610).
    /* 0x300 */ Unk_710246c458 _300;
    /* 0x310 */ Unk_710246c4d8 _310;
    /* 0x320 */ Unk_710246c498 _320;
    /* 0x330 */ Unk_71024746b0 mButtonHelper;
    /* 0x368 */ ButtonEventQueue* mButtonEvents = nullptr;
    // controls registered next to mControls (ScreenAppPictureBookUnk::sub_7100944004)
    /* 0x370 */ sead::FixedPtrArray<eui::ControlBase, 5> _370;
    // The units and buttons are parallel arrays (the setBuffer calls of the constructor: 400 entries each, the
    // storage follows the array header).
    /* 0x3a8 */ sead::FixedPtrArray<Unk_7102474e38, 400> mButtonUnits;
    /* 0x1038 */ sead::FixedPtrArray<eui::AnimButton, 400> mButtons;
    /* 0x1cc8 */ bool _1cc8 = true;
    /* 0x1cd0 */ sead::FixedPtrArray<u8, 400> _1cd0;
    /* 0x2960 */ u64 _2960 = 0;
    /* 0x2968 */ UiTimer _2968;
    /* 0x2980 */ sead::FixedPtrArray<u8, 400> _2980;

    // Unnamed helpers of ScreenEx (placeholder names after the addresses; the hubs of the UI: 20 / 52 / 62 callers).
    // 0x7100a480b4: the button of the pane that `path` (slash separated) resolves to
    eui::ButtonBase* sub_7100A480B4(const sead::SafeString& path);
    // 0x7100a48104 / 0x7100a48328: the pane / object `path` resolves to in the screen's layout (`out` receives the parent)
    nn::ui2d::Pane* sub_7100A48104(const sead::SafeString& path, nn::ui2d::Pane** parent);
    void* sub_7100A48328(const sead::SafeString& path, void* out);
    // 0x7100a4810c: the button whose layout is `layout`
    eui::ControlBase* sub_7100A4810C(const eui::LayoutEx* layout);
    eui::ControlBase* sub_7100A4815C(nn::ui2d::Pane* pane, nn::ui2d::Pane* target, bool* found);
    // 0x7100a48a18 / 48aac / 48b40 / 48bd4: m127 - m130 followed by ScreenChildEx::m81 - m84 of every ScreenChildEx child
    void sub_7100A48A18();
    void sub_7100A48AAC();
    void sub_7100A48B40();
    void sub_7100A48BD4();
    // 0x7100a47a5c (hub: 49 callers): copies the layout `source` under `name` and links its root pane next to /
    // below `base` (mode 0: before, 1: after, 2: first child, 3: last child); the flags select the follow-up
    // setups 0x7100a47bc4 / 0x7100a47d60 (declared only)
    eui::LayoutEx* sub_7100A47A5C(sead::Heap* heap, s32 mode, const eui::LayoutEx* source,
                                  const sead::SafeString& name, nn::ui2d::Pane* base, bool setup1,
                                  bool setup2);
    void sub_7100A47BC4(sead::Heap* heap, const eui::LayoutEx* source, eui::LayoutEx* layout);
    void sub_7100A47D60(sead::Heap* heap, const eui::LayoutEx* source, eui::LayoutEx* layout);
    // 0x7100a48258: appends a button's unit and the button itself
    void sub_7100A48258(Unk_7102474e38* unit, eui::AnimButton* button);
    // 0x7100a482a4 / 0x7100a482e8: index of / control with the layout in the screen's control list
    s32 sub_7100A482A4(const eui::ControlBase* control) const;
    eui::ControlBase* sub_7100A482E8(const eui::LayoutEx* layout) const;

    // New virtual slots of ScreenEx (CSV ScreenEx::mNN, 127-153). Only the trivial ones have known signatures.
    virtual void m127();
    virtual void m128();
    virtual void m129();
    virtual void m130();
    virtual void m131(void* a1);
    virtual void m132(void* a1);
    virtual void m133(void* a1, void* a2);
    virtual void m134(void* a1, void* a2);
    virtual void m135(void* a1, void* a2);
    virtual void m136(void* a1, void* a2);
    virtual void m137(void* a1, void* a2);
    virtual void m138(void* a1, void* a2);
    virtual void m139(void* a1, void* a2);
    virtual void m140(void* a1, void* a2);
    virtual s32 m141(const ksys::Message& message);
    virtual s32 m142(const ksys::Message& message);
    virtual const sead::Buffer<ButtonPanePath>* m143();
    // m144 - m153: call the hook m131 - m140 of the same argument(s), then forward the call to the slots 95 - 104
    // of every child that is a ScreenChildEx
    virtual void m144(void* a1);
    virtual void m145(void* a1);
    virtual void m146(void* a1, void* a2);
    virtual void m147(void* a1, void* a2);
    virtual void m148(void* a1, void* a2);
    virtual void m149(void* a1, void* a2);
    virtual void m150(void* a1, void* a2);
    virtual void m151(void* a1, void* a2);
    virtual void m152(void* a1, void* a2);
    virtual void m153(void* a1, void* a2);
};

KSYS_CHECK_SIZE_NX150(ScreenEx, 0x3610);

// Screen ids: the jump table of ScreenFactory::create (0x7100a81f34), which is also the index into
// eui::ScreenMgr's screen table.
struct ScreenId {
    enum : s32 {
        GamePadBG = 0,
        Title = 1,
        MainScreen3D = 2,
        Message3D = 3,
        AppCamera = 4,
        WolfLinkHeartGauge = 5,
        EnergyMeterDLC = 6,
        MainHorse = 7,
        MiniGame = 8,
        ReadyGo = 9,
        KeyNum = 10,
        MessageGet = 11,
        DoCommand = 12,
        SousaGuide = 13,
        GameTitle = 14,
        DemoName = 15,
        DemoNameEnemy = 16,
        Unk17 = 17,
        ShopBG = 18,
        ShopBtnList5 = 19,
        ShopBtnList20 = 20,
        ShopBtnList15 = 21,
        ShopInfo = 22,
        ShopHorse = 23,
        Rupee = 24,
        KologNum = 25,
        AkashNum = 26,
        MamoNum = 27,
        Time = 28,
        PauseMenuBG = 29,
        SeekPadMenuBG = 30,
        AppTool = 31,
        AppAlbum = 32,
        AppPictureBook = 33,
        AppMapDungeon = 34,
        MainScreenMS = 35,
        MainScreenHeartIchigekiDLC = 36,
        MainScreen = 37,
        MainDungeon = 38,
        ChallengeWin = 39,
        PickUp = 40,
        MessageTipsRunTime = 41,
        AppMap = 42,
        AppSystemWindowNoBtn = 43,
        AppHome = 44,
        MainShortCut = 45,
        PauseMenu = 46,
        PauseMenuInfo = 47,
        GameOver = 48,
        HardMode = 49,
        SaveTransferWindow = 50,
        MessageTipsPauseMenu = 51,
        MessageTips = 52,
        OptionWindow = 53,
        AmiiboWindow = 54,
        SystemWindowNoBtn = 55,
        ControllerWindow = 56,
        SystemWindow01 = 57,
        SystemWindow00 = 58,
        PauseMenuRecipe = 59,
        PauseMenuMantan = 60,
        PauseMenuEiketsu = 61,
        AppSystemWindow = 62,
        DLCWindow = 63,
        HardModeTextDLC = 64,
        Unk65 = 65,
        Unk66 = 66,
        Unk67 = 67,
        BoxCursorTV = 68,
        FadeDemo = 69,
        StaffRoll = 70,
        StaffRollDLC = 71,
        End = 72,
        DLCSinJuAkashiNum = 73,
        MessageDialog = 74,
        DemoMessage = 75,
        Unk76 = 76,
        PlainScreen = 77,
        Fade = 78,
        KeyBoradTextArea = 79,
        LastComplete = 80,
        OPtext = 81,
        LoadingWeapon = 82,
        MainHardMode = 83,
        LoadSaveIcon = 84,
        FadeStatus = 85,
        Skip = 86,
        ChangeController = 87,
        ChangeController2 = 88,
        DemoStart = 89,
        BootUp = 90,
        BootUp2 = 91,
        ChangeControllerNN = 92,
        AppMenuBtn = 93,
        HomeMenuCapture = 94,
        HomeMenuCapture2 = 95,
        HomeNixSign = 96,
        ErrorViewer = 97,
        ErrorViewer2 = 98,
    };
};

class ScreenPauseMenuInfo : public ScreenEx {
public:
    void m94() override;
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    void m96() override;
    ~ScreenPauseMenuInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuInfo, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    // 0x7100a3081c (1492 B, placeholder name): fills the info text records at _39f8 from the message set at
    // 0x71025f0710 for mode `mode` and ends with sub_7100934478(a2); mode 4 uses the extra record when
    // sub_7100A82E38() is true.
    void sub_7100A3081C(s32 mode, bool a2);
    // 0x7100a30df0 (CSV unnamed, declared only): refreshes the info for the pause menu's current tab
    void sub_7100A30DF0(bool a2);
    // 0x7100a2effc: updates gauge deltas and the deferred effect display
    void sub_7100A2EFFC();
    void sub_7100A31998(f32 time, s32 effect, s32 level);
    // A2E510 combines equipment resistance with deferred effect fields 3910/3914.
    void sub_7100A2E510(s32* hot, s32* cold, s32* fire);
    void sub_7100A2FEDC();
    void sub_7100A300AC();
    void sub_7100A2E844();
    void sub_7100A30510(u32 mode);
    // A30444 selects the tab endpoint; A306F4 animates the tab change.
    void sub_7100A30444(u32 mode);
    void sub_7100A306F4(s32 previous_mode, u32 mode);
    // 0x7100a313a8 (CSV unnamed, declared only): shows the info page for `page`
    void sub_7100A313A8(s32 page, bool a2);
    // 0x7100a31190 (CSV unnamed, declared only): refreshes the info when the pause menu closes
    void sub_7100A31190(bool a2);
    // 0x7100a30194 (CSV unnamed, declared only): resets the info panes before refilling them
    void sub_7100A30194();

    // A2CE68 stores the gauge singleton here.
    /* 0x3610 */ Unk_71025d6578* _3610;
    /* 0x3618 */ Unk_7102474c08 _3618;
    u8 _pad_3650[0x3688 - 0x3650];
    // A2CE68 creates State, Pos and GanbariPos animators in this order.
    /* 0x3688 */ eui::Animator* _3688;
    /* 0x3690 */ eui::Animator* _3690;
    /* 0x3698 */ eui::Animator* _3698;
    /* 0x36a0 */ eui::Animator* _36a0;
    /* 0x36a8 */ eui::Animator* _36a8;
    // 0x7100a2dc30 / 0x7100a2dcd8: preview heart / stamina changes in the pause menu.
    void sub_7100A2DC30(f32 delta);
    void sub_7100A2DCD8(f32 delta);

    /* 0x36b0 */ eui::Animator* _36b0;
    /* 0x36b8 */ eui::Animator* _36b8;
    // A2CE68 creates an AnimatorSet from ChangeR/ChangeL, then SlidePoint.
    /* 0x36c0 */ eui::AnimatorSet* _36c0;
    /* 0x36c8 */ u32 _36c8;
    u8 _pad_36cc[4];
    /* 0x36d0 */ eui::Animator* _36d0;
    /* 0x36d8 */ f32 _36d8;
    u8 _pad_36dc[4];
    /* 0x36e0 */ ::Unk_7102475050 _36e0;
    /* 0x3810 */ ::Unk_71024750c8 _3810;
    /* 0x38f0 */ f32 _38f0;
    /* 0x38f4 */ f32 _38f4;
    /* 0x38f8 */ f32 _38f8;
    /* 0x38fc */ f32 _38fc;
    /* 0x3900 */ u8 _3900;
    u8 _pad_3901[3];
    /* 0x3904 */ u8 _3904;
    u8 _pad_3905[3];
    // Setup 0x7100a2ce68 casts child 1 to Unk_710247bcb8 before storing this pointer.
    /* 0x3908 */ Unk_710247bcb8* _3908;
    // A2C890 initializes the deferred effect to -1 and the level/time to zero.
    /* 0x3910 */ s32 _3910;
    /* 0x3914 */ s32 _3914;
    /* 0x3918 */ f32 _3918;
    /* 0x391c */ u8 _391c;
    // Setup A2CE68 stores child 2; A2DDE4 writes temperature 39b8 and fire level 39bc.
    u8 _pad_391d[0x39a0 - 0x391d];
    /* 0x39a0 */ Unk_710247e0c8* _39a0;
    /* 0x39a8 */ s32 _39a8;
    /* 0x39ac */ s32 _39ac;
    /* 0x39b0 */ s32 _39b0;
    /* 0x39b4 */ s32 _39b4;
    /* 0x39b8 */ f32 _39b8;
    /* 0x39bc */ s32 _39bc;
    /* 0x39c0 */ u8 _39c0;
    u8 _pad_39c1[0x39c8 - 0x39c1];
    // A2CE68 checks ScreenChildEx then the leaf RTTI at 25da4a8 before inserting group 7 children.
    /* 0x39c8 */ sead::PtrArray<Unk_710247b960> _39c8;
    u8 _pad_39d8[0x39e8 - 0x39d8];
    /* 0x39e8 */ ScreenChildEx* _39e8;  // the control whose layout shows the number (T_Num_00)
    /* 0x39f0 */ u8 _39f0;
    u8 _pad_39f1[0x39f8 - 0x39f1];
    /* 0x39f8 */ Unk_7102474bc8 _39f8;
    // A2CE68 casts children 5 and 4 to ScreenChildEx before these stores.
    /* 0x3b50 */ ScreenChildEx* _3b50;
    /* 0x3b58 */ ScreenChildEx* _3b58;
    /* 0x3b60 */ eui::Animator* _3b60;
    /* 0x3b68 */ u8 _3b68;
    u8 _pad_3b69[0x3b70 - 0x3b69];
    // A2CB00 constructs this control; its final string ends at the next animator.
    /* 0x3b70 */ Unk_71024774a8 _3b70;
    /* 0x3c28 */ eui::Animator* _3c28;

    // 0x7100a30380 (placeholder name): shows `value` in the number pane of the control at 0x39e8
    void sub_7100A30380(s32 value);
    void sub_7100A31BE0();
    // 0x7100a31c64: forwards to the existing gauge-frame getter.
    f32 sub_7100A31C64() const;
    // 0x7100a31c74: read-only forwarding query; const spelling is inferred.
    eui::Animator* sub_7100A31C74() const;
    // 0x7100a31c70 (placeholder name): no callers or data references in the original; tail-calls eui::Screen::x_2
    void sub_7100A31C70();
    bool sub_7100A31C1C() const;
    // 0x7100a31988 (placeholder name): forwards to the member at 0x39f8
    void sub_7100A31988(bool flag);
};

class ScreenMessageTipsRunTime : public ScreenEx {
public:
    ScreenMessageTipsRunTime();
    ~ScreenMessageTipsRunTime() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)
    const char* getLayoutName_() const override;
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m93(sead::Heap* heap) override;
    void m101() override;

    /* 0x3610 */ eui::Animator* _3610{};
    sead::CriticalSection _3618;
    s32 _3658 = -1;
    u8 _365c{};
    s32 _3660 = -1;
    u8 _3664{};
    /* 0x3668 */ UiTimer _3668;
    u8 _3680{};
    s32 _3684 = -1;

    void sub_7100A268AC(s32, s32);
    // 0x7100a26954 (CSV ScreenMessageTipsRunTime::x; placeholder name): takes the requested tip, and after 15 frames
    // shows it (or drops it while sub_7100AA8F10 holds)
    void sub_7100A26954();
    // 0x7100a26a5c (CSV ScreenMessageTipsRunTime::x_0; declared only): sets up the tip `index`
    void sub_7100A26A5C(s32 index);
};

class ScreenDoCommand : public ScreenEx {
public:
    ScreenDoCommand();
    void m100() override;
    void m101() override;
    void m130() override;
    ~ScreenDoCommand() override;
    SEAD_RTTI_OVERRIDE(ScreenDoCommand, ScreenEx)

    /* 0x3610 */ u8 _3610[0x28]{};
    sead::PtrArray<Unk_Elem> _3638{};
    sead::PtrArray<Unk_Elem> _3648{};
    s32 _3658 = -1;
    s32 _365c = -1;
    s32 _3660 = -1;
    s32 _3664 = -1;

    // 0x7100a07cf4 (placeholder name): closes the screen (remembering the command at 0x365c in 0x3664) unless it is closed
    // or in state 3
    void sub_7100A07CF4();
    // 0x7100a07d18 (placeholder name): resets the two command slots at 0x3658 / 0x365c
    void sub_7100A07D18();

    // 0x7100a0768c (CSV ScreenDoCommand::setCommand)
    bool setCommand(s32 command);

    void sub_7100A0772C(s32);
    // 0x7100a07830 (placeholder name): while the player rides a horse, switches command 4 / 20 to the riding variant 5 / 21
    void sub_7100A07830();
};

// Placeholder for the object ScreenMainScreen3D keeps at 0x4090 (0xb0 bytes).
struct ScreenMainScreen3DSub {
    u8 _0[0xb0];
    // 0x710094745c (CSV unnamed; not decompiled)
    void sub_710094745C();
};

// Intrusive list entry tested by ScreenMainScreen3D::sub_7100A11D34.
struct ScreenMainScreen3DEntry {
    u8 _0[0x3c];
    /* 0x3c */ s32 mId;
    /* 0x40 */ nn::util::IntrusiveListNode mNode;
};

class ScreenMainScreen3D : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    const char* getLayoutName_() const override;
    void m84() override;
    void m87() override;
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    void m82() override;
    ~ScreenMainScreen3D() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen3D, ScreenEx)

    u8 _pad_3610[0x3b70 - 0x3610];
    using EntryList = nn::util::IntrusiveList<ScreenMainScreen3DEntry,
        nn::util::IntrusiveListMemberNodeTraits<ScreenMainScreen3DEntry, &ScreenMainScreen3DEntry::mNode>>;
    /* 0x3b70 */ EntryList mEntries;
    u8 _pad_3b80[0x3f34 - 0x3b80];
    /* 0x3f34 */ s32 _3f34;
    /* 0x3f38 */ u8 _3f38;
    u8 _pad_3f39[0x4010 - 0x3f39];
    /* 0x4010 */ u64 _4010;
    u8 _pad_4018[0x4090 - 0x4018];
    /* 0x4090 */ ScreenMainScreen3DSub _4090;
    /* 0x4140 */ u64 _4140;

    void sub_7100A115E4(s64);
    bool sub_7100A11B10(s64);
    bool sub_7100A11D34(s32);
};

// Information child: factory a17358, full ctor 98a1f4 and D1 98a2c8.
struct ScreenMainScreenUnk3648 : ScreenChildEx {
    explicit ScreenMainScreenUnk3648(eui::LayoutEx* layout);
    ~ScreenMainScreenUnk3648() override;
    bool m5(bool a1) override;
    void m16() override;
    void m24(sead::Heap* heap) override;
    void m25() override;
    // 0x710098a5d4 (CSV mainScreenMessageStuff; declared only)
    void sub_710098A5D4();
    // inline-only in the original; name is a guess: m16 and m25 (twice) repeat this sequence
    void clearAndClose_(bool a1) {
        _1f0.clear();
        _388 = 0;
        _148 = -1;
        _150.clear();
        _1a8 = false;
        _130.reset();
        ScreenChild::m6(a1);
    }

    // 0x710098a93c (CSV unnamed; declared only)
    void sub_710098A93C(s32 type, const sead::SafeString& text);
    // 0x710098ae8c (declared only)
    void sub_710098AE8C(s32 a1);
    // 0x710098b07c (placeholder name): when the option guide is up and the shown entry is one of the controller
    // types (8 / 9), clears the entry list and closes the child.
    void sub_710098B07C();

    // Element of the three-entry list at 0x1f0 (0x78-byte list nodes), as constructed inline by 0x98ae8c.
    struct Entry {
        s32 _0 = -1;  // type (8..13 are compared by slot 5)
        sead::FixedSafeString<64> _8;
        bool _60 = false;
    };

    /* 0x130 */ UiTimer _130;
    /* 0x148 */ s32 _148 = -1;  // type of the entry being shown (Entry::_0)
    /* 0x150 */ sead::FixedSafeString<64> _150;
    /* 0x1a8 */ bool _1a8 = false;
    /* 0x1b0 */ sead::CriticalSection _1b0;
    /* 0x1f0 */ sead::FixedObjList<Entry, 3> _1f0;
    /* 0x388 */ u8 _388 = 0;  // 0, 1, 2 (slot 25 moves 1 to 2)
};
static_assert(sizeof(ScreenMainScreenUnk3648) == 0x390);

// Item-pointer child at 0x3658: factory a17550, ctor 98b59c and D1 98b600.
struct ScreenMainScreenUnk3658 : ScreenChildEx {
    explicit ScreenMainScreenUnk3658(eui::LayoutEx* layout);
    ~ScreenMainScreenUnk3658() override;
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    void m21() override;
    void m24(sead::Heap* heap) override;
    void m25() override;
    /* 0x130 */ eui::Animator* mChangeType = nullptr;
    /* 0x138 */ eui::Animator* mItemChange = nullptr;
    /* 0x140 */ eui::Animator* mItemCancel = nullptr;
    /* 0x148 */ eui::Animator* mInvalid = nullptr;
    /* 0x150 */ s32 _150 = -1;
    /* 0x154 */ s32 _154 = -1;
    /* 0x158 */ bool mPendingLoad = false;
    u8 _159[7];
    /* 0x160 */ ksys::res::Handle* mTextureHandle = nullptr;
    /* 0x168 */ nn::ui2d::Material* mMaterial = nullptr;
    /* 0x170 */ nn::ui2d::ExternalTextureInfo mTexInfo;
};
static_assert(sizeof(ScreenMainScreenUnk3658) == 0x188);

// Embedded MainScreen gauge helper at 3CE8, with two destructor slots at 248EA70.
class Unk_710248ea70 {
public:
    virtual ~Unk_710248ea70();
    void sub_7100A1964C(eui::LayoutEx* layout, sead::Heap* heap);
    // inline-only in the original; name is a guess: the destructor (0x7100a1ea44) and ScreenMainScreen::m90
    // (0x7100a19e44) repeat this sequence
    void unload() {
        if (mTextureHandle) {
            mTextureHandle->requestUnload();
            const auto* fallback_texture = &mTexInfo;
            if (mMaterials[0])
                mMaterials[0]->GetTexMapArray()[0].ReplaceTextureInfo(fallback_texture);
            if (mMaterials[1])
                mMaterials[1]->GetTexMapArray()[0].ReplaceTextureInfo(fallback_texture);
        }
        _38 = -1;
        _40 = -1;
    }
    /* 0x08 */ eui::LayoutEx* mLayout = nullptr;
    /* 0x10 */ eui::Animator* mGauge = nullptr;
    /* 0x18 */ eui::Animator* mIconOff = nullptr;
    /* 0x20 */ eui::Animator* mFull = nullptr;
    /* 0x28 */ eui::Animator* mOut = nullptr;
    u8 _30[8];
    /* 0x38 */ s64 _38 = -1;
    /* 0x40 */ s64 _40 = -1;
    /* 0x48 */ ksys::res::Handle* mTextureHandle = nullptr;
    /* 0x50 */ nn::ui2d::Material* mMaterials[2]{};
    /* 0x60 */ eui::CapturePane* mCapturePane = nullptr;
    /* 0x68 */ nn::ui2d::ExternalTextureInfo mTexInfo;
};
static_assert(sizeof(Unk_710248ea70) == 0x80);

// The boss gauge info passed to ScreenMainScreen::sub_7100A1AB14 / sub_7100A1A4E4 (0x90 bytes, filled by
// EventPlayUiBossHpAction; name is a guess).
struct BossGaugeInfo {
    u64 _0 = 0;
    u32 _8 = 0;
    /* 0x0c */ u32 value = 0;
    /* 0x10 */ u32 maxValue = 0;
    /* 0x18 */ sead::FixedSafeString<64> name;
    /* 0x70 */ s32 actorId = -1;
    /* 0x78 */ sead::SafeString layoutName;
    /* 0x88 */ bool _88 = false;
    // PriestBossMetaAIRoot sets it from bit 0 of the boss's LifeRecoverInfo flags (master mode regeneration)
    /* 0x89 */ bool _89 = false;
};
static_assert(sizeof(BossGaugeInfo) == 0x90);

class ScreenMainScreen : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    void m85() override;
    void m88() override;
    bool isEnableControl() const override;
    void m90() override;
    ~ScreenMainScreen() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen, ScreenEx)
    const char* getLayoutName_() const override;
    // 0x7100a19c7c
    void m84() override;
    // 0x7100a19d78
    void m98() override;

    u8 _pad_3610[0x3620 - 0x3610];
    /* 0x3620 */ void* _3620;
    /* 0x3628 */ eui::Animator* _3628;  // stopped at the main screen mode frame (m84)
    u8 _pad_3630[0x3638 - 0x3630];
    // The screen's children (indices 0 - 6 of sub_7100A1A3C8 / sub_7100A1A460 are 3638, 3640, 3648, 3678, 3650, 3660,
    // 3658)
    /* 0x3638 */ ScreenChild* _3638;
    /* 0x3640 */ Unk_7102477110* _3640;
    /* 0x3648 */ ScreenMainScreenUnk3648* _3648;
    /* 0x3650 */ ScreenChild* _3650;
    /* 0x3658 */ ScreenMainScreenUnk3658* _3658;
    /* 0x3660 */ Unk_710247bcb8* _3660;
    u8 _pad_3668[4];
    /* 0x366c */ s32 _366c;  // the frame _3628 was last stopped at
    /* 0x3670 */ bool _3670;
    u8 _pad_3671[7];
    /* 0x3678 */ Unk_7102474c08 _3678;  // 0x38 bytes (0x7100a1ab68 / 0x7100a1ab94 call into it)
    /* 0x36b0 */ void* _36b0;
    // The two ints are written together by sub_7100A1ABF8 ({1, 0}) and separately by sub_7100A1ABC8.
    /* 0x36b8 */ s32 _36b8;
    /* 0x36bc */ s32 _36bc;
    u8 _pad_36c0[0x3704 - 0x36c0];
    /* 0x3704 */ s32 _3704;
    u8 _pad_3708[0x3720 - 0x3708];
    /* 0x3720 */ f32 _3720;  // -99.0f initially
    u8 _pad_3724[0x3728 - 0x3724];
    /* 0x3728 */ sead::CriticalSection _3728;  // destroyed by the destructor 0x7100a17ff4
    u8 _pad_3768[0x3968 - 0x3768];
    /* 0x3968 */ eui::LayoutEx* mLocationNameLayout;
    /* 0x3970 */ eui::LayoutEx* mLocationNameSLayout;
    u8 _pad_3978[0x3aa8 - 0x3978];
    /* 0x3aa8 */ u8 _3aa8;
    /* 0x3aa9 */ bool _3aa9;
    u8 _pad_3aaa[0x3ca8 - 0x3aaa];
    /* 0x3ca8 */ eui::LayoutEx* _3ca8;
    /* 0x3cb0 */ eui::Animator* _3cb0;
    /* 0x3cb8 */ eui::Animator* _3cb8;
    /* 0x3cc0 */ eui::Animator* _3cc0;
    /* 0x3cc8 */ u8 _3cc8;
    u8 _pad_3cc9[3];
    /* 0x3ccc */ UiTimer _3ccc;
    /* 0x3ce4 */ f32 mPreviousQuestFrame;
    /* 0x3ce8 */ Unk_710248ea70 mGaugeHelper;
    // Full ctor A17AF8 and setup A18464 group 7 cast through native RTTI 25DAC48.
    /* 0x3d68 */ Unk_710247c368* _3d68;
    u8 _pad_3d70[0x3dca - 0x3d70];
    /* 0x3dca */ bool _3dca;  // set by m84 while the main screen is on

    void sub_7100A1AC14();
    void sub_7100A1AC24(bool stop);
    void sub_7100A1ACB4();
    void sub_7100A1AD40();
    void sub_7100A1AE54();
    void sub_7100A1AF60();
    void sub_7100A1E958(s32 state);
    void sub_7100A1E968();
    void sub_7100A1E978();
    bool sub_7100A1E3EC(const ksys::qst::Quest* quest);

    bool sub_7100A1A1C4(s32 a1, bool a2);
    // 0x7100a1a3c8 / 0x7100a1a460 (placeholder names): open / close request (ScreenChild::m6) and "state 7" check of
    // child `index`
    bool sub_7100A1A3C8(s32 index, bool a2);
    bool sub_7100A1A460(s32 index);
    void sub_7100A1AB58(s32 a1);
    // 0x7100a1ab74 (CSV ScreenMainScreen::showInfoOverlayWithString)
    void showInfoOverlayWithString(s32 type, const sead::SafeString& text);

    void sub_7100A1A4E4(BossGaugeInfo* info);
    // 0x7100a1ab14 / 0x7100a1abc8 / 0x7100a1abe8 / 0x7100a1abf8 (placeholder names)
    void sub_7100A1AB14(BossGaugeInfo* info, f32 value);
    void sub_7100A1AB84(s32 a1);
    void sub_7100A1ABC8(s32 value);
    bool sub_7100A1ABE8() const;
    void sub_7100A1ABF8();
    // 0x7100a1a518 (CSV unnamed; declared only; the types are guesses)
    void sub_7100A1A518(BossGaugeInfo* info, bool a2);
    void sub_7100A1957C(s32 count);
    void sub_7100A1AB48();
    void sub_7100A1958C();
    bool sub_7100A1E28C(const ksys::qst::Quest* quest);
    bool sub_7100A1E214(const ksys::qst::Quest* quest);
    // 0x7100a1e454: updates the quest category message and animation.
    void sub_7100A1E454(const ksys::qst::Quest* quest);
    bool sub_7100A1E1E0();
    // 0x7100a1e44c (placeholder name): always 1.0
    static f32 sub_7100A1E44C();
    // 0x7100a1ab68 (placeholder name; called by Unk_7102474c08::sub_7100936254): the value of the gauge member
    f32 sub_7100A1AB68() const;
    // 0x7100a1de08: sends the native heart-alert message to the player.
    void sub_7100A1DE08();
    // 0x7100a1de60: tells the revival fairy / Zora hero actors (message 0x800007b)
    void sub_7100A1DE60();
    void sub_7100A1DE04();
    // 0x7100a1ab94 (placeholder name): runs the gauge update with this screen's animation step
    void sub_7100A1AB94();
    // 0x7100a1adc4 (placeholder name): closes the child screens on leaving the main screen.
    void sub_7100A1ADC4();
};

// The MessageTips screen (members from 0x300 recovered from the constructor).
class ScreenMessageTips : public Screen {
public:
    ScreenMessageTips();
    ~ScreenMessageTips() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTips, Screen)
    void m93(sead::Heap* heap) override;
    // 0x71010a88e4: tip-type sounds, opens the A button, closes the tips on the decide trigger (or when the type
    // changed)
    void m94() override;
    void m98() override;
    void m100() override;
    // 0x71010a8afc
    const char* getLayoutName_() const override;
    bool isEnableControl() const override { return true; }

    // 0x71010a87f0 (CSV unnamed, declared only): called by ui::sub_7100A981B0 with the tip type 18.
    bool sub_71010A87F0(s32 type);

    /* 0x300 */ eui::LayoutEx* _300{};
    /* 0x308 */ eui::Animator* _308{};
    /* 0x310 */ bool _310 = false;
    /* 0x318 */ Unk_7102509148 _318;
    /* 0x3a8 */ s32 _3a8 = 29;
    /* 0x3ac */ s32 _3ac = 29;
    /* 0x3b0 */ s32 _3b0 = 3;
    /* 0x3b4 */ s32 _3b4 = 0;
};

// Only the nominal types are recovered; owned members and construction remain undeclared.
class ScreenMessage3D : public Screen {
public:
    ScreenMessage3D();
    ~ScreenMessage3D() override;
    SEAD_RTTI_OVERRIDE(ScreenMessage3D, Screen)
    bool isEnableControl() const override;
    // 0x71010af818
    const char* getLayoutName_() const override;
    void sub_71010AE7C0(bool flag);
    // 0x71010ae548 (CSV unnamed, declared only): called by UI::sub_71010A6BEC.
    void sub_71010AE548(ksys::act::Actor* actor, bool flag);
    // 0x71010ae9e8 (CSV unnamed, declared only): called by UI::sub_71010A5B0C with the actor.
    bool sub_71010AE9E8(ksys::act::Actor* actor);
    // 0x71010ae190 (CSV unnamed): claim a free entry for an actor.
    void sub_71010AE190(ksys::act::Actor* actor, f32 x, u32 flags);
    // 0x71010adbc8 (slot 96): per-entry animation-step refresh + update driver
    void m94() override;
    // 0x71010ae104 (CSV unnamed): message lookup into _680, 0/1/2 return.
    s32 sub_71010AE104(const sead::SafeString& set, const sead::SafeString& label);
    // 0x71010aec24 (slot 85) / 0x71010aeacc (slot 103): reset all four entries
    // (identical twins; overrides of Screen::m83/m101).
    void m83() override;
    void m101() override;

    // One message entry (0xd0 bytes, linked through +0; the last of the four has a null link).
    // The entries are plain buffers: ScreenMessage3D's D1 destroys only the CriticalSection, so they
    // must have a trivial destructor (in particular they do NOT contain the +0x38 proc link below).
    struct Item {
        Item* mNext;
        u8 _8[0xd0 - 8];
    };

    // One entry referenced by _300/_660. Not owned by the screen (never destroyed/freed by it):
    // +0x8 is the layout, +0x10 an animation state, +0x38 an embedded proc link
    // (hasProc/hasProcById/reset callers in the subs), +0x48 a timer/counter.
    struct EntryState {
        u8 _0[0x30];
        /* 0x30 */ u32 _30;
        /* 0x34 */ u32 _34;
        /* 0x38 */ u32 _38;
        u8 _3c[0x58 - 0x3c];
        /* 0x58 */ u8 _58;
    };

    struct Entry {
        virtual ~Entry();
        /* 0x8 */ eui::LayoutEx* _8;
        /* 0x10 */ EntryState* _10;
        /* 0x18 */ eui::TextBoxEx* _18;
        /* 0x20 */ eui::Animator* _20;
        /* 0x28 */ eui::Animator* _28;
        u8 _30[0x38 - 0x30];
        /* 0x38 */ ksys::act::BaseProcLink m38;
        /* 0x48 */ u32 _48;
        /* 0x4c */ s32 _4c;
        /* 0x50 */ f32 _50;
        /* 0x54 */ f32 _54;
        /* 0x58 */ bool _58;
        /* 0x59 */ bool _59;
        /* 0x5a */ bool _5a;
        /* 0x5b */ bool _5b;
        /* 0x60 */ eui::MessageString _60;
        /* 0x70 */ u32 _70;
        /* 0x74 */ f32 _74;
        /* 0x78 */ u8 _78[4];
        /* 0x7c */ u32 _7c;
        /* 0x80 */ u32 _80;
        /* 0x84 */ u32 _84;
        // App-tag delegate for processAppTag (bound by the entry creator, not by any Entry method).
        /* 0x88 */ sead::Delegate1<Entry, const sead::MessageSet<char16>::TagInfo*> _88;
        /* 0xa8 */ bool _a8;
        /* 0xac */ f32 _ac;
        /* 0xb0 */ f32 _b0;
        /* 0xb4 */ f32 _b4;
        // 0x71010aeb60 (CSV unnamed)
        void sub_71010AEB60();
        // 0x71010aeff8 (CSV unnamed)
        void sub_71010AEFF8();
        // 0x71010ade64 / 0x71010af290 (CSV unnamed / placeholder): state update / look-at-camera sync
        void sub_71010ADE64();
        void sub_71010AF290();
        // 0x71010aecb8 (CSV unnamed): tag invoke (the method bound to the _88 delegate by the entry
        // creator; dispatches the voice/applause tags to the dialog helpers).
        void sub_71010AECB8(const sead::MessageSet<char16>::TagInfo* tag);
    };

    /* 0x300 */ sead::PtrArray<Entry> _300;
    /* 0x310 */ Item* _310;
    /* 0x318 */ Item* _318;
    /* 0x320 */ Item _320[4];
    /* 0x660 */ void* _660[4];
    /* 0x680 */ eui::MessageString _680;
    /* 0x690 */ f32 _690;
    u8 _694[0x698 - 0x694];
    /* 0x698 */ sead::CriticalSection _698;
};

// The class of the three message dialog screens (ids ScreenId::Unk17, MessageDialog and Unk76; constructor
// 0x71010b25c8 takes a bool). Only the nominal type and the members read by the UI facade are recovered.
class ScreenMessageDialog : public Screen {
public:
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;
    // 0x71010b5b60 (overrides eui::Screen::isEnableControl): always true
    bool isEnableControl() const override;
    // 0x71010b5a14 (slot 101): hands the dialog's result fields to the UI singleton, forgets the actor and resumes the sound ducker
    void m101() override;
    // 0x71010b5290 (slot 106): in state 3 clears the flag 0x10 of every button of the dialog
    void m106(eui::AnimButton* button) override;
    ~ScreenMessageDialog() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageDialog, Screen)
    // 0x71010b34d0
    const char* getLayoutName_() const override;
    void m99() override {}

    // 0x71010b25c8 (CSV ScreenMessageDialog::ctor)
    explicit ScreenMessageDialog(bool a1);

    // 0x71010b2788 / 0x71010b2884 / 0x71010b2a40 (CSV unnamed; not decompiled): the dialog's tag callbacks
    void sub_71010B2788(const sead::MessageSet<char16>::TagInfo* tag);
    bool sub_71010B2884(const char16* text, s32 length);
    u32 sub_71010B2A40(const sead::MessageSet<char16>::TagInfo* tag, sead::WBufferedSafeString* out);

    u8 _2fc[0x300 - 0x2fc];
    /* 0x300 */ eui::LetterAnimControl* _300 = nullptr;
    /* 0x308 */ eui::LetterAnimControl* _308 = nullptr;
    /* 0x310 */ sead::Delegate1<ScreenMessageDialog, const sead::MessageSet<char16>::TagInfo*> _310{
        this, &ScreenMessageDialog::sub_71010B2788};
    /* 0x330 */ sead::Delegate2R<ScreenMessageDialog, const char16*, s32, bool> _330{
        this, &ScreenMessageDialog::sub_71010B2884};
    /* 0x350 */ s32 _350 = 10;
    u8 _354[0x358 - 0x354];
    u8 _358[0x370 - 0x358] = {};
    // The "Type" animator (created in 0x71010b34f0); its frame selects the dialog frame style
    /* 0x370 */ eui::Animator* _370 = nullptr;
    u8 _378[0x3a0 - 0x378] = {};
    // The message being scanned (its mString/_8 are walked by sub_71010B307C/3294 as text/length;
    // sub_71010B2B30 assigns it as a whole).
    /* 0x3a0 */ eui::MessageString _3a0;
    // The constructor points each string at its inline buffer and sets capacity 256.
    /* 0x3b0 */ sead::FixedSafeString<256> _3b0;
    /* 0x4c8 */ sead::FixedSafeString<256> _4c8;
    /* 0x5e0 */ s32 _5e0 = -1;
    /* 0x5e4 */ s32 _5e4 = 0;
    /* 0x5e8 */ s32 _5e8 = 0;
    /* 0x5ec */ s32 _5ec = -1;
    u8 _5f0[0x718 - 0x5f0];
    /* 0x718 */ s32 _718 = 0;
    // The dialog's actor (set by sub_71010B306C, linked by _728).
    /* 0x720 */ ksys::act::Actor* _720 = nullptr;
    /* 0x728 */ ksys::act::BaseProcLink _728;
    /* 0x738 */ s32 _738 = -1;
    /* 0x73c */ s32 _73c = 0;
    // Vertical text offset, initialized to 3.0f and written to the output pane.
    /* 0x740 */ f32 _740 = 3.0f;
    /* 0x744 */ s32 _744 = 0;
    /* 0x748 */ sead::Delegate2R<ScreenMessageDialog, const sead::MessageSet<char16>::TagInfo*,
                                  sead::WBufferedSafeString*, u32>
        _748{this, &ScreenMessageDialog::sub_71010B2A40};
    /* 0x768 */ u16 _768 = 0xffff;
    /* 0x76a */ bool _76a;
    u8 _76b[0x76d - 0x76b] = {};
    /* 0x76d */ u8 _76d = 0;
    u8 _76e[0x772 - 0x76e] = {};
    /* 0x772 */ u8 _772 = 0;
    /* 0x773 */ u8 _773 = 0;
    /* 0x774 */ s32 _774 = 0;
    // Created by ScreenBase::doCreateTagProcessor_ in 0x71010b34f0.
    /* 0x778 */ TagProcessor* _778 = nullptr;
    /* 0x780 */ void* _780 = nullptr;

    // 0x71010b2b30: set the message archive / message name and populate the letter controls.
    s32 sub_71010B2B30(const sead::SafeString& set_name, const sead::SafeString& message_name);

    // 0x71010b343c / 0x71010b34b4 / 0x71010b34a0: called by UI::sub_71010A5C8C / setPlacedItemStockNum / sub_71010A7994.
    bool sub_71010B343C();
    void sub_71010B34B4(bool choice_mode, s32 stock);
    void sub_71010B34A0(bool a1);
    // 0x71010b2f5c / 0x71010b2f68 (placeholder names; called by UI::x_1): the choice count (_300->_61) and the value of
    // choice `index` (_300->_68)
    s32 sub_71010B2F5C() const;
    u16 sub_71010B2F68(s32 index) const;
    // 0x71010b2f84 (placeholder name; called by initMessageDialogName): set the dialog type and the speaker name
    void sub_71010B2F84(s32 type, const eui::MessageString& name);
    // 0x71010b306c (CSV unnamed): set the dialog's actor (stores it in _720, acquires _728).
    void sub_71010B306C(ksys::act::Actor* actor);
    // 0x71010b307c (CSV unnamed): scan the text for a voice tag, apply the emotion to the actor.
    void sub_71010B307C();
    // 0x71010b3294 (CSV unnamed): scan the text, record the kind in _774.
    void sub_71010B3294();
};

// Nominal types of two more screens (ScreenId::DemoMessage, ScreenId::ErrorViewer).
class ScreenDemoMessage : public Screen {
public:
    ScreenDemoMessage();
    ~ScreenDemoMessage() override;
    SEAD_RTTI_OVERRIDE(ScreenDemoMessage, Screen)
    // 0x710109ebb4
    const char* getLayoutName_() const override;

    /* 0x300 */ eui::MessageString _300;
    /* 0x310 */ void* _310{};
    /* 0x318 */ sead::FixedSafeString<256> _318;
    /* 0x430 */ sead::FixedSafeString<256> _430;
    /* 0x548 */ s32 _548 = -1;
    /* 0x550 */ eui::Animator* _550 = nullptr;
    /* 0x558 */ bool _558 = false;
    /* 0x559 */ bool _559 = false;

    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m101() override;

    // 0x710109e94c / 0x710109e96c: called by UI::sub_71010A7034 / sub_71010A6D84.
    void sub_710109E94C();
    void sub_710109E96C();
    // 0x710109e978: slot 0x558 is a bool
    void sub_710109E978();
};

// 0x7101ec39d4 (object whose address the ScreenErrorViewer ctor stores in _308; contents unknown).
struct Unk_7101EC39D4 {};
extern Unk_7101EC39D4 sUnk_7101EC39D4;

class ScreenErrorViewer : public Screen {
public:
    ScreenErrorViewer();
    ~ScreenErrorViewer() override;
    SEAD_RTTI_OVERRIDE(ScreenErrorViewer, Screen)
    bool isEnableControl() const override;
    // 0x710109ff58
    const char* getLayoutName_() const override;
    void sub_710109EE10(s32 error_code);
    // 0x710109fe14 (placeholder name): when the error code is 0, sets the UI flag _a4 to 2
    void sub_710109FE14();
    // 0x710109fe34 (slot 101): publishes the viewer's mode in the UI singleton's _a4 (screen id 0x61 only)
    void m101() override;
    // 0x710109fd90 (slot 107)
    void m107(eui::AnimButton* button) override;

    u8 _2fc[0x300 - 0x2fc];
    /* 0x300 */ s32 _300 = 0x100;
    /* 0x304 */ u8 _304[0x308 - 0x304];
    /* 0x308 */ void* _308 = &sUnk_7101EC39D4;
    /* 0x310 */ s32 mErrorCode = -1;
    /* 0x314 */ u32 _314;
    /* 0x318 */ u32 _318;
    /* 0x31c */ u8 _31c = 0;
    /* 0x31d */ bool _31d = false;
    u8 _31e[0x320 - 0x31e];
    // 0x320 .. 0x36c is zeroed by one memset; the three buttons are at 0x340 / 0x348 / 0x350
    struct Buttons {
        u8 _0[0x20];
        eui::AnimButton* _340;
        eui::AnimButton* _348;
        eui::AnimButton* _350;
        u8 _358[0x4c - 0x38];
    };
    /* 0x320 */ Buttons _320{};
};

// Only the nominal type and the three state words checked by UI::sub_71010A5CFC / sub_71010A5DB0 / sub_71010A5E64
// are recovered (the constructor, 0x71010a4560, initialises them to 3).
class ScreenMainDungeon : public Screen {
public:
    ~ScreenMainDungeon() override;
    SEAD_RTTI_OVERRIDE(ScreenMainDungeon, Screen)
    // 0x71010a486c
    const char* getLayoutName_() const override;
    void m93(sead::Heap* heap) override;
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    // 0x71010a4f24 / 0x71010a4f3c / 0x71010a4f64 (placeholder names): state changes that close the screen
    void sub_71010A4F24();
    void sub_71010A4F3C();
    void sub_71010A4F64();

    // 0x71010a53f0 (slot 101): starts the close animation of the three layouts at 0x9d0 / 0x9d8 / 0x9e0
    void m101() override;

    // 0x71010a4560 (CSV ScreenMainDungeon::ctor)
    ScreenMainDungeon();

    // A message and two strings (one per layout: message, title, location name)
    struct Entry {
        eui::MessageString message;
        sead::FixedSafeString<256> _10;
        sead::FixedSafeString<256> _128;
    };
    static_assert(sizeof(Entry) == 0x240);

    /* 0x2fc */ s32 _2fc = 3;
    /* 0x300 */ s32 _300 = 3;
    /* 0x304 */ s32 _304 = 3;
    /* 0x308 */ s32 _308 = 0;
    /* 0x310 */ Entry _310;
    /* 0x550 */ Entry _550;
    /* 0x790 */ Entry _790;
    /* 0x9d0 */ eui::LayoutEx* _9d0 = nullptr;
    /* 0x9d8 */ eui::LayoutEx* _9d8 = nullptr;
    /* 0x9e0 */ eui::LayoutEx* _9e0 = nullptr;
    // setup 10a4f8c and update 10a506c use these pointers.
    /* 0x9e8 */ eui::TagProcessor* _9e8 = nullptr;
    /* 0x9f0 */ eui::CapturePane* _9f0 = nullptr;
    /* 0x9f8 */ eui::CapturePane* _9f8 = nullptr;
    /* 0xa00 */ eui::CapturePane* _a00 = nullptr;
    /* 0xa08 */ eui::CapturePane* _a08 = nullptr;
};

// The fade screen (id 78): a full-screen fade that can also show a loading tip; its tip texts are queued in a ring
// buffer (_3b8 .. _3c8, storage _3cc).
class Fade : public Screen {
public:
    Fade();
    ~Fade() override;
    SEAD_RTTI_OVERRIDE(Fade, Screen)
    bool isEnableControl() const override;
    void open(s32 option) override;
    void close(s32 option) override;
    const char* getLayoutName_() const override;
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;
    bool isOpenEnd_() override;
    void m74(f32 progress) override;
    void m93(sead::Heap* heap) override;

    void sub_71010A0EE8(f32 progress);
    // 0x71010a1b24 (slot 101): clears the tip queue, refreshes the tip message and the draw target, tells the sound manager
    void m101() override;
    void m99() override {}
    // 0x71010a172c (CSV Fade::updateTipMessage; declared only)
    void updateTipMessage();
    // 0x71010a0b88 (placeholder name): whether the animator at _300 is at its last frame
    bool sub_71010A0B88() const;
    // 0x71010a0bbc: starts the colour animator forwards / backwards
    void x(s32 forward);
    // 0x71010a0b6c
    void stopColorAnimatorAt(s32 where);
    // 0x71010a0be0 / 0x71010a0be8 / 0x71010a0d34 / 0x71010a0d40
    void x_1(s32 type);
    void x_2();
    void setStartedMaybe(bool started);
    void clearSomeTipsField();

    /* 0x300 */ eui::Animator* _300 = nullptr;
    /* 0x308 */ eui::AnimatorSet _308;
    /* 0x328 */ eui::AnimatorSet _328;
    /* 0x348 */ eui::AnimatorSet* _348{};
    /* 0x350 */ eui::AnimatorSet* _350{};
    /* 0x358 */ eui::Animator* _358{};
    /* 0x360 */ eui::Animator* _360{};
    /* 0x368 */ eui::Animator* _368{};
    /* 0x370 */ eui::Animator* _370{};
    /* 0x378 */ eui::Animator* _378{};
    /* 0x380 */ eui::Animator* _380{};
    /* 0x388 */ eui::Animator* _388{};
    /* 0x390 */ eui::TagProcessor* _390{};
    /* 0x398 */ eui::Animator* _398{};
    /* 0x3a0 */ eui::Animator* _3a0{};
    /* 0x3a8 */ bool _3a8{};
    /* 0x3ac */ s32 _3ac = 1;
    /* 0x3b0 */ f32 _3b0 = 0;
    // Two tip texts (string pointers); 4-byte aligned, the storage starts at 0x3cc.
    struct TipEntry {
        u32 _0[4];
    };
    /* 0x3b8 */ sead::FixedRingBuffer<TipEntry, 100> mTips;
    /* 0xa10 */ s32 _a10 = 0;
    /* 0xa14 */ s32 _a14 = 0;
    /* 0xa18 */ f32 _a18 = 0;
    /* 0xa1c */ f32 _a1c = 90.0f;
    /* 0xa20 */ s32 _a20 = -1;
    /* 0xa24 */ bool _a24 = false;
    /* 0xa25 */ bool _a25 = false;
    /* 0xa26 */ bool _a26 = false;
};

// 0x71010a0de0 (placeholder name): the sound kind (0..5) of the fade demo screen's state
ksys::snd::UiSoundKind sub_71010A0DE0(bool a, bool b, s32 c);

class ScreenFadeDemo : public Screen {
public:
    ScreenFadeDemo();
    ~ScreenFadeDemo() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeDemo, Screen)
    // 0x71010a076c
    const char* getLayoutName_() const override;
    bool isOpenEnd_() override;
    void m74(f32 progress) override;
    void m98() override;
    void m100() override;
    void m101() override;
    void m94() override {}
    void m99() override {}
    // 0x71010a01f8: `_350 = value` then updates the fade animators.
    void sub_71010A01F8(s32 value);
    // 0x71010a0200 (declared only): updates the selected animator and layout transforms.
    void sub_71010A0200();
    // 0x71010a01a8 / 0x71010a01c4 (placeholder names): the same as Fade::stopColorAnimatorAt / whether the animator
    // is at its last frame
    void sub_71010A01A8(s32 where);
    bool sub_71010A01C4();

    /* 0x300 */ eui::Animator* _300{};
    /* 0x308 */ eui::AnimatorSet _308;
    /* 0x328 */ eui::AnimatorSet _328;
    /* 0x348 */ eui::Animator* _348{};
    /* 0x350 */ s32 _350 = 1;
    /* 0x354 */ s32 _354 = -1;
    /* 0x358 */ bool _358 = false;
};

// Nominal types of more Screen (not ScreenEx) leaf classes; only their constructors are recovered.
class ScreenChangeControllerNN : public Screen {
public:
    ScreenChangeControllerNN();
    ~ScreenChangeControllerNN() override;
    SEAD_RTTI_OVERRIDE(ScreenChangeControllerNN, Screen)
    // 0x710109df74
    const char* getLayoutName_() const override;
    // 0x710109deac (overrides Screen::m94): closes the screen with option -4 when it is open
    void m94() override;
};

class ScreenHomeNixSign : public Screen {
public:
    ScreenHomeNixSign();
    ~ScreenHomeNixSign() override;
    SEAD_RTTI_OVERRIDE(ScreenHomeNixSign, Screen)
    // 0x71010a2258
    const char* getLayoutName_() const override;

    /* 0x2fc */ f32 _2fc = 0;

    // 0x71010a215c (placeholder name for the override of Screen::m98): resets _2fc
    void m98() override;
    // 0x71010a2164 (slot 94): counts _2fc up by the animation step while the screen is open and closes it at 30
    void m94() override;
};

class ScreenBoxCursorTV : public Screen {
public:
    ScreenBoxCursorTV();
    ~ScreenBoxCursorTV() override;
    SEAD_RTTI_OVERRIDE(ScreenBoxCursorTV, Screen)
    void m93(sead::Heap* heap) override;
    // 0x710109db4c
    const char* getLayoutName_() const override;

    /* 0x300 */ eui::Animator* _300{};
};

class ScreenLoadSaveIcon : public Screen {
public:
    ScreenLoadSaveIcon();
    ~ScreenLoadSaveIcon() override;
    SEAD_RTTI_OVERRIDE(ScreenLoadSaveIcon, Screen)
    // 0x71010a4380
    const char* getLayoutName_() const override;
    // 0x71010a3f6c (overrides Screen::m93): creates the layout "Pa_SaveIcon_00" and its "Type" / "Color" animators
    void m93(sead::Heap* heap) override;

    // 0x71010a3f10 / 0x71010a3f3c (placeholder names): set the flag at 0x318 / 0x319; a rising edge restarts the fade
    // (90.0 at 0x31c / the pair 16.0, 10.0 at 0x320)
    void sub_71010A3F10(bool on);
    void sub_71010A3F3C(bool on);
    // 0x71010a42e0 (slot 101): shows the icon again and starts the close animation of the layout
    void m101() override;

    /* 0x300 */ eui::LayoutEx* _300{};
    /* 0x308 */ void* _308{};
    /* 0x310 */ void* _310{};
    /* 0x318 */ bool _318 = false;
    /* 0x319 */ bool _319 = false;
    /* 0x31a */ bool _31a = true;
    /* 0x31c */ f32 _31c = 0;
    /* 0x320 */ f32 _320 = 0;
    /* 0x324 */ f32 _324 = 0;
};

// State objects of ScreenGameOver (CSV: unnamed data, 0x71025edda0 / 0x71025ede00).
extern const ksys::StateBase sUnk_71025edda0;
extern const ksys::StateBase sUnk_71025ede00;

class ScreenGameOver : public ScreenEx {
public:
    ScreenGameOver();
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m101() override;
    void m99() override;
    void m100() override;
    // 0x7100a0a770: shows the sub text of the focused button (tag 0x78: "0000", 0x79: "0001" of LayoutMsg/GameOver_00)
    void m102(eui::AnimButton* button) override;
    void m106(eui::AnimButton* button) override;
    bool isEnableControl() const override;
    ~ScreenGameOver() override;
    SEAD_RTTI_OVERRIDE(ScreenGameOver, ScreenEx)

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();

    /* 0x3610 */ u8 _3610{};
    u8 _pad_3611[3];
    /* 0x3614 */ s32 _3614 = 7;
    /* 0x3618 */ eui::Animator* _3618 = nullptr;
    /* 0x3620 */ nn::ui2d::Pane* _3620 = nullptr;

    bool sub_7100A0A8D8();
    bool sub_7100A0A914();
};

extern const ksys::StateBase sUnk_71025f1bf0;
extern const ksys::StateBase sUnk_71025f1cb0;
extern const ksys::StateBase sUnk_71025f1c50;
extern const ksys::StateBase sUnk_71025f1d10;
extern const ksys::StateBase sUnk_71025f1d70;

class ScreenRupee : public ScreenEx {
public:
    ScreenRupee();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenRupee() override;
    SEAD_RTTI_OVERRIDE(ScreenRupee, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m99() override;
    void m69() override;
    void m100() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();

    /* 0x3610 */ u8 _3610{};
    s32 _3614{};
    s32 _3618{};
    /* 0x361c */ UiTimer _361c;
    s32 _3634 = 4;
    Unk_7102474b78 _3638;
    Unk_7102474b58 _3678{this};
    sead::CriticalSection _36d0;

    void sub_7100A410D8(s32);
    void sub_7100A41558();
    bool sub_7100A41440();
    bool sub_7100A41354(bool);
    void sub_7100A414A0();
    void sub_7100A41264(s32 mode);
};

// State object of the number screens (CSV: unnamed data; a StateTemplate<ScreenKologNum>, 0x71025eed10).
extern const ksys::StateBase sUnk_71025eed10;
extern const ksys::StateBase sUnk_71025eec50;
extern const ksys::StateBase sUnk_71025eecb0;
extern const ksys::StateBase sUnk_71025eed70;

class ScreenKologNum : public ScreenEx {
public:
    ScreenKologNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenKologNum() override;
    SEAD_RTTI_OVERRIDE(ScreenKologNum, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m69() override;
    void m99() override;
    void m100() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    /* 0x3610 */ u8 _3610{};
    s32 _3614{};
    s32 _3618{};
    /* 0x361c */ UiTimer _361c;
    /* 0x3634 */ s32 _3634 = -1;
    Unk_7102474b78 _3638;

    void sub_7100A0EF5C(s32 a1);

    void sub_7100A0F098();
    bool sub_7100A0F038();
    bool sub_7100A0EFA4();
    void sub_7100A0F110(s32);
};

// State object of ScreenAkashNum (a StateTemplate<ScreenAkashNum>, 0x71025dc090).
extern const ksys::StateBase sUnk_71025dc090;
extern const ksys::StateBase sUnk_71025dc030;
extern const ksys::StateBase sUnk_71025dbfd0;
extern const ksys::StateBase sUnk_71025dc0f0;
// State object of ScreenHardMode (CSV: unnamed data, 0x710261ee98).
extern const ksys::StateBase sUnk_710261ee98;

class ScreenAkashNum : public ScreenEx {
public:
    ScreenAkashNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenAkashNum() override;
    SEAD_RTTI_OVERRIDE(ScreenAkashNum, ScreenEx)
    void m94() override;
    void m98() override;
    void m99() override;
    void m100() override;
    void m93(sead::Heap* heap) override;
    void m69() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    /* 0x3610 */ u8 _3610{};
    s32 _3614{};
    s32 _3618{};
    /* 0x361c */ UiTimer _361c;
    /* 0x3634 */ s32 _3634 = -1;
    Unk_7102474b78 _3638;

    void sub_71009CEEE0(s32 a1);

    void sub_71009CF058();
    bool sub_71009CEFBC();
    bool sub_71009CEF28();
    void sub_71009CF01C(s32);
};

// State objects of ScreenMamoNum (StateTemplate<ScreenMamoNum>, 0x71025ef578 / 0x71025ef518).
extern const ksys::StateBase sUnk_71025ef578;
extern const ksys::StateBase sUnk_71025ef4b8;
extern const ksys::StateBase sUnk_71025ef518;
extern const ksys::StateBase sUnk_71025ef5d8;

class ScreenMamoNum : public ScreenEx {
public:
    ScreenMamoNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenMamoNum() override;
    SEAD_RTTI_OVERRIDE(ScreenMamoNum, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m99() override;
    void m69() override;
    void m100() override;

    /* 0x3610 */ s32 _3610{};
    s32 _3614{};
    /* 0x3618 */ UiTimer _3618;
    s32 _3630 = -1;
    Unk_7102474b78 _3638;
    Unk_7102474b58 _3678{this};
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    void sub_7100A22A80(s32 a1);

    bool sub_7100A22B98();
};

class ScreenShopHorse : public ScreenEx {
public:
    ScreenShopHorse();
    // 0x7100a503dc (placeholder name): sets the Root1 flag (index 0) to 2
    void sub_7100A503DC();
    void m96() override;
    void m104(eui::AnimButton*) override;
    void m106(eui::AnimButton*) override;
    void m107(eui::AnimButton*) override;
    bool isEnableControl() const override;
    ~ScreenShopHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenShopHorse, ScreenEx)
    void m99() override;
    /* 0x3610 */ u32 _3610 = 0;
    /* 0x3614 */ u32 _3614 = 0;
    u64 _3618[0xa0 / 8] = {};
    /* 0x36b8 */ u32 _36b8 = 5;
    s32 _36bc = 0;
    /* 0x36c0 */ s32 _36c0 = -1;
    u8 _36c4[4];
    u64 _36c8[0x70 / 8] = {};
    /* 0x3738 */ u32 _3738;
    /* 0x373c */ u32 _373c;
    /* 0x3740 */ u32 _3740;
    /* 0x3744 */ u32 _3744;
    /* 0x3748 */ u8 _3748 = 0;

    void sub_7100A4EBA0(s32);
    // 0x7100a50750: parses the two-digit frame from `param` and stops `animator` at it (clamped to its size).
    void sub_7100A50750(eui::Animator* animator, const sead::SafeString& param);
};

// 0x7101eb6d7c / 0x7101eb6d80 (rodata words read by the ScreenShopHorse ctor; owner unknown)
extern const u32 sUnk_7101EB6D7C;
extern const u32 sUnk_7101EB6D80;

// State objects of ScreenMainShortCut (StateTemplate<...>; 0x71025ef170 / 0x71025ef290) and ScreenAppTool (0x71025ec670).
extern const ksys::StateBase sUnk_71025ef170;
extern const ksys::StateBase sUnk_71025ef1d0;
extern const ksys::StateBase sUnk_71025ef290;
extern const ksys::StateBase sUnk_71025ec670;
extern const ksys::StateBase sUnk_71025ec5b0;
extern const ksys::StateBase sUnk_71025ec610;
extern const ksys::StateBase sUnk_71025ec550;
// Flag bytes next to the states of ScreenAppTool (0x71025ec548 / 0x71025ec549; written by other screens at run time).
extern bool sUnk_71025ec548;
extern bool sUnk_71025ec549;
// Run-time state of ScreenAppTool (0x71025ec540: a record id followed by two boolean options, written by its
// constructor); native copy 0x71009fd640 combines the two options as a halfword. The flag bytes at 0x71025ec548 / 0x71025ec549 / 0x71025ec54a are separate globals.
struct AppToolState {
    s32 _0;
    bool _4;
    bool _5;
    // 0x71009fff58 (placeholder name): resets the record id to -1 and the halfword to 0
    void sub_71009FFF58();
};
extern AppToolState sUnk_71025ec540;
// 0x7102483490 (.data, initial value 6, the word before the ScreenAppSystemWindow vtable)
extern s32 sUnk_7102483490;
extern u8 sUnk_71025ec54a;

struct ScreenAppPictureBookUnk;

// The shortcut producerA20E5C and icon caller936EEC share this actual record.
struct ShortcutIconInfo {
    bool mEquipOnly = false;
    sead::FixedSafeString<128> mName;
    bool mEquipped = false;
    s32 mBreakState = -1;
    f32 mBreakFrame = 0;
    s32 mBowCount = -1;
    f32 mTextureFrame = -1;
    s32 mCategory = -1;
    s32 mValue = 0;
    s32 mNumber = 0;
    bool mPlayBombLoop = false;
    f32 mBombFrame = 0;
    u32 mIconCategory = 0;
    s32 mEffect = 2;
    eui::LayoutEx* mEffectLayout = nullptr;
};
static_assert(sizeof(ShortcutIconInfo) == 0xd8);

class ScreenMainShortCut : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    void m83() override;
    void m90() override;
    void sub_7100A1F684(s32 index);
    // 0x7100a21668 (CSV unnamed, declared only): builds the shortcut icon's text / icon from _3864
    void sub_7100A21668();
    void m96() override;
    void m98() override;
    void m99() override;
    bool isEnableControl() const override;
    ~ScreenMainShortCut() override;
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)
    // 0x7100a20230: override of Screen::m84; opens the screen when it is closed, then stops the _36e0 animator at its minimum
    void m84() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    u8 _pad_3610[0x3620 - 0x3610];
    /* 0x3620 */ eui::Animator* _3620;  // stopped at max while _3738 is empty (sub_7100A2080C)
    u8 _pad_3628[0x3638 - 0x3628];
    nn::ui2d::ArchiveHandle _3638;
    /* 0x36e0 */ eui::Animator* _36e0;
    /* 0x36e8 */ s32 _36e8;
    sead::PtrArray<Unk_Elem> _36f0;
    /* 0x3700 */ sead::BitFlag8 _3700;
    u8 _pad_3701[0x3720 - 0x3701];
    /* 0x3720 */ s32 _3720;
    u8 _pad_3724[0x372c - 0x3724];
    /* 0x372c */ s32 _372c;  // arrow count shown in T_BowNum_00
    u8 _pad_3730[0x3738 - 0x3730];
    /* 0x3738 */ sead::FixedSafeString<64> _3738;  // ctor 0x7100a1ef28; 0x58 bytes with its tail padding
    /* 0x3790 */ ScreenAppPictureBookUnk* _3790;
    /* 0x3798 */ eui::Animator* _3798;
    /* 0x37a0 */ eui::Animator* _37a0;
    u8 _pad_37a8[0x3850 - 0x37a8];
    sead::Buffer<u8> _3850;  // element type not known
    u8 _3860[4];
    /* 0x3864 */ s32 _3864;
    /* 0x3868 */ s32 _3868;
    /* 0x386c */ s32 _386c[0x15];
    u8 _pad_38c0[0x38c8 - 0x38c0];
    /* 0x38c8 */ s32 _38c8;
    /* 0x38cc */ u8 _38cc;
    u8 _pad_38cd[3];
    UiTexSlots _38d0;

    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();  // 0x7100a22074
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();

    bool sub_7100A20DD0();
    bool sub_7100A20E5C(u32 index, ShortcutIconInfo* info);
    // 0x7100a21604 (declared only; 100 bytes): selects entry `index` (0 .. 20) of the shortcut list
    void sub_7100A21604(s32 index);
    // 0x7100a1fa64 / 0x7100a1fabc / 0x7100a1fa74 / 0x7100a21908 (placeholder names): set the 0x38c8 value (and clear / set
    // the byte at 0x38cc); whether the animator at 0x37a0 is at its end / at its start
    void sub_7100A1FA64(s32 value);
    void sub_7100A1FABC();
    bool sub_7100A1FA74();
    bool sub_7100A21908();
    // 0x7100a2063c / 0x7100a209e4 / 0x7100a20ad4 / 0x7100a20cbc (CSV unnamed; declared only)
    void sub_7100A2063C();
    void sub_7100A209E4();
    void sub_7100A20AD4();
    void sub_7100A20CBC();
    // 0x7100a2080c: shows the arrow count when _3738 is empty and passes it on to the main screen
    void sub_7100A2080C();
};

class ScreenReadyGo : public ScreenEx {
public:
    ScreenReadyGo();
    ~ScreenReadyGo() override;
    SEAD_RTTI_OVERRIDE(ScreenReadyGo, ScreenEx)
    void m94() override;

    bool sub_7100A40BF8();
    // 0x7100a40b58 (CSV unnamed; not decompiled)
    void sub_7100A40B58(s32 a1);
};

class ScreenMiniGame : public ScreenEx {
public:
    ScreenMiniGame();
    ~ScreenMiniGame() override;
    SEAD_RTTI_OVERRIDE(ScreenMiniGame, ScreenEx)
    void m100() override;

    /* 0x3610 */ eui::LayoutEx* _3610[7];
    /* 0x3648 */ eui::Animator* _3648;
    /* 0x3650 */ u16 _3650;  // bit n: minigame layout n is open
    u8 _pad_3652[0x3658 - 0x3652];
    /* 0x3658 */ eui::Animator* _3658;
    /* 0x3660 */ u64 _3660;
    /* 0x3668 */ u8 _3668;
    u8 _pad_3669[0x366c - 0x3669];
    // The mini game's counters: a game data key (`_36x0`, set by the sub_7100A280A4 family from the caller's key), the
    // widget layout that shows the value and the last value read. Names / types are guesses from those functions.
    /* 0x366c */ s32 _366c;
    /* 0x3670 */ sead::SafeString _3670;
    /* 0x3680 */ eui::Animator* _3680;  // played when the counter of _3698 goes up
    /* 0x3688 */ eui::Animator* _3688;
    /* 0x3690 */ s32 _3690;
    /* 0x3698 */ sead::SafeString _3698;
    /* 0x36a8 */ f32 _36a8;
    /* 0x36b0 */ sead::SafeString _36b0;
    /* 0x36c0 */ s32 _36c0;
    /* 0x36c8 */ sead::SafeString _36c8;
    /* 0x36d8 */ eui::Animator* _36d8;  // played when the counter of _36c8 goes up
    /* 0x36e0 */ eui::Animator* _36e0;
    /* 0x36e8 */ eui::Animator* _36e8;

    void sub_7100A280A4(const sead::SafeString& a1);
    void sub_7100A2813C(const sead::SafeString& a1);
    void sub_7100A28264(const sead::SafeString& a1);
    void sub_7100A28318(const sead::SafeString& a1);
    void sub_7100A283B0(s32 a1);
    void sub_7100A28418(s32 a1);
    // 0x7100a27ec0 / 0x7100a27f9c (placeholder names): refresh the counters of layouts 2 / 4 from game data
    void sub_7100A27EC0();
    void sub_7100A27F9C();

    // 0x7100a27654 (placeholder name): the layout of mini game `index` is in state 2
    bool sub_7100A27654(s32 index) const;
    bool sub_7100A275EC(s32, s32);
    // 0x7100a2747c (CSV unnamed; declared only)
    bool sub_7100A2747C(s32 index, bool a2);
    void sub_7100A28088();
    bool openMinigameScreen(s32, s32);
};

// The state ScreenAppMap::mainRun changes to (0x71025df1e0; placeholder name).
extern const ksys::StateBase sUnk_71025df180;
extern const ksys::StateBase sUnk_71025df1e0;

// Full setup 9eab28 casts child group 5 to the same RTTI as Unk_710247c010 (9bf07c).
class Unk_710247c010;
class Unk_710247d8f8;
using ScreenAppMapUnk3c98 = Unk_710247c010;

// Map animation child: full ctor 9c0ebc, vtable 247c6c0 and independent 9c1474 / 9c1814 consumers.
struct ScreenAppMapUnk3c90 : ScreenChildEx {
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit ScreenAppMapUnk3c90(eui::LayoutEx* layout);
    ~ScreenAppMapUnk3c90() override;
    void m24(sead::Heap* heap) override;
    void m27() override;
    void m31() override;
    void m34() override;
    // 0x71009c107c: forwards to sub_71009C1080 (called by the map screen)
    void sub_71009C107C();
    void sub_71009C1080();
    void sub_71009C117C();
    void sub_71009C1198(s32 type);
    // 0x71009c1218 (placeholder name; not decompiled): with 0 and UiSubsys1::get38a8() == 1, sets a widget
    // string from a TU static name
    void sub_71009C1218(s32 type);
    void sub_71009C13D4(s32 type);
    void sub_71009C1888(s32 type);
    void sub_71009C1900();
    void sub_71009C1474(f32 speed, s32 type);
    void sub_71009C1530(s32 state);
    bool sub_71009C1814(s32 type) const;

    /* 0x130 */ s32 _130 = 2;
    /* 0x134 */ bool _134 = false;
    u8 _135[3];
    /* 0x138 */ eui::Animator* _138 = nullptr;
    /* 0x140 */ eui::Animator* _140 = nullptr;
    /* 0x148 */ eui::Animator* _148 = nullptr;
    /* 0x150 */ eui::Animator* _150 = nullptr;
    /* 0x158 */ eui::Animator* _158 = nullptr;
};
static_assert(sizeof(ScreenAppMapUnk3c90) == 0x160);

// The map footprint work buffer embedded in ScreenAppMapWidget at 0xb358 (vtable 0x710249d320, size 0x148).
// It holds the packed map cells and their flag bytes (one entry per cell, 0x38400 of each = 32 maps of
// 0x1c20), a state (0 idle, 1 allocated) and the heap the arrays live in. The step 0x7100a843c0 and the
// append 0x7100a866bc drive it; 0x7100a843f4 (not decompiled) consumes the pending cell.
// One footprint block of Unk_710249d330: a 0x50-byte header, then 48 rows of 0x4c0 bytes (300 packed cells
// and 4 unused words each).
struct FootPrintBlock {
    u8 _0[0x50];
    u32 cells[0x30][0x130];
};

class Unk_710249d330 {
public:
    virtual ~Unk_710249d330();
    // 0x7100a862a4 (placeholder name): allocates the arrays and the "FootPrintWorkHeap" and sets the state
    void init(sead::Heap* heap);
    // 0x7100a863c4 (placeholder name): allocates only the heap, when the arrays already exist
    void initHeap();
    // 0x7100a843c0 (placeholder name): steps the state (1 -> 2, 2 -> the work, 3 -> 0)
    void step();
    // 0x7100a86950 (placeholder name): the state is 0
    bool isIdle() const;
    // 0x7100a866bc (placeholder name): appends the packed cell for (x, y)
    void sub_7100A866BC(f32 x, f32 y, bool flag);
    // 0x7100a843f4 (not decompiled, 3184 bytes): the state-2 step that consumes the pending cell
    void sub_7100A843F4();
    // 0x7100a85fac (placeholder name): drops the invalid cells and the repeated ones, rewriting each kept
    // cell's zone.
    void sub_7100A85FAC();
    // 0x7100a86468 (placeholder name): appends the packed cell for (x, y), replacing the last cell when it is
    // the same one.
    void sub_7100A86468(f32 x, f32 y, bool flag);
    // 0x7100a85dc4 (placeholder name): copies the packed cells of the x1..x2 / y1..y2 rectangle out of the
    // blocks into the cell buffer (the first row / cell of each starts at t1 / ends at t2).
    void sub_7100A85DC4(s32 x1, s32 y1, s32 t1, s32 x2, s32 y2, s32 t2);

    /* 0x08 */ s32 mState = 0;
    /* 0x10 */ sead::Buffer<u32> mCells;
    /* 0x20 */ sead::Buffer<u8> mFlags;
    /* 0x30 */ s32 mCount = 0;
    /* 0x38 */ sead::Heap* mHeap = nullptr;
    /* 0x40 */ FootPrintBlock* mBlocks[32]{};
    /* 0x140 */ u8 _140 = 0;
    /* 0x141 */ bool mPending = false;
    u8 _142[6];
};
static_assert(sizeof(Unk_710249d330) == 0x148);

// Placeholder for the map widget the AppMap screen owns (byte 0xb33a is set by ScreenAppMap::mainEnter).
struct ScreenAppMapWidget : public ScreenChildEx {
    // 0x71009ae3c8: toggles map selection mode and refreshes the AppHome screen
    void sub_71009AE3C8();
    // Full native ctor 9a863c calls ScreenChildEx; factory 9e7f60 allocates 0xb538 bytes.
    explicit ScreenAppMapWidget(eui::LayoutEx* layout);
    ~ScreenAppMapWidget() override;
    // 0x71009a9438 (CSV unnamed): the timer at 0xb290 is done or the flag at 0xb1db is set
    bool sub_71009A9438();
    // 0x71009aeccc (placeholder name): fills the footprint cells of the current map into the buffer and stores
    // the last cell's position.
    void sub_71009AECCC();
    // Small accessors of the widget (lane2 s46; placeholder names, the field meanings are not known)
    void sub_71009A995C();
    // 0x71009a99f0 (CSV unnamed; not decompiled): applies the map scale level
    void sub_71009A99F0(s32 level);
    // 0x71009a9a38 (placeholder name): applies the scale level to the widget's map view parameters
    void sub_71009A9A38(s32 level);
    // 0x71009af058 (placeholder name): stores the tracker progress (per-block percentage) and hands the block
    // count to the save tracker object
    void sub_71009AF058(s8 count);
    s32 sub_71009AEF7C() const;
    sead::Vector2f sub_71009AEFEC() const;
    bool sub_71009AF0B4() const;
    bool sub_71009AF0C4() const;
    bool sub_71009AF0D8() const;
    bool sub_71009AF0EC() const;
    bool sub_71009AF0FC() const;
    bool sub_71009AF110() const;
    void sub_71009AF124(sead::Vector2f* out) const;
    u8 sub_71009AF178() const;
    bool sub_71009AF194() const;
    u8 sub_71009AF37C() const;
    // 0x71009af344 / 0x71009af364 (placeholder names): queue the current area's tiles (mode 0 / 1)
    void sub_71009AF344();
    void sub_71009AF364();
    // 0x71009a9b48 / 0x71009a9b7c / 0x71009a9e74 (placeholder names): set the mode at 0xb350 (0 / 1 / 2) and tell the map state
    void sub_71009A9B48();
    void sub_71009A9B7C();
    // 0x71009a9b08 (placeholder name): sets the map view's scale and its second scale from `value`
    void sub_71009A9B08(f32 value);
    void sub_71009A9E74(const sead::Vector3f* pos);
    // 0x71009a9f4c: removes the map rotation / offset from `position` and divides by the scale and the +0x60 factors
    void sub_71009A9F4C(const sead::Vector2f& position, sead::Vector2f* result);
    // 0x71009a9e90: the inverse of sub_71009A9F4C for a 3D position (factors, rotation, scale, +0x20 offset)
    void sub_71009A9E90(const sead::Vector3f& position, sead::Vector2f* result);
    // 0x71009a9b8c (364 bytes) / 0x71009aa024 (344 bytes): declared only
    void sub_71009A9B8C();
    void sub_71009AA024();
    // 0x71009aa004 (placeholder name): runs sub_71009AA024 for DLC version 0x200 and later
    void sub_71009AA004();
    // 0x71009af034 (placeholder name): the table entry `_b4fc` (0 for an index of 32 or more)
    f32 sub_71009AF034() const;
    // 0x71009aef88 (placeholder name): clears _b4ec / _b4f0 and decodes the packed signed (x, y) word at `_b370` into _b4b8 / _b4bc
    void sub_71009AEF88();
    // 0x71009ae04c (placeholder name): stores the map display mode at 0xb4a0; closes the home screen if it is open and,
    // unless the map flag is already set, sets / clears the UiSubsys1 map flag 0x38c8 and the widget's state bytes.
    void setMode(s32 mode);
    // 0x71009adef0 (placeholder name): centers the map on the packed cursor position (sub_7100950464), stores the
    // distance to the clamped cursor at 0xb520 and, once the 0xb4fc frame counter expires, resets it to 0x20 and
    // calls setMode(2).
    void sub_71009ADEF0();
    // 0x71009af35c: forwards to the normal map's reset (sub_71009A7FA4)
    void sub_71009AF35C();

    // 0x71009a8be8 (slot 14): sets the second half of the map tiles' textures to state 1, resets the map timer
    void m14() override;
    // 0x71009a9380 / 0x71009a9280 (slots 21 / 31)
    void m21() override;
    void m31() override;

    u8 _130[0x8d8 - 0x130];
    // the UI subsystem and the map position controller (sub_71009ADEF0)
    /* 0x8d8 */ UiSubsys1* mSubsys = nullptr;
    /* 0x8e0 */ Unk_7102475368* _8e0 = nullptr;
    /* 0x8e8 */ bool _8e8;
    /* 0x8f0 */ Unk_7102479c10 mNormalMap;
    /* 0xb338 */ bool _b338 = false;
    u8 _b339;
    /* 0xb33a */ u8 _b33a;
    u8 _b33b;
    /* 0xb33c */ u8 _b33c;  // button callback sets it; constructor and update clear it
    u8 _b33d[0xb34c - 0xb33d];
    /* 0xb34c */ u8 _b34c;
    u8 _b34d[0xb350 - 0xb34d];
    /* 0xb350 */ s32 _b350;
    u8 _b354[0xb358 - 0xb354];
    /* 0xb358 */ Unk_710249d330 mFootPrint;
    /* 0xb4a0 */ s32 _b4a0;
    /* 0xb4a4 */ s32 _b4a4;
    /* 0xb4a8 */ s32 _b4a8;
    /* 0xb4ac */ s32 _b4ac;
    /* 0xb4b0 */ f32 _b4b0;
    /* 0xb4b4 */ f32 _b4b4;
    /* 0xb4b8 */ f32 _b4b8;
    /* 0xb4bc */ f32 _b4bc;
    u8 _b4c0[0xb4e0 - 0xb4c0];
    /* 0xb4e0 */ f32 _b4e0;
    /* 0xb4e4 */ f32 _b4e4;
    /* 0xb4e8 */ f32 _b4e8;
    /* 0xb4ec */ u32 _b4ec;
    /* 0xb4f0 */ u32 _b4f0;
    u8 _b4f4[0xb4f8 - 0xb4f4];
    /* 0xb4f8 */ s16 _b4f8;  // save tracker progress written by sub_71009AF058
    /* 0xb4fa */ s8 _b4fa;
    /* 0xb4fb */ u8 _b4fb;

    /* 0xb4fc */ s8 _b4fc;
    u8 _b4fd;
    /* 0xb4fe */ s8 _b4fe;
    /* 0xb4ff */ u8 _b4ff;
    u8 _b500[0xb51c - 0xb500];
    /* 0xb51c */ f32 _b51c;
    /* 0xb520 */ f32 _b520;
    /* 0xb524 */ f32 _b524;
    u8 _b528[0xb538 - 0xb528];
};
static_assert(sizeof(ScreenAppMapWidget) == 0xb538);
static_assert(offsetof(ScreenAppMapWidget, mNormalMap) == 0x8f0);

class ScreenAppMap : public ScreenEx {
public:
    void m98() override;
    void m101() override;
    // 0x71009f273c (placeholder name; called by Unk_710247c010::sub_71009BE260): Unk_71025d69f0::sub_710094E064, then
    // closes the screen
    void sub_71009F273C();
    // 0x71009eab28 (placeholder name): looks up the two screen children (group 4 and group 5)
    void sub_71009EAB28();
    // 0x71009eb0e0 (placeholder name; called by m94): toggles the UiSubsys1 map flags 0x38c8 / 0x6e4 and plays the
    // animator at 0x3630 forwards or backwards
    void sub_71009EB0E0();
    // 0x71009eb178 / 0x71009eb250 (declared only): the map update's mode-1 and per-frame steps
    void sub_71009EB178();
    void sub_71009EB250();
    // 0x71009f1b18 (placeholder name): normalises `v` and scales it by _3c48 / _3c4c
    void sub_71009F1B18(sead::Vector2f* v) const;
    // 0x71009f1b9c (placeholder name): sets the animator at 0x3c88 to its max / min end and shows the temperature
    void sub_71009F1B9C();
    // 0x71009f1ca4 (placeholder name): plays the animator at 0x3638 and shows the time in `layout`
    void sub_71009F1CA4(eui::LayoutEx* layout);
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    // 0x71009f05c0 (placeholder name): positions the map pane (_3c30) at the map view position plus the view
    // offsets, scaled by the map scale
    void sub_71009F05C0();
    // 0x71009f1a64 (declared only; Unk_7102475d70::m18 passes the marker position)
    bool sub_71009F1A64(const sead::Vector3f* pos);
    bool sub_71009EA030() const;
    // 0x71009ea048 (placeholder name): resets the map widget when the screen owns one
    void sub_71009EA048();
    // 0x71009eedf4 (placeholder name): fills the map widget's footprint cells when the screen owns one
    void sub_71009EEDF4();
    // 0x71009ed41c (CSV Screen::x; placeholder name): the child of group / index cast to ScreenChildEx (the
    // original runs the cast twice)
    ScreenChildEx* getChildExMaybe(s32 group, s32 index);
    // 0x71009f23a8 (CSV unnamed): resets the two map children to mode 3, shows map mode 5 and clears the 0x38e0 /
    // 0x38e4 UI state
    void sub_71009F23A8();
    // 0x71009f2300 (CSV unnamed, declared only): map mode 0 / 1 / 5 for the two children, then shows map mode 6
    void sub_71009F2300(s32 mode);
    // 0x71009f1828 (CSV unnamed, declared only): applies a map child's selection to the map screen
    void sub_71009F1828(Unk_710247d8f8* child);
    // 0x71009ea738 / 0x71009eee04 / 0x71009eef98 (placeholder names): find the DLC map layout parts and create
    // their layout animators
    void sub_71009EA738();
    void sub_71009EA83C();
    void sub_71009EEE04();
    void sub_71009EEF98();
    // 0x71009ef5d0 (placeholder name): creates the map hint layout's four animators
    void sub_71009EF5D0();
    // 0x71009f0668 (placeholder name): creates the map cursor layout's six animators
    void sub_71009F0668();
    // 0x71009ed4e4 (CSV unnamed): switches the map children to the mode's state
    void sub_71009ED4E4(s32 mode);
    // 0x71009ed084 / 0x71009ed1e4 (placeholder names): play the map mode animators forward / backward
    void sub_71009ED084();
    void sub_71009ED1E4();
    // 0x71009ed860 (placeholder name): whether the map may open (system window closed, no map child active)
    bool sub_71009ED860();
    // 0x71009ed97c (CSV unnamed): plays the map-mode animators around the current mode
    void sub_71009ED97C();
    // 0x71009eda64 (CSV ScreenAppMap::x_2): the same animator change from get3900, called by x_1
    void x_2();
    // 0x71009f0be4 / 0x71009f2430 (CSV unnamed, declared only)
    void sub_71009F0BE4();
    void sub_71009F2430();
    // 0x71009ec780: x and y of the layout's root pane position
    void sub_71009EC780(sead::Vector2f* out) const;
    bool sub_71009EECD0() const;
    s32 sub_71009EED10() const;
    void m92(sead::Heap*) override;
    void m94() override;
    void m83() override;
    void m100() override;
    void m130() override;
    const sead::Buffer<ButtonPanePath>* m143() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    s32 getSlink2LocalPropertyNum_() const override;
    ~ScreenAppMap() override;
    SEAD_RTTI_OVERRIDE(ScreenAppMap, ScreenEx)

    // Own virtual slots 154 - 165 (vtable 0x7102481868): main / sub / demo state callbacks, each group enter / run /
    // leave and a fourth one returning a value.
    virtual void mainEnter();
    virtual void mainRun();
    virtual void mainLeave();
    virtual s32 m157();
    virtual void subEnter();
    virtual void subRun();
    virtual void subLeave();
    virtual s32 m161();
    virtual void demoEnter();
    virtual void demoRun();
    virtual void demoLeave();
    virtual s32 demoReenter();

    void sub_71009EF488(const sead::Vector3f* a1, s32 a2);
    void sub_71009EF51C(s32 a1);
    void sub_71009EF4EC(s32 a1, s32 a2);
    void sub_71009EF57C(f32 a1, s32 a2);

    bool sub_71009EF5A8(s32);
    // 0x71009e9f48 / 0x71009eb52c / 0x71009eb72c (CSV unnamed; declared only)
    bool sub_71009E9F48();
    // 0x71009e9f20 (placeholder name): false unless `_3ad1` is set; then the negated sub_71009E9F48
    bool sub_71009E9F20();
    // 0x71009eacc0 (CSV unnamed, 640 bytes; declared only)
    void sub_71009EACC0(s32 a1);
    void sub_71009EB52C();
    void sub_71009EB72C();
    bool sub_71009E9F10();
    // 0x71009f1dbc (CSV unnamed; not decompiled)
    void sub_71009F1DBC();
    // 0x71009f08f8 (748 B, placeholder name): builds a message string from the map state for `mode` (-1: no mode)
    // and sets T_Text_00 of the layout at 0x3bf8 with getMessage / setWidgetString.
    void sub_71009F08F8(s32 mode);


    /* 0x3610 */ ScreenAppMapWidget* _3610;
    /* 0x3618 */ Unk_710247d8f8* _3618;
    u8 _3620[0x3628 - 0x3620];
    // Map-mode animators: [3] .. [6] are the four mode transitions.
    /* 0x3628 */ eui::Animator* _3628[11];
    /* 0x3680 */ u32 _3680;
    u8 _3684[0x3690 - 0x3684];
    // The DLC map layout parts and their animators (created by sub_71009EEE04 / sub_71009EEF98).
    /* 0x3690 */ eui::LayoutEx* _3690 = nullptr;
    /* 0x3698 */ eui::Animator* _3698 = nullptr;
    /* 0x36a0 */ eui::Animator* _36a0 = nullptr;
    /* 0x36a8 */ eui::Animator* _36a8 = nullptr;
    /* 0x36b0 */ eui::Animator* _36b0 = nullptr;
    /* 0x36b8 */ eui::Animator* _36b8 = nullptr;
    /* 0x36c0 */ nn::ui2d::Pane* _36c0 = nullptr;
    /* 0x36c8 */ eui::LayoutEx* _36c8 = nullptr;
    /* 0x36d0 */ eui::Animator* _36d0 = nullptr;
    /* 0x36d8 */ eui::Animator* _36d8 = nullptr;
    /* 0x36e0 */ eui::Animator* _36e0 = nullptr;
    /* 0x36e8 */ eui::Animator* _36e8 = nullptr;
    /* 0x36f0 */ nn::ui2d::Pane* _36f0 = nullptr;
    /* 0x36f8 */ f32 _36f8 = 0.0f;
    u8 _36fc[0x3700 - 0x36fc];
    /* 0x3700 */ eui::LayoutEx* _3700 = nullptr;
    /* 0x3708 */ eui::Animator* _3708 = nullptr;
    /* 0x3710 */ eui::Animator* _3710 = nullptr;
    /* 0x3718 */ eui::Animator* _3718 = nullptr;
    /* 0x3720 */ eui::Animator* _3720 = nullptr;
    /* 0x3728 */ nn::ui2d::Pane* _3728 = nullptr;
    /* 0x3730 */ eui::LayoutEx* _3730 = nullptr;
    /* 0x3738 */ eui::Animator* _3738 = nullptr;
    /* 0x3740 */ nn::ui2d::Pane* _3740 = nullptr;
    /* 0x3748 */ eui::LayoutEx* _3748 = nullptr;
    /* 0x3750 */ nn::ui2d::Pane* _3750 = nullptr;
    u8 _3758[0x3778 - 0x3758];
    /* 0x3778 */ agl::RenderBuffer _3778;
    u8 _3778pad[0x37e0 - 0x3778 - sizeof(agl::RenderBuffer)];
    /* 0x37e0 */ agl::TextureData _37e0;
    u8 _37e0pad[0x3958 - 0x37e0 - sizeof(agl::TextureData)];
    /* 0x3958 */ eui::PictureEx* _3958 = nullptr;
    /* 0x3960 */ agl::driver::NVNsampler_ _3960;
    u8 _3960pad[0x39c8 - 0x3960 - sizeof(agl::driver::NVNsampler_)];
    /* 0x39c8 */ agl::driver::NVNtexture_ _39c8;
    u8 _39c8pad[0x3ad1 - 0x39c8 - sizeof(agl::driver::NVNtexture_)];
    /* 0x3ad1 */ u8 _3ad1;
    /* 0x3ad2 */ u8 _3ad2;  // written by sub_71009EF4EC / sub_71009EF51C
    u8 _3ad3;
    /* 0x3ad4 */ f32 _3ad4;
    /* 0x3ad8 */ f32 _3ad8;
    /* 0x3adc */ f32 _3adc;
    /* 0x3ae0 */ f32 _3ae0 = 0.0f;
    u8 _3ae4[0x3ae8 - 0x3ae4];
    // The map hint layout part and its animators (created by sub_71009EF5D0).
    /* 0x3ae8 */ eui::LayoutEx* _3ae8 = nullptr;
    /* 0x3af0 */ eui::Animator* _3af0 = nullptr;
    /* 0x3af8 */ eui::Animator* _3af8 = nullptr;
    /* 0x3b00 */ eui::Animator* _3b00 = nullptr;
    /* 0x3b08 */ eui::Animator* _3b08 = nullptr;
    u8 _3b10[0x3b18 - 0x3b10];
    /* 0x3b18 */ Unk_7102481e30 _3b18;
    u8 _3bf0[0x3bf8 - 0x3b18 - sizeof(Unk_7102481e30)];
    // The map cursor layout part and its six animators (sub_71009F0668).
    /* 0x3bf8 */ eui::LayoutEx* _3bf8 = nullptr;
    /* 0x3c00 */ eui::Animator* _3c00;
    /* 0x3c08 */ eui::Animator* _3c08;
    /* 0x3c10 */ eui::Animator* _3c10;
    /* 0x3c18 */ eui::Animator* _3c18;
    /* 0x3c20 */ eui::Animator* _3c20;
    /* 0x3c28 */ eui::Animator* _3c28;
    // The icon area / map panes found by m93 (N_IconArea_00 / Pa_Map_00).
    /* 0x3c30 */ Unk_PaneTransform* _3c30;
    /* 0x3c38 */ Unk_PaneTransform* _3c38;
    /* 0x3c40 */ Unk_PaneTransform* _3c40;
    /* 0x3c48 */ f32 _3c48;
    /* 0x3c4c */ f32 _3c4c;
    /* 0x3c50 */ s32 _3c50;  // the map scale level applied to _3610
    /* 0x3c54 */ bool _3c54;  // riding a horse
    /* 0x3c55 */ bool _3c55;  // previous _3c54
    u8 _3c56[0x3c60 - 0x3c56];
    /* 0x3c60 */ f32 _3c60;  // the temperature shown in T_Temp_00
    /* 0x3c64 */ u8 _3c64;
    /* 0x3c65 */ u8 _3c65;
    /* 0x3c66 */ u8 _3c66;
    u8 _3c67;
    /* 0x3c68 */ eui::LayoutEx* _3c68;
    /* 0x3c70 */ eui::Animator* _3c70;
    u8 _3c78[8];
    /* 0x3c80 */ eui::LayoutEx* _3c80;
    /* 0x3c88 */ eui::Animator* _3c88;
    /* 0x3c90 */ ScreenAppMapUnk3c90* _3c90;
    /* 0x3c98 */ ScreenAppMapUnk3c98* _3c98;
    /* 0x3ca0 */ xlink2::HandleSLink _3ca0;  // the map cursor movement sound (mc_CursorMove)
    /* 0x3cb0 */ u8 _3cb0;  // the camera rune was selected when m130 last ran
};

// State of ScreenPauseMenu's state callbacks (0x71025f0cf0; placeholder name).
extern const ksys::StateBase sUnk_71025f0cf0;
extern const ksys::StateBase sUnk_71025f1050;
extern const ksys::StateBase sUnk_71025f0ed0;
extern const ksys::StateBase sUnk_71025f0f90;
extern const ksys::StateBase sUnk_71025f0ff0;
extern const ksys::StateBase sUnk_710261ee00;
extern const ksys::StateBase sUnk_71025d98a0;
extern const ksys::StateBase sUnk_71025d9e00;

// Placeholder for the object ScreenPauseMenu keeps at 0x3b90.
struct ScreenPauseMenuUnk3b90 {
    u8 _0[0x80];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    // 0x71009b9f94 (CSV unnamed; declared only)
    bool sub_71009B9F94(bool a1);
    // 0x71009ba010 (CSV unnamed; declared only): whether the state machine's current state id is the target
    bool sub_71009BA010();
};

// Repeated 0x90-byte button records used by PauseMenu's three page controllers.
// The original record's class name is unknown.
class PouchItem;
struct ScreenButton_7100989968 {
    ScreenButton_7100989968();
    virtual ~ScreenButton_7100989968();
    void sub_710098923C();
    void sub_71009892B0();
    void sub_710098931C(const PouchItem* item);
    void sub_71009896D8();
    void sub_710098975C(s32 count);
    void sub_7100989888(bool enabled, bool play);
    bool sub_7100989A08() const;
    void sub_7100989A40();
    void sub_710098993C(bool enabled, bool play);
    void sub_7100989968(bool enabled);
    void sub_71009899EC();

    /* 0x8 */ eui::AnimButton* mButton = nullptr;
    /* 0x10 */ eui::Animator* _10 = nullptr;
    /* 0x18 */ eui::Animator* _18 = nullptr;
    /* 0x20 */ eui::Animator* mAnimator = nullptr;
    /* 0x28 */ eui::Animator* _28 = nullptr;
    /* 0x30 */ Unk_710247aa30 mBreakNewController;
    /* 0x50 */ Unk_71024774c8 mTexturePatternController;
    /* 0x68 */ Unk_7102477508 mCategoryController;
};
KSYS_CHECK_SIZE_NX150(ScreenButton_7100989968, 0x90);

// Placeholder for the three objects ScreenPauseMenu keeps at 0x3a00 (indexed by the byte at 0x3a18).
struct ScreenPauseMenuUnk3a00 {
    u8 _0[0x20];
    /* 0x20 */ eui::LayoutEx* mLayout;  // as in eui::ControlBase (read by sub_71009B01B4)
    u8 _28[0x130 - 0x28];
    /* 0x130 */ s32 _130;
    // index of the first item shown in mButtons
    /* 0x134 */ s32 _134;
    /* 0x138 */ sead::SafeArray<ScreenButton_7100989968, 20> mButtons;
    // per button value (returned by sub_71009B0484)
    /* 0xc78 */ sead::SafeArray<s32, 20> _c78;
    /* 0xcc8 */ UiTexSlots _cc8;  // one texture per button (sub_71009B00E0 unloads one)
    // 0x71009b0224 (CSV unnamed; declared only)
    void sub_71009B0224(bool a1);
    // 0x71009b01b4: x and y of the layout's root pane position
    sead::Vector2f sub_71009B01B4() const;
    // 0x71009b01c4: moves the layout's root pane to x (z = 0; y is kept)
    void sub_71009B01C4(f32 x);
    // 0x71009b01e4: moves the layout's root pane by dx (z = 0; y is kept)
    void sub_71009B01E4(f32 dx);
    // 0x71009b020c: shows or hides the layout's root pane
    void sub_71009B020C(bool visible);
    // 0x71009aff68: _130 = -1
    void sub_71009AFF68();
    // 0x71009b0190: runs one of two button updates on button `index`
    void sub_71009B0190(s32 index, bool a2);
    // 0x71009b00e0: clears button `index` (value -1, reset, disabled) and unloads its texture
    void sub_71009B00E0(s32 index);
    // 0x71009b0468 / 0x71009b0484 (placeholder names): the button slot of item `index` (-1 when it is not shown) /
    // that slot's _c78 value (-1 when it is not shown)
    s32 sub_71009B0468(s32 index) const;
    s32 sub_71009B0484(s32 index) const;
    // 0x71009b04bc / 0x71009b04e0 (placeholder names): sub_710098993C(flag, false) / sub_7100989888(flag, true) on
    // button `index`
    void sub_71009B04BC(s32 index, bool flag);
    void sub_71009B04E0(s32 index, bool flag);
};

// Placeholder for the object ScreenPauseMenu keeps at 0x3b98.
struct ScreenPauseMenuUnk3b98 {
    u8 _0[0x80];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    u8 _a8[0x174 - 0xa8];
    /* 0x174 */ s32 _174;
    u8 _178[0x1a0 - 0x178];
    /* 0x1a0 */ s32 _1a0;
    // 0x71009b5fc8 (CSV unnamed; declared only)
    void sub_71009B5FC8(bool a1);
    // 0x71009b6040 (CSV unnamed; declared only)
    bool sub_71009B6040();
};

// Seven tab controls owned by ScreenPauseMenu (+0x3678); native ctor/dtor a341d0/a34434.
class Unk_7100A341D0 {
public:
    struct Entry {
        Unk_7102477468 mButton;
        Unk_7102474c28 mPage;
        Unk_7102474c48 mGuide;
        s32 mFirstItemIndex = 0;
        u8 _7c[4]{};
    };
    Unk_7100A341D0();
    ~Unk_7100A341D0();
    sead::SafeArray<Entry, 7> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_7100A341D0::Entry, 0x80);
KSYS_CHECK_SIZE_NX150(Unk_7100A341D0, 0x380);

class ScreenPauseMenu : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    s32 m72() override;
    void m69() override;
    void m70() override;
    void m71() override;
    void m96() override;
    bool isEnableControl() const override;
    ~ScreenPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)
    const char* getLayoutName_() const override;
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m101() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a3840c (CSV unnamed, 1248 bytes; declared only; tail-called by m106)
    void sub_7100A3840C(eui::AnimButton* button);
    // 0x7100a392d8 (CSV unnamed, 396 bytes; declared only)
    void sub_7100A392D8();
    // 0x7100a391cc (CSV unnamed): opens the info screen, selects the stored category and releases the UI actor
    void sub_7100A391CC(bool a1);
    // 0x7100a35098: plays the decide sound
    void sub_7100A35098();
    // 0x7100a38fe8 (CSV unnamed): updates the 20 button layout pairs for the category and state.
    bool sub_7100A38FE8(u8 category, bool a2);
    void sub_7100A379BC(s32 tab);
    // 0x7100a38028 (CSV unnamed, 296 bytes; declared only)
    void sub_7100A38028();
    // 0x7100a39464: after releasing the grabbed item, re-lays the three tab pages around the current one
    void sub_7100A39464(bool a2);
    // 0x7100a38a48 (CSV unnamed, declared only): shows `page` in the tab control `tab`
    void sub_7100A38A48(s32 tab, s32 page);
    // inline-only in the original; names are guesses (0x7100a39464 inlines the wrap and the page check)
    static s32 wrapTab(u8 tab) {
        s32 index = s8(tab);
        if (index < 0)
            index = 2;
        if (index > 2)
            index = 0;
        return index;
    }
    void showTabPage(s32 tab, s32 page) {
        if (page >= 0 && _3624 > page && _3624 > 0)
            sub_7100A38A48(tab, page);
    }
    // inline-only in the original; name is a guess (m191 inlines this four times around the info animators)
    void playInfoAnimator(eui::Animator* ScreenPauseMenuInfo::*animator);
    // 0x7100a3c2f0 (CSV unnamed, declared only): shows / hides the info contents for the two mode fields
    void sub_7100A3C2F0(s32 a1, s32 a2);
    // 0x7100a3a920 (CSV unnamed, declared only): moves the three tab controls by the page offset
    void sub_7100A3A920(f32 offset);
    // 0x7100a3772c (CSV unnamed, declared only): lays the tab controls out for the current page
    void sub_7100A3772C();
    // 0x7100a3471c (CSV unnamed, declared only): the pause menu's per-frame page / animator step.
    void sub_7100A3471C();
    // 0x7100a34a28 (CSV unnamed): plays mc_Close once when opened, then runs the step.
    void sub_7100A34A28();
    // 0x7100a3a7fc: moves the cursor to button tag (base tag of the page shown by `page` + offset); false if no
    // shown page matches or the tag is 0
    bool sub_7100A3A7FC(s32 page, s32 offset);
    // 0x7100a38994: closes the TV box cursor screen when the cursor box leaves _3664
    void adjstBoxCursor(sead::BoundBox2<f32>* box, const eui::BoxCursorNode* node) const override;
    /* 0x3610 */ PauseMenuDataMgr* mPauseMenuDataMgr{};  // PauseMenuDataMgr::instance(), set by the creator
    /* 0x3618 */ s32 _3618;
    union {
        /* 0x361c */ u32 _361c;
        u8 _361c_bytes[4];
    };
    /* 0x3620 */ s32 _3620;  // the shown guide page (-1: none)
    /* 0x3624 */ s32 _3624;  // the number of guide pages
    u8 _pad_3628[0x3630 - 0x3628];
    /* 0x3630 */ void* _3630;  // the recipe screen's item argument
    u8 _pad_3638[0x3640 - 0x3638];
    /* 0x3640 */ bool _3640;  // read by m180 to choose the info mode
    /* 0x3641 */ u8 _3641;
    /* 0x3642 */ bool _3642;
    /* 0x3643 */ u8 _3643;
    /* 0x3644 */ s32 _3644;  // current page
    /* 0x3648 */ s32 _3648;  // target page
    /* 0x364c */ s32 _364c;  // pending page offset (-1: none)
    /* 0x3650 */ f32 _3650;  // new page offset
    /* 0x3654 */ f32 _3654;  // tab control position
    u8 _pad_3658[0x3660 - 0x3658];
    /* 0x3660 */ u16 _3660;
    u8 _pad_3662[2];
    /* 0x3664 */ sead::BoundBox2f _3664;  // the box cursor must stay inside it while _3674 is set (adjstBoxCursor)
    /* 0x3674 */ s32 _3674;
    /* 0x3678 */ Unk_7100A341D0 mTabControls;
    /* 0x39f8 */ s32 mSelectedCategory;
    u8 _39fc[4];
    /* 0x3a00 */ ScreenPauseMenuUnk3a00* _3a00[3];
    /* 0x3a18 */ u8 _3a18;
    /* 0x3a19 */ u8 _3a19;
    u8 _pad_3a1a[0x3a20 - 0x3a1a];
    /* 0x3a20 */ eui::LayoutEx* mFirstGuideLayout;
    /* 0x3a28 */ eui::LayoutEx* mSecondGuideLayout;
    /* 0x3a30 */ s32 _3a30;
    /* 0x3a34 */ s32 _3a34;
    /* 0x3a38 */ Unk_7102474df8 _3a38;
    u8 _pad_3ac0[0x3b80 - 0x3ac0];
    /* 0x3b80 */ s32 _3b80;
    /* 0x3b84 */ s32 _3b84;
    /* 0x3b88 */ s32 _3b88;
    u8 _pad_3b8c[0x3b90 - 0x3b8c];
    /* 0x3b90 */ ScreenPauseMenuUnk3b90* _3b90;
    /* 0x3b98 */ ScreenPauseMenuUnk3b98* _3b98;
    /* 0x3ba0 */ s32 _3ba0;
    /* 0x3ba4 */ u8 _3ba4;
    u8 _pad_3ba5[3];
    /* 0x3ba8 */ bool _3ba8;
    u8 _pad_3ba9[3];
    /* 0x3bac */ s32 _3bac;
    u8 _pad_3bb0[0x3bb4 - 0x3bb0];
    /* 0x3bb4 */ s32 _3bb4;
    /* 0x3bb8 */ UiTimer _3bb8;
    /* 0x3bd0 */ s32 _3bd0;  // button index in _3a00[_3a18] (m175)
    u8 _pad_3bd4[0x3be8 - 0x3bd4];
    // The 20 layout pairs updated by sub_7100A38FE8 and the state (0 / 1 / 2) it uses.
    /* 0x3be8 */ sead::Buffer<Unk_7102474b38> _3be8;
    /* 0x3bf8 */ s32 _3bf8;
    u8 _pad_3bfc[0x3c10 - 0x3bfc];
    /* 0x3c10 */ u8 _3c10;
    u8 _pad_3c11[3];
    /* 0x3c14 */ UiTimer _3c14;
    /* 0x3c2c */ bool _3c2c;  // blocks sub_7100A34A80 (set by m100's reset)

    // inherited slot; the pause menu decides from it whether the state may settle
    void m99() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual s32 m173();
    virtual void m174();
    virtual void m175();
    virtual void m176();
    virtual s32 m177();
    virtual void m178();
    virtual void m179();
    virtual void m180();
    virtual s32 m181();
    virtual void m182();
    virtual void m183();
    virtual void m184();
    virtual s32 m185();
    virtual void m186();
    virtual void m187();
    virtual void m188();
    virtual s32 m189();
    virtual void m190();
    virtual void m191();
    virtual void m192();
    virtual s32 m193();

    void sub_7100A34A04();

    bool sub_7100A34A10();
    bool sub_7100A349F4();
    // 0x7100a34a80: whether the pause selection may settle (the current state's own box test)
    bool sub_7100A34A80();
};

class ScreenAppTool : public ScreenEx {
public:
    ScreenAppTool();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppTool() override;
    SEAD_RTTI_OVERRIDE(ScreenAppTool, ScreenEx)
    void m99() override;
    void m100() override;
    void m102(eui::AnimButton*) override;
    void m107(eui::AnimButton*) override;
    // 0x71009fe318 (declared only; placeholder name)
    void sub_71009FE318(s32 value, bool flag);

    // An element of the table at 0x3638 (0x28 bytes).
    struct Record {
        /* 0x00 */ eui::ButtonBase* button;
        u8 _8[0x18 - 0x8];
        /* 0x18 */ eui::Animator* animator;
        u8 _20[0x24 - 0x20];
        /* 0x24 */ s32 _24;
    };

    // Members used by the state callbacks (see the constructor 0x71009fcd64).
    /* 0x3610 */ u8 _3610 = 1;
    u8 _pad_3611[0x3618 - 0x3611];
    /* 0x3618 */ u64 _3618 = 0;
    /* 0x3620 */ eui::Animator* _3620 = nullptr;
    /* 0x3628 */ u64 _3628 = 0;
    /* 0x3630 */ u8 _3630 = 0;
    u8 _pad_3631[0x3638 - 0x3631];
    /* 0x3638 */ sead::Buffer<Record> _3638;  // freed by the destructor
    /* 0x3648 */ u64 _3648 = 0;
    /* 0x3650 */ eui::Animator* _3650 = nullptr;
    /* 0x3658 */ u64 _3658 = 0;
    /* 0x3660 */ u64 _3660 = 0;
    /* 0x3668 */ u64 _3668 = 0;
    /* 0x3670 */ UiTexSlots _3670;
    /* 0x3740 */ s32 _3740;
    /* 0x3744 */ u8 _3744;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();

    bool sub_71009FD674();
};

struct PictureBookGroupList;
struct PictureBookGroupRecord;

// Placeholder (vtable not identified): ScreenAppPictureBookEntry::Params::_2d0. Slot 0 (called by 0x710093c304 for
// every group with a layout) returns the group's item.
class PictureBookItemFactoryMaybe {
public:
    virtual PictureBookItem* create(sead::Heap* heap, s32 index) = 0;
};

// The 0x398-byte entry allocated by 943e80, with vtable 2474f30.
struct ScreenAppPictureBookEntry {
    // Constructor 938c94 and destructor 938e9c; also used as a standalone setup block.
    // Field names retain their offsets in the outer entry.
    struct Params {
        Params();
        ~Params();
        // 0x7100938f28 (placeholder name): copies every member of `other` (returns nothing, so not operator=)
        void sub_7100938F28(const Params& other);

        sead::FixedSafeString<64> _28;
        sead::FixedSafeString<64> _80;
        sead::FixedSafeString<64> _d8;
        sead::FixedSafeString<64> _130;
        sead::FixedSafeString<64> _188;
        sead::FixedSafeString<64> _1e0;
        u32 _238 = 0;
        sead::FixedSafeString<64> _240;
        s32 _298 = 0;
        s32 _29c = -1;
        s32 _2a0 = -1;
        s32 _2a4 = -1;
        sead::Vector2f _2a8;
        sead::Vector2f _2b0{0, 0};
        sead::Vector2f _2b8{0, 0};
        sead::Vector2f _2c0{0, 0};
        bool _2c8 = false;
        bool _2c9 = false;
        bool _2ca = false;
        bool _2cb = false;
        bool _2cc = false;
        bool _2cd = false;
        // Not owned; slot 0 is called by 93c304 to create the item of each group.
        PictureBookItemFactoryMaybe* _2d0 = nullptr;
    };

    // Same-owner native setup chain; later stages remain declaration only.
    // 0x710093a2f8 (placeholder name): finds the group list whose first unit uses the layout of the parts
    // "<_28>/<_80>00" (or "<_80>00"), adding a new list to `lists` if there is none
    void sub_710093A2F8(sead::Heap* heap, sead::PtrArray<PictureBookGroupList>* lists);
    // 0x710093c24c (placeholder name): allocates the list's _298 groups
    void sub_710093C24C(sead::Heap* heap);
    // 0x710093c304 (placeholder name): binds every group to its layout (sub_710093C48C), its close animation (_240)
    // and its item (_2d0)
    void sub_710093C304(sead::Heap* heap);
    // 0x710093c48c (declared only; 468 bytes): the layout of group `index`
    eui::LayoutEx* sub_710093C48C(sead::Heap* heap, s32 index);
    // 0x710093c660 (placeholder name): binds the units of every group to their parts layouts ("<_d8>NN"), buttons and
    // cursor nodes
    void sub_710093C660();
    // Template (placeholder name): allocates mParams._2a0 * _2a4 units of type T for every group of the group list.
    // One copy per unit type in the original (e.g. 0x71009fb528 for Unk_71024826c0); defined after
    // ScreenAppPictureBookUnk.
    template <typename T>
    void createUnits(sead::Heap* heap);
    void sub_710093A500(sead::Heap* heap);
    void sub_710093A5C0(sead::Heap* heap);
    void sub_710093A758();
    void sub_710093AC7C();
    void sub_710093AE60(const sead::Vector2f& position);
    // 0x710093ad60 (placeholder name): moves the entry (sub_710093AE60), recomputes the page _388 along the config
    // direction, then updates the group records (sub_710093B0D8)
    void sub_710093AD60(const sead::Vector2f& position);
    // 0x710093b0d8 (declared only; 1452 bytes)
    void sub_710093B0D8(PictureBookGroupRecord* record);
    // 0x710093b9f4 (placeholder name): when the record's group is out of the view box _308, releases the group
    // (item, units, record link)
    void sub_710093B9F4(PictureBookGroupRecord* record);
    void sub_710093AF74();
    // 0x710093cb64 (declared only; 444 bytes): resets the entry's records (run by
    // ScreenAppPictureBookUnk::sub_710094004C)
    void sub_710093CB64();
    // 0x710093b684 / 0x710093b830 (declared only): per-record steps run by ScreenAppPictureBookUnk::Update while the
    // list scrolls
    void sub_710093B684(PictureBookGroupRecord* record);
    void sub_710093B830(PictureBookGroupRecord* record);
    // 0x710093cd20 (declared only; run for every entry at the end of ScreenAppPictureBookUnk::Update)
    void sub_710093CD20();
    void sub_710093BB48();
    void sub_710093BDFC();
    void sub_710093C040();
    ScreenAppPictureBookEntry() = default;
    virtual ~ScreenAppPictureBookEntry();

    /* 0x8 */ ScreenAppPictureBookUnk* mController = nullptr;
    /* 0x10 */ PictureBookGroupList* mGroupList = nullptr;
    // 93a500 allocates 0x10-byte PictureBookGroupRecord objects in this array.
    /* 0x18 */ sead::PtrArray<PictureBookGroupRecord> mRecords;
    /* 0x28 */ Params mParams;
    // Producer 93a5c0 allocates and constructs these three controllers.
    /* 0x2d8 */ Unk_7102477468* mIconControl = nullptr;
    /* 0x2e0 */ Unk_7102474c28* mPageControl = nullptr;
    /* 0x2e8 */ Unk_7102474c48* mGuideControl = nullptr;
    /* 0x2f0 */ s32 _2f0 = -1;
    /* 0x2f4 */ s32 _2f4 = -1;
    /* 0x2f8 */ sead::BoundBox2f _2f8;
    /* 0x308 */ sead::BoundBox2f _308;
    /* 0x318 */ sead::BoundBox2f _318;
    /* 0x328 */ sead::BoundBox2f _328;
    /* 0x338 */ sead::Vector2f _338 = sead::Vector2f::zero;
    /* 0x340 */ sead::Vector2f _340 = sead::Vector2f::zero;
    /* 0x348 */ sead::BoundBox2f _348;
    /* 0x358 */ sead::BoundBox2f _358;
    /* 0x368 */ sead::Vector2f _368 = sead::Vector2f::zero;
    /* 0x370 */ sead::Vector2f _370 = sead::Vector2f::zero;
    /* 0x378 */ sead::Vector2f _378 = sead::Vector2f::zero;
    /* 0x380 */ sead::Vector2f _380 = sead::Vector2f::zero;
    /* 0x388 */ s32 _388 = -1;
    /* 0x38c */ bool _38c = false;
    /* 0x38d */ bool _38d = false;
    /* 0x390 */ u32 _390 = 0;
};
static_assert(sizeof(ScreenAppPictureBookEntry::Params) == 0x2b0);
static_assert(offsetof(ScreenAppPictureBookEntry, mParams) == 0x28);
static_assert(offsetof(ScreenAppPictureBookEntry, mIconControl) == 0x2d8);
static_assert(offsetof(ScreenAppPictureBookEntry, _38c) == 0x38c);
static_assert(sizeof(ScreenAppPictureBookEntry) == 0x398);

// Producer93C24C allocates this 0x48-byte button group. Binding93C304
// writes its entry and list controller, and93C660 attaches its units.
struct PictureBookGroupRecord {
    u32 _0;
    sead::Vector2f mPosition;
    s32 _c;
};
static_assert(sizeof(PictureBookGroupRecord) == 0x10);
class Unk_7102474f10 {
public:
    SEAD_RTTI_BASE(Unk_7102474f10)
    virtual ~Unk_7102474f10();
    // 0x710093a008 (placeholder name): modes 3 / 4 / 5 of sub_710093A0A8 (play from current / play auto / stop at max)
    void sub_710093A008(s32 mode);
    // 0x710093a0a8 (placeholder name; called for every group by 0x7100943d5c): mode 0 / 1 / 2 plays the _30 animator
    // (from current / auto / stops at min), or starts the close animation of the layout when there is none.
    void sub_710093A0A8(s32 mode);
    eui::LayoutEx* _8{};
    ScreenAppPictureBookEntry* mEntry{};
    ScreenAppPictureBookUnk* mController{};
    sead::PtrArray<Unk_7102474e38> mUnits;
    eui::Animator* _30{};
    PictureBookGroupRecord* mRecord{};
    PictureBookItem* _40{};
};
static_assert(sizeof(Unk_7102474f10) == 0x48);

// Placeholder name: the picture book list controller (0x710093cd20 - 0x7100945000, about 100 unnamed rows).
// Placeholder for the selectable picture-book item held at ScreenAppPictureBookUnk+0x318
// (byte at +0x10; slot 0x40 takes the previous item, slot 0x48 takes nothing). Only the slots
// used by ScreenAppPictureBookUnk::sub_710093F594 are named; the rest are padding slots.
struct PictureBookItem {
    // The first slots are not named from the vtable; 0x7100939f68 deletes `_40` through slot 3.
    virtual void m0();
    virtual void m1();
    virtual ~PictureBookItem();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8(PictureBookItem* prev);
    virtual void m9();
    // vtable slot 0x50 (placeholder name): the box cursor node the item uses (0x71009437c8 keeps it at _328)
    virtual eui::BoxCursorNode* m10();
    // cleared after m5 by ScreenAppPictureBookEntry::sub_710093B9F4
    /* 0x8 */ void* _8;
    /* 0x10 */ bool _10;
};


// Placeholder for a photo-group list of sub_710093FBF0 (count + group array).
// 0x71025d5ce8 (placeholder name): (FLT_MAX, FLT_MAX), "no value" for the picture book spacings
KSYS_VISIBILITY_HIDDEN extern sead::Vector2f sUnk_71025D5CE8;

// 0x50 bytes, allocated by ScreenAppPictureBookEntry::sub_710093A2F8.
struct PictureBookGroupList {
    /* 0x0 */ sead::PtrArray<Unk_7102474f10> mUnits;
    /* 0x10 */ sead::Vector2f _10 = sUnk_71025D5CE8;
    /* 0x18 */ sead::Vector2f _18 = sead::Vector2f::ones;
    // Layout sizes read and written by ScreenAppPictureBookEntry 93bb48 / 93bdfc / 93c040.
    /* 0x20 */ sead::Vector2f _20 = sead::Vector2f::zero;
    // the list's origin (sub_7100944BC4)
    /* 0x28 */ sead::Vector2f _28;
    /* 0x30 */ sead::Vector2f _30 = sead::Vector2f::zero;
    /* 0x38 */ sead::Vector2f _38 = sead::Vector2f::zero;
    /* 0x40 */ sead::Vector2f _40 = sead::Vector2f::zero;
    // set once the units are set up (ScreenAppPictureBook::sub_71009F95C4)
    /* 0x48 */ bool _48 = false;
};
static_assert(sizeof(PictureBookGroupList) == 0x50);

// The setup of a picture book list (0x220 bytes; ScreenAppPictureBookUnk + 0x68). The masks at 0x90 .. 0xa4 look like
// controller button masks. Names are placeholders after the offsets.
struct PictureBookListConfig {
    // 0x710093952c
    PictureBookListConfig();
    // 0x71009396ec (placeholder name): clears the strings and resets the values (-1 / 0)
    void sub_71009396EC();
    // 0x7100939764 (placeholder name): copies every member of `other`
    void sub_7100939764(const PictureBookListConfig& other);

    // value-initialised together (one memset in the constructor)
    struct Strings {
        sead::FixedSafeString<64> _b0;
        sead::FixedSafeString<64> _108;
        sead::FixedSafeString<64> _160;
        sead::FixedSafeString<64> _1b8;
    };

    /* 0x000 */ sead::FixedSafeString<64> _0;
    // Layout direction of the entry pages (0: horizontal, 1: vertical; read by 93c040).
    /* 0x058 */ s32 _58 = -1;
    /* 0x05c */ s32 _5c = 0;
    /* 0x060 */ s32 _60 = -1;
    // Item order modes read by 93bb48 (_64 0-3 with _68).
    /* 0x064 */ s32 _64 = -1;
    /* 0x068 */ s32 _68 = -1;
    /* 0x06c */ sead::Vector2f _6c{0, 0};
    /* 0x074 */ sead::Vector2f _74{0.28f, 300.0f};
    /* 0x07c */ f32 _7c = 0.1f;
    // how far before the target a jump to an item starts scrolling (ScreenAppPictureBookUnk::sub_710093DAFC)
    /* 0x080 */ sead::Vector2f _80;
    /* 0x088 */ u32 _88 = 0;
    /* 0x08c */ u32 _8c = 0;
    /* 0x090 */ u32 _90 = 0;
    /* 0x094 */ u32 _94 = 0;
    /* 0x098 */ u32 _98 = 0;
    /* 0x09c */ u32 _9c = 0;
    /* 0x0a0 */ u32 _a0 = 0;
    /* 0x0a4 */ u32 _a4 = 0;
    /* 0x0a8 */ s32 _a8 = 0;
    /* 0x0b0 */ Strings mStrings{};
    /* 0x210 */ bool _210;
    /* 0x214 */ s32 _214;
    /* 0x218 */ bool _218;
};
static_assert(sizeof(PictureBookListConfig) == 0x220);

// Placeholder: the class whose methods the ScreenAppPictureBookUnk callbacks (_3a0) call.
class PictureBookCallbackTargetMaybe {};

// Placeholder (pointed to by ScreenAppPictureBookUnk::_3a0): two named callbacks. ScreenAppPictureBookUnk::Update
// calls one of them (`_0` when _2e4 == _2e8, else `_b8`) with the name when the list starts moving.
struct PictureBookCallbacksMaybe {
    struct Callback {
        sead::Delegate1<PictureBookCallbackTargetMaybe, const char*> mDelegate;
        sead::FixedSafeString<128> mName;
    };
    /* 0x00 */ Callback _0;
    /* 0xb8 */ Callback _b8;
};
static_assert(sizeof(PictureBookCallbacksMaybe::Callback) == 0xb8);

// vtable 0x7102474f50 (RTTI 0x7100944ff4, D1 0x710093d76c, D0 0x710093dab0, Update 0x710094211c; m5 .. m14 are
// empty). Subclassed by the classes with vtables 0x7102474d30 and 0x7102497698 (they share Update and the empty slots).
struct ScreenAppPictureBookUnk : eui::ControlBase {
    NN_RUNTIME_TYPEINFO(eui::ControlBase)
    // 0x710093d628
    ScreenAppPictureBookUnk();
    // 0x710093d76c
    ~ScreenAppPictureBookUnk() override;
    // 0x710094211c (declared only; 2500 bytes)
    void Update(f32 dt) override;
    // called by sub_7100944290 with its heap
    virtual void m5(sead::Heap* heap) {}
    virtual void m6() {}
    // 0x7100945084 (the subclass at 0x7102474d30 overrides it)
    virtual void m7() {}
    virtual void m8() {}
    // called first by sub_710093FF88
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}
    virtual void m12() {}
    virtual void m13() {}
    virtual void m14() {}

    // 0x7100943e80: allocates and initializes the entry list.
    void sub_7100943E80(sead::Heap* heap, s32 count);
    // 0x710093ff88: releases active units across the existing group lists (undecompiled).
    void sub_710093FF88();
    // 0x710093e4b4: forwards signed item/category and mode to the bool selection helper.
    bool sub_710093E4B4(s32 index, s32 category, s32 mode);
    // 0x710093f594 (CSV unnamed; not decompiled)
    void sub_710093F594(bool a1);
    // 0x710093e900 (placeholder name): sub_710093E784 of `base` plus the _29c of the first `count` entries
    u32 sub_710093E900(s32 base, s32 count);
    // 0x710093f10c (placeholder name): finds the entry that `index` falls into (walking the _29c sizes); returns the
    // index inside it and the entry's _2f0
    void sub_710093F10C(s32 index, s32* out_index, s32* out_value);
    // 0x710093feac (declared only; 220 bytes): refreshes the groups' layouts
    void sub_710093FEAC();
    // 0x710093e428 (declared only; the 4-byte forwarder to sub_710093E784)
    u32 sub_710093E428(s32 index);
    // 0x710093dad4 / 0x710093dae8 (identical code): raise `_33c` to at least `value`
    void sub_710093DAD4(s32 value);
    void sub_710093DAE8(s32 value);
    // 0x7100939f58: whether `_340` is 2
    bool sub_7100939F58() const;
    // 0x710093fe74: the `_38d` flag of entry `index` (true for an invalid index)
    bool sub_710093FE74(s32 index) const;
    // 0x710093fd14 / 0x710093fd6c / 0x710093fdcc / 0x710093fe1c (placeholder names): set or clear `_38c` / `_38d` of the
    // entries; each ends with sub_710093F7F8 or sub_710093F29C and sub_710093F924(true)
    void sub_710093FD14(s32 index);
    void sub_710093FD6C();
    void sub_710093FDCC(s32 index);
    void sub_710093FE1C();
    // 0x710093f29c (declared only; not decompiled)
    void sub_710093F29C();
    // 0x710093f278 (placeholder name): stores `value` in the entry at `index` (if it exists), then sub_710093F29C
    void sub_710093F278(s32 value, s32 index);
    // Callees of sub_710093F594 (declared only; not decompiled yet)
    void sub_710093F670();
    void sub_710093F7F8(bool flag);
    void sub_710093F924(bool flag);
    u32 sub_710093E784(s32 index);
    s32 sub_710093FBF0(eui::BoxCursorNode* node);
    // 0x71009401e4 / 0x7100940288 (placeholder names): ForceOff the units' buttons (those without flag 0x10 / those
    // that are being pressed)
    void sub_71009401E4();
    void sub_7100940288();
    // 0x710093dafc (declared only; 704 bytes): selects item `index` of entry `entry` (clamped; mode 2 also for a
    // locked entry); false when there is nothing to select
    bool sub_710093DAFC(s32 index, s32 entry, s32 mode);
    // 0x710093e42c (placeholder name): selects the overall item `index` (clamped to _2ac) through sub_710093DAFC
    bool sub_710093E42C(s32 index, s32 mode);
    // 0x7100943fe0 (placeholder name): allocates room for `count` group lists
    void sub_7100943FE0(sead::Heap* heap, s32 count);
    // 0x71009419e0 (declared only; 592 bytes): the position of item `index` of entry `entry` (zero when invalid)
    void sub_71009419E0(s32 index, s32 entry, sead::Vector2f* out);
    // 0x7100944bc4 (placeholder name): the position of the unit at (`col`, `row`) of item `index` of entry
    // `entry_index` (zero when there is none)
    sead::Vector2f sub_7100944BC4(s32 index, s32 col, s32 row, s32 entry_index);
    // 0x7100944d18 (placeholder name): the column / row of item `index` of `entry` for the item order modes _64 / _68
    void sub_7100944D18(const ScreenAppPictureBookEntry* entry, s32 index, s32* x, s32* y) const;
    // 0x7100941c30 (placeholder name): the item (and its entry) whose box, moved by `offset`, contains the origin;
    // the outputs are left alone when there is none
    void sub_7100941C30(const sead::Vector2f& offset, s32* out_index, s32* out_entry);
    // 0x71009418d0 (placeholder name): scrolls by `delta` along the config direction, updates the item under the
    // scroll position (_2f0 / _2e8 / _2dc) and, for modes 1 and 2, runs sub_7100941D70
    void sub_71009418D0(f32 delta, s32 mode);
    // 0x7100941d70 (declared only; 940 bytes)
    void sub_7100941D70(bool flag);
    // 0x7100941354 (placeholder name): how far the list must scroll (along the config direction) to show item
    // `index` (its position clamped to _2b0)
    f32 sub_7100941354(s32 index);
    // 0x7100944004 (placeholder name): attaches the list to `screen` with a copy of `config`, registers `control`
    // (the list itself) with the screen and names it "SlideObject:<config name>" (the name defaults to the control's
    // index in the screen)
    void sub_7100944004(ScreenEx* screen, const PictureBookListConfig& config, eui::ControlBase* control);
    // 0x7100944138 (declared only; 344 bytes)
    void sub_7100944138();
    // inline-only in the original; name is a guess (the same test is inlined in Update and sub_710093DAFC): the
    // direction of a move from `from` to `to` along the config direction (-1: none or an invalid pointer)
    s32 getMoveDirectionMaybe(const sead::Vector2f& from, const sead::Vector2f& to) const {
        if (to == from || from == sead::ControllerBase::cInvalidPointer ||
            to == sead::ControllerBase::cInvalidPointer)
            return -1;
        s32 direction = -1;
        if (mConfig._58 == 1) {
            const f32 diff = to.y - from.y;
            if (diff > 0)
                direction = 0;
            else if (diff < 0)
                direction = 1;
        } else if (mConfig._58 == 0) {
            const f32 diff = to.x - from.x;
            if (diff > 0)
                direction = 3;
            else if (diff < 0)
                direction = 2;
        }
        return direction;
    }
    // 0x710093e258 (declared only; 464 bytes): the overall index of the unit at (`col`, `row`) of item `index` of entry
    // `entry_index` (placeholder description from its arguments)
    void sub_710093E258(s32 entry_index, s32 index, s32 col, s32 row, s32* out);
    // 0x7100944290 (declared only; 940 bytes): finishes the setup: item count _2ac, scroll limits _2b0, the first /
    // last item positions of every entry, sub_710094004C, the open state _340, m5(heap), Unk_7102474e38::m4(heap)
    // of every unit, then sub_710093F594(false)
    void sub_7100944290(sead::Heap* heap);
    // 0x710094004c (declared only; 408 bytes)
    void sub_710094004C();
    // 0x710093ec3c (declared only; 384 bytes): selects the overall item `index` (finds its entry and page, then
    // sub_710093DAFC with `mode`)
    void sub_710093EC3C(s32 index, s32 mode);
    // 0x710093ee8c (declared only; 464 bytes): selects item `index` of entry `entry_index` (like sub_710093DAFC)
    void sub_710093EE8C(s32 index, s32 entry_index, s32 mode);
    // 0x7100943b60 / 0x7100943c84 / 0x7100943d5c (declared only): open / close state steps of sub_7100942AE0 (the
    // first and last get the requested state _33c)
    void sub_7100943B60(s32 state);
    void sub_7100943C84();
    void sub_7100943D5C(s32 state);
    // Callees of Update (declared only; not decompiled)
    void sub_7100942AE0();
    s32 sub_7100942D78();
    bool sub_7100943080();
    void sub_710094033C();
    void sub_7100943520(const sead::Vector2f& delta);
    void sub_71009437C8();
    void sub_71009439B0();
    // 0x710093f160 (declared only; 280 bytes): the offset of item `index` from the scroll position (_2fc; zero when
    // there is no such item)
    const sead::Vector2f& sub_710093F160(s32 index);
    // 0x7100943684 (CSV placeholder): find the unit covering `index` (reads _288/_290/_2a8).
    Unk_7102474e38* sub_7100943684(s32 index);
    // Template (placeholder name): sets up entry `index` with `params`, its group list and (once per group list) its
    // units of type T. The original has 12 identical copies, one per unit type (e.g. 0x71009f95c4 for
    // Unk_71024826c0, 0x71009b91b0 for Unk_7102474e38).
    template <typename T>
    void setupEntry(sead::Heap* heap, s32 index, const ScreenAppPictureBookEntry::Params& params);

    // state flags rebuilt by Update (0x10 / 0x20: the item at the scroll position changed, 0x40 / 0x80: the list
    // started / stopped moving, 0x100: the cursor is on one of the units, 0x200: the selected record is enabled)
    /* 0x028 */ u32 _28 = 0;
    /* 0x02c */ u32 _2c = 0;
    /* 0x030 */ u32 _30 = 0;
    /* 0x034 */ s32 _34 = 0;
    /* 0x038 */ void* _38 = nullptr;
    /* 0x040 */ eui::LayoutEx* _40[4]{};
    /* 0x060 */ ScreenEx* mScreen = nullptr;
    /* 0x068 */ PictureBookListConfig mConfig;
    // Full producer 943e80 calls PtrArrayImpl::allocBuffer at +288 then pushes 0x398 entries.
    /* 0x288 */ sead::PtrArray<ScreenAppPictureBookEntry> mEntries;
    // the group lists shared by the entries (sub_7100943FE0 allocates them; ScreenAppPictureBookEntry::sub_710093A2F8
    // adds them)
    /* 0x298 */ sead::PtrArray<PictureBookGroupList> mGroupLists;
    /* 0x2a8 */ s32 _2a8 = 1;
    /* 0x2ac */ s32 _2ac = 0;
    // scroll limits (the constructor sets an empty box: min FLT_MAX, max -FLT_MAX)
    /* 0x2b0 */ sead::BoundBox2f _2b0;
    /* 0x2c0 */ sead::Vector2f _2c0 = sead::Vector2f::zero;
    /* 0x2c8 */ sead::Vector2f _2c8 = sead::Vector2f::zero;
    // scroll position (sub_7100941354)
    /* 0x2d0 */ sead::Vector2f _2d0 = sead::Vector2f::zero;
    /* 0x2d8 */ s32 _2d8 = -1;
    // the overall index of the item at the scroll position (sub_71009418D0)
    /* 0x2dc */ s32 _2dc = -1;
    /* 0x2e0 */ s32 _2e0 = -1;
    /* 0x2e4 */ s32 _2e4 = -1;
    /* 0x2e8 */ s32 _2e8 = -1;
    /* 0x2ec */ s32 _2ec = -1;
    /* 0x2f0 */ s32 _2f0 = -1;
    /* 0x2f4 */ s32 _2f4 = -1;
    /* 0x2f8 */ s32 _2f8 = -1;
    /* 0x2fc */ sead::Vector2f _2fc = sead::Vector2f::zero;
    // added to the item positions (sub_7100944BC4; not set by the constructor)
    /* 0x304 */ sead::Vector2f _304;
    /* 0x30c */ s32 _30c = -1;
    /* 0x310 */ s32 _310 = -1;
    /* 0x318 */ PictureBookItem* _318 = nullptr;
    /* 0x320 */ u32 _320 = 0;
    u8 _324[0x328 - 0x324];
    // the active box cursor node (set by Update / by PictureBookItem::m10 in sub_71009437c8)
    /* 0x328 */ eui::BoxCursorNode* _328 = nullptr;
    /* 0x330 */ s32 _330 = 1;
    /* 0x334 */ s32 _334 = -1;
    // the scroll mode passed to sub_71009418D0
    /* 0x338 */ s32 _338 = -1;
    /* 0x33c */ s32 _33c = -1;
    /* 0x340 */ s32 _340 = -1;
    /* 0x348 */ sead::FixedSafeString<64> _348;
    // the constructor zeroes 0x3a0 .. 0x3ae as one block
    /* 0x3a0 */ PictureBookCallbacksMaybe* _3a0 = nullptr;
    /* 0x3a8 */ bool _3a8 = false;
    u8 _3a9[0x3ae - 0x3a9]{};
    /* 0x3b0 */ u32 _3b0 = 0;
    /* 0x3b4 */ u32 _3b4 = 0;
    /* 0x3b8 */ void* _3b8 = nullptr;
    /* 0x3c0 */ u32 _3c0 = 0;
    // bit 0: Update calls sub_7100AA9A40 on _2b0
    /* 0x3c4 */ u32 _3c4 = 0;
};
static_assert(sizeof(ScreenAppPictureBookUnk) == 0x3c8);

// vtable 0x7102474d30 (placeholder name): the picture book list of the shortcut screen (code next to
// Unk_7102474c68 in uiShortcutIconButton.cpp). It moves a pane (_3c8) with the scroll offset and selects the
// ScreenMainShortCut entry under the scroll position.
class Unk_7102474d30 : public ScreenAppPictureBookUnk {
public:
    NN_RUNTIME_TYPEINFO(ScreenAppPictureBookUnk)
    // 0x7100937210
    Unk_7102474d30();
    // 0x710093724c
    ~Unk_7102474d30() override;
    // 0x7100937790
    void m7() override;

    // 0x71009372c4 (placeholder name): sets the pane that follows the scroll and remembers its position
    void sub_71009372C4(nn::ui2d::Pane* pane);
    // 0x71009372e0 (placeholder name): binds the page arrows to `layout`
    void sub_71009372E0(eui::LayoutEx* layout);
    // 0x71009372e8 (placeholder name): sets the page count, jumps to item `index` and resets the pane
    void sub_71009372E8(s32 index, s32 count);
    // 0x7100937424 (placeholder name): like sub_7100937550 with ArchiveHandle::sub_71009C3788
    f32 sub_7100937424(s32 index);
    // 0x7100937550 (placeholder name): the first non-zero archive value (ArchiveHandle::sub_71009C37A8) of the
    // shortcut units after unit `index` (or before it when there is no next unit)
    f32 sub_7100937550(s32 index);
    // 0x710093767c (placeholder name): the layout `kind` of the nearest other shortcut unit next to unit `index`
    // (searching from the start of its run; none for kind 2)
    eui::LayoutEx* sub_710093767C(s32 index, s32 kind);
    // 0x7100937368 (placeholder name): presses the shortcut button of the unit at the scroll position
    void sub_7100937368();
    // 0x7100937894 (placeholder name): moves the pane towards its rest position shifted by the scroll offset
    void sub_7100937894();

    /* 0x3c8 */ nn::ui2d::Pane* _3c8 = nullptr;
    // the pane's rest position (both read from its x in sub_71009372C4)
    /* 0x3d0 */ f32 _3d0;
    /* 0x3d4 */ f32 _3d4;
    /* 0x3d8 */ f32 _3d8 = 0;
    /* 0x3e0 */ Unk_7102474c48 _3e0;
};
static_assert(sizeof(Unk_7102474d30) == 0x410);

// vtable 0x7102497698 (placeholder name): the picture book list of the shop button list (code next to
// ScreenShopBtnList5); m9 forwards to UiShopMgr.
class Unk_7102497698 : public ScreenAppPictureBookUnk {
public:
    NN_RUNTIME_TYPEINFO(ScreenAppPictureBookUnk)
    // 0x7100a4d9a8
    ~Unk_7102497698() override;
    // 0x7100a4d9d0
    void m9() override;
};
static_assert(sizeof(Unk_7102497698) == 0x3c8);

template <typename T>
void ScreenAppPictureBookEntry::createUnits(sead::Heap* heap) {
    if (!mGroupList)
        return;
    const s32 count = mParams._2a0 * mParams._2a4;
    if (count < 1)
        return;
    for (auto it = mGroupList->mUnits.begin(), end = mGroupList->mUnits.end(); it != end; ++it) {
        it->mUnits.allocBuffer(count, heap);
        for (s32 i = 0; i < count; ++i)
            it->mUnits.pushBack(new (heap) T);
    }
}

template <typename T>
void ScreenAppPictureBookUnk::setupEntry(sead::Heap* heap, s32 index,
                                         const ScreenAppPictureBookEntry::Params& params) {
    if (!mEntries.isBufferReady() || index >= mEntries.size())
        return;
    ScreenAppPictureBookEntry* entry = mEntries.at(index);
    if (!entry)
        return;
    entry->mController = this;
    entry->mParams.sub_7100938F28(params);
    entry->_2f0 = index;
    entry->sub_710093A2F8(heap, &mGroupLists);
    if (entry->mGroupList && !entry->mGroupList->_48) {
        entry->sub_710093C24C(heap);
        entry->createUnits<T>(heap);
        entry->sub_710093C304(heap);
        entry->sub_710093C660();
        entry->mGroupList->_48 = true;
    }
    entry->sub_710093A500(heap);
}

class Unk_71009cb0c8;
// 0x71025eb5c0 (placeholder name): the AppPictureBook screen's texture controllers
extern sead::PtrArray<Unk_71009cb0c8> sUnk_71025eb5c0;
// 0x71025dc57c / 0x71025dc580 (placeholder names): the album position and page kind kept by ScreenAppAlbum::m100
extern s32 sUnk_71025dc57c;
extern bool sUnk_71025dc580;
// 0x71025dc5e0 (placeholder name): the AppAlbum screen's texture controllers (stored as pointers to the controller pointers)
extern sead::PtrArray<Unk_71009cb0c8*> sUnk_71025dc5e0;

class ScreenAppPictureBook : public ScreenEx {
public:
    // 0x71009fa3fc
    void m89() override;
    // 0x71009fa478
    void m128() override;
    void m100() override;
    void m106(eui::AnimButton*) override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppPictureBook() override;
    SEAD_RTTI_OVERRIDE(ScreenAppPictureBook, ScreenEx)

    // 0x71009f8284: whether the picture book's frame animator is playing
    bool sub_71009F8284() const;

    // state callbacks (slots 154-165, trivial ones defined in uiScreenLeafSlots.cpp)
    u8 _pad_3610[0x3628 - 0x3610];
    /* 0x3628 */ eui::Animator* _3628;
    u8 _pad_3630[0x3658 - 0x3630];
    /* 0x3658 */ ScreenAppPictureBookUnk* _3658;
    /* 0x3660 */ ScreenAppPictureBookUnk* _3660;
    u8 _pad_3668[0x3ab8 - 0x3668];
    /* 0x3ab8 */ bool _3ab8;  // set by sub_71009F9F30 when the sensor target changes

    // 0x71009f9f30 (placeholder name; called by m155 / m163): with the Sheikah Sensor+ obtained, sets the sensor target
    // (ActorName_SeakSensor_Slot0) to `name` and marks _3ab8 when it differs from the previous one
    void sub_71009F9F30(const sead::SafeString& name);

    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    void sub_71009F8510(s32);
};

extern const ksys::StateBase sUnk_71025ecb40;
extern const ksys::StateBase sUnk_71025ecc00;
extern const ksys::StateBase sUnk_71025ecba0;
extern const ksys::StateBase sUnk_71025ecc60;

class ScreenDLCSinJuAkashiNum : public ScreenEx {
public:
    ScreenDLCSinJuAkashiNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenDLCSinJuAkashiNum() override;
    SEAD_RTTI_OVERRIDE(ScreenDLCSinJuAkashiNum, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m99() override;
    void m69() override;
    void m100() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    // 0x7100a0488c: the number of the Hero Seal item (Goron / Zora / Rito / Gerudo) selected by `_3688`.
    s32 sub_7100A0488C();
    // 0x7100a0483c / 0x7100a04978 / 0x7100a04a0c / 0x7100a04a6c / 0x7100a04aac (placeholder names; `kind` is stored in _3688)
    void sub_7100A0483C(s32 mode, s32 kind);
    bool sub_7100A04978();
    bool sub_7100A04A0C();
    void sub_7100A04A6C(s32 add, s32 kind);
    void sub_7100A04AAC(s32 kind);

    /* 0x3610 */ u8 _3610{};
    s32 _3614{};
    s32 _3618{};
    s32 _361c{};
    /* 0x3620 */ UiTimer _3620;
    /* 0x3638 */ s32 _3638 = -1;
    Unk_7102474b78 _3640;
    /* 0x3680 */ eui::Animator* _3680{};
    /* 0x3688 */ u32 _3688{};
};

// ScreenHardMode: only the trivial virtual slots of the 154-245 block (the per-state callbacks, four
// slots per state; slot 4 overrides eui::Screen's) are declared. INCOMPLETE (see Screen).
// State objects of ScreenHardMode (StateTemplate<ScreenHardMode>; names are placeholders after the addresses).
extern const ksys::StateBase sUnk_71025ee750;
extern const ksys::StateBase sUnk_71025ee330;
extern const ksys::StateBase sUnk_71025ee5d0;
extern const ksys::StateBase sUnk_71025ee930;
extern const ksys::StateBase sUnk_71025ee810;
extern const ksys::StateBase sUnk_71025ee7b0;
extern const ksys::StateBase sUnk_71025ee6f0;
extern const ksys::StateBase sUnk_71025ee870;
extern const ksys::StateBase sUnk_71025ee8d0;

class ScreenHardMode : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ~ScreenHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenHardMode, ScreenEx)

    bool isEnableControl() const override;
    void close(s32 option) override;
    void m93(sead::Heap* heap) override;
    void m98() override;
    void m99() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a0bae4 (placeholder name): opens the screen and changes to the state at 0x71025ee7b0
    void sub_7100A0BAE4();

    // State callbacks (slots 154-245; the trivial ones are defined in uiScreenHardMode.cpp)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual s32 m173();
    virtual void m174();
    virtual void m175();
    virtual void m176();
    virtual s32 m177();
    virtual void m178();
    virtual void m179();
    virtual void m180();
    virtual s32 m181();
    virtual void m182();
    virtual void m183();
    virtual void m184();
    virtual s32 m185();
    virtual void m186();
    virtual void m187();
    virtual void m188();
    virtual s32 m189();
    virtual void m190();
    virtual void m191();
    virtual void m192();
    virtual s32 m193();
    virtual void m194();
    virtual void m195();
    virtual void m196();
    virtual s32 m197();
    virtual void m198();
    virtual void m199();
    virtual void m200();
    virtual s32 m201();
    virtual void m202();
    virtual void m203();
    virtual void m204();
    virtual s32 m205();
    virtual void m206();
    virtual void m207();
    virtual void m208();
    virtual s32 m209();
    virtual void m210();
    virtual void m211();
    virtual void m212();
    virtual s32 m213();
    virtual void m214();
    virtual void m215();
    virtual void m216();
    virtual s32 m217();
    virtual void m218();
    virtual void m219();
    virtual void m220();
    virtual s32 m221();
    virtual void m222();
    virtual void m223();
    virtual void m224();
    virtual s32 m225();
    virtual void m226();
    virtual void m227();
    virtual void m228();
    virtual s32 m229();
    virtual void m230();
    virtual void m231();
    virtual void m232();
    virtual s32 m233();
    virtual void m234();
    virtual void m235();
    virtual void m236();
    virtual s32 m237();
    virtual void m238();
    virtual void m239();
    virtual void m240();
    virtual s32 m241();
    virtual void m242();
    virtual void m243();
    virtual void m244();
    virtual s32 m245();

    // 0x7100a0bb34 (CSV ScreenHardMode::x; declaration only)
    void x();

    /* 0x3610 */ eui::Animator* _3610;
    /* 0x3618 */ eui::Animator* _3618;
    /* 0x3620 */ eui::Animator* _3620;
    u8 _3628[0x3638 - 0x3628];
    /* 0x3638 */ eui::AnimButton* _3638;
    /* 0x3640 */ eui::AnimButton* _3640;
    /* 0x3648 */ eui::LayoutEx* _3648;
    /* 0x3650 */ eui::LayoutEx* _3650;
    /* 0x3658 */ eui::LayoutEx* _3658;
    /* 0x3660 */ eui::LayoutEx* _3660;
    /* 0x3668 */ sead::FixedSafeString<128> _3668;
    /* 0x3700 */ s32 _3700;
    /* 0x3704 */ s32 _3704;
    /* 0x3708 */ s32 _3708;
    u8 _370c[0x3710 - 0x370c];
    /* 0x3710 */ const ksys::StateBase* _3710;
    /* 0x3718 */ s32 _3718;
    /* 0x371c */ s32 _371c;
    u8 _3720;
    /* 0x3721 */ u8 _3721;

    // 0x7100a0bfc8 (CSV unnamed; placeholder name): selects the state's animation `index` (-1: none)
    void sub_7100A0BFC8(s32 index);
    // 0x7100a0c084 (placeholder name): sets the text and the two button labels from the messages
    // `text`, `left` and `right` of the message set _3668 (StaticMsg/HardMode when empty; clears _3668)
    void sub_7100A0C084(const sead::SafeString& text, const sead::SafeString& left,
                        const sead::SafeString& right);
    // 0x7100a0c368 (placeholder name): as sub_7100A0C084 with one button (layout _3650)
    void sub_7100A0C368(const sead::SafeString& text, const sead::SafeString& button);
};

// Screens without members of their own that are modelled yet: only the (trivial, tail-calling)
// destructor and the RTTI.
class ScreenGamePadBG : public ScreenEx {
public:
    ScreenGamePadBG();
    void m82() override;
    // 0x7100a0b1d8
    void m83() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenGamePadBG() override;
    SEAD_RTTI_OVERRIDE(ScreenGamePadBG, ScreenEx)

    /* 0x3610 */ Unk_71024746b0Item* _3610{};
    /* 0x3618 */ eui::Animator* _3618{};
    /* 0x3620 */ eui::Animator* _3620{};
    u8 _3628[6]{};
    u8 _362e[2];
};

class ScreenWolfLinkHeartGauge : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    ScreenWolfLinkHeartGauge();
    ~ScreenWolfLinkHeartGauge() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    // 0x7100a6be1c (placeholder name): forwards to the gauge's sub_71009359E8
    void sub_7100A6BE1C();
    void sub_7100A6BD98();
    Unk_7102474be8* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenWolfLinkHeartGauge, ScreenEx)
};

class ScreenMainHorse : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ~ScreenMainHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHorse, ScreenEx)

    // 0x7100a10cd4: disables every animator of the screen
    void m101() override;

    u8 _pad_3610[0x3678 - 0x3610];
    /* 0x3678 */ eui::Animator* _3678[10];
    /* 0x36c8 */ eui::Animator* _36c8[10];
    /* 0x3718 */ sead::SafeArray<eui::Animator*, 10> _3718;
    u8 _pad_3768[0x3808 - 0x3768];
    /* 0x3808 */ eui::Animator* _3808;
    /* 0x3810 */ eui::Animator* _3810;
    /* 0x3818 */ eui::Animator* _3818;
    /* 0x3820 */ eui::Animator* _3820;
    u8 _pad_3828[0x3840 - 0x3828];
    /* 0x3840 */ eui::Animator* _3840;
    /* 0x3848 */ eui::Animator* _3848;
    /* 0x3850 */ UiTimer _3850;
    /* 0x3868 */ s32 _3868;  // number of charge animators in _3718
    /* 0x386c */ s32 _386c;

    // 0x7100a102cc (placeholder name; called by Manager 0x7100a790cc): stops the charge animators while the horse has
    // the charge penalty and closes the screen once the charge count is stable for one second
    void sub_7100A102CC();
};

class ScreenKeyNum : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenKeyNum();
    ~ScreenKeyNum() override;
    void open(s32 option) override;
    void m84() override;
    void m93(sead::Heap* heap) override;
    /* 0x3610 */ u32 _3610{};
    u8 _pad_3614[0x3618 - 0x3614];
    /* 0x3618 */ eui::Animator* _3618{};
    SEAD_RTTI_OVERRIDE(ScreenKeyNum, ScreenEx)
};

class ScreenGameTitle : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenGameTitle();
    ~ScreenGameTitle() override;
    SEAD_RTTI_OVERRIDE(ScreenGameTitle, ScreenEx)
};

struct ShopInfoTagData;

class ScreenDemoName : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    void m93(sead::Heap*) override;
    ScreenDemoName();
    ~ScreenDemoName() override;
    // 0x7100a03ee8 (one extra virtual slot, vtable offsets +8): shows the demo actor's name (T_Name_00) and its
    // sub text (<name>_SubText in StaticMsg/DemoActorSubText); false when the name has no message
    virtual bool m154(const sead::SafeString& name);
    SEAD_RTTI_OVERRIDE(ScreenDemoName, ScreenEx)
};

class ScreenDemoNameEnemy : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    void m93(sead::Heap*) override;
    ScreenDemoNameEnemy();
    ~ScreenDemoNameEnemy() override;
    // 0x7100a038bc (one extra virtual slot, vtable offsets +8): reads the argument as a string (called with
    // EventPlayUiActorName's ActorName) and returns true
    virtual bool m154(const sead::SafeString& name);
    SEAD_RTTI_OVERRIDE(ScreenDemoNameEnemy, ScreenEx)
};

class ScreenShopBG : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m94() override;
    void m98() override;
    void m100() override;
    void m101() override;
    ScreenShopBG();
    ~ScreenShopBG() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBG, ScreenEx)
};

class ScreenShopBtnList5 : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    ScreenShopBtnList5();
    ~ScreenShopBtnList5() override;
    /* 0x3610 */ ScreenAppPictureBookUnk* _3610{};  // the picture book list controller (it has _30c)
    void m93(sead::Heap* heap) override;
    /* 0x3618 */ eui::Animator* _3618{};
    /* 0x3620 */ eui::Animator* _3620{};
    /* 0x3628 */ u8 _3628{};
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList5, ScreenEx)
    void m94() override;
    void m98() override;
    void m100() override;
    // 0x7100a4df38 (slot 99)
    void m99() override;
    // 0x7100a4deb0 (placeholder name): the same body as ScreenShopBtnList15::sub_7100A4B2BC
    void sub_7100A4DEB0();
    // 0x7100a4dff0 / 0x7100a4e2dc (placeholder names; copies of ScreenShopBtnList15's sub_7100A4B3C4 / sub_7100A4B574)
    void sub_7100A4DFF0();
    bool sub_7100A4E2DC() const;
    // 0x7100a4e070 / 0x7100a4e084 (placeholder names): copies of ScreenShopBtnList20's sub_7100A4CD5C / sub_7100A4CD70
    void sub_7100A4E070(bool value);
    void sub_7100A4E084();
};

class ScreenPauseMenuBG : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m82() override;
    void m83() override;
    ScreenPauseMenuBG();
    ~ScreenPauseMenuBG() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    /* 0x3610 */ u8 _3610{};
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuBG, ScreenEx)
    // 0x7100a2bedc / 0x7100a2bf64 (placeholder names; called by ScreenPauseMenu): bring the background up (and remember
    // whether the UI manager's flag 2 was set) / close it again
    void sub_7100A2BEDC();
    void sub_7100A2BF64();
};

class ScreenSeekPadMenuBG : public ScreenEx {
public:
    void m82() override;
    void m83() override;
    const char* getLayoutName_() const override;
    ScreenSeekPadMenuBG();
    ~ScreenSeekPadMenuBG() override;
    void m93(sead::Heap* heap) override;
    // 0x7100a4a8a8 / 0x7100a4a91c (placeholder names)
    void sub_7100A4A8A8();
    void sub_7100A4A91C();
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenSeekPadMenuBG, ScreenEx)
};

class ScreenMainScreenMS : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenMainScreenMS();
    ~ScreenMainScreenMS() override;
    // 0x7100a16fd8 / 0x7100a16ff4: play the animator _3610 forward / backwards (speed 1 / -1).
    void sub_7100A16FD8();
    void sub_7100A16FF4();
    void m93(sead::Heap* heap) override;
    void m100() override;
    void m94() override;
    void sub_7100A16DF0();
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ eui::Animator* _3618{};
    /* 0x3620 */ Unk_7102474be8* _3620{};
    /* 0x3628 */ nn::ui2d::Pane* _3628{};
    /* 0x3630 */ u8 _3630{};
    SEAD_RTTI_OVERRIDE(ScreenMainScreenMS, ScreenEx)
};

class ScreenMainScreenHeartIchigekiDLC : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenMainScreenHeartIchigekiDLC();
    ~ScreenMainScreenHeartIchigekiDLC() override;
    void m93(sead::Heap* heap) override;
    void m100() override;
    void m94() override;
    // 0x7100a168f0 (declared only)
    void sub_7100A168F0();
    // 0x7100a16adc (placeholder name): forwards to the gauge's playAnimator8e0
    void sub_7100A16ADC();
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ Unk_7102474be8* _3618{};
    /* 0x3620 */ nn::ui2d::Pane* _3620{};
    /* 0x3628 */ u8 _3628{};
    SEAD_RTTI_OVERRIDE(ScreenMainScreenHeartIchigekiDLC, ScreenEx)
};

class ScreenAppSystemWindowNoBtn : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenAppSystemWindowNoBtn();
    ~ScreenAppSystemWindowNoBtn() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ u32 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindowNoBtn, ScreenEx)
    // 0x71009fb958 / 0x71009fb970 (placeholder names): set _3618 to 1 / 2, then open(2)
    void sub_71009FB958();
    void sub_71009FB970();
    // 0x71009fb930 (placeholder name): starts the animator at 0x3610 when it is stopped (rate 0)
    void sub_71009FB930();
};

class ScreenMessageTipsPauseMenu : public ScreenEx {
public:
    // 0x7100a25d9c (CSV unnamed, declared only)
    void sub_7100A25D9C(s32 a1);
public:
    ScreenMessageTipsPauseMenu();
    const char* getLayoutName_() const override;
    ~ScreenMessageTipsPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsPauseMenu, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;

    /* 0x3610 */ s32 _3610 = 2;
    /* 0x3614 */ UiTimer _3614;
    /* 0x362c */ u8 _362c{};
    u8 _362d[3];
};

class ScreenAmiiboWindow : public ScreenEx {
public:
    ScreenAmiiboWindow();
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    ~ScreenAmiiboWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAmiiboWindow, ScreenEx)

    // 0x71009d0c84: finds the layouts, buttons and animators
    void m93(sead::Heap* heap) override;
    void m98() override;
    void m99() override;
    void m100() override;
    void m101() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    /* 0x3610 */ s32 _3610 = 4;
    s32 _3614 = 3;
    /* 0x3618 */ eui::LayoutEx* _3618{};  // T_Text_00 (T_Text_01 / T_Text_02 in the five-message mode)
    /* 0x3620 */ eui::LayoutEx* _3620{};  // T_Btn_00
    /* 0x3628 */ eui::LayoutEx* _3628{};  // T_Btn_00 of the three-button mode
    /* 0x3630 */ eui::LayoutEx* _3630{};
    /* 0x3638 */ eui::LayoutEx* _3638{};
    /* 0x3640 */ eui::AnimButton* _3640{};
    eui::AnimButton* _3648{};
    eui::AnimButton* _3650{};
    eui::AnimButton* _3658{};
    eui::AnimButton* _3660{};
    eui::AnimButton* _3668{};
    /* 0x3670 */ eui::Animator* _3670{};
    /* 0x3678 */ eui::Animator* _3678{};
    /* 0x3680 */ eui::Animator* _3680{};
    /* 0x3688 */ u8 _3688{};
    u8 _3689{};
    u8 _368a{};
    u8 _368b{};
    u8 _368c[4];
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    // 0x7100a60918 (declared only): opens the window; ScreenGameOver::m158 passes (1, its draw target, nullptr)
    // 0x71009d06f4 (slot 154): sets the state (_3614) and the item flag, then opens the window
    virtual void m154(s32 type, bool flag);
    virtual void m155();

    // 0x71009d0898: sets the text and button messages (labels "%04d" in LayoutMsg/AmiiboWindow_00) and enables only
    // the first button
    void sub_71009D0898(s32 text_id, s32 button_id);
    // 0x71009d09ec: the five-message mode (two texts and three buttons; enables the last two buttons)
    void sub_71009D09EC(s32 text1_id, s32 text2_id, s32 button1_id, s32 button2_id, s32 button3_id);
};

class ScreenSystemWindowNoBtn : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenSystemWindowNoBtn();
    ~ScreenSystemWindowNoBtn() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    // 0x7100a60650 (placeholder name): starts the first animator if it is not running
    void sub_7100A60650();
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ eui::Animator* _3618{};
    SEAD_RTTI_OVERRIDE(ScreenSystemWindowNoBtn, ScreenEx)
};

class ScreenSystemWindow00 : public ScreenEx {
public:
    ScreenSystemWindow00();
    const char* getLayoutName_() const override;
    s32 m81() override;
    void m82() override;
    void m96() override;
    void m97() override;
    void m101() override;
    bool isEnableControl() const override;
    ~ScreenSystemWindow00() override;
    SEAD_RTTI_OVERRIDE(ScreenSystemWindow00, ScreenEx)
    // 0x7100a64634 / 0x7100a646b0
    void m98() override;
    void m99() override;

    /* 0x3610 */ eui::Animator* _3610 = nullptr;
    u64 _3618{};
    u64 _3620{};
    u64 _3628{};
    u64 _3630{};
    /* 0x3638 */ eui::LayoutEx* _3638;
    /* 0x3640 */ eui::LayoutEx* _3640;
    /* 0x3648 */ eui::LayoutEx* _3648;
    /* 0x3650 */ eui::LayoutEx* _3650;
    u8 _3658[0x3678 - 0x3658];
    /* 0x3678 */ eui::AnimButton* _3678[7];  // indexed by button tag - 0x58 (m99)
    /* 0x36b0 */ s32 _36b0 = 15;
    s32 _36b4;
    u64 _36b8{};
    u8 _36c0{};
    u8 _36c1{};
    u8 _36c2{};
    u8 _36c3;
    s32 _36c4 = -1;
    s32 _36c8 = -1;
    s32 _36cc = 4;
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    // 0x7100a60918 (declared only): opens the window; ScreenGameOver::m158 passes (1, its draw target, nullptr)
    virtual void m154(s32 type, s32 draw_target, void* arg);
    // 0x7100a61c40 / 0x7100a61d94 (placeholder names): one / two button window text and button state
    void sub_7100A61C40(const eui::MessageString& text, const eui::MessageString& button);
    void sub_7100A61D94(const eui::MessageString& text, const eui::MessageString& button1,
                        const eui::MessageString& button2);
    virtual void m155();

};

// 0x71009f1e9c / 0x71009f1f64 / 0x71009f202c (placeholder names; ScreenAppMap TU): load the app system window and open
// it with type 5 / 6 / 7
void sub_71009F1E9C();
void sub_71009F1F64();
void sub_71009F202C();
// 0x71009f2204 (placeholder name; ScreenAppMap TU): when the open app system window has no pending result, passes
// UiSubsys1::_3a0 to the pause menu child, sets PauseMenuDataMgr::_444fc to 2 and calls Manager::sub_7100A7C8D4
void sub_71009F2204();
// 0x71009e3b84 (placeholder name; ScreenAppMapDungeon TU): when the app system window of type 8 has closed with no
// pending result, stores the dungeon exit map / destination in the Manager and calls Manager::sub_7100A7C9C0
void sub_71009E3B84();
// 0x71025de180 (uiAppStateGlobals.cpp): flag bits of the AppMapDungeon screen functions
extern u16 sUnk_71025de180;
// 0x71009e5530 (placeholder name; ScreenAppMapDungeon TU): a dungeon-state check: false
// while bit 0 of sUnk_71025de180 is set or the curse flag is on in states 0 - 3; per state the Divine Beast boss
// appeared-and-died flags, the gear manager timer in state 4, false in state 5, true otherwise
bool sub_71009E5530();
// 0x71025de182 (uiAppStateGlobals.cpp; read with adrp + ldrb, so hidden): bit 0 makes sub_71009E6B5C true in
// states 0 - 4
KSYS_VISIBILITY_HIDDEN extern u8 sUnk_71025de182;
// 0x71009e6b5c (placeholder name; ScreenAppMapDungeon TU): per manager state (_64c38) whether the dungeon's app
// (Divine Beast relic, Final Trial) is available: true while bit 0 of sUnk_71025de180 or sUnk_71025de182 is set; in
// state 5 the Hyrule Castle area flag with no WolfLinkHeartGauge screen
bool sub_71009E6B5C();
// 0x7100a9eea4 / 0x7100a9eef4 (defined in uiManagerFacade.cpp)
const char* sub_7100A9EEA4();
const char* sub_7100A9EEF4();
// 0x71009da700 (defined in uiScreenLeafSlots.cpp; called by ScreenAppCamera::m93)
s32 sub_71009DA700(nn::ui2d::Pane* pane, const sead::SafeString& prefix);
// A pane collected by sub_71009DA7E8 (placeholder; the second word is cleared when it is added).
struct CollectedPane {
    explicit CollectedPane(nn::ui2d::Pane* pane_) : pane(pane_) {}
    nn::ui2d::Pane* pane;
    void* _8 = nullptr;
};
// 0x71009da7e8 (defined in uiScreenLeafSlots.cpp; called by ScreenAppCamera::m93): as sub_71009DA700, and also adds
// the matching panes to `out` while it has room
s32 sub_71009DA7E8(sead::ObjArray<CollectedPane>* out, nn::ui2d::Pane* pane, const sead::SafeString& prefix);
// 0x7100a9ac84 (defined in uiScreenFacade.cpp)
void sub_7100A9AC84(void* a1);
// 0x7100a96254 (defined in uiScreenFacade.cpp): passes the boss gauge info to the main screen
void sub_7100A96254(BossGaugeInfo* info);
// 0x7100aa8784 (CSV checkFlagsAndSetCurrentRuneStuff; declared only)
void checkFlagsAndSetCurrentRuneStuff();

class ScreenPauseMenuMantan : public ScreenEx {
public:
    ScreenPauseMenuMantan();
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    ~ScreenPauseMenuMantan() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuMantan, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    void m107(eui::AnimButton* button) override;

    // 0x71024929f8 (placeholder name): the window's result (5: none yet); 0x7100a3219c takes it and resets it
    static s32 sResult;
    static s32 takeResult();
    // 0x7100a31fa4 (placeholder name): shows the message for `index` (0: "0000", 2: "0006", else "0005") in T_Text_00
    void sub_7100A31FA4(s32 index);

    /* 0x3610 */ s32 _3610 = 5;
    void m99() override;
    void m106(eui::AnimButton* button) override;
};

class ScreenPauseMenuEiketsu : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m107(eui::AnimButton*) override;
    bool isEnableControl() const override;
    ScreenPauseMenuEiketsu();
    ~ScreenPauseMenuEiketsu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuEiketsu, ScreenEx)
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m101() override;
    void m99() override;
    void m106(eui::AnimButton* button) override;
};

class ScreenAppSystemWindow : public ScreenEx {
public:
    ScreenAppSystemWindow();
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    s32 m81() override;
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    bool isEnableControl() const override;
    ~ScreenAppSystemWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindow, ScreenEx)
    // 0x71009fc4a0 (placeholder name; static): returns the value of sUnk_7102483490 and sets it to 6
    static s32 sub_71009FC4A0();
    void m99() override;
    void m100() override;
    void m94() override;
    void m101() override;
    void m106(eui::AnimButton* button) override;

    /* 0x3610 */ s32 _3610 = 10;
    s32 _3614;
    u64 _3618{};
    u64 _3620{};
    u64 _3628{};
    u64 _3630{};
    eui::AnimButton* _3638{};
    u64 _3640{};
    u64 _3648{};
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    // 0x71009fbd7c (declared only, 1824 bytes): stores `type` at 0x3610 and opens the window for it (types 0 - 9)
    virtual void m154(s32 type);
    virtual void m155();

};

class ScreenHardModeTextDLC : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenHardModeTextDLC();
    ~ScreenHardModeTextDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenHardModeTextDLC, ScreenEx)
    void m98() override;
};

class ScreenEnd : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m94() override;
    ScreenEnd();
    ~ScreenEnd() override;
    SEAD_RTTI_OVERRIDE(ScreenEnd, ScreenEx)
};

class ScreenLastComplete : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenLastComplete();
    ~ScreenLastComplete() override;
    SEAD_RTTI_OVERRIDE(ScreenLastComplete, ScreenEx)
};

class ScreenOPtext : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    // 0x7100a28688: the first animator's frame of the text index 0..2 (0 / 1 / 2)
    virtual void m154(s32 index);
    ScreenOPtext();
    ~ScreenOPtext() override;
    void m93(sead::Heap* heap) override;
    /* 0x3610 */ eui::Animator* _3610{};
    /* 0x3618 */ f32 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenOPtext, ScreenEx)
};

class ScreenLoadingWeapon : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenLoadingWeapon();
    ~ScreenLoadingWeapon() override;
    SEAD_RTTI_OVERRIDE(ScreenLoadingWeapon, ScreenEx)
};

class ScreenMainHardMode : public ScreenEx {
public:
    ScreenMainHardMode();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMainHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHardMode, ScreenEx)
    void open(s32 option) override;
    void close(s32 option) override;

    /* 0x3610 */ UiTimer _3610;
    /* 0x3628 */ u8 _3628{};
    u8 _3629[7];
};

class ScreenSkip : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    // 0x7100a537f8: opens the screen and switches the skip icon (10 with the button, 8 without).
    void sub_7100A537F8(bool with_button);
    // 0x7100a537c8 (slot 93): remembers the first child as the icon holder (its layout is at 0x20)
    void m93(sead::Heap* heap) override;
    ScreenSkip();
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    bool isEnableControl() const override;
    ~ScreenSkip() override;
    SEAD_RTTI_OVERRIDE(ScreenSkip, ScreenEx)

    /* 0x3610 */ ScreenChildEx* _3610{};
    s32 _3618 = 30;
    s32 _361c;
};

class ScreenChangeController : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenChangeController();
    ~ScreenChangeController() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    // 0x7100a00ee8 (overrides Screen::m98)
    void m98() override;
    eui::Animator* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenChangeController, ScreenEx)
    // 0x7100a00ef0 (placeholder name): opens the screen (option 2 in states 1 / 2, else 1) and stops the animator at `frame`
    void sub_7100A00EF0(u32 frame);
};

class ScreenDemoStart : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ScreenDemoStart();
    ~ScreenDemoStart() override;
    void m93(sead::Heap* heap) override;
    eui::Animator* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenDemoStart, ScreenEx)
};

class ScreenBootUp : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenBootUp();
    ~ScreenBootUp() override;
    SEAD_RTTI_OVERRIDE(ScreenBootUp, ScreenEx)
    void m94() override;
};

class ScreenAppMenuBtn : public ScreenEx {
public:
    s32 m81() override;
    // 0x71009f2d8c: override of Screen::m83; opens the screen when the gliding / surfing rupee is force enabled
    void m83() override;
    void m94() override;
    void m98() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ScreenAppMenuBtn();
    ~ScreenAppMenuBtn() override;
    // 0x71009f2b84
    void m93(sead::Heap* heap) override;
    // 0x71009f2c7c
    void m107(eui::AnimButton* button) override;
    /* 0x3610 */ eui::Animator* _3610{};  // "TexPattern" of _3618's layout
    /* 0x3618 */ eui::AnimButton* _3618{};  // Pa_Btn_00
    /* 0x3620 */ u16 _3620{};
    SEAD_RTTI_OVERRIDE(ScreenAppMenuBtn, ScreenEx)
};

class ScreenHomeMenuCapture : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenHomeMenuCapture();
    ~ScreenHomeMenuCapture() override;
    void m93(sead::Heap* heap) override;
    void m94() override;
    void m98() override;
    /* 0x3610 */ eui::LayoutEx* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenHomeMenuCapture, ScreenEx)
};

class ScreenShopBtnList20 : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    // 0x7100a4cef0 (placeholder name): whether the button group has a down button
    bool sub_7100A4CEF0() const;
    ~ScreenShopBtnList20() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList20, ScreenEx)
    void m102(eui::AnimButton*) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a4c9e0 (slot 98)
    void m94() override;
    void m98() override;
    // 0x7100a4cd5c / 0x7100a4cd70 / 0x7100a4ce28 (placeholder names): forward to the picture book controller
    void sub_7100A4CD5C(bool value);
    void sub_7100A4CCB0(s32 category, s32 first, s32 last);
    void sub_7100A4CD80(s32 index);
    void sub_7100A4CC28(s32 mode);
    void sub_7100A4CC98();
    void sub_7100A4CD70();
    s32 sub_7100A4CE28();
    // 0x7100a4ce68 (placeholder name): plays the sound event of a carry action (0: decide, 1: prohibited, 2: sort, 3: carry,
    // 4: carry end)
    void sub_7100A4CE68(s32 action);
    // 0x7100a4bae4 (CSV ScreenShopBtnList20::ctor)
    ScreenShopBtnList20();

    // A callback and a name (delegate vtable 0x7102480298, shared with other delegate instantiations), as in
    // ScreenDLCWindow.
    struct Entry {
        sead::Delegate<ScreenShopBtnList20> callback;
        sead::FixedSafeString<128> name;
    };
    static_assert(sizeof(Entry) == 0xb8);
    // value-initialised in the ctor (one 0x230-byte memset before the member constructors)
    struct Unk3610 {
        ScreenAppPictureBookUnk* controller;
        Entry entries[3];
    };

    /* 0x3610 */ Unk3610 _3610;
    // Producer A4C708 creates this animator and casts the three getChild results to ScreenChildEx.
    /* 0x3840 */ eui::Animator* _3840 = nullptr;
    /* 0x3848 */ ScreenChildEx* _3848 = nullptr;
    /* 0x3850 */ ScreenChildEx* _3850 = nullptr;
    /* 0x3858 */ ScreenChildEx* _3858 = nullptr;
    /* 0x3860 */ s32 _3860 = 0;
    /* 0x3864 */ u8 _3864 = 0;
    u8 _pad_3865[0x3868 - 0x3865];
    eui::AnimButton* _3868 = nullptr;
};

class ScreenTime : public ScreenEx {
public:
    ScreenTime();
    const char* getLayoutName_() const override;
    ~ScreenTime() override;
    SEAD_RTTI_OVERRIDE(ScreenTime, ScreenEx)

    /* 0x3610 */ sead::FixedSafeString<128> _3610;
};

class ScreenChallengeWin : public ScreenEx {
public:
    ScreenChallengeWin();
    const char* getLayoutName_() const override;
    ~ScreenChallengeWin() override;
    SEAD_RTTI_OVERRIDE(ScreenChallengeWin, ScreenEx)

    bool sub_7100A007F4(const ksys::qst::Quest* quest);
    void m93(sead::Heap* heap) override;
    // Slots 83 / 86 / 91 (0x7100a00b68 / 0x7100a00af8 / 0x7100a00bfc): clear both strings, restart the timer and close
    // the layout and the screen; m83 and m91 do it only while the layout's byte at +0x91 is 1 or 2.
    void m80(bool visible) override;
    void m83() override;
    void m86() override;
    void m91() override;
    /* 0x3610 */ eui::LayoutEx* _3610{};
    /* 0x3618 */ sead::FixedSafeString<256> _3618;
    /* 0x3730 */ sead::FixedSafeString<256> _3730;
    /* 0x3848 */ UiTimer _3848;
    u8 _3860{};
    u8 _3861[7];
    eui::Animator* _3868{};
    eui::Animator* _3870{};
};

struct ScreenAppPictureBookUnk;

// The controller window's button unit (vtable 0x7102485670, 0x58 bytes). The ScreenControllerWindow
// function at 0x7100a03478 creates one per button; the unit starts a "New" animator.
class Unk_7102485670 : public Unk_7102474e38 {
public:
    SEAD_RTTI_OVERRIDE(Unk_7102485670, Unk_7102474e38)
    Unk_7102485670() = default;
    // no destructor of its own: the vtable's D1 slot is Unk_7102474e38's D1 (the implicit one is aliased to it)
    void m4(sead::Heap*) override;
    void m6() override;
    // 0x7100a01918 (not decompiled; m6 tail-calls it)
    void sub_7100A01918();

    /* 0x48 */ eui::Animator* _48{};
    /* 0x50 */ bool _50{};
};

class ScreenControllerWindow : public ScreenEx {
public:
    void m101() override;
    void m106(eui::AnimButton*) override;
    void m107(eui::AnimButton*) override;
    void m138(void* a1, void* a2) override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenControllerWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenControllerWindow, ScreenEx)
    void m99() override;
    void m100() override;

    // 0x7100a01a54 (CSV ScreenControllerWindow::ctor)
    ScreenControllerWindow();

    // A callback and a name (delegate vtable 0x7102480298, shared with other delegate instantiations).
    struct Entry {
        sead::Delegate<ScreenControllerWindow> callback;
        sead::FixedSafeString<128> name;
    };
    static_assert(sizeof(Entry) == 0xb8);
    // value-initialised in the ctor (one 0x240-byte memset before the member constructors)
    struct Entries {
        u64 _0;
        ScreenAppPictureBookUnk* _8;
        u64 _10;
        Entry entries[3];
    };

    /* 0x3610 */ Entries _3610;
    /* 0x3850 */ u8 _3850{};
    /* 0x3851 */ u8 _3851{};
    // A02A74 writes 32-bit task IDs; ObjArray free-list slots retain pointer alignment.
    /* 0x3858 */ sead::FixedObjArray<s32, 29> _3858;
    /* 0x3a48 */ s32 _3a48 = -1;
    /* 0x3a50 */ u64 _3a50{};
    /* 0x3a58 */ u64 _3a58{};
    /* 0x3a60 */ u64 _3a60{};
};
static_assert(sizeof(sead::FixedObjArray<s32, 29>) == 0x1f0);
static_assert(offsetof(ScreenControllerWindow, _3a48) == 0x3a48);

// The DLC window's tip unit (vtable 0x71024872a0, 0x50 bytes). The ScreenDLCWindow function at
// 0x7100a067a8 creates the units; each one looks up its Pa_DLCTips_00 parts layout.
class Unk_71024872a0 : public Unk_7102474e38 {
public:
    SEAD_RTTI_OVERRIDE(Unk_71024872a0, Unk_7102474e38)
    Unk_71024872a0() = default;
    // no destructor of its own: the vtable's D1 slot is Unk_7102474e38's D1 (the implicit one is aliased to it)
    void m4(sead::Heap*) override;
    void m6() override;

    /* 0x48 */ eui::LayoutEx* _48{};
};

class ScreenDLCWindow : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenDLCWindow() override;
    // 0x7100a05e2c (placeholder name; one extra virtual slot, vtable offsets +8): sets the button texts and opens
    // the window
    virtual void m154();
    SEAD_RTTI_OVERRIDE(ScreenDLCWindow, ScreenEx)
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;

    // 0x7100a05f94 (placeholder name): returns the result and sets it to 2
    s32 sub_7100A05F94();
    // 0x7100a05f7c (placeholder name): stops the animator at 0x3870 at `frame`
    void sub_7100A05F7C(f32 frame);
    // 0x7100a05cb4 (placeholder name): stops the animators, sets the title text to the message of the
    // current DLC version and opens the window with the animator pair selected by `use_alt_animators`
    void sub_7100A05CB4(bool use_alt_animators);

    // 0x7100a05528 (CSV ScreenDLCWindow::ctor)
    ScreenDLCWindow();

    // A callback and a name (delegate vtable 0x7102480298, shared with other delegate instantiations).
    struct Entry {
        sead::Delegate<ScreenDLCWindow> callback;
        sead::FixedSafeString<128> name;
    };
    static_assert(sizeof(Entry) == 0xb8);
    // value-initialised in the ctor (one 0x230-byte memset before the member constructors)
    struct Entries {
        u64 _0;
        Entry entries[3];
    };

    /* 0x3610 */ Entries _3610;
    u8 _3840[0x3850 - 0x3840] = {};
    // the window's open / close animators (set as the layout's in m154)
    /* 0x3850 */ eui::Animator* _3850 = nullptr;
    /* 0x3858 */ eui::Animator* _3858 = nullptr;
    // the second open / close animator pair (used by sub_7100A05CB4 instead of 0x3850 / 0x3858)
    /* 0x3860 */ eui::Animator* _3860 = nullptr;
    /* 0x3868 */ eui::Animator* _3868 = nullptr;
    /* 0x3870 */ eui::Animator* _3870 = nullptr;
    /* 0x3878 */ eui::Animator* _3878 = nullptr;
    /* 0x3880 */ eui::Animator* _3880 = nullptr;
    /* 0x3888 */ s32 _3888 = 1;
    // the two buttons (T_BtnL_00 / T_BtnR_00 messages)
    /* 0x3890 */ eui::ButtonBase* _3890 = nullptr;
    /* 0x3898 */ eui::ButtonBase* _3898 = nullptr;
    /* 0x38a0 */ u32 _38a0 = 0;
    /* 0x38a4 */ u8 _38a4 = 0;
    /* 0x38a5 */ u8 _38a5 = 0;
    /* 0x38a6 */ u8 _38a6 = 0;
    /* 0x38a7 */ u8 _38a7 = 0;
    /* 0x38a8 */ u32 _38a8 = 0;
    /* 0x38ac */ u8 _38ac = 0;
    /* 0x38b0 */ s32 _38b0 = 3;
    // 0x7102486d48 (placeholder name): the window's result (0: no, 1: yes, 2: none yet)
    static s32 sResult;
};

class ScreenTitle : public ScreenEx {
public:
    ScreenTitle();
    // 0x7100A6B178 consumes a bool in w0 and no receiver; NewSaveRun calls it directly.
    static void sub_7100A6B178(bool value);
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    void m96() override;
    // 0x7100a6ba08 (slot 99): moves the box cursor to the start button (tag 0x68, 0x69 or 0x6a)
    void m99() override;
    bool isEnableControl() const override;
    ~ScreenTitle() override;
    SEAD_RTTI_OVERRIDE(ScreenTitle, ScreenEx)
    // 0x7100a69aec / 0x7100a69b6c (placeholder names): restart the animator at 0x3610 and forget the two selections /
    // whether it is at its end
    void sub_7100A69AEC();
    bool sub_7100A69B6C();
    // 0x7100a69b28 (placeholder name): clears _363c, sets _3680 to 0x200 in E3 demo mode, and sets bit 1 of the button group's _38
    void sub_7100A69B28();

    /* 0x3610 */ eui::Animator* _3610;  // zeroed in the constructor body
    u64 _3618;
    u64 _3620;
    u64 _3628;
    u64 _3630;
    /* 0x3638 */ u8 _3638 = 0;
    /* 0x3639 */ bool _3639 = false;
    u8 _363a[2]{};
    s32 _363c = -1;
    s32 _3640 = -1;
    u8 _3644[4];
    u64 _3648{};
    u64 _3650{};
    u64 _3658{};
    u64 _3660{};
    u64 _3668{};
    u64 _3670{};
    u64 _3678{};
    s32 _3680 = -1;
    u8 _3684[4];
    Unk_710249d300 _3688;
};

// State object of ScreenAppCamera (a StateTemplate<ScreenAppCamera>, 0x71025dcca0).
extern const ksys::StateBase sUnk_71025dcca0;

// 0x71025dcd60 / 0x71025dcd00 (placeholder names): two more ScreenAppCamera states
extern const ksys::StateBase sUnk_71025dcd60;
extern const ksys::StateBase sUnk_71025dcd00;

class ScreenAppCamera : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    void m127() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppCamera() override;
    SEAD_RTTI_OVERRIDE(ScreenAppCamera, ScreenEx)

    /* 0x3610 */ Unk_710247dc90* _3610;  // the photo capture child (m162 writes its _6f8 / _700)
    /* 0x3618 */ eui::Animator* _3618;
    /* 0x3620 */ eui::Animator* _3620;
    /* 0x3628 */ eui::Animator* _3628;
    /* 0x3630 */ eui::Animator* _3630;
    /* 0x3638 */ eui::Animator* _3638;
    u8 _pad_3640[0x3648 - 0x3640];
    /* 0x3648 */ xlink2::HandleSLink _3648;  // the camera sound
    u8 _pad_3658[0x3688 - 0x3658];
    /* 0x3688 */ eui::LayoutEx* _3688;
    /* 0x3690 */ eui::Animator* _3690;
    u8 _pad_3698[0x36e8 - 0x3698];
    /* 0x36e8 */ s32 _36e8;
    /* 0x36ec */ s32 _36ec;  // frames counted by m159 while _3618 is stopped
    u8 _pad_36f0[0x36f8 - 0x36f0];
    // The two textures the photo is encoded into (m162 -> sub_71009DB9C8).
    /* 0x36f8 */ agl::TextureData _36f8;
    u8 _pad_3878[0x3b70 - 0x36f8 - sizeof(agl::TextureData)];
    /* 0x3b70 */ agl::GPUMemVoidAddr _3b70;  // the photo image memory (freed by m101)
    /* 0x3b88 */ agl::TextureData _3b88;
    u8 _pad_3d08[0x4018 - 0x3b88 - sizeof(agl::TextureData)];
    /* 0x4018 */ bool _4018;
    /* 0x4019 */ bool _4019;  // set when the camera mode was entered from a state that must be left
    /* 0x401a */ bool _401a;
    u8 _pad_401b[0x4020 - 0x401b];
    /* 0x4020 */ u8* _4020;
    /* 0x4028 */ s32 _4028;
    u8 _pad_402c[4];
    /* 0x4030 */ u8* _4030;
    /* 0x4038 */ s32 _4038;
    u8 _pad_403c[0x4040 - 0x403c];
    /* 0x4040 */ u8 _4040[0x20];
    /* 0x4060 */ u8 _4060[0x20];
    /* 0x4080 */ bool _4080;
    u8 _pad_4081[0x4198 - 0x4081];
    /* 0x4198 */ sead::SafeString _4198;
    u8 _pad_41a8[0x4368 - 0x41a8];
    /* 0x4368 */ Unk_7102474bc8 _4368;
    u8 _pad_44c0[0x44c8 - 0x4368 - sizeof(Unk_7102474bc8)];
    /* 0x44c8 */ eui::Animator* _44c8;
    /* 0x44d0 */ eui::Animator* _44d0;

    // 0x71009d9ad8 (placeholder name): stops every animator of the screen at its start and applies it
    void sub_71009D9AD8();

    void m99() override;
    // 0x71009db754: closes the camera screen
    void m100() override;
    // 0x71009d94e8 (CSV ScreenAppCamera::calledFromM159; declared only)
    void sub_71009D94E8();

    // 0x71009db888: frees the photo image memory and the two work buffers
    void m101() override;

    // state callbacks (slots 154-166, trivial ones defined in uiScreenLeafSlots.cpp)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    // 0x71009d80b8 (declared only; 404 bytes): tears down the camera run's allocations
    void sub_71009D80B8(u8 a1, s32 a2);
    virtual s32 m165();
    virtual void m166();
};

class ScreenEnergyMeterDLC : public ScreenEx {
public:
    ScreenEnergyMeterDLC();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenEnergyMeterDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenEnergyMeterDLC, ScreenEx)

    // 0x7100a08850 (slot 0x2f8, overrides Screen::m93): finds the energy meter parts and the Dungeon animator, starts the animator
    void m93(sead::Heap*) override;
    // 0x7100a094f8 (placeholder name): copies two values of _3618 into the motorcycle manager's energy position
    void sub_7100A094F8();
    void m98() override;

    /* 0x3610 */ u8 _3610 = 0;
    u8 _3611[7];
    /* 0x3618 */ Unk_71024774a8 _3618;
    /* 0x36d0 */ nn::ui2d::Pane* _36d0 = nullptr;
    /* 0x36d8 */ u8 _36d8 = 0;
    u8 _36d9[3];
    /* 0x36dc */ u32 _36dc[2]{};
    u8 _36e4[4];
    /* 0x36e8 */ eui::Animator* _36e8 = nullptr;
    /* 0x36f0 */ u64 _36f0 = 0;
    /* 0x36f8 */ sead::PerspectiveProjection mProjection;
    /* 0x37b8 */ u64 _37b8 = 0;
};
KSYS_CHECK_SIZE_NX150(ScreenEnergyMeterDLC, 0x37c0);

struct ShopInfoTagData {
    sead::FixedSafeString<64> str;
    u32 _58 = 0xffffffff;
    u32 _5c = 1;
};

// Placeholder name: the shop info tag row that shows a tag as either the item name or the cook name
// (0x71009b0c34 / 0x71009b0cf4). Only the fields those two methods use are modelled.
class ShopInfoTagRow {
public:
    void sub_71009B0C34(ShopInfoTagData* data);
    void sub_71009B0CF4(ShopInfoTagData* data);

    u8 _0[0x20];
    /* 0x20 */ eui::LayoutEx* _20 = nullptr;
    u8 _28[0x148 - 0x28];
    /* 0x148 */ eui::LetterAnimControl* _148 = nullptr;
};

class ScreenMessageGet : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMessageGet() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageGet, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m99() override;
    // 0x7100a257f4 (slot 101): clears the UI singleton's actor name and runs ui::sub_7100A9B2D0
    void m101() override;

    // 0x7100a23778 (CSV ScreenMessageGet::ctor)
    ScreenMessageGet();
    // 0x7100a238c8 (placeholder name): app-tag handler bound to _3750 (same body as ScreenShopInfo::sub_7100A51790)
    u32 sub_7100A238C8(const sead::MessageSet<char16>::TagInfo* tag, sead::WBufferedSafeString* out);

    // The ctor zeroes 0x3610-0x3652 with one memset (merged member initialisers).
    u8 _pad_3610[0x3640 - 0x3610] = {};
    /* 0x3640 */ eui::LayoutEx* _3640 = nullptr;
    u8 _pad_3648[0x3650 - 0x3648] = {};
    /* 0x3650 */ u8 _3650 = 0;
    /* 0x3651 */ u8 _3651 = 0;
    /* 0x3658 */ eui::ControlBase* _3658 = nullptr;
    u8 _pad_3660[0x3670 - 0x3660];
    Unk_710247adc8 _3670[2];
    /* 0x36f0 */ ShopInfoTagData _36f0;
    /* 0x3750 */ sead::Delegate2R<ScreenMessageGet, const sead::MessageSet<char16>::TagInfo*,
                                  sead::WBufferedSafeString*, u32>
        _3750;
    /* 0x3770 */ s32 _3770 = -1;
    /* 0x3774 */ u32 _3774 = 0;
    /* 0x3778 */ u32 _3778 = 0;
    /* 0x3780 */ sead::FixedSafeString<64> _3780;
    /* 0x37d8 */ sead::Buffer<Unk_7102474ba8> _37d8;
};

class ScreenSousaGuide : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    ScreenSousaGuide();
    ~ScreenSousaGuide() override;
    SEAD_RTTI_OVERRIDE(ScreenSousaGuide, ScreenEx)

    /* 0x3610 */ s32 _3610 = -1;
    u8 _pad_3614[0x3618 - 0x3614];
    Unk_7102474bc8 _3618;

    // 0x7100a56d08 (placeholder name): clears _3610 and calls _3618.sub_71009348D0(true) if it was set
    void sub_7100A56D08();
    // 0x7100a54270 (slot 94)
    void m94() override;
    // 0x7100a5434c (placeholder name; 10684 bytes, declared only): shows the guide page `guide`; `flag` is true when the screen was just opened
    void sub_7100A5434C(s32 guide, bool flag);
    // 0x7100a542e4 (placeholder name): opens the screen and shows the guide page `guide` unless it is -1 / 0x16 / shown already
    void sub_7100A542E4(s32 guide);
    // 0x7100a56d30 (placeholder name): redraws the current guide page (if any) and runs x_2
    void sub_7100A56D30();
};

struct ShopInfoTagData;

class ScreenShopBtnList15 : public ScreenEx {
public:
    ScreenShopBtnList15();
    bool isEnableControl() const override;
    // 0x7100a4b574 (placeholder name): whether the button group has a down button
    bool sub_7100A4B574() const;
    // 0x7100a4b10c (placeholder name): moves the box cursor to tag 122 + index (122 for an index out of range)
    void sub_7100A4B10C(s32 index);
    const char* getLayoutName_() const override;
    ~ScreenShopBtnList15() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList15, ScreenEx)
    void m94() override;
    void m100() override;
    // 0x7100a4b444: a button was selected; tells the shop manager the index (tag - 122) of the item
    void m102(eui::AnimButton* button) override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a4b0b4 (placeholder name): sets the flag 0x10 of the 15 buttons (tags 122 - 136)
    void sub_7100A4B0B4(bool on);
    // 0x7100a4b2bc (placeholder name): sets up the "Pa_GuideA_00" / "Pa_GuideB_00" layouts when they are idle or stopped
    void sub_7100A4B2BC();
    // 0x7100a4b3c4 (placeholder name): closes the "Pa_GuideA_00" / "Pa_GuideB_00" layouts when they are opening or open
    void sub_7100A4B3C4();
    // 0x7100a4b50c (placeholder name): shows the name of the item described by `data` in "T_Name_00"
    void sub_7100A4B50C(ShopInfoTagData* data);

    UiTexSlots _3610;
};

// Tag-argument block at ScreenShopInfo +0x3788: a FixedSafeString<64> (the ScreenShopInfo ctor
// carries its two vtable stores) followed by the selector u32s the 0xaa4b4c/0xaa4e70 tag handlers
// compare (read through the 0xaa4e60/0xaa5140 forwarders as +0x58/+0x5c; the ctor writes both halves
// with one 0x1ffffffff store).

// 0x7100aa4b4c / 0x7100aa4e70 (CSV placeholders, not decompiled yet): resolve a shop tag into `out`
// (the handlers compare the selector against a table and copy the found message).
u32 sub_7100AA4B4C(ShopInfoTagData* data, u32 selector, sead::WBufferedSafeString* out);
u32 sub_7100AA4E70(ShopInfoTagData* data, u32 sel_lo, u32 sel_hi, sead::WBufferedSafeString* out);
// 0x7100aa4e60 / 0x7100aa5140 (CSV placeholders): forwarders reading the selector from the tag data.
u32 sub_7100AA4E60(ShopInfoTagData* data, sead::WBufferedSafeString* out);
u32 sub_7100AA5140(ShopInfoTagData* data, sead::WBufferedSafeString* out);
// 0x7100aa2e08 (CSV unnamed): resolve the tag data's string into a message (empty message when
// the string is empty, else the "<profile>" / "<name>_Desc" lookup through sub_7100AA2FA0).
u32 sub_7100AA2E08(ShopInfoTagData* data, eui::MessageString* out);
// 0x7100aa2fa0 (CSV unnamed): fill `arg1` with "ActorType/<profile>" and `arg2` with
// "<name>_Desc" for the tag data's (suffix-stripped) actor name.
void sub_7100AA2FA0(ShopInfoTagData* data, sead::BufferedSafeStringBase<char>* arg1,
                    sead::BufferedSafeStringBase<char>* arg2);
// 0x7100aa29c4 (CSV unnamed): strip the "_Far" suffix from the name, reporting whether it changed.
bool sub_7100AA29C4(const sead::SafeString& actor_name, sead::SafeString& name);
// 0x7100aa2bdc (CSV unnamed): resolve the tag data's string into a message (suffix-stripped actor
// name under ActorType/<profile>, or the empty message).
u32 sub_7100AA2BDC(const sead::SafeString& actor_name, eui::MessageString* out);
// 0x7100aa3b50 (CSV unnamed): build the "UI/StockItem/<icon>" texture path for `name` into `out`
// (icon-actor lookup, Weapon_Sword_502/503 quirk, ".%02d" count suffix, ".bitemico" extension).
void sub_7100AA3B50(const sead::SafeString& name, sead::BufferedSafeStringBase<char>* out,
                    s32 count);
// 0x7100aa3ea0 / 0x7100aa4354: inventory icon path and Master Sword state icon name.
void sub_7100AA3EA0(const PouchItem* item, sead::BufferedSafeString* out);
void sub_7100AA4354(const PouchItem* item, sead::BufferedSafeString* out);
// 0x7100a91e40 (CSV unnamed): the item count for `name` (0 when the name is empty or there is
// no pouch manager).
s32 sub_7100A91E40(const sead::SafeString& name, bool count_equipped);
u32 sub_7100A92180(const sead::SafeString& name, s32 a2, s32 a3);
u32 sub_7100A91E84(const sead::SafeString& name, s32 type, s32 a3, bool flag);
// 0x7100a90e40 (CSV unnamed): the trade state of the item for the shop states 3 / 7 / 8 and the rest
// (payment check through the rupee / mamo flags; `a4` is the item count).
u32 sub_7100A90E40(const sead::SafeString& name, s32 a2, s32 a3, s32 a4);
// 0x7100a91f64 (CSV unnamed): the armour upgrade state of the item (next rank name lookup).
u32 sub_7100A91F64(const sead::SafeString& name, s32 a2, s32 a3);
// 0x71010b3468 / 0x71010b3484 (CSV placeholders): TagInfo adapters into the ksys::eft helpers
// (called by the ScreenMessage3D tag invoke).
void sub_71010B3468(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag);
void sub_71010B3484(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag);
// 0x71010b3188 (CSV unnamed): TagInfo dispatch shared by the ScreenMessage3D tag invoke (below)
// and the dialog scan (calls the eft voice helper and the WeaponBase TU helper).
void sub_71010B3188(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool a,
                    s16* out, bool b);

class Unk_710247d0c8;

class ScreenShopInfo : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    ScreenShopInfo();
    const char* getLayoutName_() const override;
    void m94() override;
    void m96() override;
    void m101() override;
    ~ScreenShopInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenShopInfo, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;
    // 0x7100a51790 (CSV placeholder): app-tag router bound to _3768 (TagInfo type 7 routes to
    // sub_7100AA4E60, type 8 to sub_7100AA5140; anything else returns 0).
    u32 sub_7100A51790(const sead::MessageSet<char16>::TagInfo* tag,
                       sead::WBufferedSafeString* out);
    // 0x7100a52088 (placeholder name): the child at (group, index) if it is a ScreenChildEx
    ScreenChildEx* getChildExMaybe(s32 group, s32 index);

    // 0x7100a52db0 (CSV placeholder): mode select (1 = full refresh through sub_7100A52E60,
    // 0 = re-resolve the shop message into _3650; anything else only runs the _3620 animator).
    void sub_7100A52DB0(u32 mode, ShopInfoTagData* data);
    // 0x7100a53328 (placeholder name): closes the number pane's current animation and shows `value` in T_Num_00
    void sub_7100A53328(s32 value);
    // 0x7100a52e60 (CSV placeholder, not decompiled yet): the full shop refresh (888B; uses
    // _3690/_3698/_3658, calls sub_7100AA2BDC + unnamed 0x9c2c28/2c44/2c8c/2d44 + sub_7100AA3B50).
    // Declared only so sub_7100A52DB0 can tail-call it.
    void sub_7100A52E60(ShopInfoTagData* data, u32 a2, s32 a3);
    // 0x7100a5233c / 0x7100a52358 (CSV unnamed): the two shop info animators.
    void sub_7100A5233C(u32 value);
    void sub_7100A52358(bool flag);
    // 0x7100a5237c (CSV unnamed): sets the shop info texture from `name` and stops the 0x3630 animator at
    // the matching end.
    void sub_7100A5237C(const sead::SafeString& name, bool a2, s32 a3);
    // 0x7100a524b0 (CSV unnamed): as sub_7100A5237C but for a PouchItem.
    void sub_7100A524B0(const PouchItem* item, bool a2);
    // 0x7100a52c88 (CSV unnamed): mode-based update of the two item elements and the T_Text_00 message.
    void sub_7100A52C88(s32 mode, s32 a2, u32 a3);
    // 0x7100a525c8 (CSV unnamed): shows `name` (or the equipped armor name) and stops the 0x3618 animator.
    void sub_7100A525C8(const sead::SafeString& name, bool a2);
    // 0x7100a527cc (CSV unnamed): shows a PouchItem (or its cooking info) in the shop info widgets.
    void sub_7100A527CC(PouchItem* item);
    // 0x7100a52a04 (CSV unnamed): shows the armor next-rank name of a PouchItem.
    void sub_7100A52A04(PouchItem* item, bool a2);
    /* 0x3610 */ eui::Animator* _3610 = nullptr;
    /* 0x3618 */ eui::Animator* _3618 = nullptr;
    // 0x7100a52db0 (CSV placeholder): resolved by the Animator::Stop slot-24 call (vtable-proven)
    // and the sibling screens' `eui::Animator* _3620` at the same offset.
    /* 0x3620 */ eui::Animator* _3620 = nullptr;
    /* 0x3628 */ eui::Animator* _3628 = nullptr;
    /* 0x3630 */ eui::Animator* _3630 = nullptr;
    /* 0x3638 */ Unk_710247ca18* _3638 = nullptr;
    /* 0x3640 */ Unk_710247d0c8* _3640 = nullptr;
    /* 0x3648 */ Unk_710247d0c8* _3648 = nullptr;
    // 0x7100a52db0 (CSV placeholder): the LetterAnimControl fed by sub_7100AA2E08 +
    // sub_7100BD9CDC / sub_7100BD9B5C (same tail as ScreenMessageDialog's 0x10b2b30).
    /* 0x3650 */ eui::LetterAnimControl* _3650 = nullptr;
    sead::PtrArray<ShopInfoItem> _3658;
    u8 _pad_3668[0x3678 - 0x3668];
    Unk_710247dc70 _3678;
    /* 0x3690 */ eui::LayoutEx* _3690 = nullptr;

    UiTexSlots _3698;
    // App-tag delegate (bound to sub_7100A51790 in the ctor; invoke 0x7100a534e8, clone 0x7100a5351c).
    // The second argument and u32 return are guesses from the 0xaa4b4c/0xaa4e70 handlers (buffer at
    // +8, size at +0x10; the handlers return a 32-bit value).
    /* 0x3768 */ sead::Delegate2R<ScreenShopInfo, const sead::MessageSet<char16>::TagInfo*,
                                  sead::WBufferedSafeString*, u32>
        _3768;
    // Tag-argument block (seen by the 0xaa4e60/0xaa5140 forwarders): a FixedSafeString<64> (its two
    // vtable stores are in the ctor) followed by the selector u32s the handlers compare. A plain
    // composition (not a derived struct, which would get its own vtable) with no mem-init (a `: _x()`
    // value-init emits a zeroing memset first).
    /* 0x3788 */ ShopInfoTagData _3788;
};

class ScreenAppAlbum : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppAlbum() override;
    SEAD_RTTI_OVERRIDE(ScreenAppAlbum, ScreenEx)
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual s32 m173();
    virtual void m174();
    virtual void m175();
    virtual void m176();
    virtual s32 m177();


    bool sub_71009D3DA0() const;
    bool sub_71009D3DC0() const;
    void m128() override;
    void m94() override;
    void m100() override;
    // 0x71009d5100 (CSV unnamed; not decompiled): called at the end of m94
    void sub_71009D5100();
    u8 _3610[0x3618 - 0x3610];
    /* 0x3618 */ nn::ui2d::Pane* _3618;
    /* 0x3620 */ nn::ui2d::Pane* _3620;
    u8 _3628[0x3630 - 0x3628];
    /* 0x3630 */ eui::Animator* _3630;
    /* 0x3638 */ ScreenAppPictureBookUnk* _3638;
    /* 0x3640 */ ScreenAppPictureBookUnk* _3640;
    u8 _pad_3648[0x3a9c - 0x3648];
    /* 0x3a9c */ s32 _3a9c;

};

class ScreenAppMapDungeon : public ScreenEx {
public:
    // 0x71009e70b8 (placeholder name; called by Unk_710247c010::sub_71009BE4E8): Unk_71025d69f0::sub_710094E064, then
    // closes this screen and the map screen
    void sub_71009E70B8();
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    bool sub_71009E0DF8() const;
    void m100() override;
    // 0x71009e4f88: closes the screen when the camera rune is used, the screen is closing while sub_7100AA8F50 holds,
    // the UI manager flags 0xa000 are both set or the remote bomb state bit is set
    void m130() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppMapDungeon() override;
    SEAD_RTTI_OVERRIDE(ScreenAppMapDungeon, ScreenEx)

    // state callbacks (slots 154-165, trivial ones defined in uiScreenLeafSlots.cpp)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();

    // 0x71009e62fc (placeholder name): whether the layer 1 camera looks along the current dungeon's direction
    // (the look vector of the camera target minus _3668)
    bool sub_71009E62FC() const;
    // 0x71009e65d4 (placeholder name): moves _3680 to look at its target along the layer 1 camera direction, keeping
    // its distance, and stores the resulting pitch and yaw
    void sub_71009E65D4();

    // Full ctor 9e00b0 and setup helper 9e2584; factory a81f34 allocates 0x11938 bytes.
    u8 _3610[0x3658 - 0x3610];
    /* 0x3658 */ f32 _3658;  // camera pitch
    /* 0x365c */ f32 _365c;  // camera yaw
    u8 _3660[0x3668 - 0x3660];
    /* 0x3668 */ sead::Vector3f _3668;
    u8 _3674[0x3680 - 0x3674];
    /* 0x3680 */ sead::LookAtCamera _3680;
    u8 _36e0[0x36e4 - 0x36e0];
    /* 0x36e4 */ bool _36e4;
    u8 _36e5[0x11518 - 0x36e5];
    /* 0x11518 */ ScreenAppMapUnk3c90* _11518;
    /* 0x11520 */ Unk_710247c010* mSensorChild;
    u8 _11528[0x11530 - 0x11528];
    // 11 parts layouts with four animators each (set up by 0x71009e1518)
    struct PartsEntry {
        eui::LayoutEx* layout;
        eui::Animator* animators[4];
        u8 _28[0x38 - 0x28];
    };
    /* 0x11530 */ sead::SafeArray<PartsEntry, 11> _11530;
    struct Entry11798 {
        u8 _0[0x18];
        /* 0x18 */ eui::Animator* animator;
    };
    // indexed by _117b0[getDungeonTableIndex()] + entry
    /* 0x11798 */ Entry11798** _11798;
    u8 _117a0[0x117b0 - 0x117a0];
    /* 0x117b0 */ sead::SafeArray<s32, 6> _117b0;
    u8 _117c8[0x11818 - 0x117c8];
    struct Entry11818 {
        eui::Animator* animator;
        u8 _8[0x30 - 0x8];
    };
    /* 0x11818 */ sead::SafeArray<Entry11818, 3> _11818;
    u8 _118a8[0x118ac - 0x118a8];
    /* 0x118ac */ s32 _118ac;  // selected entry (-1: none)
    u8 _118b0[0x118d0 - 0x118b0];
    /* 0x118d0 */ s32 _118d0;  // last selected entry
    u8 _118d4[0x11918 - 0x118d4];
    /* 0x11918 */ eui::Animator* _11918;
    u8 _11920[0x11938 - 0x11920];

    // 0x71009e5868 (placeholder name): selects entry `index` (-1: none), playing its animators backwards / forwards
    void sub_71009E5868(s32 index);
    // 0x71009e2584 (placeholder name): looks up the two screen children (group 1 and group 0)
    void sub_71009E2584();
    // 0x71009e0c28 / 0x71009e0d14 (placeholder names): false while the sensor child is opening or closing or the
    // system window is open; then _36e4 / true
    bool sub_71009E0C28();
    bool sub_71009E0D14();
    // 0x71009e5ca8 (placeholder name): like sub_71009E5868, also resetting the other entries and playing the
    // per-dungeon animators of _11798
    void sub_71009E5CA8(s32 index);
};
static_assert(sizeof(ScreenAppMapDungeon) == 0x11938);

class ScreenPickUp : public ScreenEx {
public:
    ScreenPickUp();
    ~ScreenPickUp() override;
    SEAD_RTTI_OVERRIDE(ScreenPickUp, ScreenEx)

    // 0x7100a3f3f4 (CSV ScreenPickUp::setItemAndOpen): opens the screen (option 3); with `show` it also shows the item
    // for 5 seconds (the argument type is a guess)
    void setItemAndOpen(const sead::SafeString& item, bool show);
    // 0x7100a3f450: shows `item` in the oldest free window for `time` seconds; the other shown windows move one
    // place down (mOrder)
    void sub_7100A3F450(const sead::SafeString& item, f32 time);

    const char* getLayoutName_() const override;
    void m80(bool visible) override;
    void m83() override;
    void m86() override;
    void m91() override;
    void m93(sead::Heap* heap) override;
    void m94() override;

    // One pickup window (0xe8 bytes; the layout pane is Pa_PickUpWin_00 .. 06). Its resources are requested by
    // the name "uiPickUpWin_00Screen".
    struct PickUpWin {
        PickUpWin() {}
        ~PickUpWin() { delete mResHandle; }

        // 0x7100a3fab4
        void init(sead::Heap* heap);
        // 0x7100a3f5ac
        void setItem(const sead::SafeString& item);
        // 0x7100a3fd44
        void update();
        // 0x7100a40224
        void close();
        // 0x7100a40360
        void applyTexture();
        // 0x7100a40470: compares the item with the equipped one (frame 0 - 3 of the Color animation)
        void updateCompareAnim();
        // 0x7100a4055c
        void requestTexture(const sead::SafeString& path);

        /* 0x00 */ UiTimer mTimer;
        /* 0x18 */ sead::FixedSafeString<64> mName;
        /* 0x70 */ PouchItemType mType = PouchItemType::Invalid;
        /* 0x78 */ ScreenPickUp* mScreen = nullptr;
        /* 0x80 */ eui::LayoutEx* mLayout = nullptr;
        /* 0x88 */ eui::Animator* mColorAnim = nullptr;
        /* 0x90 */ eui::Animator* mGuideOutAnim = nullptr;
        /* 0x98 */ eui::Animator* mGuideOffAnim = nullptr;
        /* 0xa0 */ eui::Animator* mFlashAnim = nullptr;
        /* 0xa8 */ ksys::res::Handle* mResHandle = nullptr;
        /* 0xb0 */ nn::ui2d::ExternalTextureInfo mTexInfo;
        /* 0xc8 */ nn::util::Float3 mPos{};
        /* 0xd4 */ nn::util::Float3 mBasePos{};
        /* 0xe0 */ bool mInPlace = false;
        /* 0xe1 */ bool mWasInPlace = false;
        /* 0xe2 */ bool mArrived = false;
        /* 0xe3 */ bool mFadedOut = false;
        /* 0xe4 */ bool mTextureRequested = false;
        /* 0xe5 */ s8 mOrder = -1;  // -1: free
        /* 0xe6 */ bool mClosing = false;
    };
    static_assert(sizeof(PickUpWin) == 0xe8);

    /* 0x3610 */ sead::CriticalSection mCS;
    /* 0x3650 */ sead::FixedObjArray<PickUpWin, 7> mWins;
};

class ScreenAppHome : public ScreenEx {
public:
    void doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) override;
    ScreenAppHome();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppHome() override;
    SEAD_RTTI_OVERRIDE(ScreenAppHome, ScreenEx)
    // 0x71009de0f0: shows the Skip screen and runs UiSubsys1::sub_7100966A74 when UiSubsys1::returnTrue
    void m101() override;

    // 0x3610 .. 0x3660 is zeroed by one memset in the constructor; the pointer at 0x3640 is an animator
    // (0x71009dd81c reads its finished flag).
    struct Unk3610 {
        u8 _0[0x30];
        eui::Animator* _30;
        u8 _38[0x50 - 0x38];
    };
    /* 0x3610 */ Unk3610 _3610 = {};
    u64 _3660[0x30 / 8];
    u64 _3690[2] = {};
    /* 0x36a0 */ Unk_7102474bc8 _36a0;
    /* 0x37f8 */ sead::PtrArrayImpl _37f8;  // freed by the destructor (0x71009dc3ec)
    /* 0x3808 */ u32 _3808 = 0;
    /* 0x380c */ u32 _380c = 4;
    /* 0x3810 */ u8 _3810 = 0;
    /* 0x3811 */ u8 _3811 = 0;
    u8 _3812[0x3818 - 0x3812];
    /* 0x3818 */ Unk_7102474df8 _3818;
    /* 0x38a0 */ Unk_7102474dd0 _38a0[4];

    // 0x71009de1c8 / 0x71009dcf18 (CSV unnamed; the second is declared only)
    void sub_71009DE1C8();
    void sub_71009DCF18(s32 a1);
    // 0x71009dc99c (placeholder name): reads the page at 0x380c and tail-calls sub_71009DCF18 with the page's
    // replacement value. The bool argument is unused in the body.
    void sub_71009DC99C(bool a1);
    // 0x71009dd7a8 / 0x71009dd7ec / 0x71009dd800 (placeholder names): switch the page (12 keeping _3808 / 8 or 9 / 10 or 11)
    void sub_71009DD7A8();
    void sub_71009DD7D4();
    void sub_71009DD7DC();
    void sub_71009DD7E4();
    void sub_71009DD814();
    void sub_71009DD7EC(bool a1);
    void sub_71009DD800(bool a1);
    // 0x71009dd81c (placeholder name): the finished flag of the animator at 0x3640
    bool sub_71009DD81C() const;
    // 0x71009ddfb8 (slot 99): when the byte at 0x3811 is set, calls ui::sub_7100AA86EC(1, false)
    void m99() override;
    // 0x71009dc77c (placeholder name): stores `value` in the third word (+0x10) of the Unk_7102474dd0 `index` (0-3)
    void sub_71009DC77C(s32 index, Unk_PaneTransform* value);
    // 0x71009dd838 (placeholder name): forwards the float to the _3818 Unk_7102474df8 check
    bool sub_71009DD838(f32 a1) const;
};

extern const ksys::StateBase sUnk_71025dc3c0;

// The state ScreenSaveTransferWindow changes to from many of its state callbacks (0x71025f2de0; placeholder name).
extern const ksys::StateBase sUnk_71025f2de0;
// The save transfer's other states (sub_7100A4473C).
extern const ksys::StateBase sUnk_71025f26c0;
extern const ksys::StateBase sUnk_71025f2840;
extern const ksys::StateBase sUnk_71025f2900;
extern const ksys::StateBase sUnk_71025f2cc0;
// The save transfer's static state block (0x71025f2eb0): the transfer state at +0xc and its mode at +0x10.
struct Unk_71025f2eb0 {
    u8 _0[0xc];
    /* 0xc */ s32 _c;
    /* 0x10 */ s32 _10;
};
extern Unk_71025f2eb0 sUnk_71025f2eb0;
extern const ksys::StateBase sUnk_71025f1fa0;
extern const ksys::StateBase sUnk_71025f2000;
extern const ksys::StateBase sUnk_71025f2240;
extern const ksys::StateBase sUnk_71025f23c0;
extern const ksys::StateBase sUnk_71025f2480;
extern const ksys::StateBase sUnk_71025f2d20;
extern const ksys::StateBase sUnk_71025f2d80;
// More states of ScreenSaveTransferWindow (placeholder names; the 0x60 spaced StateBase objects 0x71025f2180 ..
// 0x71025f2c60, found from the GOT loads in its state callbacks).
extern const ksys::StateBase sUnk_71025f2180;
extern const ksys::StateBase sUnk_71025f21e0;
extern const ksys::StateBase sUnk_71025f2300;
extern const ksys::StateBase sUnk_71025f2360;
extern const ksys::StateBase sUnk_71025f2540;
extern const ksys::StateBase sUnk_71025f25a0;
extern const ksys::StateBase sUnk_71025f2720;
// Constructed by the SaveTransfer state initializer at a471bc (four member callbacks).
extern const ksys::StateBase sUnk_71025f2780;
extern const ksys::StateBase sUnk_71025f2960;
extern const ksys::StateBase sUnk_71025f2b40;
extern const ksys::StateBase sUnk_71025f2c60;

class ScreenSaveTransferWindow : public ScreenEx {
public:
    void m98() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenSaveTransferWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenSaveTransferWindow, ScreenEx)
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual s32 m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual s32 m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual s32 m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual s32 m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual s32 m173();
    virtual void m174();
    virtual void m175();
    virtual void m176();
    virtual s32 m177();
    virtual void m178();
    virtual void m179();
    virtual void m180();
    virtual s32 m181();
    virtual void m182();
    virtual void m183();
    virtual void m184();
    virtual s32 m185();

    // 0x7100a45fc0 (placeholder name): starts state 6 through the save system singleton.
    bool sub_7100A45FC0();
    // 0x7100a45da0 / 0x7100a46124 / 0x7100a46268 (placeholder names): the m158 pattern with _3668 set to 0 / 1 / 4
    void sub_7100A45DA0();
    void sub_7100A46124();
    void sub_7100A46268();
    void sub_7100A46004();
    // 0x7100a45fd0 (placeholder name): leaves the window's state when the save system is not in state 7
    void sub_7100A45FD0();
    void sub_7100A44544();
    void sub_7100A44458();
    void sub_7100A44878();
    // 0x7100a4473c (declared only; 240 bytes): the save transfer's per-frame step, tail-called by m223
    void sub_7100A4473C();
    void sub_7100A45080();
    // NetworkCalcThread's Delegate2 callback (a44a34); its arguments are unused.
    void sub_7100A44B80(sead::Thread* thread, s64 message);
    /* 0x3610 */ eui::Animator* _3610;
    /* 0x3618 */ eui::Animator* _3618;
    /* 0x3620 */ eui::Animator* _3620;
    u8 _pad_3628[0x3630 - 0x3628];
    /* 0x3630 */ eui::AnimButton* _3630;
    /* 0x3638 */ eui::AnimButton* _3638;
    /* 0x3640 */ eui::AnimButton* _3640;
    u8 _pad_3648[0x3668 - 0x3648];
    /* 0x3668 */ s32 _3668;
    s32 _366c;
    /* 0x3670 */ const ksys::StateBase* _3670;
    // Bits set by the state callbacks (0x7100a432fc, 0x7100a43ac0, 0x7100a45e40, 0x7100a46234): the bit index goes
    // through a 4-byte enum class, so the original spills it to the stack (same form as Horse / PriestBoss flags).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)
    /* 0x3678 */ u8 _3678;
    u8 _3679;
    u8 _367a;
    u8 _pad_367b[0x3760 - 0x367b];
    /* 0x3760 */ s32 _3760;
    u8 _pad_3764[0x3788 - 0x3764];
    /* 0x3788 */ sead::SafeString _3788;
    /* 0x3798 */ f32 _3798;
    /* 0x379c */ s32 _379c;
    /* 0x37a0 */ s32 _37a0;
    virtual void m186();
    virtual void m187();
    virtual void m188();
    virtual s32 m189();
    virtual void m190();
    virtual void m191();
    virtual void m192();
    virtual s32 m193();
    virtual void m194();
    virtual void m195();
    virtual void m196();
    virtual s32 m197();
    virtual void m198();
    virtual void m199();
    virtual void m200();
    virtual s32 m201();
    virtual void m202();
    virtual void m203();
    virtual void m204();
    virtual s32 m205();
    virtual void m206();
    virtual void m207();
    virtual void m208();
    virtual s32 m209();
    virtual void m210();
    virtual void m211();
    virtual void m212();
    virtual s32 m213();
    virtual void m214();
    virtual void m215();
    virtual void m216();
    virtual s32 m217();
    virtual void m218();
    virtual void m219();
    virtual void m220();
    virtual s32 m221();
    virtual void m222();
    virtual void m223();
    virtual void m224();
    virtual s32 m225();
    virtual void m226();
    virtual void m227();
    virtual void m228();
    virtual s32 m229();
    virtual void m230();
    virtual void m231();
    virtual void m232();
    virtual s32 m233();
    virtual void m234();
    virtual void m235();
    virtual void m236();
    virtual s32 m237();
    virtual void m238();
    virtual void m239();
    virtual void m240();
    virtual s32 m241();
    virtual void m242();
    virtual void m243();
    virtual void m244();
    virtual s32 m245();
    virtual void m246();
    virtual void m247();
    virtual void m248();
    virtual s32 m249();
    virtual void m250();
    virtual void m251();
    virtual void m252();
    virtual s32 m253();
    virtual void m254();
    virtual void m255();
    virtual void m256();
    virtual s32 m257();
    virtual void m258();
    virtual void m259();
    virtual void m260();
    virtual s32 m261();
    virtual void m262();
    virtual void m263();
    virtual void m264();
    virtual s32 m265();
    virtual void m266();
    virtual void m267();
    virtual void m268();
    virtual s32 m269();
    virtual void m270();
    virtual void m271();
    virtual void m272();
    virtual s32 m273();
    virtual void m274();
    virtual void m275();
    virtual void m276();
    virtual s32 m277();
    virtual void m278();
    virtual void m279();
    virtual void m280();
    virtual s32 m281();
    virtual void m282();
    virtual void m283();
    virtual void m284();
    virtual s32 m285();
    virtual void m286();
    virtual void m287();
    virtual void m288();
    virtual s32 m289();
    virtual void m290();
    virtual void m291();
    virtual void m292();
    virtual s32 m293();
    virtual void m294();
    virtual void m295();
    virtual void m296();
    virtual s32 m297();
    virtual void m298();
    virtual void m299();
    virtual void m300();
    virtual s32 m301();
    virtual void m302();
    virtual void m303();
    virtual void m304();
    virtual s32 m305();
    virtual void m306();
    virtual void m307();
    virtual void m308();
    virtual s32 m309();
    virtual void m310();
    virtual void m311();
    virtual void m312();
    virtual s32 m313();
    virtual void m314();
    virtual void m315();
    virtual void m316();
    virtual s32 m317();

    // 0x7100a428d0 (CSV unnamed, 2.5 KB; declared only): the first-time setup of the animators
    void sub_7100A428D0();
};

class ScreenOptionWindow : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    bool isEnableControl() const override;
    ~ScreenOptionWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenOptionWindow, ScreenEx)
    const char* getLayoutName_() const override;

    // 0x7100a28c20
    ScreenOptionWindow();
    // 0x7100a28cd0 (placeholder name; the _36c8 callback): sets bit 1 of _36e8
    void sub_7100A28CD0();

    // The option values read from the game data flags (0x1c bytes; m93 allocates one at _36c0, m100 builds one on the
    // stack to compare).
    struct Settings {
        // 0x7100a2abb8
        Settings();

        bool balloonText;
        bool cameraUpDownReverse;
        bool cameraRLReverse;
        bool jumpButtonChange;
        bool gyro;
        bool textRuby;
        bool miniMapDirection;
        s32 stickSensitivity;
        s32 mainScreen;
        bool amiiboItem;
        s32 textWindowChange;
        s32 voiceLanguage;
    };
    static_assert(sizeof(Settings) == 0x1c);

    // 0x7100a2ac88: saves (SaveSystem::sub_71009145F8) when the flags differ from the copy taken by m93
    void m100() override;

    /* 0x3610 */ Unk_7102474df8 _3610;
    /* 0x3698 */ sead::PtrArray<Unk_OptionWindowEntry> _3698;
    /* 0x36a8 */ s32 _36a8 = 3;
    /* 0x36b0 */ u64 _36b0 = 0;
    /* 0x36b8 */ s32 _36b8 = 99;
    /* 0x36bc */ bool _36bc = false;
    /* 0x36bd */ bool _36bd = false;
    /* 0x36be */ bool _36be = false;
    /* 0x36c0 */ Settings* _36c0 = nullptr;
    /* 0x36c8 */ sead::Delegate<ScreenOptionWindow> _36c8;
    /* 0x36e8 */ sead::Atomic<u32> _36e8 = 0;
};

// 0x710249ad74 (placeholder name; a mode of the system window: 1 / 2 close the window without saving)
extern s32 sUnk_710249ad74;
// 0x710249ad68 / 0x710249ad6c / 0x710249ad70 / 0x71025f5740 / 0x71025f5741 (placeholder names): more of the
// system window's global state (reset by ScreenSystemWindow01::sub_7100A6670C)
extern s32 sUnk_710249ad68;
extern s32 sUnk_710249ad6c;
extern s32 sUnk_710249ad70;
extern bool sUnk_71025f5740;
extern bool sUnk_71025f5741;

// Native ctor 9cb0c8 and D1 9cbcc0 establish this non-polymorphic 0x2e8-byte controller.
// Queue count/state are also initialized by inner ctor 9cc648 and consumed by 9cc3a0 / 9cc970.
class Unk_71009cb0c8 {
public:
    Unk_71009cb0c8();
    ~Unk_71009cb0c8();
    void sub_71009CC3A0();
    void sub_71009CC970();
    bool sub_71009CBFA4() const;
    bool sub_71009CBEAC() const;
    void sub_71009CBE38();
    // Returns one of the resource's two texture records under the controller lock.
    nn::ui2d::TextureInfo* sub_71009CBECC();
    void sub_71009CBD48(sead::Heap* heap, eui::LayoutEx* layout, const sead::SafeString& name);
    void sub_71009CBDE8(eui::LayoutEx* layout, const sead::SafeString& name);
    // 0x71009cbfc4: queue a texture load using the existing resource context.
    void sub_71009CBFC4(const ::Unk_710247e960& request);

    bool sub_71009CB188(void* user_data);
    void sub_71009CB804(ksys::TaskPostRunResult* result, const ksys::TaskPostRunContext& context);
    void sub_71009CBC64(const ksys::TaskRemoveCallbackContext& context);

    /* 0x0 */ u32 mLastFrame = 0;
    /* 0x4 */ u32 mRetryCount;
    /* 0x8 */ bool mApplied = false;
    u8 _9[7];
    /* 0x10 */ ksys::res::Handle* mTextureHandle = nullptr;
    /* 0x18 */ nn::ui2d::Material* mMaterial = nullptr;
    /* 0x20 */ nn::ui2d::ExternalTextureInfo mTexInfo;
    /* 0x38 */ eui::Animator* mAnimator = nullptr;
    /* 0x40 */ sead::CriticalSection mCS;
    /* 0x080 */ ::Unk_710247e990 mLoader;
    /* 0x288 */ ksys::TaskDelegateT<Unk_71009cb0c8> mTaskDelegate;
    /* 0x2a8 */ ksys::TaskPostRunCallbackT<Unk_71009cb0c8> mPostRunCallback;
    /* 0x2c8 */ ksys::TaskRemoveCallbackT<Unk_71009cb0c8> mRemoveCallback;
};
static_assert(sizeof(Unk_71009cb0c8) == 0x2e8);

class ScreenSystemWindow01 : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m96() override;
    void m97() override;
    void m101() override;
    bool isEnableControl() const override;
    ~ScreenSystemWindow01() override;
    SEAD_RTTI_OVERRIDE(ScreenSystemWindow01, ScreenEx)

    void m100() override;
    void m102(eui::AnimButton* button) override;
    // 0x7100a66824 (placeholder name): whether the window shows the E3-only state
    bool sub_7100A66824() const;
    // 0x7100a6637c
    void m128() override;
    void m129() override;

    // 0x7100a67704
    void m89() override;
    // 0x7100a68010
    void m98() override;
    // 0x7100a680a8
    void m99() override;
    // 0x7100a6670c (placeholder name): resets the window's global state
    static void sub_7100A6670C();
    // 0x7100a66760 (placeholder name): the save window result (-1: none; 0 in the E3 demo outside the RID demo)
    static s32 sub_7100A66760();
    // 0x7100a667ec (placeholder name): sUnk_710249ad70 (0 in the E3 demo outside the RID demo)
    static s32 sub_7100A667EC();
    // 0x7100a684cc (CSV unnamed): fills the save-slot date and place texts for `slot_index`.
    void sub_7100A684CC(s32 slot_index);
    // 0x7100a66c3c (CSV unnamed): stops the window's animators at their start.
    void sub_7100A66C3C();
    // 0x7100a66d00 (CSV unnamed): clears flag 10 of the window's buttons.
    void sub_7100A66D00();
    // 0x7100a67068 (CSV unnamed): when the 0x3690 animator ends, releases the cursor and
    // downs the 0x60 button off.
    void sub_7100A67068();

    // Members from the ctor 0x7100a65ff0 and D1 0x7100a66208.
    /* 0x3610 */ eui::ButtonBase* _3610{};
    /* 0x3618 */ eui::ButtonBase* _3618{};
    /* 0x3620 */ eui::ButtonBase* _3620{};
    /* 0x3628 */ eui::ButtonBase* _3628{};
    /* 0x3630 */ eui::ButtonBase* _3630{};
    /* 0x3638 */ eui::ButtonBase* _3638{};
    /* 0x3640 */ eui::ButtonBase* _3640{};
    /* 0x3648 */ eui::ButtonBase* _3648{};
    u8 _pad_3650[0x3680 - 0x3650];
    // 0x7100a684cc passes this to setWidgetString; 0x3688 is the second layout used by m106.
    /* 0x3680 */ eui::LayoutEx* _3680{};
    u8 _pad_3688[0x3690 - 0x3688];
    /* 0x3690 */ eui::Animator* _3690{};
    // Animators stopped by 0x7100a684cc (slots 24 / 26 of eui::Animator).
    /* 0x3698 */ eui::Animator* _3698{};
    /* 0x36a0 */ eui::Animator* _36a0{};
    /* 0x36a8 */ eui::Animator* _36a8{};
    /* 0x36b0 */ eui::Animator* _36b0{};
    /* 0x36b8 */ eui::Animator* _36b8{};
    u8 _pad_36c0[0x3720 - 0x36c0];
    /* 0x3720 */ eui::Animator* _3720{};
    u8 _pad_3728[0x3730 - 0x3728];
    /* 0x3730 */ nn::ui2d::ExternalTextureInfo _3730;
    /* 0x3748 */ Unk_71009cb0c8 _3748[6];
    /* 0x48b8 */ agl::TextureData _48b8;
    /* 0x49e0 */ sead::SafeArray<Unk_7102474dd0, 6> _49e0;
    /* 0x4ad0 */ Unk_7102474df8 _4ad0;
    u8 _pad_4b58[0x4b5c - 0x4b58];
    /* 0x4b5c */ bool _4b5c;
    u8 _pad_4b5d[0x4b60 - 0x4b5d];
    /* 0x4b60 */ bool _4b60;
    /* 0x4b61 */ bool _4b61;
    /* 0x4b62 */ bool _4b62;
    /* 0x4b64 */ UiTimer _4b64;
    /* 0x4b7c */ UiTimer _4b7c;
    // 0x7100a6641c (CSV unnamed; not decompiled)
    bool sub_7100A6641C();
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();

};

class ScreenPauseMenuRecipe : public ScreenEx {
public:
    // 0x7100a327b0 (CSV unnamed, declared only): fills the recipe list from the argument
    void sub_7100A327B0(void* arg);
public:
    ScreenPauseMenuRecipe();
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    ~ScreenPauseMenuRecipe() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuRecipe, ScreenEx)

    /* 0x3610 */ u8 _3610[0x85]{};
    u8 _3695[3];
    ksys::res::Handle* _3698{};
    ksys::res::Handle* _36a0{};
    ksys::res::Handle* _36a8{};
    ksys::res::Handle* _36b0{};
    ksys::res::Handle* _36b8{};

    // 0x7100a32d98 (slot 101): unloads the requested resources
    void m101() override;
};

// 0x71025f5450: credit-entry range. EventPlayUiStaffRoll writes it just before the staff roll
// screen opens; the ScreenStaffRoll entry builder reads it. The original zero-initialises it from
// the ScreenStaffRoll TU's static initialiser to {0, 9999, 1, 1}.
struct Unk_71025f5450 {
    s32 _0;
    s32 _4;
    bool _8;
    bool _9;
};
extern Unk_71025f5450 sUnk_71025f5450;

class ScreenStaffRoll : public ScreenEx {
public:
    // 0x7100a5d890 (CSV ScreenStaffRoll::ctor); members as in ScreenStaffRollDLC without its 0x38 bytes at 0x36c4
    ScreenStaffRoll();
    ~ScreenStaffRoll() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRoll, ScreenEx)
    // 0x7100a5e0b8 / 0x7100a5e1b0: as Screen::m73 / m76 but open(1) / close(-1)
    void m73(f32 value) override;
    void m76() override;
    // 0x7100a5e58c
    void m101() override;
    // EventPlayUiStaffRollImage supplies event duration and the image range, then elapsed time.
    void sub_7100A5E1C4(f32 duration, s32 start, s32 end);
    void sub_7100A5E42C(f32 time);
    // 0x7100a5dce8: the implementation sub_7100A5E42C tail-calls (declaration only).
    void sub_7100A5DCE8(f32 time);

    /* 0x3610 */ u32 _3610 = 0;
    /* 0x3614 */ u32 _3614 = 0;
    /* 0x3618 */ f32 _3618 = 1.0f;
    u8 _361c[0x3620 - 0x361c];
    // 0x3670 is a pointer array the destructor empties (deleting each entry)
    u64 _3620[0x60 / 8] = {};
    /* 0x3680 */ sead::Vector2f _3680 = sead::Vector2f::zero;
    /* 0x3688 */ sead::Vector2f _3688 = sead::Vector2f::zero;
    /* 0x3690 */ sead::BoundBox2f _3690;
    /* 0x36a0 */ u64 _36a0;
    /* 0x36a8 */ u64 _36a8;
    /* 0x36b0 */ u64 _36b0;
    /* 0x36b8 */ u64 _36b8;
    /* 0x36c0 */ f32 _36c0 = -1.0f;
    u32 _36c4[0x1c / 4] = {};
    /* 0x36e0 */ u64 _36e0 = 0x439600003F800000;  // two f32 {1.0f, 300.0f} in memory order
    /* 0x36e8 */ u32 _36e8 = 0;
    /* 0x36f0 */ UiTexSlots _36f0;
    /* 0x37c0 */ sead::PtrArrayImpl _37c0;
    /* 0x37d0 */ void* _37d0[2];
    u8 _37e0[0x38a0 - 0x37e0];
    /* 0x38a0 */ u64 _38a0;
    /* 0x38a8 */ u64 _38a8;
    /* 0x38b0 */ u64 _38b0;
    /* 0x38b8 */ u32 _38b8;
    /* 0x38bc */ s32 _38bc;
    /* 0x38c0 */ f32 _38c0;
    /* 0x38c4 */ u8 _38c4;
};

class ScreenStaffRollDLC : public ScreenEx {
public:
    ScreenStaffRollDLC();
    bool isEnableControl() const override;
    ~ScreenStaffRollDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRollDLC, ScreenEx)
    // 0x7100a58c5c / 0x7100a58cc8: as ScreenStaffRoll::m73 / m76
    void m73(f32 value) override;
    void m76() override;
    // 0x7100a58c70: updates the roll, then closes the screen once `progress` passes _270
    void m74(f32 progress) override;
    // 0x7100a58508 (CSV unnamed; not decompiled)
    void sub_7100A58508(f32 progress, f32 end);

    /* 0x3610 */ u32 _3610 = 0;
    /* 0x3614 */ u32 _3614 = 0;
    /* 0x3618 */ f32 _3618 = 1.0f;
    u8 _361c[0x3620 - 0x361c];
    u64 _3620[0x60 / 8] = {};
    /* 0x3680 */ sead::Vector2f _3680 = sead::Vector2f::zero;
    /* 0x3688 */ sead::Vector2f _3688 = sead::Vector2f::zero;
    /* 0x3690 */ sead::BoundBox2f _3690;
    /* 0x36a0 */ u64 _36a0;
    /* 0x36a8 */ u64 _36a8;
    /* 0x36b0 */ u64 _36b0;
    /* 0x36b8 */ u64 _36b8;
    /* 0x36c0 */ f32 _36c0 = -1.0f;
    u32 _36c4[0x54 / 4] = {};
    /* 0x3718 */ u64 _3718 = 0x439600003F800000;  // two f32 {1.0f, 300.0f} in memory order
    /* 0x3720 */ u32 _3720 = 0;
    /* 0x3728 */ UiTexSlots _3728;
    /* 0x37f8 */ sead::PtrArrayImpl _37f8;
    /* 0x3808 */ void* _3808[2];
    u8 _3818[0x38d8 - 0x3818];
    /* 0x38d8 */ u64 _38d8;
    /* 0x38e0 */ u64 _38e0;
    /* 0x38e8 */ u64 _38e8;
    /* 0x38f0 */ u32 _38f0;
    /* 0x38f4 */ s32 _38f4;
    /* 0x38f8 */ f32 _38f8;
    /* 0x38fc */ u8 _38fc;
    u8 _38fd[0x3900 - 0x38fd];
    /* 0x3900 */ u32 _3900;
    /* 0x3904 */ f32 _3904;
    /* 0x3908 */ u32 _3908;
};

class ScreenKeyBoradTextArea : public ScreenEx {
public:
    ScreenKeyBoradTextArea();
    // 0x7100a0e528: lets the software keyboard go (Root4 flag _2 back on, record 5)
    void close(s32 option) override;
    // 0x7100a0e5bc / 0x7100a0e5dc: overrides of Screen::m98 / m101; set a Root1 flag (index 0) to 1 / 2
    void m98() override;
    void m101() override;
    const char* getLayoutName_() const override;
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    void m93(sead::Heap*) override;
    void m94() override;
    void m96() override;
    void m97() override;
    ~ScreenKeyBoradTextArea() override;
    SEAD_RTTI_OVERRIDE(ScreenKeyBoradTextArea, ScreenEx)

    /* 0x3610 */ s32 _3610 = 2;
    s32 _3614;
    // 0x7100a0e44c (own slot 154): stores the keyboard type, clears T_Answer_00, shows the software keyboard and opens
    // the screen
    virtual void m154(s32 type, bool clear_input);

};

class ScreenFadeStatus : public ScreenEx {
public:
    ScreenFadeStatus();
    bool isPlayPartsInOut_() const override;
    ~ScreenFadeStatus() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeStatus, ScreenEx)
    const char* getLayoutName_() const override;

    /* 0x3610 */ u64 _3610 = 0;
    /* 0x3618 */ u64 _3618 = 0;
    /* 0x3620 */ sead::FixedPtrArray<u8*, 4> _3620;
    /* 0x3650 */ u64 _3650 = 0;
    /* 0x3658 */ sead::Buffer<u8*> _3658;
    /* 0x3668 */ sead::Buffer<u8*> _3668;
};

// Placeholder-named UI facade helpers (declared only unless noted; names after the original addresses).
// 0x7100a98038 (defined in uiScreenFacade.cpp)
bool sub_7100A98038(s32 excluded_id);
// 0x7100a25d7c (placeholder name): the "guide point" flag of kind 0 (challenge points) or 1 (visit marks); true otherwise.
bool sub_7100A25D7C(s32 kind);
// 0x7100a9b278 (defined in uiMiscFacade.cpp)
bool sub_7100A9B278();
// 0x7100aa8f70: `isActiveEventDemo000Or001Or002()` (a 4-byte jump in the original: its own function)
bool sub_7100AA8F70();
// 0x7100aa92ac: the step of the counter roll from `current` to `target` (signed, 1 / 20 / 50 / 500 / 1000 by distance)
s32 sub_7100AA92AC(s32 current, s32 target);
// 0x7100aa930c: sets the digits of the number text pane `pane_name` of `layout` (the roll randomises the low digits)
void sub_7100AA930C(eui::LayoutEx* layout, const sead::SafeString& pane_name, s32 value, s32 prev, s32 delta);

// 0x7100aa948c (declared only)
bool sub_7100AA948C();
// 0x7100a9a9f4 (uiScreenFacade.cpp): whether the UI is in the state that allows the pause menu
bool sub_7100A9A9F4();
// 0x7100a1b9d0 (placeholder name; ScreenMainScreen TU): opens the DLC energy meter while the Master Cycle is out
// (unless the pause menu info screen exists) and closes it otherwise
void sub_7100A1B9D0();

// 0x7100aa0dc0 / 0x7100aa1260 (declared only): resolve a slash separated pane path inside a layout
nn::ui2d::Pane* sub_7100AA0DC0(eui::LayoutEx* layout, const sead::SafeString& path, nn::ui2d::Pane** parent);
void* sub_7100AA1260(eui::LayoutEx* layout, const sead::SafeString& path, void* out);

// 0x7100a64304 (declared only): takes the pending result of a system window (and resets it to 13)
s32 sub_7100A64304();

// 0x7100aa1cb8 (declared only): sets the alpha byte of a material's color
void sub_7100AA1CB8(nn::ui2d::Material* material, u8 alpha);

// 0x7100949d18 (declared only): the heart gauge value of `count` quarter hearts
s32 sub_7100949CE8(u32 count);
f32 sub_7100949D18(s32 count);

// 0x7100aa8784 (declared only)
void sub_7100AA8784();

// 0x7100a9760c / 0x7100a9732c / 0x7100a97198 / 0x7100a96eb8 / 0x7100a97ddc / 0x7100a97860 (declared only): the
// message-get facade (reward text pages)
bool sub_7100A9760C();
void sub_7100A9732C();
bool sub_7100A97198();
void sub_7100A96EB8();
bool sub_7100A97DDC(s32 index);
void sub_7100A97860(s32 index);

// Iterator over one of the new-picture name lists. The original compares only the indices.
struct PictureBookNameIterator {
    PictureBookNameIterator(sead::FixedSafeString<64>* buffer, s32 index)
        : mBuffer(buffer), mIndex(index) {}
    bool operator!=(const PictureBookNameIterator& rhs) const { return mIndex != rhs.mIndex; }
    PictureBookNameIterator& operator++() {
        ++mIndex;
        return *this;
    }
    sead::SafeString& operator*() const { return mBuffer[mIndex]; }
    sead::FixedSafeString<64>* operator->() const { return &mBuffer[mIndex]; }

    sead::FixedSafeString<64>* mBuffer;
    s32 mIndex;
};

// 0x71009f8474 / 0x71009f8484: begin / end of the new enemy picture names (category 2, at most 16)
PictureBookNameIterator newEnemyPictureBookNamesBegin();
PictureBookNameIterator newEnemyPictureBookNamesEnd();
// 0x71009f84a8 / 0x71009f84b8: begin / end of the new boss picture names (category 6, at most 16)
PictureBookNameIterator newBossPictureBookNamesBegin();
PictureBookNameIterator newBossPictureBookNamesEnd();
// 0x71009f84dc / 0x71009f84ec: begin / end of the new weapon picture names (category 4, at most 2)
PictureBookNameIterator newWeaponPictureBookNamesBegin();
PictureBookNameIterator newWeaponPictureBookNamesEnd();
// 0x71009f8464: the two starting weapon pictures (bow / sword), used by the weapon vacancy check
const sead::SafeString* getInitialWeaponPictureBookNames();

}  // namespace uking::ui

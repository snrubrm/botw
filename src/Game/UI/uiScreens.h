#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <math/seadBoundBox.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <math/seadVector.h>
#include <gfx/seadProjection.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiControlBase.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiTimer.h"
#include "KingSystem/System/DebugBoard.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiUIController.h"
#include "Game/UI/uiButtonEventQueue.h"
#include "Game/UI/uiArchiveHandle.h"
#include "Game/UI/uiShopItemElement.h"
#include "Game/UI/uiTexSlots.h"
#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Utils/StateMachine.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace ksys {
class SeadController;
}

namespace ksys::act {
class Actor;
}

namespace ksys::res {
class Handle;
}

namespace uking {
// 0x71025cb0eb (defined in gameScene.cpp)
extern bool sForceEnableGlidingSurfingRupee;
}  // namespace uking

namespace uking::ui {

class TagProcessor;

// The game's UI screen classes (CSV: ScreenBase / Screen / ScreenEx / Screen<Name>, IDA placeholder
// names; the namespace is a guess). The chain eui::Screen <- ScreenBase <- Screen <- ScreenEx <-
// Screen<Name> is established by the RTTI (the leaf classes' checkDerivedRuntimeTypeInfo compares
// against four typeinfo statics and their Derive<> typeinfo is Derive<ScreenEx>). The layouts are
// not modelled yet: only what the facade functions in uiScreenFacade.cpp use is declared.

class ScreenBase : public eui::Screen {
public:
    ScreenBase();
    ~ScreenBase() override;
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
    // 0x71010a9b44 (placeholder name): empty; called with `true` by ScreenChangeController::m98 and Screen::doInitialize
    void sub_71010A9B44(bool flag);
};

// Base class of the screens' child components (elements of Screen::mChildren at 0x250; the 24 classes with a
// 105-slot vtable derive from it). Slots 43-52 etc. are the ones Screen::m117 - m126 call. The first slots belong to
// eui::ControlBase in the original (0 / 4); slots 2 / 3 are the destructor. Most default implementations are empty or
// forward to another slot of the same object (the argument types of the forwarded slots are unknown).
class ScreenChild : public eui::ControlBase {
public:
    NN_RUNTIME_TYPEINFO(eui::ControlBase)
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
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
    virtual void m54();
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
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
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
};

// The class between ScreenChild and the concrete child classes (guess: the name; the RTTI chain of the leaf classes
// is ControlBase <- ScreenChild-sized class <- this one <- leaf, e.g. the static at 0x71009865a8; ScreenEx::m144 -
// m153 cast their children to it before forwarding the child slots 95 - 104). Its GetRuntimeTypeInfoStatic is
// the out-of-line function at 0x710096a9c4.
class ScreenChildEx : public ScreenChild {
public:
    NN_RUNTIME_TYPEINFO(ScreenChild)
};


// A child class of the PauseMenu screen (id 46, child group 1) derived from ScreenChildEx (placeholder name: its typeinfo
// static is at 0x71025d9b08, guard 0x71025d9b10; the facade helpers of the 0x7100a94000 TU DynamicCast to it). Only the
// member the facade writes is declared.
class ScreenChildUnk_71025d9b08 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    // 0x71009b62cc (`_1a8 = a1`)
    void sub_71009B62CC(void* a1);

    u8 _28[0x80 - 0x28];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    u8 _a8[0x1a8 - 0xa8];
    /* 0x1a8 */ void* _1a8;
};

// A state of ScreenChildUnk_71025d9b08's state machine (a plain StateBase object).
extern const ksys::StateBase sUnk_71025d9960;

// 0x71009de2b8 (uiPaneCasts.cpp)
ScreenChildEx* sub_71009DE2B8(eui::ControlBase* control);

// The secondary RxOnly/TxOnly handlers are at0x108/0x110. Screen introduces its
// handleMessage override at primary slot111; ScreenEx overrides that same slot.
class Screen : public ScreenBase, public ksys::ActorMessageTransceiver::IHandler {
public:
    // 0x71010aa3b0 (CSV Screen::ctor; declared only)
    Screen();
    ~Screen() override;
    SEAD_RTTI_OVERRIDE(Screen, ScreenBase)
    u8 _118[0x160 - 0x118];
    // The screen's state machine (the leaf classes' own virtual slots 154+ are the callbacks of its states).
    ksys::StateMachine mStateMachine;
    u8 _188[0x250 - 0x188];
    /* 0x250 */ sead::PtrArray<ScreenChild> mChildren;
    /* 0x260 */ sead::Buffer<s32> mChildGroupSizes;  // the number of children of each group (the groups are consecutive in mChildren)
    /* 0x270 */ f32 _270;
    u8 _274[0x288 - 0x274];
    /* 0x288 */ eui::Animator* _288;
    /* 0x290 */ u8 _290;
    u8 _291;
    /* 0x292 */ u16 _292;
    // Ends at 0x2fc: the members of ScreenMainDungeon start there (tail padding of the non-POD base).
    u8 _294[0x2fc - 0x294];

    void open(s32 option) override;
    void close(s32 option) override;
    void update() override;
    // 0x71010aa7a0 (CSV Screen::x_0): the child with index `index` of the group `group` (null if out of range)
    ScreenChild* getChild(s32 group, s32 index);
    // 0x71010ab66c (CSV Screen::doUpdate_WorldMgrStuff; not decompiled)
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
    // 0x71010aa9d0 (placeholder name; 107 callers): `DynamicCast<ksys::SeadController>(mUIController->getController())`
    ksys::SeadController* sub_71010AA9D0();

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
    virtual void m74(f32 progress);
    virtual void m75();
    virtual void m76();
    virtual void m77();
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
    int handleMessage(const ksys::Message& message) override;
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
class Unk_71024746b0Item {
public:
    virtual ~Unk_71024746b0Item() = default;
    // 0x710092f374 (declared only)
    void sub_710092F374(bool a1);
};

// ScreenEx's helper at+0x330. The constructor0x92fc8c and destructor0x92fcb4 prove
// size0x38, heap+8, Screen*+0x10, config+0x18, item buffer+0x20 (a sead::Buffer of pointers) and boolean+0x30.
class Unk_71024746b0 {
public:
    Unk_71024746b0();
    virtual ~Unk_71024746b0();

    void setHeap(sead::Heap* heap);
    void initialize(Screen* screen, eui::LayoutEx* layout, void* config);
    void update();
    // 0x71009301f4 (placeholder name): the item `index` (null when there is no buffer or the index is out of range)
    Unk_71024746b0Item* sub_71009301F4(s32 index);

    /* 0x08 */ sead::Heap* mHeap{};
    /* 0x10 */ Screen* mScreen{};
    /* 0x18 */ void* mConfig{};
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

    int handleMessage(const ksys::Message& message) override;
    void m112(sead::Heap* heap) override;
    void m114(sead::Heap* heap) override;
    void m115() override;
    eui::UIController* doCreateUIController_(sead::Heap* heap) override;
    void registerController_() override;

    // Placeholder for the real data (0x300 ...; the leaf classes' members start at 0x3610).
    /* 0x300 */ Unk_710246c458 _300;
    /* 0x310 */ Unk_710246c4d8 _310;
    /* 0x320 */ Unk_710246c498 _320;
    /* 0x330 */ Unk_71024746b0 mButtonHelper;
    /* 0x368 */ ButtonEventQueue* mButtonEvents;
    u8 _370[0x3a8 - 0x370];
    // The units and buttons are parallel arrays (the setBuffer calls of the constructor: 400 entries each, the
    // storage follows the array header).
    /* 0x3a8 */ sead::FixedPtrArray<Unk_7102474e38, 400> mButtonUnits;
    /* 0x1038 */ sead::FixedPtrArray<eui::AnimButton, 400> mButtons;
    u8 _1cc8[0x3610 - 0x1cc8];

    // Unnamed helpers of ScreenEx (placeholder names after the addresses; the hubs of the UI: 20 / 52 / 62 callers).
    // 0x7100a480b4: the button of the pane that `path` (slash separated) resolves to
    eui::ButtonBase* sub_7100A480B4(const sead::SafeString& path);
    // 0x7100a48104 / 0x7100a48328: the pane / object `path` resolves to in the screen's layout (`out` receives the parent)
    nn::ui2d::Pane* sub_7100A48104(const sead::SafeString& path, nn::ui2d::Pane** parent);
    void* sub_7100A48328(const sead::SafeString& path, void* out);
    // 0x7100a4810c: the button whose layout is `layout`
    eui::ControlBase* sub_7100A4810C(const eui::LayoutEx* layout);
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
    virtual void* m143();
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
    void m96() override;
    ~ScreenPauseMenuInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuInfo, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    u8 _pad_3610[0x3904 - 0x3610];
    /* 0x3904 */ u8 _3904;
    u8 _pad_3905[0x391c - 0x3905];
    /* 0x391c */ u8 _391c;
    u8 _pad_391d[0x39f8 - 0x391d];
    /* 0x39f8 */ Unk_7102474bc8 _39f8;

    void sub_7100A31BE0();
    // 0x7100a31988 (placeholder name): forwards to the member at 0x39f8
    void sub_7100A31988(bool flag);
};

class ScreenMessageTipsRunTime : public ScreenEx {
public:
    ScreenMessageTipsRunTime();
    ~ScreenMessageTipsRunTime() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)
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
};

class ScreenDoCommand : public ScreenEx {
public:
    ScreenDoCommand();
    void m100() override;
    void m101() override;
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

// Placeholder for the info overlay object ScreenMainScreen keeps at 0x3648.
struct ScreenMainScreenUnk3648 {
    // 0x710098a93c (CSV unnamed; declared only)
    void sub_710098A93C(s32 type, const sead::SafeString& text);
    // 0x710098ae8c (declared only)
    void sub_710098AE8C(s32 a1);
};

// Placeholder for the object ScreenMainScreen keeps at 0x3658 (the int at 0x150 is written by sub_7100A1AB58).
struct ScreenMainScreenUnk3658 {
    u8 _0[0x150];
    /* 0x150 */ s32 _150;
};

class ScreenMainScreen : public ScreenEx {
public:
    void m85() override;
    void m88() override;
    bool isEnableControl() const override;
    ~ScreenMainScreen() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen, ScreenEx)

    u8 _pad_3610[0x3620 - 0x3610];
    /* 0x3620 */ void* _3620;
    u8 _pad_3628[0x3648 - 0x3628];
    /* 0x3648 */ ScreenMainScreenUnk3648* _3648;
    u8 _pad_3650[0x3658 - 0x3650];
    /* 0x3658 */ ScreenMainScreenUnk3658* _3658;
    u8 _pad_3660[0x3678 - 0x3660];
    /* 0x3678 */ Unk_7102474c08 _3678;  // 0x38 bytes (0x7100a1ab68 / 0x7100a1ab94 call into it)
    /* 0x36b0 */ void* _36b0;
    // The two ints are written together by sub_7100A1ABF8 ({1, 0}) and separately by sub_7100A1ABC8.
    /* 0x36b8 */ s32 _36b8;
    /* 0x36bc */ s32 _36bc;
    u8 _pad_36c0[0x3704 - 0x36c0];
    /* 0x3704 */ s32 _3704;
    u8 _pad_3708[0x3720 - 0x3708];
    /* 0x3720 */ f32 _3720;  // -99.0f initially
    u8 _pad_3724[0x3aa8 - 0x3724];
    /* 0x3aa8 */ u8 _3aa8;
    u8 _pad_3aa9[0x3ca8 - 0x3aa9];
    /* 0x3ca8 */ eui::LayoutEx* _3ca8;

    bool sub_7100A1A1C4(s32 a1, bool a2);
    void sub_7100A1AB58(s32 a1);
    // 0x7100a1ab74 (CSV ScreenMainScreen::showInfoOverlayWithString)
    void showInfoOverlayWithString(s32 type, const sead::SafeString& text);

    void sub_7100A1A4E4(s64);
    // 0x7100a1ab14 / 0x7100a1abc8 / 0x7100a1abe8 / 0x7100a1abf8 (placeholder names)
    void sub_7100A1AB14(s64 a1, f32 value);
    void sub_7100A1AB84(s32 a1);
    void sub_7100A1ABC8(s32 value);
    bool sub_7100A1ABE8() const;
    void sub_7100A1ABF8();
    // 0x7100a1a518 (CSV unnamed; declared only; the types are guesses)
    void sub_7100A1A518(s64 a1, bool a2);
    bool sub_7100A1E1E0();
    // 0x7100a1e44c (placeholder name): always 1.0
    static f32 sub_7100A1E44C();
    // 0x7100a1ab68 (placeholder name; called by Unk_7102474c08::sub_7100936254): the value of the gauge member
    f32 sub_7100A1AB68() const;
    // 0x7100a1ab94 (placeholder name): runs the gauge update with this screen's animation step
    void sub_7100A1AB94();
};

// The MessageTips screen (members from 0x300 recovered from the constructor).
class ScreenMessageTips : public Screen {
public:
    ScreenMessageTips();
    ~ScreenMessageTips() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTips, Screen)
    void m93(sead::Heap* heap) override;
    void m98() override;
    void m100() override;
    // 0x71010a8afc
    const char* getLayoutName_() const override;

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

    u8 _2fc[0x300 - 0x2fc];
    /* 0x300 */ eui::LetterAnimControl* _300 = nullptr;
    /* 0x308 */ eui::LetterAnimControl* _308 = nullptr;
    u8 _310[0x350 - 0x310];
    /* 0x350 */ s32 _350;
    u8 _354[0x3a0 - 0x354];
    // The message being scanned (its mString/_8 are walked by sub_71010B307C/3294 as text/length;
    // sub_71010B2B30 assigns it as a whole).
    /* 0x3a0 */ eui::MessageString _3a0;
    u8 _3b0[0x3b8 - 0x3b0];
    /* 0x3b8 */ char* _3b8 = nullptr;
    /* 0x3c0 */ s32 _3c0 = 0;
    u8 _3c4[0x4d0 - 0x3c4];
    /* 0x4d0 */ char* _4d0 = nullptr;
    /* 0x4d8 */ s32 _4d8 = 0;
    u8 _4dc[0x5e0 - 0x4dc];
    /* 0x5e0 */ s32 _5e0 = 0;
    u8 _5e4[0x5ec - 0x5e4];
    /* 0x5ec */ s32 _5ec;
    u8 _5f0[0x720 - 0x5f0];
    // The dialog's actor (set by sub_71010B306C, linked by _728).
    /* 0x720 */ ksys::act::Actor* _720;
    /* 0x728 */ ksys::act::BaseProcLink _728;
    /* 0x738 */ s32 _738;
    /* 0x73c */ s32 _73c;
    /* 0x740 */ u32 _740 = 0;
    u8 _744[0x768 - 0x744];
    /* 0x768 */ u16 _768;
    /* 0x76a */ bool _76a;
    u8 _76b[0x76d - 0x76b];
    /* 0x76d */ u8 _76d;
    u8 _76e[0x773 - 0x76e];
    /* 0x773 */ u8 _773;
    /* 0x774 */ s32 _774;
    // Created by ScreenBase::doCreateTagProcessor_ in 0x71010b34f0.
    /* 0x778 */ TagProcessor* _778;

    // 0x71010b343c / 0x71010b34b4 / 0x71010b34a0: called by UI::sub_71010A5C8C / setPlacedItemStockNum / sub_71010A7994.
    bool sub_71010B343C();
    void sub_71010B34B4(bool choice_mode, s32 stock);
    void sub_71010B34A0(bool a1);
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
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    // 0x71010a4f24 / 0x71010a4f3c / 0x71010a4f64 (placeholder names): state changes that close the screen
    void sub_71010A4F24();
    void sub_71010A4F3C();
    void sub_71010A4F64();

    // 0x71010a53f0 (slot 101): starts the close animation of the three layouts at 0x9d0 / 0x9d8 / 0x9e0
    void m101() override;

    /* 0x2fc */ s32 _2fc;
    /* 0x300 */ s32 _300;
    /* 0x304 */ s32 _304;
    u8 _pad_308[0x9d0 - 0x308];
    /* 0x9d0 */ eui::LayoutEx* _9d0;
    /* 0x9d8 */ eui::LayoutEx* _9d8;
    /* 0x9e0 */ eui::LayoutEx* _9e0;
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
// Run-time state of ScreenAppTool (0x71025ec540: a record id followed by a halfword, written by its
// constructor); the flag bytes at 0x71025ec548 / 0x71025ec549 / 0x71025ec54a are separate globals.
struct AppToolState {
    s32 _0;
    u16 _4;
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
    void m96() override;
    void m98() override;
    void m99() override;
    bool isEnableControl() const override;
    ~ScreenMainShortCut() override;
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)
    // 0x7100a20230: override of Screen::m84; opens the screen when it is closed, then stops the _36e0 animator at its minimum
    void m84() override;

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    u8 _pad_3610[0x3638 - 0x3610];
    nn::ui2d::ArchiveHandle _3638;
    /* 0x36e0 */ eui::Animator* _36e0;
    /* 0x36e8 */ s32 _36e8;
    sead::PtrArray<Unk_Elem> _36f0;
    /* 0x3700 */ sead::BitFlag8 _3700;
    u8 _pad_3701[0x3720 - 0x3701];
    /* 0x3720 */ s32 _3720;
    u8 _pad_3724[0x3790 - 0x3724];
    /* 0x3790 */ ScreenAppPictureBookUnk* _3790;
    /* 0x3798 */ eui::Animator* _3798;
    /* 0x37a0 */ eui::Animator* _37a0;
    u8 _pad_37a8[0x3850 - 0x37a8];
    sead::Buffer<u8> _3850;  // element type not known
    u8 _pad_3860[0x38c8 - 0x3860];
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
    /* 0x3658 */ u64 _3658;
    /* 0x3660 */ u64 _3660;
    /* 0x3668 */ u8 _3668;
    u8 _pad_3669[0x366c - 0x3669];
    // The mini game's counters: a game data key (`_36x0`, set by the sub_7100A280A4 family from the caller's key), the
    // widget layout that shows the value and the last value read. Names / types are guesses from those functions.
    /* 0x366c */ s32 _366c;
    /* 0x3670 */ sead::SafeString _3670;
    /* 0x3680 */ u64 _3680;
    /* 0x3688 */ eui::Animator* _3688;
    /* 0x3690 */ s32 _3690;
    /* 0x3698 */ sead::SafeString _3698;
    /* 0x36a8 */ f32 _36a8;
    /* 0x36b0 */ sead::SafeString _36b0;
    /* 0x36c0 */ s32 _36c0;
    /* 0x36c8 */ sead::SafeString _36c8;
    /* 0x36d8 */ u64 _36d8;
    /* 0x36e0 */ eui::Animator* _36e0;
    /* 0x36e8 */ eui::Animator* _36e8;

    void sub_7100A280A4(const sead::SafeString& a1);
    void sub_7100A2813C(const sead::SafeString& a1);
    void sub_7100A28264(const sead::SafeString& a1);
    void sub_7100A28318(const sead::SafeString& a1);
    void sub_7100A283B0(s32 a1);
    void sub_7100A28418(s32 a1);

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

// Placeholder for the object ScreenAppMap keeps at 0x3c98 (its state at 0x104 decides which animators play).
struct ScreenAppMapUnk3c98 {
    u8 _0[0x104];
    /* 0x104 */ s32 _104;
};

// The AppMap animation controller at +0x3c90; only its animation state is recovered.
struct ScreenAppMapUnk3c90 {
    void sub_71009C1474(f32 speed, s32 type);
    void sub_71009C1530(s32 state);
    bool sub_71009C1814(s32 type) const;

    u8 _0[0x130];
    /* 0x130 */ s32 _130;
    /* 0x134 */ bool _134;
    u8 _135[3];
    /* 0x138 */ eui::Animator* _138;
    /* 0x140 */ eui::Animator* _140;
    /* 0x148 */ eui::Animator* _148;
    u8 _150[8];
    /* 0x158 */ eui::Animator* _158;
};

// Placeholder for the map widget the AppMap screen owns (byte 0xb33a is set by ScreenAppMap::mainEnter).
struct ScreenAppMapWidget {
    // 0x71009a9438 (CSV unnamed): the timer at 0xb290 is done or the flag at 0xb1db is set
    bool sub_71009A9438();
    // Small accessors of the widget (lane2 s46; placeholder names, the field meanings are not known)
    void sub_71009A995C();
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
    // 0x71009a9b48 / 0x71009a9b7c / 0x71009a9e74 (placeholder names): set the mode at 0xb350 (0 / 1 / 2) and tell the map state
    void sub_71009A9B48();
    void sub_71009A9B7C();
    void sub_71009A9E74(const sead::Vector3f* pos);
    // 0x71009a9b8c (364 bytes) / 0x71009aa024 (344 bytes): declared only
    void sub_71009A9B8C();
    void sub_71009AA024();
    // 0x71009aa004 (placeholder name): runs sub_71009AA024 for DLC version 0x200 and later
    void sub_71009AA004();
    // 0x71009af034 (placeholder name): the table entry `_b4fc` (0 for an index of 32 or more)
    f32 sub_71009AF034() const;
    // 0x71009aef88 (placeholder name): clears _b4ec / _b4f0 and decodes the packed signed (x, y) word at `_b370` into _b4b8 / _b4bc
    void sub_71009AEF88();

    u8 _0[0xb1db];
    /* 0xb1db */ u8 _b1db;
    u8 _b1dc[0xb290 - 0xb1dc];
    /* 0xb290 */ UiTimer _b290;
    u8 _b2a8[0xb33a - 0xb2a8];
    /* 0xb33a */ u8 _b33a;
    u8 _b33b[0xb34c - 0xb33b];
    /* 0xb34c */ u8 _b34c;
    u8 _b34d[0xb350 - 0xb34d];
    /* 0xb350 */ s32 _b350;
    u8 _b354[0xb370 - 0xb354];
    /* 0xb370 */ u32* _b370;  // points at a packed (x, y) word
    u8 _b378[0xb388 - 0xb378];
    /* 0xb388 */ s32 _b388;
    u8 _b38c[0xb499 - 0xb38c];
    /* 0xb499 */ u8 _b499;
    u8 _b49a[0xb4a0 - 0xb49a];
    /* 0xb4a0 */ s32 _b4a0;
    u8 _b4a4[0xb4a8 - 0xb4a4];
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
    u8 _b4f4[0xb4fc - 0xb4f4];
    /* 0xb4fc */ s8 _b4fc;
    u8 _b4fd;
    /* 0xb4fe */ s8 _b4fe;
    /* 0xb4ff */ u8 _b4ff;
};

class ScreenAppMap : public ScreenEx {
public:
    bool sub_71009EECD0() const;
    s32 sub_71009EED10() const;
    void m92(sead::Heap*) override;
    void m83() override;
    void m100() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    s32 getSlink2LocalPropertyNum_() const override;
    ~ScreenAppMap() override;
    SEAD_RTTI_OVERRIDE(ScreenAppMap, ScreenEx)

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

    // State callbacks (slots 154-165: main / sub / demo screens x enter / run / leave / a fourth one that returns 0)
    virtual void mainEnter();
    virtual void mainRun();
    virtual void mainLeave();
    virtual void subEnter();
    virtual void subRun();
    virtual void subLeave();
    virtual void demoEnter();
    virtual void demoRun();
    virtual void demoLeave();
    virtual s32 demoReenter();

    /* 0x3610 */ ScreenAppMapWidget* _3610;
    u8 _3618[0x3638 - 0x3618];
    /* 0x3638 */ eui::Animator* _3638;
    u8 _3640[0x3ad1 - 0x3640];
    /* 0x3ad1 */ u8 _3ad1;
    /* 0x3ad2 */ u8 _3ad2;  // written by sub_71009EF4EC / sub_71009EF51C
    u8 _3ad3;
    /* 0x3ad4 */ f32 _3ad4;
    /* 0x3ad8 */ f32 _3ad8;
    /* 0x3adc */ f32 _3adc;
    u8 _3ae0[0x3c00 - 0x3ae0];
    /* 0x3c00 */ eui::Animator* _3c00;
    /* 0x3c08 */ eui::Animator* _3c08;
    u8 _3c10[0x3c88 - 0x3c10];
    /* 0x3c88 */ eui::Animator* _3c88;
    /* 0x3c90 */ ScreenAppMapUnk3c90* _3c90;
    /* 0x3c98 */ ScreenAppMapUnk3c98* _3c98;
};

// State of ScreenPauseMenu's state callbacks (0x71025f0cf0; placeholder name).
extern const ksys::StateBase sUnk_71025f0cf0;
extern const ksys::StateBase sUnk_710261ee00;
extern const ksys::StateBase sUnk_71025d98a0;
extern const ksys::StateBase sUnk_71025d9e00;

// Placeholder for the object ScreenPauseMenu keeps at 0x3b90.
struct ScreenPauseMenuUnk3b90 {
    u8 _0[0x80];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    // 0x71009b9f94 (CSV unnamed; declared only)
    bool sub_71009B9F94(bool a1);
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
    u8 _0[0x130];
    /* 0x130 */ s32 _130;
    u8 _134[4];
    /* 0x138 */ ScreenButton_7100989968 mButtons[20];
    // 0x71009b0224 (CSV unnamed; declared only)
    void sub_71009B0224(bool a1);
};

// Placeholder for the object ScreenPauseMenu keeps at 0x3b98.
struct ScreenPauseMenuUnk3b98 {
    u8 _0[0x80];
    /* 0x80 */ ksys::StateMachine mStateMachine;
    u8 _a8[0x1a0 - 0xa8];
    /* 0x1a0 */ s32 _1a0;
    // 0x71009b5fc8 (CSV unnamed; declared only)
    void sub_71009B5FC8(bool a1);
};

class ScreenPauseMenu : public ScreenEx {
public:
    s32 m72() override;
    void m69() override;
    void m70() override;
    void m71() override;
    void m96() override;
    bool isEnableControl() const override;
    ~ScreenPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m101() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a3840c (CSV unnamed, 1248 bytes; declared only; tail-called by m106)
    void sub_7100A3840C(eui::AnimButton* button);
    // 0x7100a392d8 (CSV unnamed, 396 bytes; declared only)
    void sub_7100A392D8();
    // 0x7100a38028 (CSV unnamed, 296 bytes; declared only)
    void sub_7100A38028();
    u8 _pad_3610[0x3618 - 0x3610];
    /* 0x3618 */ s32 _3618;
    u8 _pad_361c[0x3674 - 0x361c];
    /* 0x3674 */ s32 _3674;
    u8 _pad_3678[0x3a00 - 0x3678];
    /* 0x3a00 */ ScreenPauseMenuUnk3a00* _3a00[3];
    /* 0x3a18 */ u8 _3a18;
    u8 _pad_3a19[0x3b80 - 0x3a19];
    /* 0x3b80 */ s32 _3b80;
    /* 0x3b84 */ s32 _3b84;
    /* 0x3b88 */ s32 _3b88;
    u8 _pad_3b8c[0x3b90 - 0x3b8c];
    /* 0x3b90 */ ScreenPauseMenuUnk3b90* _3b90;
    /* 0x3b98 */ ScreenPauseMenuUnk3b98* _3b98;
    u8 _pad_3ba0[0x3ba4 - 0x3ba0];
    /* 0x3ba4 */ u8 _3ba4;
    u8 _pad_3ba5[0x3bb4 - 0x3ba5];
    /* 0x3bb4 */ s32 _3bb4;
    u8 _pad_3bb8[0x3c10 - 0x3bb8];
    /* 0x3c10 */ u8 _3c10;
    u8 _pad_3c11[3];
    /* 0x3c14 */ UiTimer _3c14;

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

    // An element of the table at 0x3640 (0x28 bytes; only the s32 at 0x24 is used so far).
    struct Record {
        u8 _0[0x24];
        s32 _24;
    };

    // Members used by the state callbacks (see the constructor 0x71009fcd64).
    /* 0x3610 */ u8 _3610 = 1;
    u8 _pad_3611[0x3618 - 0x3611];
    /* 0x3618 */ u64 _3618 = 0;
    /* 0x3620 */ eui::Animator* _3620 = nullptr;
    /* 0x3628 */ u64 _3628 = 0;
    /* 0x3630 */ u8 _3630 = 0;
    u8 _pad_3631[0x3638 - 0x3631];
    // Count and storage of the array the destructor deletes (element type not known).
    /* 0x3638 */ u32 _3638 = 0;
    u8 _pad_363c[0x3640 - 0x363c];
    /* 0x3640 */ Record* _3640 = nullptr;  // delete[]d by the destructor
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

// Placeholder for the objects ScreenAppPictureBook keeps at 0x3658 / 0x3660.
// An entry of the picture book's list (placeholder; only the two flag bytes are known).
struct ScreenAppPictureBookEntry {
    u8 _0[0x29c];
    /* 0x29c */ s32 _29c;
    /* 0x2a0 */ s32 _2a0;
    /* 0x2a4 */ s32 _2a4;
    u8 _2a8[0x2ca - 0x2a8];
    /* 0x2ca */ bool _2ca;
    u8 _2cb[0x2f0 - 0x2cb];
    /* 0x2f0 */ s32 _2f0;
    /* 0x2f4 */ s32 _2f4;
    u8 _2f8[0x38c - 0x2f8];
    /* 0x38c */ bool _38c;
    /* 0x38d */ bool _38d;
};

// Producer93C24C allocates this 0x48-byte button group. Binding93C304
// writes its entry and list controller, and93C660 attaches its units.
struct PictureBookGroupRecord {
    u32 _0;
    f32 _4;
    f32 _8;
    s32 _c;
};
class Unk_7102474f10 {
public:
    SEAD_RTTI_BASE(Unk_7102474f10)
    virtual ~Unk_7102474f10();
    // 0x710093a008 (placeholder name): modes 3 / 4 / 5 of sub_710093A0A8 (play from current / play auto / stop at max)
    void sub_710093A008(s32 mode);
    // 0x710093a0a8 (placeholder name; called for every group by 0x7100943d5c): mode 0 / 1 / 2 plays the _30 animator
    // (from current / auto / stops at min), or starts the close animation of the layout when there is none.
    void sub_710093A0A8(s32 mode);
    eui::LayoutEx* _8;
    ScreenAppPictureBookEntry* mEntry;
    ScreenAppPictureBookUnk* mController;
    sead::PtrArray<Unk_7102474e38> mUnits;
    eui::Animator* _30;
    PictureBookGroupRecord* mRecord;
    PictureBookItem* _40;
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
    /* 0x8 */ u8 _8[0x10 - 0x8];
    /* 0x10 */ bool _10;
};

// Placeholder for a photo-group list of sub_710093FBF0 (count + group array).
struct PictureBookGroupList {
    /* 0x0 */ s32 _0;
    u8 _4[0x8 - 0x4];
    /* 0x8 */ Unk_7102474f10** _8;
};

struct ScreenAppPictureBookUnk {
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
    // 0x7100943684 (CSV placeholder): find the unit covering `index` (reads _288/_290/_2a8).
    Unk_7102474e38* sub_7100943684(s32 index);

    /* 0x000 */ u8 _0[0x28];
    /* 0x028 */ u8 _28;
    u8 _29[0x2c - 0x29];
    /* 0x02c */ u32 _2c;
    /* 0x030 */ u32 _30;
    u8 _34[0x38 - 0x34];
    /* 0x038 */ void* _38;
    /* 0x040 */ eui::LayoutEx* _40[4];
    /* 0x060 */ ScreenEx* mScreen;
    u8 _68[0xc8 - 0x68];
    /* 0x0c8 */ s32 _c8;
    u8 _cc[0x288 - 0xcc];
    /* 0x288 */ u32 _288;
    u32 _28c;
    /* 0x290 */ ScreenAppPictureBookEntry** _290;
    /* 0x298 */ s32 _298;
    u8 _29c[0x2a0 - 0x29c];
    /* 0x2a0 */ PictureBookGroupList** _2a0;
    /* 0x2a8 */ s32 _2a8;
    /* 0x2ac */ u8 _2ac[0x2d8 - 0x2ac];
    /* 0x2d8 */ s32 _2d8;
    u8 _2dc[0x2e4 - 0x2dc];
    /* 0x2e4 */ s32 _2e4;
    /* 0x2e8 */ s32 _2e8;
    /* 0x2ec */ s32 _2ec;
    /* 0x2f0 */ s32 _2f0;
    u8 _2f4[0x30c - 0x2f4];
    /* 0x30c */ s32 _30c;
    /* 0x310 */ s32 _310;
    /* 0x318 */ PictureBookItem* _318;
    /* 0x320 */ s32 _320;
    u8 _324[0x33c - 0x324];
    /* 0x33c */ s32 _33c;
    /* 0x340 */ s32 _340;
};

class ScreenAppPictureBook : public ScreenEx {
public:
    void m100() override;
    void m106(eui::AnimButton*) override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppPictureBook() override;
    SEAD_RTTI_OVERRIDE(ScreenAppPictureBook, ScreenEx)

    // state callbacks (slots 154-165, trivial ones defined in uiScreenLeafSlots.cpp)
    u8 _pad_3610[0x3658 - 0x3610];
    /* 0x3658 */ ScreenAppPictureBookUnk* _3658;
    /* 0x3660 */ ScreenAppPictureBookUnk* _3660;

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
    u8 _3650[0x3658 - 0x3650];
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
};

// Screens without members of their own that are modelled yet: only the (trivial, tail-calling)
// destructor and the RTTI.
class ScreenGamePadBG : public ScreenEx {
public:
    ScreenGamePadBG();
    void m82() override;
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
    Unk_7102474be8* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenWolfLinkHeartGauge, ScreenEx)
};

class ScreenMainHorse : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ~ScreenMainHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHorse, ScreenEx)

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

class ScreenDemoName : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    void m93(sead::Heap*) override;
    ScreenDemoName();
    ~ScreenDemoName() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDemoName, ScreenEx)
};

class ScreenDemoNameEnemy : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    void m93(sead::Heap*) override;
    ScreenDemoNameEnemy();
    ~ScreenDemoNameEnemy() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
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

    void m98() override;
    void m99() override;
    void m100() override;
    void m101() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;
    /* 0x3610 */ s32 _3610 = 4;
    s32 _3614 = 3;
    u8 _3618[0x28]{};
    /* 0x3640 */ eui::AnimButton* _3640{};
    eui::AnimButton* _3648{};
    eui::AnimButton* _3650{};
    eui::AnimButton* _3658{};
    eui::AnimButton* _3660{};
    eui::AnimButton* _3668{};
    u8 _3670[8]{};
    /* 0x3678 */ eui::Animator* _3678{};
    u8 _3680[8]{};
    /* 0x3688 */ u8 _3688{};
    u8 _3689{};
    u8 _368a{};
    u8 _368b{};
    u8 _368c[4];
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();
    virtual void m155();

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

    /* 0x3610 */ u64 _3610{};
    u64 _3618{};
    u64 _3620{};
    u64 _3628{};
    u64 _3630{};
    u8 _3638[0x36b0 - 0x3638];
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
    virtual void m154();
    virtual void m155();

};

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
    virtual void m154();
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
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
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
    const char* getLayoutName_() const override;
    bool isEnableControl() const override;
    // 0x7100a4cef0 (placeholder name): whether the button group has a down button
    bool sub_7100A4CEF0() const;
    ~ScreenShopBtnList20() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList20, ScreenEx)
    void m102(eui::AnimButton*) override;
    void m107(eui::AnimButton* button) override;
    // 0x7100a4c9e0 (slot 98)
    void m98() override;
    // 0x7100a4cd5c / 0x7100a4cd70 / 0x7100a4ce28 (placeholder names): forward to the picture book controller
    void sub_7100A4CD5C(bool value);
    void sub_7100A4CD70();
    s32 sub_7100A4CE28();
    /* 0x3610 */ ScreenAppPictureBookUnk* _3610;
    u8 _pad_3618[0x3864 - 0x3618];
    /* 0x3864 */ u8 _3864;
    u8 _pad_3865[0x3868 - 0x3865];
    eui::AnimButton* _3868;
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
    ~Unk_7102485670() override;
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

    u8 _pad_3610[0x3618 - 0x3610];
    /* 0x3618 */ ScreenAppPictureBookUnk* _3618;
    u8 _pad_3620[0x3850 - 0x3620];
    /* 0x3850 */ u8 _3850;
    /* 0x3851 */ u8 _3851;
};

// The DLC window's tip unit (vtable 0x71024872a0, 0x50 bytes). The ScreenDLCWindow function at
// 0x7100a067a8 creates the units; each one looks up its Pa_DLCTips_00 parts layout.
class Unk_71024872a0 : public Unk_7102474e38 {
public:
    SEAD_RTTI_OVERRIDE(Unk_71024872a0, Unk_7102474e38)
    Unk_71024872a0() = default;
    ~Unk_71024872a0() override;
    void m4(sead::Heap*) override;
    void m6() override;

    /* 0x48 */ eui::LayoutEx* _48{};
};

class ScreenDLCWindow : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenDLCWindow() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDLCWindow, ScreenEx)
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;

    // 0x7100a05f94 (placeholder name): returns the result and sets it to 2
    s32 sub_7100A05F94();
    // 0x7100a05f7c (placeholder name): stops the animator at 0x3870 at `frame`
    void sub_7100A05F7C(f32 frame);
    u8 _pad_3610[0x3870 - 0x3610];
    /* 0x3870 */ eui::Animator* _3870;
    // 0x7102486d48 (placeholder name): the window's result (0: no, 1: yes, 2: none yet)
    static s32 sResult;
};

class ScreenTitle : public ScreenEx {
public:
    ScreenTitle();
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

// Placeholder for the object ScreenAppCamera keeps at 0x3610 (the int at 0x104 is tested).
struct ScreenAppCameraUnk3610 {
    u8 _0[0x104];
    /* 0x104 */ s32 _104;
};

class ScreenAppCamera : public ScreenEx {
public:
    void m127() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppCamera() override;
    SEAD_RTTI_OVERRIDE(ScreenAppCamera, ScreenEx)

    /* 0x3610 */ ScreenAppCameraUnk3610* _3610;

    void m99() override;

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

class ScreenMessageGet : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMessageGet() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageGet, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m99() override;
    // 0x7100a257f4 (slot 101): clears the UI singleton's actor name and runs ui::sub_7100A9B2D0
    void m101() override;

    u8 _pad_3610[0x3640 - 0x3610];
    /* 0x3640 */ eui::LayoutEx* _3640;
    u8 _pad_3648[0x3650 - 0x3648];
    /* 0x3650 */ u8 _3650;
    u8 _pad_3651[0x3658 - 0x3651];
    /* 0x3658 */ eui::ControlBase* _3658;
    u8 _pad_3660[0x3670 - 0x3660];
    Unk_710247adc8 _3670[2];
    u8 _pad_36f0[0x37d8 - 0x36f0];
    /* 0x37d8 */ sead::Buffer<Unk_7102474ba8> _37d8;
};

class ScreenSousaGuide : public ScreenEx {
public:
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
struct ShopInfoTagData {
    sead::FixedSafeString<64> str;
    u32 _58 = 0xffffffff;
    u32 _5c = 1;
};

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
bool sub_7100AA29C4(ShopInfoTagData* data, sead::SafeString& name);
// 0x7100aa2bdc (CSV unnamed): resolve the tag data's string into a message (suffix-stripped actor
// name under ActorType/<profile>, or the empty message).
u32 sub_7100AA2BDC(ShopInfoTagData* data, eui::MessageString* out);
// 0x7100aa3b50 (CSV unnamed): build the "UI/StockItem/<icon>" texture path for `name` into `out`
// (icon-actor lookup, Weapon_Sword_502/503 quirk, ".%02d" count suffix, ".bitemico" extension).
void sub_7100AA3B50(const sead::SafeString& name, sead::BufferedSafeStringBase<char>* out,
                    s32 count);
// 0x7100a91e40 (CSV unnamed): the item count for `name` (0 when the name is empty or there is
// no pouch manager).
s32 sub_7100A91E40(const sead::SafeString& name, bool count_equipped);
// 0x71010b3468 / 0x71010b3484 (CSV placeholders): TagInfo adapters into the ksys::eft helpers
// (called by the ScreenMessage3D tag invoke).
void sub_71010B3468(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag);
void sub_71010B3484(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool flag);
// 0x71010b3188 (CSV unnamed): TagInfo dispatch shared by the ScreenMessage3D tag invoke (below)
// and the dialog scan (calls the eft voice helper and the WeaponBase TU helper).
void sub_71010B3188(const sead::MessageSet<char16>::TagInfo* tag, ksys::act::Actor* actor, bool a,
                    s16* out, bool b);
// 0x7100ee6b88 (CSV unnamed; WeaponBase-TU helper, lane4's — declared only): apply an emotion voice
// name to the actor (stores it at +0x8a8, flag at +0x8b8) or trigger the head-shot go-limp path.
bool sub_7100EE6B88(ksys::act::Actor* actor, const sead::SafeStringBase<char>& name, bool flag);

class ScreenShopInfo : public ScreenEx {
public:
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

    // 0x7100a52db0 (CSV placeholder): mode select (1 = full refresh through sub_7100A52E60,
    // 0 = re-resolve the shop message into _3650; anything else only runs the _3620 animator).
    void sub_7100A52DB0(u32 mode, ShopInfoTagData* data);
    // 0x7100a52e60 (CSV placeholder, not decompiled yet): the full shop refresh (888B; uses
    // _3690/_3698/_3658, calls sub_7100AA2BDC + unnamed 0x9c2c28/2c44/2c8c/2d44 + sub_7100AA3B50).
    // Declared only so sub_7100A52DB0 can tail-call it.
    void sub_7100A52E60(ShopInfoTagData* data, u32 a2, s32 a3);
    u8 _pad_3610[0x3620 - 0x3610];
    // 0x7100a52db0 (CSV placeholder): resolved by the Animator::Stop slot-24 call (vtable-proven)
    // and the sibling screens' `eui::Animator* _3620` at the same offset.
    /* 0x3620 */ eui::Animator* _3620 = nullptr;
    u8 _pad_3628[0x3650 - 0x3628];
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
    u8 _3610[0x3630 - 0x3610];
    /* 0x3630 */ eui::Animator* _3630;
    u8 _pad_3638[0x3a9c - 0x3638];
    /* 0x3a9c */ s32 _3a9c;

};

class ScreenAppMapDungeon : public ScreenEx {
public:
    void m100() override;
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
};

class ScreenPickUp : public ScreenEx {
public:
    ScreenPickUp();
    ~ScreenPickUp() override;
    SEAD_RTTI_OVERRIDE(ScreenPickUp, ScreenEx)

    // 0x7100a3f3f4 (CSV ScreenPickUp::setItemAndOpen): opens the screen (option 3); with `show` it also shows the item
    // for 5 seconds (the argument type is a guess)
    void setItemAndOpen(const sead::SafeString& item, bool show);
    // 0x7100a3f450 (CSV unnamed; not decompiled)
    void sub_7100A3F450(const sead::SafeString& item, f32 time);

    // One pickup-item slot (0xe8 bytes; the D1 at 0x7100a3f450 walks the list, checks the busy bit at +0xe5
    // and calls UiTimer::init on the slot). Only the link matters here.
    struct Slot {
        Slot* mNext;
        u8 _8[0xe8 - 8];
    };

    /* 0x3610 */ sead::CriticalSection _3610;
    /* 0x3650 */ sead::PtrArrayImpl _3650;
    /* 0x3660 */ Slot* _3660;
    /* 0x3668 */ Slot* _3668;
    /* 0x3670 */ Slot _3670[7];
    /* 0x3cc8 */ void* _3cc8[7];
};

class ScreenAppHome : public ScreenEx {
public:
    ScreenAppHome();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppHome() override;
    SEAD_RTTI_OVERRIDE(ScreenAppHome, ScreenEx)

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
    void sub_7100A45080();
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
    u8 _pad_3764[0x3798 - 0x3764];
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

    /* 0x3610 */ Unk_7102474df8 _3610;
    /* 0x3698 */ sead::PtrArray<Unk_OptionWindowEntry> _3698;
};

// 0x710249ad74 (placeholder name; a mode of the system window: 1 / 2 close the window without saving)
extern s32 sUnk_710249ad74;

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
    void m129() override;

    u8 _pad_3610[0x4b5c - 0x3610];
    /* 0x4b5c */ bool _4b5c;
    u8 _pad_4b5d[0x4b60 - 0x4b5d];
    /* 0x4b60 */ bool _4b60;
    // 0x7100a6641c (CSV unnamed; not decompiled)
    bool sub_7100A6641C();
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();

};

class ScreenPauseMenuRecipe : public ScreenEx {
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

class ScreenStaffRoll : public ScreenEx {
public:
    ~ScreenStaffRoll() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRoll, ScreenEx)
};

class ScreenStaffRollDLC : public ScreenEx {
public:
    ScreenStaffRollDLC();
    bool isEnableControl() const override;
    ~ScreenStaffRollDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRollDLC, ScreenEx)

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
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();

};

class ScreenFadeStatus : public ScreenEx {
public:
    ScreenFadeStatus();
    bool isPlayPartsInOut_() const override;
    ~ScreenFadeStatus() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeStatus, ScreenEx)

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

// 0x7100aa0dc0 / 0x7100aa1260 (declared only): resolve a slash separated pane path inside a layout
nn::ui2d::Pane* sub_7100AA0DC0(eui::LayoutEx* layout, const sead::SafeString& path, nn::ui2d::Pane** parent);
void* sub_7100AA1260(eui::LayoutEx* layout, const sead::SafeString& path, void* out);

// 0x7100a64304 (declared only): takes the pending result of a system window (and resets it to 13)
s32 sub_7100A64304();

// 0x7100aa1cb8 (declared only): sets the alpha byte of a material's color
void sub_7100AA1CB8(nn::ui2d::Material* material, u8 alpha);

// 0x7100949d18 (declared only): the heart gauge value of `count` quarter hearts
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

}  // namespace uking::ui

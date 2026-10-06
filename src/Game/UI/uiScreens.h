#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiControlBase.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiTimer.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiUIController.h"
#include "Game/UI/uiButtonEventQueue.h"
#include "Game/UI/uiArchiveHandle.h"
#include "Game/UI/uiTexSlots.h"
#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Utils/StateMachine.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace ksys {
class SeadController;
}

namespace ksys::act {
class Actor;
}

namespace uking::ui {

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
    // 0x71010aa894 (declared only; 19 callers)
    void sub_71010AA894();
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
class Unk_7102474e38 {
public:
    SEAD_RTTI_BASE(Unk_7102474e38)
    virtual ~Unk_7102474e38();
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
    virtual void m15(eui::AnimButton* button);
    virtual void m16(eui::AnimButton* button);
    virtual void m17(eui::AnimButton* button);
    virtual void m18(eui::AnimButton* button);
    virtual void m19(eui::AnimButton* button);
    virtual void m20(eui::AnimButton* button);
    virtual void m21(eui::AnimButton* button);
    virtual void m22(eui::AnimButton* button);

    void sub_7100939EF8(eui::AnimButton* button);
    void sub_7100939F04(eui::AnimButton* button);
    void sub_7100939F10(eui::AnimButton* button);
    void sub_7100939F1C(eui::AnimButton* button);
    void sub_7100939F28(eui::AnimButton* button);
    void sub_7100939F34(eui::AnimButton* button);
    void sub_7100939F40(eui::AnimButton* button);
    void sub_7100939F4C(eui::AnimButton* button);

    // 0x7100939bd8 (C2) / 0x7100939c18 (C1): two identical copies in the original
    Unk_7102474e38();

    /* 0x08 */ u64 _8{};
    /* 0x10 */ u64 _10{};
    /* 0x18 */ u64 _18{};
    /* 0x20 */ u64 _20{};
    /* 0x28 */ u64 _28{};
    /* 0x30 */ s32 _30{};
    /* 0x34 */ sead::Vector2f _34 = sead::Vector2f::zero;
    /* 0x3c */ s32 _3c = -1;
    /* 0x40 */ s32 _40 = -1;
    /* 0x44 */ s32 _44 = -1;
};

// ScreenEx's helper at+0x330. The constructor0x92fc8c and destructor0x92fcb4 prove
// size0x38, heap+8, Screen*+0x10, config+0x18, buffer+0x20 and boolean+0x30.
class Unk_71024746b0 {
public:
    Unk_71024746b0();
    virtual ~Unk_71024746b0();

    void setHeap(sead::Heap* heap);
    void initialize(Screen* screen, eui::LayoutEx* layout, void* config);
    void update();

    /* 0x08 */ sead::Heap* mHeap;
    u8 _10[0x38 - 0x10];
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
    u8 _300[0x330 - 0x300];
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

    void sub_7100A31BE0();
};

class ScreenMessageTipsRunTime : public ScreenEx {
public:
    ScreenMessageTipsRunTime();
    ~ScreenMessageTipsRunTime() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m101() override;

    /* 0x3610 */ u64 _3610{};
    sead::CriticalSection _3618;
    s32 _3658 = -1;
    u8 _365c{};
    s32 _3660 = -1;
    u8 _3664{};
    u64 _3668{};
    u64 _3670{};
    f32 _3678 = 1.0f;
    u8 _367c{};
    u8 _367d[3];
    u8 _3680{};
    s32 _3684 = -1;

    void sub_7100A268AC(s32, s32);
};

class ScreenDoCommand : public ScreenEx {
public:
    ScreenDoCommand();
    void m101() override;
    ~ScreenDoCommand() override;
    SEAD_RTTI_OVERRIDE(ScreenDoCommand, ScreenEx)

    /* 0x3610 */ u8 _3610[0x28]{};
    sead::PtrArray<Unk_Elem> _3638{};
    sead::PtrArray<Unk_Elem> _3648{};
    s32 _3658 = -1;
    s32 _365c = -1;
    s64 _3660 = -1;

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

class ScreenMainScreen3D : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m84() override;
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    void m82() override;
    ~ScreenMainScreen3D() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen3D, ScreenEx)

    u8 _pad_3610[0x3f38 - 0x3610];
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

    u8 _pad_3610[0x3648 - 0x3610];
    /* 0x3648 */ ScreenMainScreenUnk3648* _3648;
    u8 _pad_3650[0x3658 - 0x3650];
    /* 0x3658 */ ScreenMainScreenUnk3658* _3658;
    u8 _pad_3660[0x3704 - 0x3660];
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
    // 0x7100a1a518 (CSV unnamed; declared only; the types are guesses)
    void sub_7100A1A518(s64 a1, bool a2);
    bool sub_7100A1E1E0();
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

    u8 _2fc[0x698 - 0x2fc];
    /* 0x698 */ sead::CriticalSection _698;
};

// The class of the three message dialog screens (ids ScreenId::Unk17, MessageDialog and Unk76; constructor
// 0x71010b25c8 takes a bool). Only the nominal type and the members read by the UI facade are recovered.
class ScreenMessageDialog : public Screen {
public:
    ~ScreenMessageDialog() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageDialog, Screen)
    // 0x71010b34d0
    const char* getLayoutName_() const override;

    u8 _2fc[0x350 - 0x2fc];
    /* 0x350 */ s32 _350;
    u8 _354[0x5ec - 0x354];
    /* 0x5ec */ s32 _5ec;
    u8 _5f0[0x720 - 0x5f0];
    /* 0x720 */ u64 _720;
    /* 0x728 */ ksys::act::BaseProcLink _728;
    /* 0x738 */ s32 _738;
    /* 0x73c */ s32 _73c;
    u8 _740[0x76a - 0x740];
    /* 0x76a */ bool _76a;
    u8 _76b[0x773 - 0x76b];
    /* 0x773 */ u8 _773;

    // 0x71010b343c / 0x71010b34b4 / 0x71010b34a0: called by UI::sub_71010A5C8C / setPlacedItemStockNum / sub_71010A7994.
    bool sub_71010B343C();
    void sub_71010B34B4(bool choice_mode, s32 stock);
    void sub_71010B34A0(bool a1);
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

class ScreenErrorViewer : public Screen {
public:
    ~ScreenErrorViewer() override;
    SEAD_RTTI_OVERRIDE(ScreenErrorViewer, Screen)
    bool isEnableControl() const override;
    // 0x710109ff58
    const char* getLayoutName_() const override;
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

    /* 0x2fc */ s32 _2fc;
    /* 0x300 */ s32 _300;
    /* 0x304 */ s32 _304;
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

class ScreenFadeDemo : public Screen {
public:
    ScreenFadeDemo();
    ~ScreenFadeDemo() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeDemo, Screen)
    // 0x71010a076c
    const char* getLayoutName_() const override;
    void m74(f32 progress) override;
    // 0x71010a01f8 (declaration only; lane3 s38): `_350 = value` then a tail call into 0x71010a0200.
    void sub_71010A01F8(s32 value);

    /* 0x300 */ void* _300{};
    /* 0x308 */ eui::AnimatorSet _308;
    /* 0x328 */ eui::AnimatorSet _328;
    /* 0x348 */ void* _348{};
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
};

class ScreenHomeNixSign : public Screen {
public:
    ScreenHomeNixSign();
    ~ScreenHomeNixSign() override;
    SEAD_RTTI_OVERRIDE(ScreenHomeNixSign, Screen)
    // 0x71010a2258
    const char* getLayoutName_() const override;

    /* 0x2fc */ s32 _2fc = 0;
};

class ScreenBoxCursorTV : public Screen {
public:
    ScreenBoxCursorTV();
    ~ScreenBoxCursorTV() override;
    SEAD_RTTI_OVERRIDE(ScreenBoxCursorTV, Screen)
    void m93(sead::Heap* heap) override;

    /* 0x300 */ eui::Animator* _300{};
};

class ScreenLoadSaveIcon : public Screen {
public:
    ScreenLoadSaveIcon();
    ~ScreenLoadSaveIcon() override;
    SEAD_RTTI_OVERRIDE(ScreenLoadSaveIcon, Screen)
    // 0x71010a4380
    const char* getLayoutName_() const override;

    /* 0x300 */ void* _300{};
    /* 0x308 */ void* _308{};
    /* 0x310 */ void* _310{};
    /* 0x318 */ u16 _318 = 0;
    /* 0x31a */ bool _31a = true;
    /* 0x31c */ u32 _31c = 0;
    /* 0x320 */ u32 _320 = 0;
    /* 0x324 */ u32 _324 = 0;
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

// inline-only in the original; name is a guess. The number screens compare state ids through the vtable (a call on a
// reference parameter is not devirtualized, a call on the static state object is).
inline bool isSameStateId(const ksys::StateBase& a, const ksys::StateBase& b) {
    return a.getId() == b.getId();
}

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
    void m96() override;
    void m104(eui::AnimButton*) override;
    void m107(eui::AnimButton*) override;
    bool isEnableControl() const override;
    ~ScreenShopHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenShopHorse, ScreenEx)
    void m99() override;
    u8 _pad_3610[0x36bc - 0x3610];
    s32 _36bc;

    void sub_7100A4EBA0(s32);
};

// State objects of ScreenMainShortCut (StateTemplate<...>; 0x71025ef170 / 0x71025ef290) and ScreenAppTool (0x71025ec670).
extern const ksys::StateBase sUnk_71025ef170;
extern const ksys::StateBase sUnk_71025ef1d0;
extern const ksys::StateBase sUnk_71025ef290;
extern const ksys::StateBase sUnk_71025ec670;

class ScreenMainShortCut : public ScreenEx {
public:
    void m96() override;
    void m99() override;
    bool isEnableControl() const override;
    ~ScreenMainShortCut() override;
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    u8 _pad_3610[0x3638 - 0x3610];
    nn::ui2d::ArchiveHandle _3638;
    sead::PtrArray<Unk_Elem> _36f0;
    /* 0x3700 */ sead::BitFlag8 _3700;
    u8 _pad_3701[0x3798 - 0x3701];
    /* 0x3798 */ eui::Animator* _3798;
    /* 0x37a0 */ eui::Animator* _37a0;
    u8 _pad_37a8[0x3850 - 0x37a8];
    sead::Buffer<u8> _3850;  // element type not known
    u8 _pad_3860[0x38cc - 0x3860];
    /* 0x38cc */ u8 _38cc;
    u8 _pad_38cd[3];
    UiTexSlots _38d0;

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

    bool sub_7100A20DD0();
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
    ~ScreenMiniGame() override;
    SEAD_RTTI_OVERRIDE(ScreenMiniGame, ScreenEx)
    void m100() override;

    /* 0x3610 */ eui::LayoutEx* _3610[7];
    /* 0x3648 */ eui::Animator* _3648;
    /* 0x3650 */ u16 _3650;  // bit n: minigame layout n is open
    u8 _pad_3652[0x3660 - 0x3652];
    /* 0x3660 */ u64 _3660;
    /* 0x3668 */ u8 _3668;
    u8 _pad_3669[0x366c - 0x3669];
    // The mini game's counters: a game data key (`_36x0`, set by the sub_7100A280A4 family from the caller's key), the
    // widget layout that shows the value and the last value read. Names / types are guesses from those functions.
    /* 0x366c */ s32 _366c;
    /* 0x3670 */ sead::SafeString _3670;
    u8 _pad_3680[0x3688 - 0x3680];
    /* 0x3688 */ eui::Animator* _3688;
    /* 0x3690 */ s32 _3690;
    /* 0x3698 */ sead::SafeString _3698;
    /* 0x36a8 */ f32 _36a8;
    /* 0x36b0 */ sead::SafeString _36b0;
    /* 0x36c0 */ s32 _36c0;
    /* 0x36c8 */ sead::SafeString _36c8;
    u8 _pad_36d8[0x36e0 - 0x36d8];
    /* 0x36e0 */ eui::Animator* _36e0;
    /* 0x36e8 */ eui::Animator* _36e8;

    void sub_7100A280A4(const sead::SafeString& a1);
    void sub_7100A2813C(const sead::SafeString& a1);
    void sub_7100A28264(const sead::SafeString& a1);
    void sub_7100A28318(const sead::SafeString& a1);
    void sub_7100A283B0(s32 a1);
    void sub_7100A28418(s32 a1);

    bool sub_7100A275EC(s32, s32);
    // 0x7100a2747c (CSV unnamed; declared only)
    bool sub_7100A2747C(s32 index, bool a2);
    void sub_7100A28088();
    bool openMinigameScreen(s32, s32);
};

// The state ScreenAppMap::mainRun changes to (0x71025df1e0; placeholder name).
extern const ksys::StateBase sUnk_71025df1e0;

// Placeholder for the map widget the AppMap screen owns (byte 0xb33a is set by ScreenAppMap::mainEnter).
struct ScreenAppMapWidget {
    // 0x71009a9438 (CSV unnamed; declared only)
    bool sub_71009A9438();
    u8 _0[0xb33a];
    /* 0xb33a */ u8 _b33a;
};

class ScreenAppMap : public ScreenEx {
public:
    void m92(sead::Heap*) override;
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
    u8 _3618[0x3ad1 - 0x3618];
    /* 0x3ad1 */ u8 _3ad1;
    /* 0x3ad2 */ u8 _3ad2;  // written by sub_71009EF4EC / sub_71009EF51C
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

    void m107(eui::AnimButton* button) override;
    u8 _pad_3610[0x3618 - 0x3610];
    /* 0x3618 */ s32 _3618;
    u8 _pad_361c[0x3bb4 - 0x361c];
    /* 0x3bb4 */ s32 _3bb4;

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
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppTool() override;
    SEAD_RTTI_OVERRIDE(ScreenAppTool, ScreenEx)

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
struct ScreenAppPictureBookUnk {
    // 0x710093f594 (CSV unnamed; not decompiled)
    void sub_710093F594(bool a1);
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
    void m94() override;
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenGamePadBG() override;
    SEAD_RTTI_OVERRIDE(ScreenGamePadBG, ScreenEx)

    /* 0x3610 */ u64 _3610{};
    u64 _3618{};
    u8 _3620[14]{};
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
    void m100() override;
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
    // Placeholder: the object `_3610` points to (only the s32 at 0x30c is used).
    struct Unk3610 {
        u8 _0[0x30c];
        s32 _30c;
    };
    /* 0x3610 */ Unk3610* _3610{};
    void m93(sead::Heap* heap) override;
    /* 0x3618 */ eui::Animator* _3618{};
    /* 0x3620 */ eui::Animator* _3620{};
    /* 0x3628 */ u8 _3628{};
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList5, ScreenEx)
    void m94() override;
    void m98() override;
    void m100() override;
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
};

class ScreenSeekPadMenuBG : public ScreenEx {
public:
    void m82() override;
    void m83() override;
    const char* getLayoutName_() const override;
    ScreenSeekPadMenuBG();
    ~ScreenSeekPadMenuBG() override;
    void m93(sead::Heap* heap) override;
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
    void m99() override;
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
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
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
    // The icon holder at ScreenSkip + 0x3610 (placeholder; only the pointer at +0x20 is used).
    struct IconHolder {
        u8 _0[0x20];
        void* _20;
    };

    // 0x7100a537f8: opens the screen and switches the skip icon (10 with the button, 8 without).
    void sub_7100A537F8(bool with_button);
    ScreenSkip();
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    bool isEnableControl() const override;
    ~ScreenSkip() override;
    SEAD_RTTI_OVERRIDE(ScreenSkip, ScreenEx)

    /* 0x3610 */ IconHolder* _3610{};
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
    eui::Animator* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenChangeController, ScreenEx)
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
    ~ScreenShopBtnList20() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList20, ScreenEx)
    void m102(eui::AnimButton*) override;
    void m107(eui::AnimButton* button) override;
    u8 _pad_3610[0x3868 - 0x3610];
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
    /* 0x3610 */ eui::LayoutEx* _3610{};
    /* 0x3618 */ sead::FixedSafeString<256> _3618;
    /* 0x3730 */ sead::FixedSafeString<256> _3730;
    /* 0x3848 */ u64 _3848{};
    u64 _3850{};
    f32 _3858 = 1.0f;
    u8 _385c{};
    u8 _385d[3];
    u8 _3860{};
    u8 _3861[7];
    eui::Animator* _3868{};
    eui::Animator* _3870{};
};

struct ScreenAppPictureBookUnk;

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

class ScreenDLCWindow : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenDLCWindow() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDLCWindow, ScreenEx)
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;

    // 0x7102486d48 (placeholder name): the window's result (0: no, 1: yes, 2: none yet)
    static s32 sResult;
};

class ScreenTitle : public ScreenEx {
public:
    ScreenTitle();
    s32 m141(const ksys::Message& message) override;
    s32 m142(const ksys::Message& message) override;
    void m96() override;
    bool isEnableControl() const override;
    ~ScreenTitle() override;
    SEAD_RTTI_OVERRIDE(ScreenTitle, ScreenEx)

    /* 0x3610 */ u64 _3610;  // zeroed in the constructor body
    u64 _3618;
    u64 _3620;
    u64 _3628;
    u64 _3630;
    /* 0x3638 */ s32 _3638 = 0;
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
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenEnergyMeterDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenEnergyMeterDLC, ScreenEx)
};

class ScreenMessageGet : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMessageGet() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageGet, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    void m99() override;

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
};

class ScreenShopBtnList15 : public ScreenEx {
public:
    ScreenShopBtnList15();
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenShopBtnList15() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList15, ScreenEx)
    void m100() override;
    void m106(eui::AnimButton* button) override;
    void m107(eui::AnimButton* button) override;

    UiTexSlots _3610;
};

class ScreenShopInfo : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m96() override;
    ~ScreenShopInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenShopInfo, ScreenEx)
    eui::TagProcessor* doCreateTagProcessor_(sead::Heap* heap) override;

    u8 _pad_3610[0x3658 - 0x3610];
    sead::PtrArray<Unk_Elem> _3658;
    u8 _pad_3668[0x3678 - 0x3668];
    Unk_710247dc70 _3678;
    u8 _pad_3680[0x3698 - 0x3680];
    UiTexSlots _3698;
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
    ~ScreenPickUp() override;
    SEAD_RTTI_OVERRIDE(ScreenPickUp, ScreenEx)

    // 0x7100a3f3f4 (CSV ScreenPickUp::setItemAndOpen): opens the screen (option 3); with `show` it also shows the item
    // for 5 seconds (the argument type is a guess)
    void setItemAndOpen(const sead::SafeString& item, bool show);
    // 0x7100a3f450 (CSV unnamed; not decompiled)
    void sub_7100A3F450(const sead::SafeString& item, f32 time);
};

class ScreenAppHome : public ScreenEx {
public:
    bool isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppHome() override;
    SEAD_RTTI_OVERRIDE(ScreenAppHome, ScreenEx)
};

// The state ScreenSaveTransferWindow changes to from many of its state callbacks (0x71025f2de0; placeholder name).
extern const ksys::StateBase sUnk_71025f2de0;
extern const ksys::StateBase sUnk_71025f1fa0;
extern const ksys::StateBase sUnk_71025f2000;
extern const ksys::StateBase sUnk_71025f2240;
extern const ksys::StateBase sUnk_71025f23c0;
extern const ksys::StateBase sUnk_71025f2480;
extern const ksys::StateBase sUnk_71025f2d20;
extern const ksys::StateBase sUnk_71025f2d80;

class ScreenSaveTransferWindow : public ScreenEx {
public:
    void m98() override;
    void m106(eui::AnimButton* button) override;
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
    u8 _pad_3630[0x3698 - 0x3630];
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
    eui::ControlBase* _3698{};
    eui::ControlBase* _36a0{};
    eui::ControlBase* _36a8{};
    eui::ControlBase* _36b0{};
    eui::ControlBase* _36b8{};
};

class ScreenStaffRoll : public ScreenEx {
public:
    ~ScreenStaffRoll() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRoll, ScreenEx)
};

class ScreenStaffRollDLC : public ScreenEx {
public:
    bool isEnableControl() const override;
    ~ScreenStaffRollDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRollDLC, ScreenEx)
};

class ScreenKeyBoradTextArea : public ScreenEx {
public:
    ScreenKeyBoradTextArea();
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

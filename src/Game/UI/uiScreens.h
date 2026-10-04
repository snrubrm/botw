#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/UI/euiControlBase.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiArchiveHandle.h"
#include "Game/UI/uiTexSlots.h"
#include "Game/UI/uiUnkTiny.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Utils/StateMachine.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"

namespace uking::ui {

// The game's UI screen classes (CSV: ScreenBase / Screen / ScreenEx / Screen<Name>, IDA placeholder
// names; the namespace is a guess). The chain eui::Screen <- ScreenBase <- Screen <- ScreenEx <-
// Screen<Name> is established by the RTTI (the leaf classes' checkDerivedRuntimeTypeInfo compares
// against four typeinfo statics and their Derive<> typeinfo is Derive<ScreenEx>). The layouts are
// not modelled yet: only what the facade functions in uiScreenFacade.cpp use is declared.

class ScreenBase : public eui::Screen {
public:
    ~ScreenBase() override;
    SEAD_RTTI_OVERRIDE(ScreenBase, eui::Screen)

    // 0x71010a9f44 (CSV ScreenBase::getAnimationStep_)
    f32 getAnimationStep_() const override;
    const char* getArchiveName_() const override;

    // 0x71010a9da0 (CSV ScreenBase::updateButton_; the game's Screen overrides it again and forwards to this one)
    void updateButton_() override;
};

// Screen's second and third bases (offsets 0x108 / 0x110: the RxOnly / TxOnly message handler interfaces,
// see the vtable at +0x508 / +0x530 of the leaf classes' vtables).
// Implements RxOnly::IHandler::handleMessage for all screens (the original's ScreenEx::handleMessage at
// 0x7100a48728; declared in this intermediate class because an override declared in ScreenEx would add a slot
// to ScreenEx's primary vtable).
class ScreenHandlerImpl : public ksys::ActorMessageTransceiver::IHandler {
public:
    int handleMessage(const ksys::Message& message) override;
};

// Base class of the screens' child components (elements of Screen::mChildren at 0x250; the 24 classes with a
// 105-slot vtable derive from it). Slots 43-52 etc. are the ones Screen::m117 - m126 call. The first slots belong to
// eui::ControlBase in the original (0 / 4); slots 2 / 3 are the destructor. Most default implementations are empty or
// forward to another slot of the same object (the argument types of the forwarded slots are unknown).
class ScreenChild {
public:
    virtual const char* m0();
    virtual void m1();
    virtual ~ScreenChild();
    virtual void m4();
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

class Screen : public ScreenBase, public ScreenHandlerImpl {
public:
    ~Screen() override;
    SEAD_RTTI_OVERRIDE(Screen, ScreenBase)
    u8 _118[0x160 - 0x118];
    // The screen's state machine (the leaf classes' own virtual slots 154+ are the callbacks of its states). The
    // union keeps the implicit constructor from requiring StateMachine's (the constructor is not decompiled).
    union {
        ksys::StateMachine mStateMachine;
    };
    u8 _188[0x250 - 0x188];
    /* 0x250 */ sead::PtrArray<ScreenChild> mChildren;
    u8 _260[0x270 - 0x260];
    /* 0x270 */ s32 _270;
    u8 _274[0x288 - 0x274];
    /* 0x288 */ void* _288;
    /* 0x290 */ u8 _290;
    u8 _291;
    /* 0x292 */ u16 _292;
    u8 _294[0x300 - 0x294];

    void open(s32 option) override;

    // Overrides of the eui::Screen callbacks (not decompiled yet; CSV Screen::doAfterBuildLayout etc.)
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

    // New virtual slots of Screen (CSV Screen::mNN; the number is the vtable slot, 69-126). Only the trivial
    // ones have known signatures.
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual s32 m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
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
    virtual void m92();
    virtual void m93();
    virtual void m94();
    virtual void m95();
    virtual void m96();  // open(1)
    virtual void m97();  // close(-1)
    virtual void m98();
    virtual void m99();
    virtual void m100();
    virtual void m101();
    virtual void m102();
    virtual void m103();
    virtual void m104();
    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual void m108();
    virtual void m109();
    virtual void m110();
    virtual s32 m111();
    virtual void m112();
    virtual void m113();
    virtual void m114();
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

class ScreenEx : public Screen {
public:
    ScreenEx();
    ~ScreenEx() override;
    SEAD_RTTI_OVERRIDE(ScreenEx, Screen)

    // Overrides of the eui::Screen button callbacks (not decompiled yet; CSV ScreenEx::doButton*)
    void doButtonOnStart_(eui::AnimButton* button) override;
    void doButtonOnEnd_(eui::AnimButton* button) override;
    void doButtonOffStart_(eui::AnimButton* button) override;
    void doButtonOffEnd_(eui::AnimButton* button) override;
    void doButtonDownStart_(eui::AnimButton* button) override;
    void doButtonDownEnd_(eui::AnimButton* button) override;
    void doButtonCancelStart_(eui::AnimButton* button) override;
    void doButtonCancelEnd_(eui::AnimButton* button) override;

    // Placeholder for the real data (0x300 ...; the leaf classes' members start at 0x3610).
    u8 _300[0x3610 - 0x300];

    // New virtual slots of ScreenEx (CSV ScreenEx::mNN, 127-153). Only the trivial ones have known signatures.
    virtual void m127();
    virtual void m128();
    virtual void m129();
    virtual void m130();
    virtual void m131();
    virtual void m132();
    virtual void m133();
    virtual void m134();
    virtual void m135();
    virtual void m136();
    virtual void m137();
    virtual void m138();
    virtual void m139();
    virtual void m140();
    virtual s32 m141();
    virtual s32 m142();
    virtual void* m143();
    virtual void m144();
    virtual void m145();
    virtual void m146();
    virtual void m147();
    virtual void m148();
    virtual void m149();
    virtual void m150();
    virtual void m151();
    virtual void m152();
    virtual void m153();
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

    void sub_7100A31BE0();
};

class ScreenMessageTipsRunTime : public ScreenEx {
public:
    ScreenMessageTipsRunTime();
    ~ScreenMessageTipsRunTime() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)

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

class ScreenMainScreen3D : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m84() override;
    s32 m141() override;
    s32 m142() override;
    void m82() override;
    ~ScreenMainScreen3D() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen3D, ScreenEx)

    u8 _pad_3610[0x3f38 - 0x3610];
    /* 0x3f38 */ u8 _3f38;

    void sub_7100A115E4(s64);
    bool sub_7100A11B10(s64);
    bool sub_7100A11D34(s32);
};

class ScreenMainScreen : public ScreenEx {
public:
    void m88() override;
    s32 isEnableControl() const override;
    ~ScreenMainScreen() override;
    SEAD_RTTI_OVERRIDE(ScreenMainScreen, ScreenEx)

    u8 _pad_3610[0x3704 - 0x3610];
    /* 0x3704 */ s32 _3704;

    bool sub_7100A1A1C4(s32 a1, bool a2);
    void sub_7100A1AB58(s32 a1);
    // 0x7100a1ab74 (CSV ScreenMainScreen::showInfoOverlayWithString)
    void showInfoOverlayWithString(s32 type, const sead::SafeString& text);

    void sub_7100A1A4E4(s64);
    bool sub_7100A1E1E0();
};

class ScreenGameOver : public ScreenEx {
public:
    ScreenGameOver();
    s32 isEnableControl() const override;
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
    u64 _3618{};
    u64 _3620{};

    bool sub_7100A0A8D8();
    bool sub_7100A0A914();
};

class ScreenRupee : public ScreenEx {
public:
    ScreenRupee();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenRupee() override;
    SEAD_RTTI_OVERRIDE(ScreenRupee, ScreenEx)

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
    s32 _361c{};
    s32 _3620{};
    s32 _3624{};
    s32 _3628{};
    f32 _362c = 1.0f;
    u8 _3630{};
    s32 _3634 = 4;
    Unk_7102474b78 _3638;
    Unk_7102474b58 _3678{this};
    sead::CriticalSection _36d0;

    void sub_7100A410D8(s32);
    void sub_7100A41558();
    bool sub_7100A41440();
    bool sub_7100A41354(s32);
    void sub_7100A414A0();
};

// State object of the number screens (CSV: unnamed data; a StateTemplate<ScreenKologNum>, 0x71025eed10).
extern const ksys::StateBase sUnk_71025eed10;

class ScreenKologNum : public ScreenEx {
public:
    ScreenKologNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenKologNum() override;
    SEAD_RTTI_OVERRIDE(ScreenKologNum, ScreenEx)

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
    s32 _361c{};
    s32 _3620{};
    s32 _3624{};
    s32 _3628{};
    f32 _362c = 1.0f;
    u8 _3630{};
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

class ScreenAkashNum : public ScreenEx {
public:
    ScreenAkashNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenAkashNum() override;
    SEAD_RTTI_OVERRIDE(ScreenAkashNum, ScreenEx)

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
    s32 _361c{};
    s32 _3620{};
    s32 _3624{};
    s32 _3628{};
    f32 _362c = 1.0f;
    u8 _3630{};
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
extern const ksys::StateBase sUnk_71025ef518;

class ScreenMamoNum : public ScreenEx {
public:
    ScreenMamoNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenMamoNum() override;
    SEAD_RTTI_OVERRIDE(ScreenMamoNum, ScreenEx)

    /* 0x3610 */ s32 _3610{};
    s32 _3614{};
    s32 _3618{};
    s32 _361c{};
    s32 _3620{};
    s32 _3624{};
    f32 _3628 = 1.0f;
    u8 _362c{};
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
    void m104() override;
    void m107() override;
    s32 isEnableControl() const override;
    ~ScreenShopHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenShopHorse, ScreenEx)

    void sub_7100A4EBA0(s32);
};

class ScreenMainShortCut : public ScreenEx {
public:
    void m96() override;
    s32 isEnableControl() const override;
    ~ScreenMainShortCut() override;
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)

    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    u8 _pad_3610[0x3638 - 0x3610];
    nn::ui2d::ArchiveHandle _3638;
    sead::PtrArray<Unk_Elem> _36f0;
    u8 _pad_3700[0x3850 - 0x3700];
    sead::Buffer<u8> _3850;  // element type not known
    u8 _pad_3860[0x38d0 - 0x3860];
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
};

class ScreenReadyGo : public ScreenEx {
public:
    ScreenReadyGo();
    ~ScreenReadyGo() override;
    SEAD_RTTI_OVERRIDE(ScreenReadyGo, ScreenEx)

    bool sub_7100A40BF8();
};

class ScreenMiniGame : public ScreenEx {
public:
    ~ScreenMiniGame() override;
    SEAD_RTTI_OVERRIDE(ScreenMiniGame, ScreenEx)

    u8 _pad_3610[0x3660 - 0x3610];
    /* 0x3660 */ u64 _3660;
    /* 0x3668 */ u8 _3668;

    void sub_7100A280A4(const sead::SafeString& a1);
    void sub_7100A2813C(const sead::SafeString& a1);
    void sub_7100A28264(const sead::SafeString& a1);
    void sub_7100A28318(const sead::SafeString& a1);
    void sub_7100A283B0(s32 a1);
    void sub_7100A28418(s32 a1);

    bool sub_7100A275EC(s32, s32);
    void sub_7100A28088();
    bool openMinigameScreen(s32, s32);
};

// Placeholder for the map widget the AppMap screen owns (byte 0xb33a is set by ScreenAppMap::mainEnter).
struct ScreenAppMapWidget {
    u8 _0[0xb33a];
    /* 0xb33a */ u8 _b33a;
};

class ScreenAppMap : public ScreenEx {
public:
    void m92() override;
    s32 isEnableControl() const override;
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
};

class ScreenPauseMenu : public ScreenEx {
public:
    s32 m72() override;
    void m69() override;
    void m70() override;
    void m71() override;
    void m96() override;
    s32 isEnableControl() const override;
    ~ScreenPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)

    u8 _pad_3610[0x3bb4 - 0x3610];
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
    s32 isEnableControl() const override;
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

class ScreenAppPictureBook : public ScreenEx {
public:
    void m106() override;
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppPictureBook() override;
    SEAD_RTTI_OVERRIDE(ScreenAppPictureBook, ScreenEx)

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

    void sub_71009F8510(s32);
};

class ScreenDLCSinJuAkashiNum : public ScreenEx {
public:
    ScreenDLCSinJuAkashiNum();
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenDLCSinJuAkashiNum() override;
    SEAD_RTTI_OVERRIDE(ScreenDLCSinJuAkashiNum, ScreenEx)

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
    s32 _361c{};
    s32 _3620{};
    s32 _3624{};
    s32 _3628{};
    s32 _362c{};
    f32 _3630 = 1.0f;
    u8 _3634{};
    /* 0x3638 */ s32 _3638 = -1;
    Unk_7102474b78 _3640;
    u64 _3680{};
    /* 0x3688 */ s32 _3688{};
};

// ScreenHardMode: only the trivial virtual slots of the 154-245 block (the per-state callbacks, four
// slots per state; slot 4 overrides eui::Screen's) are declared. INCOMPLETE (see Screen).
class ScreenHardMode : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ~ScreenHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenHardMode, ScreenEx)

    s32 isEnableControl() const override;

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

    u8 _3610[0x3704 - 0x3610];
    /* 0x3704 */ s32 _3704;
    u8 _3708[0x3718 - 0x3708];
    /* 0x3718 */ s32 _3718;
};

// Screens without members of their own that are modelled yet: only the (trivial, tail-calling)
// destructor and the RTTI.
class ScreenGamePadBG : public ScreenEx {
public:
    ScreenGamePadBG();
    void m82() override;
    void m94() override;
    s32 isEnableControl() const override;
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
    void* _3610{};
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
    /* 0x3610 */ u32 _3610{};
    u8 _pad_3614[0x3618 - 0x3614];
    /* 0x3618 */ void* _3618{};
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
    void m93() override;
    ScreenDemoName();
    ~ScreenDemoName() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDemoName, ScreenEx)
};

class ScreenDemoNameEnemy : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    void m93() override;
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
    s32 isEnableControl() const override;
    ScreenShopBtnList5();
    ~ScreenShopBtnList5() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
    /* 0x3620 */ void* _3620{};
    /* 0x3628 */ u8 _3628{};
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList5, ScreenEx)
};

class ScreenPauseMenuBG : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m82() override;
    void m83() override;
    ScreenPauseMenuBG();
    ~ScreenPauseMenuBG() override;
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
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenSeekPadMenuBG, ScreenEx)
};

class ScreenMainScreenMS : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenMainScreenMS();
    ~ScreenMainScreenMS() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
    /* 0x3620 */ void* _3620{};
    /* 0x3628 */ void* _3628{};
    /* 0x3630 */ u8 _3630{};
    SEAD_RTTI_OVERRIDE(ScreenMainScreenMS, ScreenEx)
};

class ScreenMainScreenHeartIchigekiDLC : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenMainScreenHeartIchigekiDLC();
    ~ScreenMainScreenHeartIchigekiDLC() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
    /* 0x3620 */ void* _3620{};
    /* 0x3628 */ u8 _3628{};
    SEAD_RTTI_OVERRIDE(ScreenMainScreenHeartIchigekiDLC, ScreenEx)
};

class ScreenAppSystemWindowNoBtn : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenAppSystemWindowNoBtn();
    ~ScreenAppSystemWindowNoBtn() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u32 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindowNoBtn, ScreenEx)
};

class ScreenMessageTipsPauseMenu : public ScreenEx {
public:
    ScreenMessageTipsPauseMenu();
    const char* getLayoutName_() const override;
    ~ScreenMessageTipsPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsPauseMenu, ScreenEx)

    /* 0x3610 */ s32 _3610 = 2;
    s32 _3614{};
    s32 _3618{};
    s32 _361c{};
    s32 _3620{};
    f32 _3624 = 1.0f;
    u8 _3628{};
    u8 _3629[3];
    u8 _362c{};
    u8 _362d[3];
};

class ScreenAmiiboWindow : public ScreenEx {
public:
    ScreenAmiiboWindow();
    const char* getLayoutName_() const override;
    s32 isEnableControl() const override;
    ~ScreenAmiiboWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAmiiboWindow, ScreenEx)

    /* 0x3610 */ s32 _3610 = 4;
    s32 _3614 = 3;
    u8 _3618[0x74]{};
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
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
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
    s32 isEnableControl() const override;
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
    s32 isEnableControl() const override;
    ~ScreenPauseMenuMantan() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuMantan, ScreenEx)

};

class ScreenPauseMenuEiketsu : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m107() override;
    s32 isEnableControl() const override;
    ScreenPauseMenuEiketsu();
    ~ScreenPauseMenuEiketsu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuEiketsu, ScreenEx)
};

class ScreenAppSystemWindow : public ScreenEx {
public:
    ScreenAppSystemWindow();
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    s32 m81() override;
    s32 m141() override;
    s32 m142() override;
    s32 isEnableControl() const override;
    ~ScreenAppSystemWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindow, ScreenEx)

    /* 0x3610 */ s32 _3610 = 10;
    s32 _3614;
    u64 _3618{};
    u64 _3620{};
    u64 _3628{};
    u64 _3630{};
    u64 _3638{};
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
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u32 _3618{};
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
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMainHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHardMode, ScreenEx)

    /* 0x3610 */ u64 _3610{};
    u64 _3618{};
    f32 _3620 = 1.0f;
    u8 _3624{};
    u8 _3625[3];
    u8 _3628{};
    u8 _3629[7];
};

class ScreenSkip : public ScreenEx {
public:
    ScreenSkip();
    const char* getLayoutName_() const override;
    bool isPlayPartsInOut_() const override;
    s32 isEnableControl() const override;
    ~ScreenSkip() override;
    SEAD_RTTI_OVERRIDE(ScreenSkip, ScreenEx)

    /* 0x3610 */ u64 _3610{};
    s32 _3618 = 30;
    s32 _361c;
};

class ScreenChangeController : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenChangeController();
    ~ScreenChangeController() override;
    void* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenChangeController, ScreenEx)
};

class ScreenDemoStart : public ScreenEx {
public:
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ScreenDemoStart();
    ~ScreenDemoStart() override;
    void* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenDemoStart, ScreenEx)
};

class ScreenBootUp : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    ScreenBootUp();
    ~ScreenBootUp() override;
    SEAD_RTTI_OVERRIDE(ScreenBootUp, ScreenEx)
};

class ScreenAppMenuBtn : public ScreenEx {
public:
    s32 m81() override;
    void m94() override;
    void m98() override;
    s32 isEnableControl() const override;
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
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenHomeMenuCapture, ScreenEx)
};

class ScreenShopBtnList20 : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    s32 isEnableControl() const override;
    ~ScreenShopBtnList20() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList20, ScreenEx)
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

    /* 0x3610 */ u64 _3610{};
    /* 0x3618 */ sead::FixedSafeString<256> _3618;
    /* 0x3730 */ sead::FixedSafeString<256> _3730;
    /* 0x3848 */ u64 _3848{};
    u64 _3850{};
    f32 _3858 = 1.0f;
    u8 _385c{};
    u8 _385d[3];
    u8 _3860{};
    u8 _3861[7];
    u64 _3868{};
    u64 _3870{};
};

class ScreenControllerWindow : public ScreenEx {
public:
    void m101() override;
    void m106() override;
    void m107() override;
    void m138() override;
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenControllerWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenControllerWindow, ScreenEx)
};

class ScreenDLCWindow : public ScreenEx {
public:
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenDLCWindow() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDLCWindow, ScreenEx)
};

class ScreenTitle : public ScreenEx {
public:
    ScreenTitle();
    s32 m141() override;
    s32 m142() override;
    void m96() override;
    s32 isEnableControl() const override;
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

class ScreenAppCamera : public ScreenEx {
public:
    void m127() override;
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppCamera() override;
    SEAD_RTTI_OVERRIDE(ScreenAppCamera, ScreenEx)

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
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenEnergyMeterDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenEnergyMeterDLC, ScreenEx)
};

class ScreenMessageGet : public ScreenEx {
public:
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenMessageGet() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageGet, ScreenEx)

    u8 _pad_3610[0x3658 - 0x3610];
    /* 0x3658 */ eui::ControlBase* _3658;
    u8 _pad_3660[0x3670 - 0x3660];
    Unk_710247adc8 _3670[2];
    u8 _pad_36f0[0x37d8 - 0x36f0];
    /* 0x37d8 */ sead::Buffer<Unk_7102474ba8> _37d8;
};

class ScreenSousaGuide : public ScreenEx {
public:
    ~ScreenSousaGuide() override;
    SEAD_RTTI_OVERRIDE(ScreenSousaGuide, ScreenEx)

    u8 _pad_3610[0x3618 - 0x3610];
    Unk_7102474bc8 _3618;
};

class ScreenShopBtnList15 : public ScreenEx {
public:
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenShopBtnList15() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList15, ScreenEx)

    UiTexSlots _3610;
};

class ScreenShopInfo : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m96() override;
    ~ScreenShopInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenShopInfo, ScreenEx)

    u8 _pad_3610[0x3658 - 0x3610];
    sead::PtrArray<Unk_Elem> _3658;
    u8 _pad_3668[0x3678 - 0x3668];
    Unk_710247dc70 _3678;
    u8 _pad_3680[0x3698 - 0x3680];
    UiTexSlots _3698;
};

class ScreenAppAlbum : public ScreenEx {
public:
    s32 isEnableControl() const override;
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
    s32 isEnableControl() const override;
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
};

class ScreenAppHome : public ScreenEx {
public:
    s32 isEnableControl() const override;
    const char* getLayoutName_() const override;
    ~ScreenAppHome() override;
    SEAD_RTTI_OVERRIDE(ScreenAppHome, ScreenEx)
};

class ScreenSaveTransferWindow : public ScreenEx {
public:
    void m98() override;
    s32 isEnableControl() const override;
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

};

class ScreenOptionWindow : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    s32 isEnableControl() const override;
    ~ScreenOptionWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenOptionWindow, ScreenEx)

    /* 0x3610 */ Unk_7102474df8 _3610;
    u8 _pad_3630[0x3698 - 0x3630];
    /* 0x3698 */ sead::PtrArray<Unk_OptionWindowEntry> _3698;
};

class ScreenSystemWindow01 : public ScreenEx {
public:
    const char* getLayoutName_() const override;
    void m96() override;
    void m97() override;
    void m101() override;
    s32 isEnableControl() const override;
    ~ScreenSystemWindow01() override;
    SEAD_RTTI_OVERRIDE(ScreenSystemWindow01, ScreenEx)
    // own virtual slots (state callbacks; groups of four: void, void, void, s32 -- the types are guesses from the trivial ones)
    virtual void m154();

};

class ScreenPauseMenuRecipe : public ScreenEx {
public:
    ScreenPauseMenuRecipe();
    const char* getLayoutName_() const override;
    s32 isEnableControl() const override;
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
    s32 isEnableControl() const override;
    ~ScreenStaffRollDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRollDLC, ScreenEx)
};

class ScreenKeyBoradTextArea : public ScreenEx {
public:
    ScreenKeyBoradTextArea();
    const char* getLayoutName_() const override;
    s32 m141() override;
    s32 m142() override;
    void m93() override;
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
    bool isPlayPartsInOut_() const override;
    ~ScreenFadeStatus() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeStatus, ScreenEx)

    u8 _pad_3610[0x3658 - 0x3610];
    /* 0x3658 */ sead::Buffer<u8*> _3658;
    /* 0x3668 */ sead::Buffer<u8*> _3668;
};

}  // namespace uking::ui

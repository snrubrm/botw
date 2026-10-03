#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiScreen.h"
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

class Screen : public ScreenBase, public ScreenHandlerImpl {
public:
    ~Screen() override;
    SEAD_RTTI_OVERRIDE(Screen, ScreenBase)
    u8 _118[0x270 - 0x118];
    /* 0x270 */ s32 _270;
    u8 _274[0x288 - 0x274];
    /* 0x288 */ void* _288;
    /* 0x290 */ u8 _290;
    u8 _291;
    /* 0x292 */ u16 _292;
    u8 _294[0x300 - 0x294];

    void m51() override;
    void m59() override;

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
    virtual void m111();
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
    ~ScreenMessageTipsRunTime() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)

    void sub_7100A268AC(s32, s32);
};

class ScreenDoCommand : public ScreenEx {
public:
    void m101() override;
    ~ScreenDoCommand() override;
    SEAD_RTTI_OVERRIDE(ScreenDoCommand, ScreenEx)

    // 0x7100a0768c (CSV ScreenDoCommand::setCommand)
    bool setCommand(s32 command);

    void sub_7100A0772C(s32);
};

class ScreenMainScreen3D : public ScreenEx {
public:
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
    s32 m4() override;
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
    s32 m4() override;
    ~ScreenGameOver() override;
    SEAD_RTTI_OVERRIDE(ScreenGameOver, ScreenEx)

    /* 0x3610 */ u8 _3610;
    u8 _pad_3611[3];
    /* 0x3614 */ s32 _3614;

    bool sub_7100A0A8D8();
    bool sub_7100A0A914();
};

class ScreenRupee : public ScreenEx {
public:
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenRupee() override;
    SEAD_RTTI_OVERRIDE(ScreenRupee, ScreenEx)

    void sub_7100A410D8(s32);
    void sub_7100A41558();
    bool sub_7100A41440();
    bool sub_7100A41354(s32);
    void sub_7100A414A0();
};

class ScreenKologNum : public ScreenEx {
public:
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenKologNum() override;
    SEAD_RTTI_OVERRIDE(ScreenKologNum, ScreenEx)

    u8 _pad_3610[0x3634 - 0x3610];
    /* 0x3634 */ s32 _3634;

    void sub_7100A0EF5C(s32 a1);

    void sub_7100A0F098();
    bool sub_7100A0F038();
    bool sub_7100A0EFA4();
    void sub_7100A0F110(s32);
};

class ScreenAkashNum : public ScreenEx {
public:
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenAkashNum() override;
    SEAD_RTTI_OVERRIDE(ScreenAkashNum, ScreenEx)

    u8 _pad_3610[0x3634 - 0x3610];
    /* 0x3634 */ s32 _3634;

    void sub_71009CEEE0(s32 a1);

    void sub_71009CF058();
    bool sub_71009CEFBC();
    bool sub_71009CEF28();
    void sub_71009CF01C(s32);
};

class ScreenMamoNum : public ScreenEx {
public:
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenMamoNum() override;
    SEAD_RTTI_OVERRIDE(ScreenMamoNum, ScreenEx)

    void sub_7100A22A80(s32 a1);

    void sub_7100A22B98();
};

class ScreenShopHorse : public ScreenEx {
public:
    void m96() override;
    void m104() override;
    void m107() override;
    s32 m4() override;
    ~ScreenShopHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenShopHorse, ScreenEx)

    void sub_7100A4EBA0(s32);
};

class ScreenMainShortCut : public ScreenEx {
public:
    void m96() override;
    s32 m4() override;
    ~ScreenMainShortCut() override;
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)

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

class ScreenAppMap : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenAppMap() override;
    SEAD_RTTI_OVERRIDE(ScreenAppMap, ScreenEx)

    void sub_71009EF488(const sead::Vector3f* a1, s32 a2);
    void sub_71009EF51C(s32 a1);
    void sub_71009EF4EC(s32 a1, s32 a2);
    void sub_71009EF57C(f32 a1, s32 a2);

    bool sub_71009EF5A8(s32);
    bool sub_71009E9F10();
};

class ScreenPauseMenu : public ScreenEx {
public:
    s32 m72() override;
    void m69() override;
    void m70() override;
    void m71() override;
    void m96() override;
    s32 m4() override;
    ~ScreenPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)

    void sub_7100A34A04();

    bool sub_7100A34A10();
    bool sub_7100A349F4();
};

class ScreenAppTool : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenAppTool() override;
    SEAD_RTTI_OVERRIDE(ScreenAppTool, ScreenEx)

    bool sub_71009FD674();
};

class ScreenAppPictureBook : public ScreenEx {
public:
    void m106() override;
    s32 m4() override;
    const char* m15() const override;
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
    s32 m72() override;
    void m70() override;
    void m71() override;
    ~ScreenDLCSinJuAkashiNum() override;
    SEAD_RTTI_OVERRIDE(ScreenDLCSinJuAkashiNum, ScreenEx)

    u8 _pad_3610[0x3638 - 0x3610];
    /* 0x3638 */ s32 _3638;
    u8 _pad_363c[0x3688 - 0x363c];
    /* 0x3688 */ s32 _3688;
};

// ScreenHardMode: only the trivial virtual slots of the 154-245 block (the per-state callbacks, four
// slots per state; slot 4 overrides eui::Screen's) are declared. INCOMPLETE (see Screen).
class ScreenHardMode : public ScreenEx {
public:
    const char* m15() const override;
    ~ScreenHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenHardMode, ScreenEx)

    virtual void m156();
    virtual void m160();
    virtual void m164();
    virtual void m168();
    virtual void m172();
    virtual void m176();
    virtual void m180();
    virtual void m184();
    virtual void m188();
    virtual void m192();
    virtual void m196();
    virtual void m200();
    virtual void m204();
    virtual void m208();
    virtual void m211();
    virtual void m212();
    virtual void m216();
    virtual void m220();
    virtual void m224();
    virtual void m228();
    virtual void m232();
    virtual void m235();
    virtual void m236();
    virtual void m240();
    virtual void m242();
    virtual void m243();
    virtual void m244();
    virtual s32 m4();
    virtual s32 m157();
    virtual s32 m161();
    virtual s32 m165();
    virtual s32 m169();
    virtual s32 m173();
    virtual s32 m177();
    virtual s32 m181();
    virtual s32 m185();
    virtual s32 m189();
    virtual s32 m193();
    virtual s32 m197();
    virtual s32 m201();
    virtual s32 m205();
    virtual s32 m209();
    virtual s32 m213();
    virtual s32 m217();
    virtual s32 m221();
    virtual s32 m225();
    virtual s32 m229();
    virtual s32 m233();
    virtual s32 m237();
    virtual s32 m241();
    virtual s32 m245();
};

// Screens without members of their own that are modelled yet: only the (trivial, tail-calling)
// destructor and the RTTI.
class ScreenGamePadBG : public ScreenEx {
public:
    void m82() override;
    void m94() override;
    s32 m4() override;
    const char* m15() const override;
    ~ScreenGamePadBG() override;
    SEAD_RTTI_OVERRIDE(ScreenGamePadBG, ScreenEx)
};

class ScreenWolfLinkHeartGauge : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    ScreenWolfLinkHeartGauge();
    ~ScreenWolfLinkHeartGauge() override;
    void* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenWolfLinkHeartGauge, ScreenEx)
};

class ScreenMainHorse : public ScreenEx {
public:
    ~ScreenMainHorse() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHorse, ScreenEx)
};

class ScreenKeyNum : public ScreenEx {
public:
    ScreenKeyNum();
    ~ScreenKeyNum() override;
    /* 0x3610 */ u32 _3610{};
    u8 _pad_3614[0x3618 - 0x3614];
    /* 0x3618 */ void* _3618{};
    SEAD_RTTI_OVERRIDE(ScreenKeyNum, ScreenEx)
};

class ScreenGameTitle : public ScreenEx {
public:
    const char* m15() const override;
    ScreenGameTitle();
    ~ScreenGameTitle() override;
    SEAD_RTTI_OVERRIDE(ScreenGameTitle, ScreenEx)
};

class ScreenDemoName : public ScreenEx {
public:
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
    void m94() override;
    void m100() override;
    ScreenShopBG();
    ~ScreenShopBG() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBG, ScreenEx)
};

class ScreenShopBtnList5 : public ScreenEx {
public:
    s32 m4() override;
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
    const char* m15() const override;
    ScreenSeekPadMenuBG();
    ~ScreenSeekPadMenuBG() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenSeekPadMenuBG, ScreenEx)
};

class ScreenMainScreenMS : public ScreenEx {
public:
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
    ScreenAppSystemWindowNoBtn();
    ~ScreenAppSystemWindowNoBtn() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u32 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindowNoBtn, ScreenEx)
};

class ScreenMessageTipsPauseMenu : public ScreenEx {
public:
    ~ScreenMessageTipsPauseMenu() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsPauseMenu, ScreenEx)
};

class ScreenAmiiboWindow : public ScreenEx {
public:
    s32 m4() override;
    ~ScreenAmiiboWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAmiiboWindow, ScreenEx)
};

class ScreenSystemWindowNoBtn : public ScreenEx {
public:
    ScreenSystemWindowNoBtn();
    ~ScreenSystemWindowNoBtn() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
    SEAD_RTTI_OVERRIDE(ScreenSystemWindowNoBtn, ScreenEx)
};

class ScreenSystemWindow00 : public ScreenEx {
public:
    s32 m81() override;
    void m82() override;
    void m96() override;
    void m97() override;
    void m101() override;
    s32 m4() override;
    ~ScreenSystemWindow00() override;
    SEAD_RTTI_OVERRIDE(ScreenSystemWindow00, ScreenEx)
};

class ScreenPauseMenuMantan : public ScreenEx {
public:
    s32 m4() override;
    ~ScreenPauseMenuMantan() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuMantan, ScreenEx)
};

class ScreenPauseMenuEiketsu : public ScreenEx {
public:
    void m107() override;
    s32 m4() override;
    ScreenPauseMenuEiketsu();
    ~ScreenPauseMenuEiketsu() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuEiketsu, ScreenEx)
};

class ScreenAppSystemWindow : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    s32 m81() override;
    s32 m141() override;
    s32 m142() override;
    s32 m4() override;
    ~ScreenAppSystemWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenAppSystemWindow, ScreenEx)
};

class ScreenHardModeTextDLC : public ScreenEx {
public:
    const char* m15() const override;
    ScreenHardModeTextDLC();
    ~ScreenHardModeTextDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenHardModeTextDLC, ScreenEx)
};

class ScreenEnd : public ScreenEx {
public:
    void m94() override;
    ScreenEnd();
    ~ScreenEnd() override;
    SEAD_RTTI_OVERRIDE(ScreenEnd, ScreenEx)
};

class ScreenLastComplete : public ScreenEx {
public:
    const char* m15() const override;
    ScreenLastComplete();
    ~ScreenLastComplete() override;
    SEAD_RTTI_OVERRIDE(ScreenLastComplete, ScreenEx)
};

class ScreenOPtext : public ScreenEx {
public:
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    ScreenOPtext();
    ~ScreenOPtext() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u32 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenOPtext, ScreenEx)
};

class ScreenLoadingWeapon : public ScreenEx {
public:
    ScreenLoadingWeapon();
    ~ScreenLoadingWeapon() override;
    SEAD_RTTI_OVERRIDE(ScreenLoadingWeapon, ScreenEx)
};

class ScreenMainHardMode : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenMainHardMode() override;
    SEAD_RTTI_OVERRIDE(ScreenMainHardMode, ScreenEx)
};

class ScreenSkip : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    s32 m4() override;
    ~ScreenSkip() override;
    SEAD_RTTI_OVERRIDE(ScreenSkip, ScreenEx)
};

class ScreenChangeController : public ScreenEx {
public:
    ScreenChangeController();
    ~ScreenChangeController() override;
    void* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenChangeController, ScreenEx)
};

class ScreenDemoStart : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ScreenDemoStart();
    ~ScreenDemoStart() override;
    void* _3610{};
    SEAD_RTTI_OVERRIDE(ScreenDemoStart, ScreenEx)
};

class ScreenBootUp : public ScreenEx {
public:
    const char* m15() const override;
    ScreenBootUp();
    ~ScreenBootUp() override;
    SEAD_RTTI_OVERRIDE(ScreenBootUp, ScreenEx)
};

class ScreenAppMenuBtn : public ScreenEx {
public:
    s32 m81() override;
    void m94() override;
    void m98() override;
    s32 m4() override;
    const char* m15() const override;
    ScreenAppMenuBtn();
    ~ScreenAppMenuBtn() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ void* _3618{};
    /* 0x3620 */ u16 _3620{};
    SEAD_RTTI_OVERRIDE(ScreenAppMenuBtn, ScreenEx)
};

class ScreenHomeMenuCapture : public ScreenEx {
public:
    const char* m15() const override;
    ScreenHomeMenuCapture();
    ~ScreenHomeMenuCapture() override;
    /* 0x3610 */ void* _3610{};
    /* 0x3618 */ u8 _3618{};
    SEAD_RTTI_OVERRIDE(ScreenHomeMenuCapture, ScreenEx)
};

class ScreenShopBtnList20 : public ScreenEx {
public:
    s32 m4() override;
    ~ScreenShopBtnList20() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList20, ScreenEx)
};

class ScreenTime : public ScreenEx {
public:
    ~ScreenTime() override;
    SEAD_RTTI_OVERRIDE(ScreenTime, ScreenEx)
};

class ScreenChallengeWin : public ScreenEx {
public:
    const char* m15() const override;
    ~ScreenChallengeWin() override;
    SEAD_RTTI_OVERRIDE(ScreenChallengeWin, ScreenEx)
};

class ScreenControllerWindow : public ScreenEx {
public:
    void m101() override;
    void m106() override;
    void m107() override;
    void m138() override;
    s32 m4() override;
    const char* m15() const override;
    ~ScreenControllerWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenControllerWindow, ScreenEx)
};

class ScreenDLCWindow : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenDLCWindow() override;
    virtual void m154();  // placeholder: one extra virtual slot (vtable offsets +8)
    SEAD_RTTI_OVERRIDE(ScreenDLCWindow, ScreenEx)
};

class ScreenTitle : public ScreenEx {
public:
    s32 m141() override;
    s32 m142() override;
    void m96() override;
    s32 m4() override;
    ~ScreenTitle() override;
    SEAD_RTTI_OVERRIDE(ScreenTitle, ScreenEx)
};

class ScreenAppCamera : public ScreenEx {
public:
    void m127() override;
    s32 m4() override;
    const char* m15() const override;
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
    s32 m4() override;
    const char* m15() const override;
    ~ScreenEnergyMeterDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenEnergyMeterDLC, ScreenEx)
};

class ScreenMessageGet : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenMessageGet() override;
    SEAD_RTTI_OVERRIDE(ScreenMessageGet, ScreenEx)
};

class ScreenSousaGuide : public ScreenEx {
public:
    ~ScreenSousaGuide() override;
    SEAD_RTTI_OVERRIDE(ScreenSousaGuide, ScreenEx)
};

class ScreenShopBtnList15 : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenShopBtnList15() override;
    SEAD_RTTI_OVERRIDE(ScreenShopBtnList15, ScreenEx)
};

class ScreenShopInfo : public ScreenEx {
public:
    void m96() override;
    ~ScreenShopInfo() override;
    SEAD_RTTI_OVERRIDE(ScreenShopInfo, ScreenEx)
};

class ScreenAppAlbum : public ScreenEx {
public:
    s32 m4() override;
    const char* m15() const override;
    ~ScreenAppAlbum() override;
    SEAD_RTTI_OVERRIDE(ScreenAppAlbum, ScreenEx)
};

class ScreenAppMapDungeon : public ScreenEx {
public:
    void m100() override;
    s32 m4() override;
    const char* m15() const override;
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
    s32 m4() override;
    const char* m15() const override;
    ~ScreenAppHome() override;
    SEAD_RTTI_OVERRIDE(ScreenAppHome, ScreenEx)
};

class ScreenSaveTransferWindow : public ScreenEx {
public:
    void m98() override;
    s32 m4() override;
    const char* m15() const override;
    ~ScreenSaveTransferWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenSaveTransferWindow, ScreenEx)
};

class ScreenOptionWindow : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    s32 m4() override;
    ~ScreenOptionWindow() override;
    SEAD_RTTI_OVERRIDE(ScreenOptionWindow, ScreenEx)
};

class ScreenSystemWindow01 : public ScreenEx {
public:
    void m96() override;
    void m97() override;
    void m101() override;
    s32 m4() override;
    ~ScreenSystemWindow01() override;
    SEAD_RTTI_OVERRIDE(ScreenSystemWindow01, ScreenEx)
};

class ScreenPauseMenuRecipe : public ScreenEx {
public:
    s32 m4() override;
    ~ScreenPauseMenuRecipe() override;
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuRecipe, ScreenEx)
};

class ScreenStaffRoll : public ScreenEx {
public:
    ~ScreenStaffRoll() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRoll, ScreenEx)
};

class ScreenStaffRollDLC : public ScreenEx {
public:
    s32 m4() override;
    ~ScreenStaffRollDLC() override;
    SEAD_RTTI_OVERRIDE(ScreenStaffRollDLC, ScreenEx)
};

class ScreenKeyBoradTextArea : public ScreenEx {
public:
    s32 m141() override;
    s32 m142() override;
    void m93() override;
    void m94() override;
    void m96() override;
    void m97() override;
    ~ScreenKeyBoradTextArea() override;
    SEAD_RTTI_OVERRIDE(ScreenKeyBoradTextArea, ScreenEx)
};

class ScreenFadeStatus : public ScreenEx {
public:
    bool isPlayPartsInOut_() const override;
    ~ScreenFadeStatus() override;
    SEAD_RTTI_OVERRIDE(ScreenFadeStatus, ScreenEx)
};

}  // namespace uking::ui

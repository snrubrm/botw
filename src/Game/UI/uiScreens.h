#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiScreen.h"

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

class Screen : public ScreenBase {
public:
    ~Screen() override;
    SEAD_RTTI_OVERRIDE(Screen, ScreenBase)

    // New virtual slots of Screen (CSV Screen::mNN; the number is the vtable slot). INCOMPLETE: only the
    // trivial slots that are defined in uiScreenSlots.cpp are declared, so the vtable order is not yet
    // usable (slots 73-79, 80, 81, 83-89, 93-94, 96-100, 111-126 are missing).
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual s32 m72();
    virtual s32 m81();
    virtual void m96();  // open(1)
    virtual void m97();  // close(-1)
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m90();
    virtual void m91();
    virtual void m92();
    virtual void m95();
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
};

class ScreenEx : public Screen {
public:
    ~ScreenEx() override;
    SEAD_RTTI_OVERRIDE(ScreenEx, Screen)

    // New virtual slots of ScreenEx (127-153; INCOMPLETE, see Screen).
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

    // Placeholder for the real base-class data (the leaf classes' members start at 0x3610).
    u8 _8[0x3610 - 8];
};

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
    SEAD_RTTI_OVERRIDE(ScreenPauseMenuInfo, ScreenEx)

    void sub_7100A31BE0();
};

class ScreenMessageTipsRunTime : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMessageTipsRunTime, ScreenEx)

    void sub_7100A268AC(s32, s32);
};

class ScreenDoCommand : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenDoCommand, ScreenEx)

    // 0x7100a0768c (CSV ScreenDoCommand::setCommand)
    bool setCommand(s32 command);

    void sub_7100A0772C(s32);
};

class ScreenMainScreen3D : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMainScreen3D, ScreenEx)

    u8 _pad_3610[0x3f38 - 0x3610];
    /* 0x3f38 */ u8 _3f38;

    void sub_7100A115E4(s64);
    bool sub_7100A11B10(s64);
    bool sub_7100A11D34(s32);
};

class ScreenMainScreen : public ScreenEx {
public:
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
    SEAD_RTTI_OVERRIDE(ScreenGameOver, ScreenEx)

    /* 0x3610 */ u8 _3610;
    u8 _pad_3611[3];
    /* 0x3614 */ s32 _3614;

    bool sub_7100A0A8D8();
    bool sub_7100A0A914();
};

class ScreenRupee : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenRupee, ScreenEx)

    void sub_7100A410D8(s32);
    void sub_7100A41558();
    bool sub_7100A41440();
    bool sub_7100A41354(s32);
    void sub_7100A414A0();
};

class ScreenKologNum : public ScreenEx {
public:
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
    SEAD_RTTI_OVERRIDE(ScreenMamoNum, ScreenEx)

    void sub_7100A22A80(s32 a1);

    void sub_7100A22B98();
};

class ScreenShopHorse : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenShopHorse, ScreenEx)

    void sub_7100A4EBA0(s32);
};

class ScreenMainShortCut : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMainShortCut, ScreenEx)

    bool sub_7100A20DD0();
};

class ScreenReadyGo : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenReadyGo, ScreenEx)

    bool sub_7100A40BF8();
};

class ScreenMiniGame : public ScreenEx {
public:
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
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)

    void sub_7100A34A04();

    bool sub_7100A34A10();
    bool sub_7100A349F4();
};

class ScreenAppTool : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenAppTool, ScreenEx)

    bool sub_71009FD674();
};

class ScreenAppPictureBook : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenAppPictureBook, ScreenEx)

    void sub_71009F8510(s32);
};

class ScreenDLCSinJuAkashiNum : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenDLCSinJuAkashiNum, ScreenEx)

    u8 _pad_3610[0x3638 - 0x3610];
    /* 0x3638 */ s32 _3638;
    u8 _pad_363c[0x3688 - 0x363c];
    /* 0x3688 */ s32 _3688;
};

}  // namespace uking::ui

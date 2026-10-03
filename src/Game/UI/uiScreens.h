#pragma once

#include <math/seadVector.h>
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
};

class ScreenEx : public Screen {
public:
    ~ScreenEx() override;
    SEAD_RTTI_OVERRIDE(ScreenEx, Screen)
    // 0x7100a48a18 / 0x7100a48aac / 0x7100a48b40 are members of the Ex layer (see the facade file).
};

// Screen ids: the jump table of ScreenFactory::create (0x7100a81f34), which is also the index into
// eui::ScreenMgr's screen table.
struct ScreenId {
    enum : s32 {
        MainScreen3D = 2,
        MiniGame = 8,
        ReadyGo = 9,
        DoCommand = 12,
        ShopHorse = 23,
        Rupee = 24,
        KologNum = 25,
        AkashNum = 26,
        MamoNum = 27,
        AppTool = 31,
        AppPictureBook = 33,
        MainScreen = 37,
        MessageTipsRunTime = 41,
        AppMap = 42,
        MainShortCut = 45,
        PauseMenu = 46,
        PauseMenuInfo = 47,
        GameOver = 48,
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

    void sub_7100A0772C(s32);
};

class ScreenMainScreen3D : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMainScreen3D, ScreenEx)

    void sub_7100A115E4(s64);
    bool sub_7100A11B10(s64);
    bool sub_7100A11D34(s32);
};

class ScreenMainScreen : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMainScreen, ScreenEx)

    void sub_7100A1A4E4(s64);
    bool sub_7100A1E1E0();
};

class ScreenGameOver : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenGameOver, ScreenEx)

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

    void sub_7100A0F098();
    bool sub_7100A0F038();
    bool sub_7100A0EFA4();
    void sub_7100A0F110(s32);
};

class ScreenAkashNum : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenAkashNum, ScreenEx)

    void sub_71009CF058();
    bool sub_71009CEFBC();
    bool sub_71009CEF28();
    void sub_71009CF01C(s32);
};

class ScreenMamoNum : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenMamoNum, ScreenEx)

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

    bool sub_7100A275EC(s32, s32);
    void sub_7100A28088();
    bool openMinigameScreen(s32, s32);
};

class ScreenAppMap : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenAppMap, ScreenEx)

    bool sub_71009EF5A8(s32);
    bool sub_71009E9F10();
};

class ScreenPauseMenu : public ScreenEx {
public:
    SEAD_RTTI_OVERRIDE(ScreenPauseMenu, ScreenEx)

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

}  // namespace uking::ui

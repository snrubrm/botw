#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/DLC/aocManager.h"

// Trivial overrides of the leaf screens' own state-callback slots (154+).
namespace uking::ui {

// 0x71009d6568
void ScreenAppAlbum::m172() {}

// 0x71009d6c44
s32 ScreenAppAlbum::m173() { return 0; }

// 0x71009d6c4c
s32 ScreenAppAlbum::m177() { return 0; }

// 0x7100a3ee60
s32 ScreenPauseMenu::m173() { return 0; }

// 0x7100a3de48
void ScreenPauseMenu::m176() {}

// 0x7100a3ee68
s32 ScreenPauseMenu::m177() { return 0; }

// 0x7100a3ee70
s32 ScreenPauseMenu::m181() { return 0; }

// 0x7100a3ee78
s32 ScreenPauseMenu::m185() { return 0; }

// 0x7100a3ee80
s32 ScreenPauseMenu::m189() { return 0; }

// 0x7100a3ec10
void ScreenPauseMenu::m192() {}

// 0x7100a3ee88
s32 ScreenPauseMenu::m193() { return 0; }

// 0x7100a438fc
void ScreenSaveTransferWindow::m172() {}

// 0x7100a46554
s32 ScreenSaveTransferWindow::m173() { return 0; }

// 0x7100a43920
void ScreenSaveTransferWindow::m176() {}

// 0x7100a4655c
s32 ScreenSaveTransferWindow::m177() { return 0; }

// 0x7100a43a0c
void ScreenSaveTransferWindow::m180() {}

// 0x7100a46564
s32 ScreenSaveTransferWindow::m181() { return 0; }

// 0x7100a43b60
void ScreenSaveTransferWindow::m184() {}

// 0x7100a4656c
s32 ScreenSaveTransferWindow::m185() { return 0; }

// 0x7100a43e14
void ScreenSaveTransferWindow::m188() {}

// 0x7100a46574
s32 ScreenSaveTransferWindow::m189() { return 0; }

// 0x7100a44008
void ScreenSaveTransferWindow::m192() {}

// 0x7100a4657c
s32 ScreenSaveTransferWindow::m193() { return 0; }

// 0x7100a44088
void ScreenSaveTransferWindow::m196() {}

// 0x7100a46584
s32 ScreenSaveTransferWindow::m197() { return 0; }

// 0x7100a44180
void ScreenSaveTransferWindow::m200() {}

// 0x7100a4658c
s32 ScreenSaveTransferWindow::m201() { return 0; }

// 0x7100a44298
void ScreenSaveTransferWindow::m204() {}

// 0x7100a46594
s32 ScreenSaveTransferWindow::m205() { return 0; }

// 0x7100a44390
void ScreenSaveTransferWindow::m208() {}

// 0x7100a4659c
s32 ScreenSaveTransferWindow::m209() { return 0; }

// 0x7100a44454
void ScreenSaveTransferWindow::m212() {}

// 0x7100a465a4
s32 ScreenSaveTransferWindow::m213() { return 0; }

// 0x7100a44540
void ScreenSaveTransferWindow::m216() {}

// 0x7100a465ac
s32 ScreenSaveTransferWindow::m217() { return 0; }

// 0x7100a44620
void ScreenSaveTransferWindow::m220() {}

// 0x7100a465b4
s32 ScreenSaveTransferWindow::m221() { return 0; }

// 0x7100a4482c
void ScreenSaveTransferWindow::m224() {}

// 0x7100a465bc
s32 ScreenSaveTransferWindow::m225() { return 0; }

// 0x7100a44850
void ScreenSaveTransferWindow::m228() {}

// 0x7100a465c4
s32 ScreenSaveTransferWindow::m229() { return 0; }

// 0x7100a44874
void ScreenSaveTransferWindow::m232() {}

// 0x7100a465cc
s32 ScreenSaveTransferWindow::m233() { return 0; }

// 0x7100a44960
void ScreenSaveTransferWindow::m236() {}

// 0x7100a465d4
s32 ScreenSaveTransferWindow::m237() { return 0; }

// 0x7100a465dc
s32 ScreenSaveTransferWindow::m241() { return 0; }

// 0x7100a44db4
void ScreenSaveTransferWindow::m244() {}

// 0x7100a465e4
s32 ScreenSaveTransferWindow::m245() { return 0; }

// 0x7100a44dd8
void ScreenSaveTransferWindow::m248() {}

// 0x7100a465ec
s32 ScreenSaveTransferWindow::m249() { return 0; }

// 0x7100a45058
void ScreenSaveTransferWindow::m252() {}

// 0x7100a465f4
s32 ScreenSaveTransferWindow::m253() { return 0; }

// 0x7100a4507c
void ScreenSaveTransferWindow::m256() {}

// 0x7100a465fc
s32 ScreenSaveTransferWindow::m257() { return 0; }

// 0x7100a45168
void ScreenSaveTransferWindow::m260() {}

// 0x7100a46604
s32 ScreenSaveTransferWindow::m261() { return 0; }

// 0x7100a45398
void ScreenSaveTransferWindow::m264() {}

// 0x7100a4660c
s32 ScreenSaveTransferWindow::m265() { return 0; }

// 0x7100a45680
void ScreenSaveTransferWindow::m268() {}

// 0x7100a46614
s32 ScreenSaveTransferWindow::m269() { return 0; }

// 0x7100a4576c
void ScreenSaveTransferWindow::m272() {}

// 0x7100a4661c
s32 ScreenSaveTransferWindow::m273() { return 0; }

// 0x7100a45b4c
void ScreenSaveTransferWindow::m276() {}

// 0x7100a46624
s32 ScreenSaveTransferWindow::m277() { return 0; }

// 0x7100a45bb4
void ScreenSaveTransferWindow::m280() {}

// 0x7100a4662c
s32 ScreenSaveTransferWindow::m281() { return 0; }

// 0x7100a45d9c
void ScreenSaveTransferWindow::m284() {}

// 0x7100a46634
s32 ScreenSaveTransferWindow::m285() { return 0; }

// 0x7100a45e8c
void ScreenSaveTransferWindow::m288() {}

// 0x7100a4663c
s32 ScreenSaveTransferWindow::m289() { return 0; }

// 0x7100a45fbc
void ScreenSaveTransferWindow::m292() {}

// 0x7100a46644
s32 ScreenSaveTransferWindow::m293() { return 0; }

// 0x7100a46000
void ScreenSaveTransferWindow::m296() {}

// 0x7100a4664c
s32 ScreenSaveTransferWindow::m297() { return 0; }

// 0x7100a46120
void ScreenSaveTransferWindow::m300() {}

// 0x7100a46654
s32 ScreenSaveTransferWindow::m301() { return 0; }

// 0x7100a46224
void ScreenSaveTransferWindow::m304() {}

// 0x7100a4665c
s32 ScreenSaveTransferWindow::m305() { return 0; }

// 0x7100a46228
void ScreenSaveTransferWindow::m306() {}

// 0x7100a4622c
void ScreenSaveTransferWindow::m307() {}

// 0x7100a46230
void ScreenSaveTransferWindow::m308() {}

// 0x7100a46664
s32 ScreenSaveTransferWindow::m309() { return 0; }

// 0x7100a46260
void ScreenSaveTransferWindow::m311() {}

// 0x7100a46264
void ScreenSaveTransferWindow::m312() {}

// 0x7100a4666c
s32 ScreenSaveTransferWindow::m313() { return 0; }

// 0x7100a46448
void ScreenSaveTransferWindow::m316() {}

// 0x7100a46674
s32 ScreenSaveTransferWindow::m317() { return 0; }

// 0x71009f28a8
s32 ScreenAppMap::getSlink2LocalPropertyNum_() const {
    return 2;
}

// 0x7100a438b8
void ScreenSaveTransferWindow::m166() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a438c8
void ScreenSaveTransferWindow::m167() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a438dc
void ScreenSaveTransferWindow::m170() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a438ec
void ScreenSaveTransferWindow::m171() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a43900
void ScreenSaveTransferWindow::m174() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a43910
void ScreenSaveTransferWindow::m175() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a44078
void ScreenSaveTransferWindow::m195() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a4362c
void ScreenSaveTransferWindow::m155() {
    switch (_366c) {
    case 0x8d: {
        auto* manager = aoc::Manager::instance();
        if (manager && manager->getVersion() != 0)
            mStateMachine.changeState(&sUnk_71025f1fa0);
        else
            mStateMachine.changeState(&sUnk_71025f2000);
        break;
    }
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d80);
        break;
    }
}

// 0x7100a439d4
void ScreenSaveTransferWindow::m179() {
    switch (_366c) {
    case 0x8d:
        mStateMachine.changeState(&sUnk_71025f2240);
        break;
    case 0x8c:
        mStateMachine.changeState(&sUnk_71025f2d20);
        break;
    }
}

// 0x7100a44160
void ScreenSaveTransferWindow::m199() {
    if (_366c == 0x8b)
        mStateMachine.changeState(&sUnk_71025f23c0);
}

// 0x7100a44278
void ScreenSaveTransferWindow::m203() {
    if (_366c == 0x8b)
        mStateMachine.changeState(&sUnk_71025f2d80);
}

// 0x7100a44370
void ScreenSaveTransferWindow::m207() {
    if (_366c == 0x8b)
        mStateMachine.changeState(&sUnk_71025f2480);
}

// 0x7100a44434
void ScreenSaveTransferWindow::m211() {
    if (_366c == 0x8b)
        mStateMachine.changeState(&sUnk_71025f2d80);
}

// 0x7100a44830
void ScreenSaveTransferWindow::m226() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a44840
void ScreenSaveTransferWindow::m227() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a44854
void ScreenSaveTransferWindow::m230() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a44864
void ScreenSaveTransferWindow::m231() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a4505c
void ScreenSaveTransferWindow::m254() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a4506c
void ScreenSaveTransferWindow::m255() {
    mStateMachine.changeState(&sUnk_71025f2de0);
}

// 0x7100a44db8
void ScreenSaveTransferWindow::m246() {
    close(-1);
}

// 0x7100a44dc8
void ScreenSaveTransferWindow::m247() {
    close(-1);
}

// 0x71009fc91c
void ScreenAppSystemWindow::m99() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a2c278
void ScreenPauseMenuEiketsu::m99() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a2c29c
void ScreenPauseMenuEiketsu::m106(eui::AnimButton*) {
    mButtonGroup->_38 &= ~2;
}

// 0x7100a322e8
void ScreenPauseMenuMantan::m99() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a322fc
void ScreenPauseMenuMantan::m106(eui::AnimButton*) {
    mButtonGroup->_38 &= ~2;
}

// 0x7100a04c98
void ScreenDLCSinJuAkashiNum::m156() {
    _3610 = false;
}

// 0x7100a418d8
void ScreenRupee::m156() {
    _3610 = false;
}

// 0x7100a22d64
void ScreenMamoNum::m69() {
    _3610 = 0;
    _3630 = -1;
}

// 0x7100a22d54
void ScreenMamoNum::m100() {
    mStateMachine.changeState(&sUnk_71025ef4b8);
}

// 0x7100a4185c
void ScreenRupee::m69() {
    _3634 = 4;
    _3614 = 0;
}

// 0x7100a4184c
void ScreenRupee::m100() {
    mStateMachine.changeState(&sUnk_71025f1bf0);
}

// 0x7100a04c20
void ScreenDLCSinJuAkashiNum::m69() {
    _3614 = 0;
    _3638 = -1;
}

// 0x7100a04c10
void ScreenDLCSinJuAkashiNum::m100() {
    mStateMachine.changeState(&sUnk_71025ecb40);
}

// 0x71010af810
bool ScreenMessage3D::isEnableControl() const {
    return true;
}

// 0x710109ff50
bool ScreenErrorViewer::isEnableControl() const {
    return true;
}

// 0x7100a3d64c
void ScreenPauseMenu::m160() {
    _3618 = 15;
    mButtonGroup->_38 |= 2;
}

// 0x7100a3db00
void ScreenPauseMenu::m171() {
    auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::PauseMenuEiketsu);
    if (screen && screen->isClosedOrClosing()) {
        sub_7100A392D8();
        mStateMachine.changeState(&sUnk_71025f0cf0);
    }
}

// 0x7100a3d014
void ScreenPauseMenu::m156() {
    if (mActiveCursorNode)
        _3b80 = mActiveCursorNode->mButton->mTag;
    const u32 index = _3a18 < 3 ? _3a18 : 0;
    if (_3a00[index])
        _3a00[index]->sub_71009B0224(false);
}

// 0x7100a3e2d4
void ScreenPauseMenu::m186() {
    if (_3674)
        sub_7100A38028();
    moveBoxCursorByTag_(_3b88);
    if (_3b98)
        _3b98->sub_71009B5FC8(true);
    _3ba4 = 0;
    if (!sub_7100A25D7C(0) && _3b98 && _3b98->_1a0 >= 2) {
        _3c14.reset();
        _3c10 = 1;
    }
}

// 0x7100a3e654
void ScreenPauseMenu::m188() {
    if (_3b98)
        _3b98->sub_71009B5FC8(false);
    _3c10 = 0;
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageTipsPauseMenu))
        screen->close(-1);
}

// 0x7100a3e0f4
void ScreenPauseMenu::m182() {
    if (_3674)
        sub_7100A38028();
    moveBoxCursorByTag_(_3b84);
    if (_3b90)
        _3b90->sub_71009B9F94(true);
    _3ba4 = 0;
}

// 0x7100a3e2c0
void ScreenPauseMenu::m184() {
    if (_3b90)
        _3b90->sub_71009B9F94(false);
}

// 0x7100a3d80c
void ScreenPauseMenu::m164() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a3d820
void ScreenPauseMenu::m166() {
    mButtonGroup->_38 &= ~2;
}

// 0x7100a3d9f8
void ScreenPauseMenu::m168() {
    mButtonGroup->_38 |= 2;
}

// 0x7100a3db6c
void ScreenPauseMenu::m172() {
    mButtonGroup->_38 |= 2;
}

}  // namespace uking::ui

namespace uking::ui {

// 0x7100a3ec14 (D1) / 0x7100a3ec58 (D0)
Unk_7102493bd0::~Unk_7102493bd0() {
    _28.freeBuffer();
}

// 0x7100a3eca4
// NON_MATCHING: in the original the per-object position copy stays one 8-byte copy and the z store sits between the
// load and the store of the flag byte; ours merges the y and z stores
void Unk_7102493bd0::m2(const sead::Vector2f& a, const sead::Vector2f& b) {
    _20 = _18;
    const sead::Vector2f pos = a + b + _20;
    _20 = pos;
    if (Unk_PaneTransform* pane = _10) {
        pane->_30.x = pos.x;
        pane->_30.y = pos.y;
        pane->_38 = 0;
        pane->_58 |= 0x10;
    }
    const s32 count = _38;
    for (s32 i = 0; i < count; ++i) {
        if (Unk_PaneTransform* pane = _28[i]) {
            pane->_30 = _20;
            pane->_38 = 0;
            pane->_58 |= 0x10;
        }
    }
}

}  // namespace uking::ui

namespace uking::ui {

// 0x71009de1c8 (kept out of the TU of its caller ScreenAppSystemWindow::m100: the original does not inline it)
void ScreenAppHome::sub_71009DE1C8() {
    sub_71009DCF18(_3808);
}

}  // namespace uking::ui

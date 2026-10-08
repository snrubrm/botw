#include "Game/UI/uiScreens.h"
#include "Game/gameRoot1.h"

// Overrides that return a constant (slots 18, 72, 81, 141, 142) in the Screen<Name> classes.
namespace uking::ui {

// 0x7100a6ba80
s32 ScreenTitle::m141(const ksys::Message&) {
    return 0;
}

// 0x7100a6ba88
s32 ScreenTitle::m142(const ksys::Message&) {
    return 0;
}

// 0x7100a1630c
s32 ScreenMainScreen3D::m141(const ksys::Message&) {
    return 0;
}

// 0x7100a16314
s32 ScreenMainScreen3D::m142(const ksys::Message&) {
    return 1;
}

// 0x7100a6bf0c
bool ScreenWolfLinkHeartGauge::isPlayPartsInOut_() const {
    return true;
}

// 0x7100a040dc
bool ScreenDemoName::isPlayPartsInOut_() const {
    return true;
}

// 0x7100a03e10
bool ScreenDemoNameEnemy::isPlayPartsInOut_() const {
    return true;
}

// 0x7100a41c84
s32 ScreenRupee::m72() {
    return 0;
}

// 0x7100a0f5f8
s32 ScreenKologNum::m72() {
    return 0;
}

// 0x71009cf89c
s32 ScreenAkashNum::m72() {
    return 0;
}

// 0x7100a230a4
s32 ScreenMamoNum::m72() {
    return 0;
}

// 0x7100a3ee34
s32 ScreenPauseMenu::m72() {
    return 0;
}

// 0x7100a2bcfc
bool ScreenOptionWindow::isPlayPartsInOut_() const {
    return true;
}

// 0x7100a65df8
s32 ScreenSystemWindow00::m81() {
    return 1;
}

// 0x71009fcd54
bool ScreenAppSystemWindow::isPlayPartsInOut_() const {
    return true;
}

// 0x71009fcd5c
s32 ScreenAppSystemWindow::m81() {
    return 1;
}

// 0x71009fcc5c
s32 ScreenAppSystemWindow::m141(const ksys::Message&) {
    return 0;
}

// 0x71009fcc64
s32 ScreenAppSystemWindow::m142(const ksys::Message&) {
    return 0;
}

// 0x7100a04ffc
s32 ScreenDLCSinJuAkashiNum::m72() {
    return 0;
}

// 0x7100a0e5fc
s32 ScreenKeyBoradTextArea::m141(const ksys::Message&) {
    return 0;
}

// 0x7100a0e604
s32 ScreenKeyBoradTextArea::m142(const ksys::Message&) {
    return 0;
}

// 0x7100a0a418
bool ScreenFadeStatus::isPlayPartsInOut_() const {
    return true;
}

// 0x7100a53968
bool ScreenSkip::isPlayPartsInOut_() const {
    return true;
}

// 0x71009f2ea4
s32 ScreenAppMenuBtn::m81() {
    return 1;
}

// 0x71009f2d8c
void ScreenAppMenuBtn::m83() {
    if (sForceEnableGlidingSurfingRupee)
        open(1);
}

// 0x7100a0e5bc
void ScreenKeyBoradTextArea::m98() {
    if (auto* root = Root1::instance())
        root->sub_7100899CA4(Root1::FlagIdx::_0, 1);
}

// 0x7100a0e5dc
void ScreenKeyBoradTextArea::m101() {
    if (auto* root = Root1::instance())
        root->sub_7100899CA4(Root1::FlagIdx::_0, 2);
}

// 0x7100a503dc
void ScreenShopHorse::sub_7100A503DC() {
    if (auto* root = Root1::instance())
        root->sub_7100899CA4(Root1::FlagIdx::_0, 2);
}

}  // namespace uking::ui

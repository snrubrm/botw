#include "Game/E3Mgr.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameRuneMgr.h"

namespace uking::ui {

// 0x7100aa0700 (CSV isE3DemoMode)
bool isE3DemoMode() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isDemoMode();
}

// 0x7100aa0718 (CSV isRIDDemo)
bool isRIDDemo() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isRidDemo();
}

// 0x7100aa0730
bool sub_7100AA0730() {
    auto* mgr = E3Mgr::instance();
    return mgr && mgr->isRidDemoAnd28IsOne();
}

// 0x7100aa0a74
void sub_7100AA0A74(s32 a1) {
    Manager::instance()->sub_7100A7B8CC(a1);
}

// 0x7100aa0a8c
void sub_7100AA0A8C(s32 a1) {
    Manager::instance()->sub_7100A7B92C(a1);
}

// 0x7100a9f4f8
void sub_7100A9F4F8() {
    Manager::instance()->loadStaticInfo(getHeap());
}

// 0x7100a9f888
bool sub_7100A9F888() {
    auto* mgr = RuneMgr::instance();
    if (mgr && (mgr->_90 & 0x10))
        return mgr->isSelectedRune(5);
    return false;
}

}  // namespace uking::ui

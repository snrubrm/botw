#include "KingSystem/Event/evtS7.h"
#include "Game/E3Mgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/Scene/gameScene.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/System/AutoDim.h"
#include "KingSystem/System/SeadController.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/Terrain/teraSystem.h"

// Declaration only; the original source namespace is unknown (0x7100f40360).
void setInitBeforeStageGenDone(bool done);

namespace ksys::evt {

// 0x71008add3c
S7::S7(sead::Heap* heap, EventFlowBase* flow) : mFlow(flow) {}

// D1 0x71008add5c, D0 0x71008addf4
S7::~S7() {
    sub_71008ADDB0();
}

// 0x71008addb0
void S7::sub_71008ADDB0() {
    if (_14 & 1) {
        EventSystem::instance()->sub_71008AC148(mFlow);
        _14 &= ~1u;
    }
}

// NON_MATCHING: same logic, but the original keeps the blocked flag as a materialised bool (`mov w0, wzr; tbz w0, ...`
// after the name compare, jumps through it) where ours threads the branches.
// 0x71008ade40
// NON_MATCHING: the original loads EventSystem::instance() before computing the stored value (C++14 order) and
// keeps the two flag masks as immediates
void S7::handleEventSkip() {
    if (mFlow->getType() == EventFlowType::MovieWithNoPath)
        return;

    auto* controller = SeadController::getInstance();
    auto* ui_mgr = uking::ui::Manager::instance();
    const bool blocked = ui_mgr->isPausedMaybe() && (ui_mgr->_64c30 & 8) == 0;
    const bool is_movie = mFlow->getEventFlowType() == 1 || mFlow->getEventFlowType() == 2;

    switch (_10) {
    case 1:
        if (controller->isTrig(8) && !blocked)
            _10 = 2;
        break;
    case 2:
        if (controller->isTrig(is_movie ? 0x800 : 2) && !blocked) {
            _10 = 3;
            mFlow->_340 |= 0x2000000000;
        }
        if (controller->isTrig(2))
            _10 = 1;
        break;
    case 4:
        if (controller->isTrig(8))
            _10 = 3;
        break;
    case 5:
        if (controller->isTrig(2 | 8))
            _10 = 3;
        break;
    }

    if (_10 == 2)
        EventSystem::instance()->_138 = 1;
    else if (_10 == 4)
        EventSystem::instance()->_138 = 2;
    else
        EventSystem::instance()->_138 = _10 == 5 ? 2 : 0;

    if (_10 == 4 || _10 == 2)
        uking::ui::openSkipScreen(is_movie);
    else
        uking::ui::closeSkipScreen();

    if (_14 & 2) {
        if (controller->isHold(2))
            _14 |= 4;
        _14 &= ~2u;
    } else {
        _14 &= ~4u;
    }
}

// 0x71008ae08c
void S7::blockSkipForDemo102(bool a, bool b) {
    bool blocked = false;
    if (mFlow->mEventName == "Demo102_0") {
        auto* e3 = uking::E3Mgr::instance();
        if (!(e3 && e3->isDemoMode()) && uking::GameScene::getIsFirstLaunch())
            blocked = true;
    }
    if (!blocked && a) {
        if (_10 == 0)
            _10 = b ? 4 : 1;
        return;
    }
    _10 = 0;
    uking::ui::closeSkipScreen();
    if (int(mFlow->getType()) != EventFlowType::MovieWithNoPath)
        EventSystem::instance()->_138 = 0;
}

// 0x71008ae1c4
void S7::setDemoIsPlayedFlag() {
    if (mFlow->mEventName.findIndex("Demo") == 0) {
        sead::FixedSafeString<73> flag;
        flag.format("IsPlayed_%s", mFlow->mEventName.cstr());
        gdt::Manager::instance()->setBoolNoCheck(true, flag);
    }
}

// 0x71008af278
void S7::sub_71008AF278() {
    if (!(_14 & 1)) {
        EventSystem::instance()->sub_71008AC1BC(mFlow);
        _14 |= 1;
    }
}

// 0x71008af2bc
void S7::sub_71008AF2BC(bool enabled) {
    if (auto* dim = AutoDim::instance())
        dim->setEnabled(enabled);
}

// 0x71008af3b8
S5* S7::sub_71008AF3B8() const {
    return sead::DynamicCast<S5>(mFlow->_118->_200);
}

// 0x71008af44c
void S7::sub_71008AF44C() {
    S5* s5 = sub_71008AF3B8();
    if (s5->_8 == this) {
        if (tera::System::instance()->sub_710111F618(0))
            setInitBeforeStageGenDone(true);
        s5->_8 = nullptr;
    }
}

// 0x71008aeac4
bool S7::m11() {
    using namespace uking::ui;
    eui::ScreenMgr::instance()->getScreen(ScreenId::FadeDemo)->close(-4);
    eui::ScreenMgr::instance()->getScreen(ScreenId::Fade)->close(-4);
    return closeFadeStatus();
}

// 0x71008af504
S5::S5() {
    _12 = 0;
    _10 = 0;
    _11 = 0;
    EventSystem::instance()->_144 |= 2;
}

}  // namespace ksys::evt

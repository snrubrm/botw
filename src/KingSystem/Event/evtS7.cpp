#include "KingSystem/Event/evtS7.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtEventSystem.h"

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
    EventSystem::instance()->_144 |= 2;
}

}  // namespace ksys::evt

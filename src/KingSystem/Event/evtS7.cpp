#include "KingSystem/Event/evtS7.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/System/AutoDim.h"
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
    EventSystem::instance()->_144 |= 2;
}

}  // namespace ksys::evt

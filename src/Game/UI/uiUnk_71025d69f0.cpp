#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_71025d69f0)

// D1 0x710094d8c4, D0 0x710094d8c8
Unk_71025d69f0::~Unk_71025d69f0() = default;

// 0x710094e920
bool Unk_71025d69f0::sub_710094E920() {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    return screen && !screen->isClosed();
}

}  // namespace uking::ui

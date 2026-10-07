#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_71025d69f0)

// D1 0x710094d8c4, D0 0x710094d8c8
Unk_71025d69f0::~Unk_71025d69f0() = default;

void Unk_71025d69f0::sub_710094D8CC() {
    _28 = 1;
    _38 = 0;
}

void Unk_71025d69f0::sub_710094D8DC() {
    _28 = 1;
    _38 = 0;
}

// 0x710094e920
bool Unk_71025d69f0::sub_710094E920() {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    return screen && !screen->isClosed();
}

void Unk_71025d69f0::sub_710094E480() {
    sub_710094E1C0(false);
}

}  // namespace uking::ui

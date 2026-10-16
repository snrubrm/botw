#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

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

// 0x710094e064
void Unk_71025d69f0::sub_710094E064() {
    const s32 prev = _28;
    _28 = 3;
    sub_71009F8420(3);
    sub_710094DCC4(_28, _28 - prev);
}

// 0x710094f6f8
bool Unk_71025d69f0::sub_710094F6F8() const {
    auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    return screen && screen->sub_71009DD81C();
}

// 0x710094f7ac
bool Unk_71025d69f0::sub_710094F7AC(s32 app) const {
    if (_30 == app)
        return true;
    switch (app) {
    case 0:
        for (s32 i = 0; i < 8; ++i) {
            if (checkIsGetRune(i, 0))
                return true;
        }
        break;
    case 1:
        return true;
    case 2:
        return ksys::gdt::getFlag_IsGet_Obj_Album();
    case 3:
        return ksys::gdt::getFlag_IsGet_Obj_PictureBook();
    }
    return false;
}

}  // namespace uking::ui

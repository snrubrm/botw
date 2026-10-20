#include "Game/UI/uiShopItemElement.h"
#include <prim/seadSafeString.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// 0x71009c2a40
ShopInfoItem::ShopInfoItem(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009c2a7c
// NON_MATCHING: ScreenChild message receiver and state wrapper lifetimes remain opaque.
ShopInfoItem::~ShopInfoItem() = default;

void ShopInfoItem::m24(sead::Heap*) {
    _130 = mLayout->createAnimatorAuto("State", false);
}

void ShopInfoItem::sub_71009C2C28(u32 value) {
    if (_130 != nullptr)
        _130->Stop(value);
}

void ShopInfoItem::sub_71009C2C44(const eui::MessageString& msg) {
    setWidgetString(mLayout, "T_Name_00", msg);
}

void ShopInfoItem::sub_71009C2C8C(u32 value) {
    sead::FixedSafeString<0x80> buf;
    buf.format("%d", value);
    setWidgetString(mLayout, "T_NumL_00", buf);
}

void ShopInfoItem::sub_71009C2D44(u32 value) {
    sead::FixedSafeString<0x80> buf;
    buf.format("%d", value);
    setWidgetString(mLayout, "T_NumR_00", buf);
}

// 0x71009c2dfc
nn::ui2d::Material* ShopInfoItem::sub_71009C2DFC() {
    auto* pane = mLayout->mPane->FindPaneByName("P_Icon_00", true);
    if (pane)
        return pane->GetMaterial(0);
    return nullptr;
}

}  // namespace uking::ui

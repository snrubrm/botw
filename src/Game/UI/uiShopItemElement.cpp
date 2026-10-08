#include "Game/UI/uiShopItemElement.h"
#include <prim/seadSafeString.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

void ShopInfoItem::sub_71009C2BF4() {
    _130 = _20->createAnimatorAuto("State", false);
}

void ShopInfoItem::sub_71009C2C28(u32 value) {
    if (_130 != nullptr)
        _130->Stop(value);
}

void ShopInfoItem::sub_71009C2C44(const eui::MessageString& msg) {
    setWidgetString(_20, "T_Name_00", msg);
}

void ShopInfoItem::sub_71009C2C8C(u32 value) {
    sead::FixedSafeString<0x80> buf;
    buf.format("%d", value);
    setWidgetString(_20, "T_NumL_00", buf);
}

void ShopInfoItem::sub_71009C2D44(u32 value) {
    sead::FixedSafeString<0x80> buf;
    buf.format("%d", value);
    setWidgetString(_20, "T_NumR_00", buf);
}

}  // namespace uking::ui

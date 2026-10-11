#include "Game/UI/uiShopItemElement.h"
#include "Game/UI/uiShopItemElementChildren.h"
#include <prim/seadSafeString.h>
#include <prim/seadStringBuilder.h>
#include "Game/UI/euiGrammar.h"
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

// 0x71009c2f58
Unk_710247d0c8::Unk_710247d0c8(eui::LayoutEx* layout) : ScreenChildEx(layout) {}

// 0x71009c2f8c
// NON_MATCHING: ScreenChild message receiver and state wrapper lifetimes remain opaque.
Unk_710247d0c8::~Unk_710247d0c8() = default;

// 0x71009c3104
void Unk_710247d0c8::m24(sead::Heap*) {
    mAnimator = mLayout->createAnimatorAuto("State", true);
}

// 0x71009c3138
void Unk_710247d0c8::sub_71009C3138(s32 value, u32 frame) {
    sead::FixedStringBuilder<32> text;
    eui::Grammar::formatNumberWithDelimiter(&text, value);
    setWidgetString(mLayout, "T_Num_00", text.cstr());
    if (mAnimator)
        mAnimator->Stop(frame);
}

// 0x71009c31d8
void Unk_710247d0c8::sub_71009C31D8() {
    if (mAnimator)
        mAnimator->Stop(2);
}

}  // namespace uking::ui

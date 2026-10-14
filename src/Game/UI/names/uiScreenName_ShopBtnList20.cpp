#include <prim/seadSafeString.h>
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "ShopBtnList20_00";
}

// 0x7100a4bdb8
const char* ScreenShopBtnList20::getLayoutName_() const {
    return sLayoutName.cstr();
}


// ScreenShopBtnList20 creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102496ed8[] = {
    {"Pa_GuideA_00", sub_71009D7198, 0},
    {"Pa_GuideB_00", sub_71009D7198, 0},
    {"Pa_GuideY_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102496ec8(sUnk_7102496ed8);
// 0x7100a4b67c
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102496f20::getEntries() const {
    return &sUnk_7102496ec8;
}
// 0x7100a4b688
Unk_7102496f20::~Unk_7102496f20() = default;

}  // namespace uking::ui

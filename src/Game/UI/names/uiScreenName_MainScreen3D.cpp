#include <prim/seadSafeString.h>
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

namespace {
sead::SafeString sLayoutName = "MainScreen3D_00";
}

// 0x7100a11d88
const char* ScreenMainScreen3D::getLayoutName_() const {
    return sLayoutName.cstr();
}


// ScreenMainScreen3D creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_710248d260[] = {
    {"Pa_NoticeZ_00", sub_71009D7198, 0},
    {"Pa_NoticeItem_00", sub_71009D7198, 0},
    {"Pa_NoticeItemShop_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_710248d250(sUnk_710248d260);
// 0x7100a10e9c
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248d2a8::getEntries() const {
    return &sUnk_710248d250;
}

}  // namespace uking::ui

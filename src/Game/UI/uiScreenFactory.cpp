#include "Game/UI/uiScreenFactory.h"
#include <math/seadMathCalcCommon.h>
#include "Game/UI/uiUtils.h"

namespace uking::ui {

ScreenFactory::~ScreenFactory() = default;

// 0x7100a82830
const char* ScreenFactory::m3(s32 id) {
    return sub_71010AD714(sead::Mathi::min(id, 98));
}

// 0x7100a82840
s32 ScreenFactory::m4() {
    return 99;
}

// 0x7100a82850
eui::DrawTarget ScreenFactory::getDrawTarget(u8 index) const {
    return eui::DrawTarget(index > 1);
}

}  // namespace uking::ui

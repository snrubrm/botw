#include "Game/AI/Action/actionRequestOpenPopUpHelp.h"

namespace uking::ui {
void sub_7100A95DC4(s32 type);
}

namespace uking::action {

namespace {
// 0x7101e79d70: the original source enum is unknown.
const s32 sHelpTypes[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, 13, 14, 15, 16, 21};
}

RequestOpenPopUpHelp::RequestOpenPopUpHelp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestOpenPopUpHelp::~RequestOpenPopUpHelp() = default;

bool RequestOpenPopUpHelp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestOpenPopUpHelp::loadParams_() {
    getDynamicParam(&mHelpType_d, "HelpType");
}

bool RequestOpenPopUpHelp::oneShot_() {
    if (!mHelpType_d)
        return false;
    const s32 type = *mHelpType_d;
    if (type < 0 || type >= 18 || type == 12)
        return false;
    ui::sub_7100A95DC4(sHelpTypes[type]);
    return true;
}

}  // namespace uking::action

#include "Game/AI/Action/actionOpenPorch.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

OpenPorch::OpenPorch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPorch::~OpenPorch() = default;

bool OpenPorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPorch::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = false;
    _29 = false;
}

void OpenPorch::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPorch::loadParams_() {
    getDynamicParam(&mRockCategory_d, "RockCategory");
}

void OpenPorch::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_28) {
        if (!ui::isPauseMenuScreenNotClosed())
            setFinished();
    } else if (_29) {
        if (ui::isPauseMenuScreenNotClosed())
            _28 = true;
    } else {
        const s32 category = *mRockCategory_d;
        if (category == -1)
            ui::sub_7100A9E584(0);
        else
            ui::sub_7100A9E5F8(category);
        _29 = true;
    }
}

}  // namespace uking::action

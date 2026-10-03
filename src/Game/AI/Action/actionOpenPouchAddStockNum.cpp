#include "Game/AI/Action/actionOpenPouchAddStockNum.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

OpenPouchAddStockNum::OpenPouchAddStockNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPouchAddStockNum::~OpenPouchAddStockNum() = default;

bool OpenPouchAddStockNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPouchAddStockNum::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = false;
    _29 = false;
}

void OpenPouchAddStockNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPouchAddStockNum::loadParams_() {
    getDynamicParam(&mType_d, "Type");
}

void OpenPouchAddStockNum::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_29) {
        if (ui::isPauseMenuScreenNotClosed()) {
            _28 = true;
            _29 = false;
        }
    } else if (_28) {
        if (ui::sub_7100A9E864()) {
            setFinished();
            mFlags.set(Flag::Changeable);
        }
    } else {
        s32 kind;
        switch (*mType_d) {
        case 1:
            kind = 1;
            break;
        case 2:
            kind = 2;
            break;
        default:
            kind = 0;
            break;
        }
        ui::sub_7100A9E6B0(kind);
        _29 = true;
    }
}

}  // namespace uking::action

#include "Game/AI/Action/actionClosePouchAddStockNum.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

ClosePouchAddStockNum::ClosePouchAddStockNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ClosePouchAddStockNum::~ClosePouchAddStockNum() = default;

bool ClosePouchAddStockNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ClosePouchAddStockNum::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void ClosePouchAddStockNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void ClosePouchAddStockNum::loadParams_() {}

void ClosePouchAddStockNum::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_1c) {
        auto* ui = ui::UI::instance();
        if (ui && ui->sub_71010A5888())
            ui->sub_71010A6B98(nullptr);
        if (ui::isPauseMenuScreenNotClosed())
            return;
        if (ui && ui->sub_71010A5888())
            return;
        setFinished();
    } else {
        if (!ui::sub_7100A9E7AC()) {
            setFailed();
        } else {
            _1c = ui::sub_7100A9E91C();
            auto* ui = ui::UI::instance();
            if (ui && ui->sub_71010A5888())
                ui->sub_71010A6B98(nullptr);
            return;
        }
    }
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action

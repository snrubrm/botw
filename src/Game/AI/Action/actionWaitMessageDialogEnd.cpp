#include "Game/AI/Action/actionWaitMessageDialogEnd.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

WaitMessageDialogEnd::WaitMessageDialogEnd(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitMessageDialogEnd::~WaitMessageDialogEnd() = default;

bool WaitMessageDialogEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitMessageDialogEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitMessageDialogEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitMessageDialogEnd::loadParams_() {}

void WaitMessageDialogEnd::calc_() {
    if (auto* ui = ui::UI::instance()) {
        if (ui->sub_71010A5888() && ui->sub_71010A5C68())
            setFinished();
    }
}

}  // namespace uking::action

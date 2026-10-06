#include "Game/AI/Action/actionSimpleOpenMessageDialogAction.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

SimpleOpenMessageDialogAction::SimpleOpenMessageDialogAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SimpleOpenMessageDialogAction::~SimpleOpenMessageDialogAction() = default;

bool SimpleOpenMessageDialogAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleOpenMessageDialogAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = false;
}

void SimpleOpenMessageDialogAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleOpenMessageDialogAction::loadParams_() {
    getDynamicParam(&mMstxt_d, "Mstxt");
    getDynamicParam(&mLabel_d, "Label");
}

void SimpleOpenMessageDialogAction::calc_() {
    if (!ui::UI::instance()) {
        setFailed();
        mFlags.set(Flag::Changeable);
    }
    const bool was_opened = _40;
    const bool is_open = ui::UI::instance()->sub_71010A5888();
    if (was_opened) {
        if (!is_open) {
            setFinished();
            mFlags.set(Flag::Changeable);
        }
    } else if (!is_open) {
        ui::UI::instance()->messageDialogViewStyleStuff(sead::SafeString(mMstxt_d.cstr()),
                                                        sead::SafeString(mLabel_d.cstr()), nullptr, 0.0f,
                                                        0, false, false);
        _40 = true;
    }
}

}  // namespace uking::action

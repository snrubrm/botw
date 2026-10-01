#include "Game/AI/Action/actionOpenMessageDialog.h"

namespace uking::action {

OpenMessageDialog::OpenMessageDialog(const InitArg& arg) : OpenMessageDialogBase(arg) {}

OpenMessageDialog::~OpenMessageDialog() = default;

bool OpenMessageDialog::init_(sead::Heap* heap) {
    return OpenMessageDialogBase::init_(heap);
}

void OpenMessageDialog::enter_(ksys::act::ai::InlineParamPack* params) {
    OpenMessageDialogBase::enter_(params);
}

void OpenMessageDialog::leave_() {
    OpenMessageDialogBase::leave_();
}

void OpenMessageDialog::loadParams_() {
    OpenMessageDialogBase::loadParams_();
    getDynamicParam(&mASName_d, "ASName");
}

void OpenMessageDialog::calc_() {
    OpenMessageDialogBase::calc_();
}

const char* OpenMessageDialog::m32() {
    return mASName_d.cstr();
}

}  // namespace uking::action

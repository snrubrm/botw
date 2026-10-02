#include "Game/AI/Action/actionOpenMessageDialog.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

OpenMessageDialog::OpenMessageDialog(const InitArg& arg) : OpenMessageDialogBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OpenMessageDialog::~OpenMessageDialog() {
    ;
}

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

void OpenMessageDialog::m33(const sead::SafeString& name) {
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115BC28(name, -1.0f);
}

}  // namespace uking::action

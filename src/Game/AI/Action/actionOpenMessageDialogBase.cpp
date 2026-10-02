#include "Game/AI/Action/actionOpenMessageDialogBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

OpenMessageDialogBase::OpenMessageDialogBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogBase::~OpenMessageDialogBase() = default;

bool OpenMessageDialogBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenMessageDialogBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenMessageDialogBase::leave_() {
    if (_74)
        _64.resetMotionType(_64.sub_710072ACF8(mActor));
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115C11C();
}

void OpenMessageDialogBase::loadParams_() {
    getDynamicParam(&mCloseDialogOption_d, "CloseDialogOption");
    getDynamicParam(&mMessageOpenDelayTime_d, "MessageOpenDelayTime");
    getDynamicParam(&mIsCloseMessageDialog_d, "IsCloseMessageDialog");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mIsWaitAS_d, "IsWaitAS");
    getDynamicParam(&mMessageId_d, "MessageId");
}

void OpenMessageDialogBase::calc_() {
    ksys::act::ai::Action::calc_();
}

const char* OpenMessageDialogBase::m32() {
    return nullptr;
}

void OpenMessageDialogBase::m33(const sead::SafeString& name) {}

}  // namespace uking::action

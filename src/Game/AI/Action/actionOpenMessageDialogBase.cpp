#include "Game/AI/Action/actionOpenMessageDialogBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

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

void OpenMessageDialogBase::sub_7100218184() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    sead::Matrix34f mtx;
    sead::Matrix34f delta;
    as_list->sub_710115D4A4(as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8), &delta, true);
    mtx.setMul(*static_cast<const sead::Matrix34f*>(actor->get7d0()), delta);
    auto* controller = actor->getCharacterController();
    auto* body = actor->getMainBody();
    if (controller) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F60500(mtx);
    } else if (body) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
        body->setTransform(mtx);
    } else {
        actor->sub_71011C88C0(mtx);
    }
}

}  // namespace uking::action

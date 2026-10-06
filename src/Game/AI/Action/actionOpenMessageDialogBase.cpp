#include "Game/AI/Action/actionOpenMessageDialogBase.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

OpenMessageDialogBase::OpenMessageDialogBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogBase::~OpenMessageDialogBase() = default;

bool OpenMessageDialogBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the UI-null / speaker tests are combined differently (the original branches on `ui` first, then on
// `!speaker` via eor; ours folds both into a cset + two tbnz).
void OpenMessageDialogBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _74 = false;
    _70 = false;
    _71 = false;
    _72 = false;
    _73 = false;
    ksys::act::sActorDebugFlagsMaybe.reset(6);
    auto* ui = uking::ui::UI::instance();
    const bool is_speaker = ksys::evt::EventSystem::instance()->mSpeaker.sub_7100E497B8(mActor);
    if (ui && !is_speaker && ui->sub_71010A5888()) {
        _72 = true;
        ui->sub_71010A6B98(nullptr);
    }
    if (*mIsBecomingSpeaker_d)
        ksys::evt::EventSystem::instance()->setSpeaker(mActor);
    if (ui && ui->sub_71010A5A54())
        ui->x_0(false);
    if (*mMessageOpenDelayTime_d >= 1) {
        const sead::SafeString id(m32());
        if (!id.isEmpty()) {
            m33(id);
            _71 = true;
        }
        _60 = *mMessageOpenDelayTime_d;
    } else {
        _60 = 0;
    }
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

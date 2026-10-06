#include "Game/AI/Action/actionTurnAndLookAtToObjectNow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnAndLookAtToObjectNow::TurnAndLookAtToObjectNow(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookAtToObjectNow::~TurnAndLookAtToObjectNow() = default;

bool TurnAndLookAtToObjectNow::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookAtToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObject::enter_(params);
}

void TurnAndLookAtToObjectNow::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void TurnAndLookAtToObjectNow::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookAtToObjectNow::calc_() {
    LookAtObject::calc_();
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    auto* controller = mActor->getCharacterController();
    if (isFinished() || isFailed()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    if (controller)
        m41(controller);
}

void TurnAndLookAtToObjectNow::m40() {
    auto* controller = mActor->getCharacterController();
    if (_d0) {
        setFinished();
        return;
    }

    _38.y = 0;
    _38.normalize();
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0;
    front.normalize();
    if (controller) {
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

}  // namespace uking::action

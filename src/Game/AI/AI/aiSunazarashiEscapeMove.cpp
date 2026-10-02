#include "Game/AI/AI/aiSunazarashiEscapeMove.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

SunazarashiEscapeMove::SunazarashiEscapeMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiEscapeMove::~SunazarashiEscapeMove() = default;

bool SunazarashiEscapeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiEscapeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f front = mActor->getMtx().getBase(2);
    front.normalize();

    auto* controller = mActor->getCharacterController();
    auto* as_list = mActor->getASList();
    if (controller) {
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDBC(front);
        as_list->x_6(10, 0, controller->sub_7100F5EF00() / 30.0f);
    }

    if (as_list->sub_710115ED5C(66, 10))
        changeChild("逃走", params);
    else
        changeChild("地上逃走", params);
}

void SunazarashiEscapeMove::calc_() {
    auto* controller = mActor->getCharacterController();
    auto* as_list = mActor->getASList();
    if (controller)
        as_list->x_6(10, 0, controller->sub_7100F5EF00() / 30.0f);

    const bool underground = as_list->sub_710115ED5C(66, 10);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (underground) {
        if (isCurrentChild("地上逃走")) {
            changeChild("逃走", &params);
            return;
        }
    } else {
        if (isCurrentChild("逃走")) {
            changeChild("地上逃走", &params);
            return;
        }
    }
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void SunazarashiEscapeMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiEscapeMove::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

#include "Game/AI/Action/actionPlayerTurnInner.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerTurnInner::PlayerTurnInner(const InitArg& arg) : PlayerAction(arg) {}

PlayerTurnInner::~PlayerTurnInner() = default;

bool PlayerTurnInner::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerTurnInner::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    m33();
    m34();
}

void PlayerTurnInner::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PlayerTurnInner::loadParams_() {}

void PlayerTurnInner::calc_() {
    auto* controller = mActor->getCharacterController();
    if (isFinished()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (isFailed()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (controller) {
        m35(controller);
    }
}

void PlayerTurnInner::m33() {
    _20.set(sead::Vector3f::zero);
    static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(true, 0, &sead::Vector3f::zero, nullptr,
                                                           &sead::Vector3f::zero);
}

// NON_MATCHING: load / store scheduling of the camera direction and the front vector (all operations are the
// same; the original squares x before z in the normalisation)
void PlayerTurnInner::m34() {
    auto* controller = mActor->getCharacterController();
    auto* camera = sub_710092DA50();
    const auto& from = camera->_38._0;
    const auto& to = camera->_38._c;
    _20.x = to.x - from.x;
    _20.z = to.z - from.z;
    _20.y = 0.0f;
    _20.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, _20, sead::Vector3f::ey);
    mActor->getASList()->x_6(6, 0, angle * axis.y * sead::Mathf::rad2deg(1.0f));
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoTurn", true, -1.0f);
    mActor->getASList()->sub_710115EFD0(0, true, false, 0.1f);
    if (controller) {
        controller->sub_7100F5EDD8(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

bool PlayerTurnInner::isChangeable() const {
    return false;
}

}  // namespace uking::action

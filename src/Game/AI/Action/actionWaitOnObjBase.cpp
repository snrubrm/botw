#include "Game/AI/Action/actionWaitOnObjBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WaitOnObjBase::WaitOnObjBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitOnObjBase::~WaitOnObjBase() = default;

bool WaitOnObjBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitOnObjBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitOnObjBase::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        _ac.resetMotionType(controller);
        controller->sub_7100F5EE1C(_a0);
        controller->sub_7100F5E754(true);
        controller->sub_7100F5EDE8(sead::Vector3f::ey);
    }
}

void WaitOnObjBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void WaitOnObjBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionLastBossJustGuard.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LastBossJustGuard::LastBossJustGuard(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossJustGuard::~LastBossJustGuard() = default;

bool LastBossJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool LastBossJustGuard::isFinished() const {
    return mFlags.isOn(Flag::Finished) || isFinishedAS(0, 0);
}

void LastBossJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("GuardJust", false, 0, 0, -1.0f);
}

void LastBossJustGuard::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossJustGuard::loadParams_() {}

void LastBossJustGuard::calc_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

bool LastBossJustGuard::isChangeable() const {
    return true;
}

}  // namespace uking::action

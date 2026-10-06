#include "Game/AI/Action/actionGanonChangeState.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GanonChangeState::GanonChangeState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonChangeState::~GanonChangeState() = default;

bool GanonChangeState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonChangeState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonChangeState::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EE1C(_60 * 29.0f);
        controller->sub_7100F5EEB8(1.0f);
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.resetBit(3);
}

void GanonChangeState::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonChangeState::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GanonChangeState::isChangeable() const {
    return false;
}

}  // namespace uking::action

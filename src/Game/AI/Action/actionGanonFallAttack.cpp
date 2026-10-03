#include "Game/AI/Action/actionGanonFallAttack.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GanonFallAttack::GanonFallAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonFallAttack::~GanonFallAttack() = default;

bool GanonFallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonFallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonFallAttack::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
        boss->_14e8.resetBit(3);
}

void GanonFallAttack::loadParams_() {
    getStaticParam(&mIsEmitShockWave_s, "IsEmitShockWave");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonFallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

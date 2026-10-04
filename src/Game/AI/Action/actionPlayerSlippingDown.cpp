#include "Game/AI/Action/actionPlayerSlippingDown.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerSlippingDown::PlayerSlippingDown(const InitArg& arg) : ksys::act::ai::Action(arg) {
    _68 = -1.0f;
}

PlayerSlippingDown::~PlayerSlippingDown() = default;

bool PlayerSlippingDown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerSlippingDown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerSlippingDown::leave_() {
    auto* player_link = mActor->m129();
    if (player_link->m375() && !player_link->m204()) {
        player_link->getAttachedTargetActor2()->sub_7100EB51E0();
        auto* controller = mActor->getCharacterController();
        controller->sub_7100F5F458(controller->sub_7100F5F234(nullptr) ? ksys::act::MotionType::_0 :
                                                                         ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F270(player_link->m384());
}

void PlayerSlippingDown::loadParams_() {
    getStaticParam(&mDamageInterval_s, "DamageInterval");
    getStaticParam(&mDamageVal_s, "DamageVal");
    getStaticParam(&mChangeableInterval_s, "ChangeableInterval");
    getStaticParam(&mChangeableIntervalInAir_s, "ChangeableIntervalInAir");
    getStaticParam(&mEnableSpeedDamage_s, "EnableSpeedDamage");
    getDynamicParam(&mInitAddLinearImpulse_d, "InitAddLinearImpulse");
    getDynamicParam(&mInitAddRollImpulse_d, "InitAddRollImpulse");
    getDynamicParam(&mIsAddImpulse_d, "IsAddImpulse");
}

void PlayerSlippingDown::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

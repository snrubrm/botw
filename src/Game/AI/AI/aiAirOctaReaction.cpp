#include "Game/AI/AI/aiAirOctaReaction.h"

namespace uking::ai {

AirOctaReaction::AirOctaReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

AirOctaReaction::~AirOctaReaction() = default;

bool AirOctaReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void AirOctaReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m44();
    EnemyDefaultReaction::enter_(params);
}

void AirOctaReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void AirOctaReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void AirOctaReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

bool AirOctaReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    if (EnemyDefaultReaction::m34(damage_mgr, damage_type))
        return true;

    if (isCurrentChild("突風") && damage_type == 20) {
        m39(nullptr);
        return true;
    }
    return false;
}

void AirOctaReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                          ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

}  // namespace uking::ai

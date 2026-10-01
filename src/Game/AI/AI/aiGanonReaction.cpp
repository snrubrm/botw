#include "Game/AI/AI/aiGanonReaction.h"

namespace uking::ai {

GanonReaction::GanonReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GanonReaction::~GanonReaction() = default;

bool GanonReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void GanonReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void GanonReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void GanonReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

bool GanonReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    if (_63)
        return false;
    return EnemyDefaultReaction::m34(damage_mgr, damage_type);
}

bool GanonReaction::m36() {
    _63 = true;
    return false;
}

void GanonReaction::m40(ksys::act::ai::InlineParamPack* params) {
    changeChild("小ダメージ");
}

}  // namespace uking::ai

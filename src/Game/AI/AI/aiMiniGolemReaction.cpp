#include "Game/AI/AI/aiMiniGolemReaction.h"
#include "Game/AI/aiUnk_7102450410.h"

namespace uking::ai {

MiniGolemReaction::MiniGolemReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

MiniGolemReaction::~MiniGolemReaction() = default;

bool MiniGolemReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void MiniGolemReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void MiniGolemReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void MiniGolemReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void MiniGolemReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool MiniGolemReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    auto* controller = sead::DynamicCast<Unk_7102450410>(
        *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
    if (damage_type <= 21 && sub_71007090F4(controller))
        damage_type = 22;
    return EnemyDefaultReaction::m34(damage_mgr, damage_type);
}

void MiniGolemReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                            ksys::act::ai::InlineParamPack* params) {
    auto* controller = sead::DynamicCast<Unk_7102450410>(
        *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
    if (damage_type <= 21 && sub_71007090F4(controller))
        damage_type = 22;
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

}  // namespace uking::ai

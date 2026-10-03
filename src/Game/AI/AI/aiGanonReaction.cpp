#include "Game/AI/AI/aiGanonReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void GanonReaction::calc_() {
    if (!getCurrentChild())
        return;
    if (isCurrentChild("デモ待ち大ダメージ"))
        return;

    sub_7100739900(mActor);
    if (auto* damage_mgr = sub_710072BA90(mActor)) {
        switch (damage_mgr->getField54()) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
            EnemyDefaultReaction::m44();
            changeChild("小ダメージ");
            return;
        case 13:
            return;
        default:
            break;
        }
    }
    EnemyDefaultReaction::calc_();
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

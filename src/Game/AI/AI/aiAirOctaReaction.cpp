#include "Game/AI/AI/aiAirOctaReaction.h"
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void AirOctaReaction::m42(ksys::act::ai::InlineParamPack* params) {
    if (auto* mgr = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a))
        mgr->mFlags |= 8;

    const char* name = "通常";
    if (auto* damage_mgr = sub_710072BA90(mActor)) {
        if (damage_mgr->getField50() == 3 && damage_mgr->checkDamageFlags(0))
            name = "ヘッドショット";
    }
    mActor->getASList()->goLimpFromHeadShotMaybe(0x2f, name, 0);
    EnemyDefaultReaction::m42(params);
}

void AirOctaReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                          ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

}  // namespace uking::ai

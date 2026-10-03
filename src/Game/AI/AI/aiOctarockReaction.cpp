#include "Game/AI/AI/aiOctarockReaction.h"
#include "Game/AI/aiUnk_7102450d10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

OctarockReaction::OctarockReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

OctarockReaction::~OctarockReaction() = default;

bool OctarockReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void OctarockReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void OctarockReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void OctarockReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void OctarockReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsWigBreackByGust_s, "IsWigBreackByGust");
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

bool OctarockReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    if (!EnemyDefaultReaction::m34(damage_mgr, damage_type))
        return false;

    if (!isCurrentChild("突風"))
        sub_71004ED6D4();
    return true;
}

void OctarockReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                           ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
    if (!isCurrentChild("突風"))
        sub_71004ED6D4();
}

void OctarockReaction::sub_71004ED6D4() {
    if (mActor->getConnectedCalcChild()) {
        mActor->resetConnectedCalcChild(false);
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714ED4(false);
    }
}

void OctarockReaction::m39(ksys::act::ai::InlineParamPack* params) {
    if (*mIsWigBreackByGust_s)
        sub_71004ED6D4();
    EnemyDefaultReaction::m39(params);
}

void OctarockReaction::m42(ksys::act::ai::InlineParamPack* params) {
    sub_71004ED6D4();
    EnemyDefaultReaction::m42(params);
}

}  // namespace uking::ai

#include "Game/AI/Action/actionForkStalEnemyForceDamage.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/Damage/dmgStruct20.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkStalEnemyForceDamage::ForkStalEnemyForceDamage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkStalEnemyForceDamage::~ForkStalEnemyForceDamage() = default;

bool ForkStalEnemyForceDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyForceDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkStalEnemyForceDamage::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStalEnemyForceDamage::loadParams_() {
    getStaticParam(&mDamage_s, "Damage");
    getStaticParam(&mASTrigType_s, "ASTrigType");
    getStaticParam(&mDamageType_s, "DamageType");
    getStaticParam(&mDamageAttr_s, "DamageAttr");
    getStaticParam(&mLifeRate_s, "LifeRate");
}

void ForkStalEnemyForceDamage::calc_() {
    auto* actor = mActor;
    const auto* life = actor->getLife();
    if ((life ? f32(*life) : 1.0f) / f32(actor->getMaxLife()) <= *mLifeRate_s &&
        *mASTrigType_s == 0 && sub_71005DD780(mActor, 0x3b, nullptr, 0, 0)) {
        auto* manager = mActor->getDamageMgr();
        if (manager) {
            uking::dmg::Struct20_2 damage;
            damage.mField_8 = *mDamage_s;
            if (*mDamageType_s == 0)
                damage.mField_14 = 4;
            if (*mDamageAttr_s == 0)
                damage.mField_18 = 0x16;
            if (manager->mStruct20_a) {
                manager->mField_30.lock();
                manager->mStruct20_a->combineMaybe(&damage);
                manager->mField_30.unlock();
            }
        }
    }
}

}  // namespace uking::action

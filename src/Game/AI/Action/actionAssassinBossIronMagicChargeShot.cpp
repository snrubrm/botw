#include "Game/AI/Action/actionAssassinBossIronMagicChargeShot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AssassinBossIronMagicChargeShot::AssassinBossIronMagicChargeShot(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronMagicChargeShot::~AssassinBossIronMagicChargeShot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mIronBallNum_s; ++i) {
            key.format("%s%d", mIronBallPartsName_s.cstr(), i);
            enemy->sub_7100D3CFEC(key);
        }
    }
    _48.freeBuffer();
    _58.freeBuffer();
}

bool AssassinBossIronMagicChargeShot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AssassinBossIronMagicChargeShot::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _58.fill(false);
    _68 = 0;
}

void AssassinBossIronMagicChargeShot::leave_() {
    ksys::act::ai::Action::leave_();
}

void AssassinBossIronMagicChargeShot::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
    getStaticParam(&mLevel2AttackLifeRatio_s, "Level2AttackLifeRatio");
}

void AssassinBossIronMagicChargeShot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

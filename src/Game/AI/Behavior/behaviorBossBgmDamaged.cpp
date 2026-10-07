#include "Game/AI/Behavior/behaviorBossBgmDamaged.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

BossBgmDamaged::BossBgmDamaged(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BossBgmDamaged::~BossBgmDamaged() = default;

bool BossBgmDamaged::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the original loads the DamageInfoMgr singleton after the getLife() call (matches with a once-used local
// `const bool dead = life ? *life < 1 : false;` before the call)
void BossBgmDamaged::m7() {
    auto* manager = sub_710072BA90(mActor);
    if (!manager)
        return;

    const s32 damage = manager->getDamage();
    const s32 field54 = manager->getField54();
    if (damage >= 1 && field54 >= 2) {
        const bool flag = manager->checkDamageFlags(7) || manager->checkDamageFlags(0) ||
                          manager->checkDamageFlags(1) || manager->checkDamageFlags(8) ||
                          manager->checkDamageFlags(12);
        auto* life = mActor->getLife();
        dmg::DamageInfoMgr::instance()->get450().sub_710065D674(
            mActor, damage, flag, life ? *life < 1 : false, *mDieType_s == 1);
    }
}

void BossBgmDamaged::m8() {}

void BossBgmDamaged::m9() {}

void BossBgmDamaged::loadParams() {
    getStaticParam(&mDieType_s, "DieType");
}

}  // namespace uking::behavior

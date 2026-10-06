#include "Game/AI/Behavior/behaviorBossBgm.h"
#include "Game/Damage/dmgInfoManager.h"

namespace uking::behavior {

BossBgm::BossBgm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BossBgm::~BossBgm() = default;

bool BossBgm::m6(sead::Heap* heap) {
    return true;
}

void BossBgm::m7() {}

// Inline-only in the original (name is a guess): the switch is compiled to a lookup table (0x1e7af50: 2, 1, 3, 5, 4).
static s32 getBossBgmValue(s32 boss_type) {
    switch (boss_type) {
    case 0:
        return 2;
    case 1:
        return 1;
    case 2:
        return 3;
    case 3:
        return 5;
    case 4:
        return 4;
    default:
        return 0;
    }
}

void BossBgm::m8() {
    const s32 value = getBossBgmValue(*mBossType_s);
    dmg::DamageInfoMgr::instance()->get450().sub_710065D428(mActor, value);
}

void BossBgm::m9() {
    dmg::DamageInfoMgr::instance()->get450().sub_710065D5D4(mActor);
}

void BossBgm::loadParams() {
    getStaticParam(&mBossType_s, "BossType");
}

}  // namespace uking::behavior

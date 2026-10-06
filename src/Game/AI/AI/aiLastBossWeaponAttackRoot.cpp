#include "Game/AI/AI/aiLastBossWeaponAttackRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LastBossWeaponAttackRoot::LastBossWeaponAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossWeaponAttackRoot::~LastBossWeaponAttackRoot() = default;

bool LastBossWeaponAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossWeaponAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->enable();
    }
    auto* target = sub_71005D9050(mActor);
    if ((target && target->hasProc() && ksys::act::isPlayerProfile(target)) ||
        mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        sub_710047EA10();
        return;
    }
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_2) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sub_710047ED84();
        return;
    }
    auto* damage = sub_710072BA90(mActor);
    if (damage && s32(damage->getDamage()) >= 1)
        sub_710047ED84();
    else
        changeToWait();
}

void LastBossWeaponAttackRoot::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
}

void LastBossWeaponAttackRoot::loadParams_() {
    getStaticParam(&mEnemyType_s, "EnemyType");
    getStaticParam(&mIsStartBossBgm_s, "IsStartBossBgm");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mReappearanceDist_s, "ReappearanceDist");
    getStaticParam(&mReappearanceDistOffset_s, "ReappearanceDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

void LastBossWeaponAttackRoot::changeToWait() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(true, "IsResetEndTime", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai

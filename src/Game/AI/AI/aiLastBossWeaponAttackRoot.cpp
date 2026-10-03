#include "Game/AI/AI/aiLastBossWeaponAttackRoot.h"
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
    ksys::act::ai::Ai::enter_(params);
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

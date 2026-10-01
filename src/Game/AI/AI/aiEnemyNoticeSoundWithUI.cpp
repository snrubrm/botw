#include "Game/AI/AI/aiEnemyNoticeSoundWithUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyNoticeSoundWithUI::EnemyNoticeSoundWithUI(const InitArg& arg) : EnemyNoticeSound(arg) {}

EnemyNoticeSoundWithUI::~EnemyNoticeSoundWithUI() = default;

bool EnemyNoticeSoundWithUI::init_(sead::Heap* heap) {
    return EnemyNoticeSound::init_(heap);
}

void EnemyNoticeSoundWithUI::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSound::enter_(params);
    _50 = *mTargetActor_d;
    if (!ksys::act::isPreyOrSwarm(mTargetActor_d) &&
        (ksys::act::isPlayerProfile(mTargetActor_d) ||
         ksys::act::isNotLivingCreature(mTargetActor_d))) {
        mActor->m93(2, 0.0f);
    }
}

void EnemyNoticeSoundWithUI::leave_() {
    EnemyNoticeSound::leave_();
    mActor->m93(0, 0.0f);
}

void EnemyNoticeSoundWithUI::loadParams_() {
    EnemyNoticeSound::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

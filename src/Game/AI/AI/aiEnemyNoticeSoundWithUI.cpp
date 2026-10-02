#include "Game/AI/AI/aiEnemyNoticeSoundWithUI.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/AI/aiUnk_71005D6D10.h"
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

void EnemyNoticeSoundWithUI::calc_() {
    EnemyNoticeSound::calc_();
    if (!isCurrentChild("行動"))
        return;

    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    if (_50 == *mTargetActor_d)
        return;

    auto* notice_targets = sub_71005D9D68(mActor);
    if (getCurrentChild()->isChangeable()) {
        if (!notice_targets || !notice_targets->sub_71002DC9E8(*mTargetActor_d, 4, true))
            sub_71003A6298();
    }
    _50 = *mTargetActor_d;
}

}  // namespace uking::ai

#include "Game/AI/Action/actionSiteBossSwordCreateIronPile.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

SiteBossSwordCreateIronPile::SiteBossSwordCreateIronPile(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordCreateIronPile::~SiteBossSwordCreateIronPile() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mCreateNum_s) {
            for (s32 i = 0; i <= *mCreateNum_s; ++i) {
                const sead::FormatFixedSafeString<64> name("IronPile%d", i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

bool SiteBossSwordCreateIronPile::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordCreateIronPile::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordCreateIronPile::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordCreateIronPile::loadParams_() {
    getStaticParam(&mCreateNum_s, "CreateNum");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mAppearPosDist_s, "AppearPosDist");
    getStaticParam(&mAppearPosHeight_s, "AppearPosHeight");
    getStaticParam(&mCreateWaitTime_s, "CreateWaitTime");
    getStaticParam(&mIgnitionInterval_s, "IgnitionInterval");
    getStaticParam(&mPileScale_s, "PileScale");
    getStaticParam(&mNotCreateRange_s, "NotCreateRange");
    getStaticParam(&mIsRotate_s, "IsRotate");
    getStaticParam(&mIsGuard_s, "IsGuard");
    getStaticParam(&mIsChasePlayer_s, "IsChasePlayer");
    getStaticParam(&mIsRemainBoss_s, "IsRemainBoss");
    getStaticParam(&mWaitAS_s, "WaitAS");
    getStaticParam(&mCreatePileAS_s, "CreatePileAS");
    getStaticParam(&mThunderActorName_s, "ThunderActorName");
    getStaticParam(&mNotCreatePosBase_s, "NotCreatePosBase");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSwordCreateIronPile::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionSiteBossSwordCreateIronPile.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

SiteBossSwordCreateIronPile::SiteBossSwordCreateIronPile(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordCreateIronPile::~SiteBossSwordCreateIronPile() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mCreateNum_s) {
            for (s32 i = 0; i <= *mCreateNum_s; ++i) {
                const sead::FormatFixedSafeString<64> name("IronPile%d", i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

// NON_MATCHING: the original compares the kind before the IsRemainBoss flag in its ccmp; same values.
bool SiteBossSwordCreateIronPile::init_(sead::Heap* heap) {
    if (sub_71005D6D10())
        return true;
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return true;

    ksys::act::InstParamPack params;
    params->add(sead::SafeString("Normal"), "DropTable");
    params->add(false, "EnableRevival");
    params->add(false, "IsFixedPlace");
    params->add(true, "IsInGround");
    params->add(*mAttackPower_s, "AttackPower");
    s32 power_level = getNumberOfDeadBlights();
    const s32 kind = boss->_1534 & ~3;
    if (!*mIsRemainBoss_s && kind == 4)
        power_level = 3;
    if (kind == 8)
        power_level = 4;
    const s32 add_power = power_level * *mAddAttackPower_s;
    params->add(*mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    params->add(*mAtMinDamage_s, "AtMinDamage");
    params->add(add_power, "AddAtkPower");
    params->add(mThunderActorName_s, "ActorName");

    for (int i = 0; i <= *mCreateNum_s; ++i) {
        sead::FormatFixedSafeString<64> name("IronPile%d", i);
        boss->_1128.sub_7100D3CED8(name, heap);
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            "SiteBossSwordIronPile", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params,
            true, false);
        if (actor) {
            actor->clearFadeInCreate();
            boss->_1128.sub_7100D3D108(name, actor);
        }
    }
    return true;
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

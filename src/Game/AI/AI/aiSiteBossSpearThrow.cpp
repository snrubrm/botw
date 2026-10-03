#include "Game/AI/AI/aiSiteBossSpearThrow.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SiteBossSpearThrow::SiteBossSpearThrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearThrow::~SiteBossSpearThrow() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC("Spear");
}

bool SiteBossSpearThrow::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Spear").hasProc())
            return true;

        enemy->sub_7100D3CED8("Spear", heap);

        s32 num_dead_blights = getNumberOfDeadBlights();
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            const s32 kind = boss->_1534 & ~3;
            if (kind == 4)
                num_dead_blights = 3;
            else if (kind == 8)
                num_dead_blights = 4;
        }

        const s32 add_power = *mAddAttackPower_s * num_dead_blights;
        const s32 attack_power = *mAttackPower_s + add_power;
        const s32 min_damage = *mAtMnDamage_s + add_power;
        ksys::act::InstParamPack pack;
        pack->add(attack_power, "AttackPower");
        pack->add(1.0f, "ScaleTime");
        ksys::act::ActorCreator::addScale(pack, 1.0f);
        pack->add(min_damage, "AtMinDamage");
        auto* spear = ksys::act::ActorCreator::instance()->createActor(
            mThrowActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &pack, true, false);
        if (spear) {
            spear->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
            enemy->sub_7100D3D108("Spear", spear);
            spear->clearFadeInCreate();
        }
    }
    return true;
}

void SiteBossSpearThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: the original addresses SiteBoss _2378-_237b through one base register (as if they
// were members of a struct at SiteBoss+0x2378; same as SiteBossSpearAttackBase::leave_)
void SiteBossSpearThrow::leave_() {
    if (_68.isAllocatedOrFailed())
        _68.deleteProc();

    if (isActorGoingBackToRootAi()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("Spear"), &accessor);
            if (accessor.hasProc() && accessor.isStateCalc())
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_2378) {
            boss->_237a = boss->_237b;
            boss->_2378 = 0;
        }
    }
}

void SiteBossSpearThrow::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMnDamage_s, "AtMnDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SiteBossSpearThrow::isFailed() const {
    if (getCurrentChild())
        return getCurrentChild()->isFailed();
    return false;
}

bool SiteBossSpearThrow::isFinished() const {
    if (getCurrentChild())
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai

#include "Game/AI/AI/aiSiteBossSpearThrow.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SiteBossSpearThrow::SiteBossSpearThrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearThrow::~SiteBossSpearThrow() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC("Spear");
}

bool SiteBossSpearThrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
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

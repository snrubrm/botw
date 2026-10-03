#include "Game/AI/AI/aiSiteBossSwordIronPileRoot.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

SiteBossSwordIronPileRoot::SiteBossSwordIronPileRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg), _c0() {}

SiteBossSwordIronPileRoot::~SiteBossSwordIronPileRoot() {
    if (_b0.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (_c0.sub_7101241AD8(1))
        _c0.fadeXLink();
}

bool SiteBossSwordIronPileRoot::init_(sead::Heap* heap) {
    if (sub_71005D6D10())
        return true;

    ksys::act::InstParamPack pack;
    pack->add(*mAttackPower_m, "AttackPower");
    pack->add(*mAttackPowerForPlayer_m + *mAddAtkPower_m, "AttackPowerForPlayer");
    pack->add(*mAtMinDamage_m, "AtMinDamage");
    auto* actor = ksys::act::ActorCreator::instance()->createActor(
        mActorName_m.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false);
    if (actor)
        _b0.acquire(actor, false);
    return true;
}

void SiteBossSwordIronPileRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c = ksys::Timer(*mFallWaitCount_s, *mFallWaitCount_s);
    _84 = 0;
    _88 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi2();
    if (auto* body = mActor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    changeChild("待機");
    _80 = false;
    _81 = false;
    _82 = false;
}

void SiteBossSwordIronPileRoot::leave_() {
    if (!mActor->getConnectedCalcChild())
        return;
    mActor->resetConnectedCalcChild(false);
    if (_b0.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        if (accessor.isStateCalc())
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void SiteBossSwordIronPileRoot::loadParams_() {
    getStaticParam(&mFallWaitCount_s, "FallWaitCount");
    getStaticParam(&mFallSpeed_s, "FallSpeed");
    getStaticParam(&mSlopeRate_s, "SlopeRate");
    getMapUnitParam(&mAddAtkPower_m, "AddAtkPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mActorName_m, "ActorName");
}

// NON_MATCHING: the original null-checks the message reference (cbz x1)
bool SiteBossSwordIronPileRoot::handleMessage_(const ksys::Message* message) {
    if (message->getBrokerId() != u32(-1))
        return false;
    if (message->getType() == 0x8000004 || message->getType() == 0x3000007) {
        _80 = true;
        return true;
    }
    if (message->getType() == 0x800005b) {
        _81 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai

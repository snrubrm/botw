#include "Game/AI/AI/aiBokoblinRestraint.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the BaseProcHandle ctor argument setup)
BokoblinRestraint::BokoblinRestraint(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinRestraint::~BokoblinRestraint() = default;

void BokoblinRestraint::enter_(ksys::act::ai::InlineParamPack* params) {
    _84 = sub_7100726F28(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    sub_7100332BF0();
    _78.reset(*mLostTimer_s);
}

// inline-only in the original (the same sequence is inlined into sub_7100332BF0, sub_7100333040 and calc_);
// name is a guess.
inline void BokoblinRestraint::spawnRock() {
    ksys::act::InstParamPack pack;
    pack->addPosition(mActor->getMtx().getTranslation());
    ksys::act::ActorCreator::addScale(pack, sead::GlobalRandom::instance()->getF32() * 0.4f + 0.8f);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "Rock_Weapon", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_68, &pack, nullptr,
        1);
}

void BokoblinRestraint::calc_() {
    const sead::Vector3f target = *mTargetPos_d;
    sub_71005DB1D8(mActor, target);

    if (getCurrentChild()->isFinishedOrFailed()) {
        if (isCurrentChild("投石")) {
            if (!mActor->getConnectedCalcChild() && !_68.isAllocatedOrFailed())
                spawnRock();
            sub_7100332BF0();
        } else if (!sub_7100333040()) {
            sub_7100332BF0();
        }
    }

    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isChangeable() && sub_71003331A0())
        setFailed();
}

void BokoblinRestraint::sub_7100332BF0() {
    if (!mActor->getConnectedCalcChild() && !_68.isAllocatedOrFailed())
        spawnRock();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("威嚇", &pack);
}

void BokoblinRestraint::sub_71003332B4() {
    mActor->setConnectedCalcChild(_68.releaseAndWakeProc(), false);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("投石", &pack);
}

bool BokoblinRestraint::sub_7100333040() {
    if (!_84)
        return false;

    if (_68.isProcReady()) {
        sub_71003332B4();
        return true;
    }

    if (!mActor->getConnectedCalcChild() && _68.hasProcCreationFailed()) {
        _68.deleteProcIfFailed();
        spawnRock();
    }
    return false;
}

void BokoblinRestraint::leave_() {
    _68.deleteProc();
    mActor->resetConnectedCalcChild(false);
    sub_71005DB3EC(mActor);
}

void BokoblinRestraint::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mLostRange_s, "LostRange");
}

bool BokoblinRestraint::isChangeable() const {
    if (getCurrentChild()->isChangeable())
        return true;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

}  // namespace uking::ai

#include "Game/AI/AI/aiBokoblinRestraint.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

BokoblinRestraint::BokoblinRestraint(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinRestraint::~BokoblinRestraint() = default;

void BokoblinRestraint::enter_(ksys::act::ai::InlineParamPack* params) {
    _84 = sub_7100726F28(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    changeToThreaten();
    _78.reset(*mParams.mLostTimer_s);
}

// inline-only in the original (the same sequence is inlined into changeToThreaten, sub_7100333040 and calc_);
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
    const sead::Vector3f target = *mParams.mTargetPos_d;
    sub_71005DB1D8(mActor, target);

    if (getCurrentChild()->isFinishedOrFailed()) {
        if (isCurrentChild("投石")) {
            if (!mActor->getConnectedCalcChild() && !_68.isAllocatedOrFailed())
                spawnRock();
            changeToThreaten();
        } else if (!sub_7100333040()) {
            changeToThreaten();
        }
    }

    getCurrentChild()->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isChangeable() && sub_71003331A0())
        setFailed();
}

bool BokoblinRestraint::sub_71003331A0() {
    sead::Vector3f pos;
    sead::Vector3f dir;
    if (auto* awareness = mActor->getAwareness()) {
        awareness->_230.getBase(dir, 2);
        pos = awareness->_2c8;
    } else {
        mActor->getMtx().getTranslation(pos);
        mActor->getMtx().getBase(dir, 2);
    }

    if (sub_710072DEF0(sub_71005D960C(mActor), *mParams.mLostRange_s, *mParams.mLostVMin_s,
                       *mParams.mLostVMax_s, pos, dir, sead::Mathf::pi(), sead::Mathf::maxNumber(),
                       0.0f)) {
        _78.reset(*mParams.mLostTimer_s);
    } else {
        _78.update();
    }
    return _78.value <= sead::Mathf::epsilon();
}

void BokoblinRestraint::changeToThreaten() {
    if (!mActor->getConnectedCalcChild() && !_68.isAllocatedOrFailed())
        spawnRock();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("威嚇", &pack);
}

void BokoblinRestraint::changeToThrowRock() {
    mActor->setConnectedCalcChild(_68.releaseAndWakeProc(), false);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    changeChild("投石", &pack);
}

bool BokoblinRestraint::sub_7100333040() {
    if (!_84)
        return false;

    if (_68.isProcReady()) {
        changeToThrowRock();
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
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mBaseDist_s, "BaseDist");
    getStaticParam(&mParams.mLostVMin_s, "LostVMin");
    getStaticParam(&mParams.mLostVMax_s, "LostVMax");
    getStaticParam(&mParams.mLostTimer_s, "LostTimer");
    getStaticParam(&mParams.mLostRange_s, "LostRange");
}

bool BokoblinRestraint::isChangeable() const {
    if (getCurrentChild()->isChangeable())
        return true;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

bool BokoblinRestraint::sub_71003331A0() {
    auto& timer = _78;
    sead::Vector3f pos, dir;
    if (auto* awareness = mActor->getAwareness()) {
        awareness->_230.getBase(dir, 2);
        pos = awareness->_2c8;
    } else {
        mActor->getMtx().getTranslation(pos);
        mActor->getMtx().getBase(dir, 2);
    }

    if (sub_710072DEF0(sub_71005D960C(mActor), *mParams.mLostRange_s, *mParams.mLostVMin_s, *mParams.mLostVMax_s, pos, dir,
                       sead::Mathf::pi(), std::numeric_limits<f32>::max(), 0.0f)) {
        timer = ksys::Timer(*mParams.mLostTimer_s, *mParams.mLostTimer_s);
    } else {
        timer.update();
    }
    return timer.value <= sead::Mathf::epsilon();
}

}  // namespace uking::ai

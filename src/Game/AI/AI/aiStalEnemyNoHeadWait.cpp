#include "Game/AI/AI/aiStalEnemyNoHeadWait.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StalEnemyNoHeadWait::StalEnemyNoHeadWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyNoHeadWait::~StalEnemyNoHeadWait() = default;

bool StalEnemyNoHeadWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyNoHeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 time = *mRebootTimer_s;
    _60.mTimer = ksys::Timer(time, time);
    if (*mIsExistActiveActor_d) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("活動者有", &pack);
    } else if (*mIsExistLivingHead_d) {
        sub_710059E790();
    } else {
        changeChild("生存者無");
    }
}

void StalEnemyNoHeadWait::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("活動者有")) {
        if (!*mIsExistLivingHead_d &&
            (child->isChangeable() || child->isFinished() || child->isFailed())) {
            changeChild("生存者無");
        } else if (!*mIsExistActiveActor_d &&
                   (child->isChangeable() || child->isFinished() || child->isFailed())) {
            sub_710059E790();
        } else if (child->isFinished() || child->isFailed()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("活動者有", &pack);
        } else {
            child->setDynamicParam(*mTargetPos_d, "TargetPos");
        }
    } else if (isCurrentChild("生存者有")) {
        child->setDynamicParam(*mIsExistActiveActor_d, "IsFinish");
        if (!*mIsExistLivingHead_d &&
            (child->isChangeable() || child->isFinished() || child->isFailed())) {
            changeChild("生存者無");
        } else if (*mIsExistActiveActor_d &&
                   (child->isChangeable() || child->isFinished() || child->isFailed())) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("活動者有", &pack);
        } else if (child->isFinished() || child->isFailed()) {
            sub_710059E790();
        } else {
            child->setDynamicParam(*mTargetPos_d, "TargetPos");
        }
    } else if (isCurrentChild("生存者無")) {
        if (*mIsExistActiveActor_d) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("活動者有", &pack);
        } else if (*mIsExistLivingHead_d) {
            sub_710059E790();
        } else if (child->isFinished() || child->isFailed()) {
            changeChild("生存者無");
        }
    }
    sub_710059ED70();
}

void StalEnemyNoHeadWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyNoHeadWait::loadParams_() {
    getStaticParam(&mRebootDistance_s, "RebootDistance");
    getStaticParam(&mRebootTimer_s, "RebootTimer");
    getDynamicParam(&mIsExistLivingHead_d, "IsExistLivingHead");
    getDynamicParam(&mIsExistActiveActor_d, "IsExistActiveActor");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void StalEnemyNoHeadWait::sub_710059E790() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(false, "IsFinish", -1);
    const f32 time = *mRebootTimer_s;
    _60.mTimer = ksys::Timer(time, time);
    changeChild("生存者有", &pack);
}

void StalEnemyNoHeadWait::sub_710059ED70() {
    if (!isCurrentChild("生存者有"))
        return;

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
    if (diff.length() > *mRebootDistance_s) {
        if (!(_60.mTimer.value <= sead::Mathf::epsilon()))
            _60.sub_7100D3BCE4();
        if (_60.mTimer.value <= sead::Mathf::epsilon()) {
            if (auto* unit = sub_7100726FF4(mActor))
                unit->_8.set(0x40);
        }
    } else {
        const f32 time = *mRebootTimer_s;
        _60.mTimer = ksys::Timer(time, time);
    }
}

}  // namespace uking::ai

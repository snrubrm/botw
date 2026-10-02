#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

SiteBossSwordApproachRoot::SiteBossSwordApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordApproachRoot::~SiteBossSwordApproachRoot() = default;

bool SiteBossSwordApproachRoot::isFailed() const {
    if (!isCurrentChild("移動開始") && getCurrentChild()) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return _8c;
    }
    return ksys::act::ai::Ai::isFinished();
}

bool SiteBossSwordApproachRoot::isFinished() const {
    if (!isCurrentChild("移動開始") && getCurrentChild()) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return !_8c;
    }
    return ksys::act::ai::Ai::isFinished();
}

bool SiteBossSwordApproachRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c = false;
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }
    sub_71007A36BC(mActor);
    act::SiteBoss::x_2(sead::DynamicCast<act::SiteBoss>(mActor), mActor);
    _88 = 0;
    if (*mIsPlayRunStartAS_s) {
        _78 = ksys::Timer(0, 0, 1.0f);
        if (m39()) {
            m36();
            return;
        }
    }
    if (!m35())
        _8c = true;
    if (isSlowTimeMaybe())
        m38();
    else
        m37();
}

void SiteBossSwordApproachRoot::calc_() {
    if (!getCurrentChild()) {
        setFailed();
        return;
    }

    if (isCurrentChild("移動開始")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            _78 = ksys::Timer(0, 0, 1.0f);
            _88 = 0;
            if (!m35())
                _8c = true;
            if (isSlowTimeMaybe())
                m38();
            else
                m37();
        }
        return;
    }

    if (isCurrentChild("移動")) {
        sub_71005DB41C(mActor);
        if (isSlowTimeMaybe()) {
            m38();
            return;
        }
        if (_78.value > _88 + 5.0f) {
            _88 = _78.value;
            if (!m35())
                _8c = true;
            getCurrentChild()->setDynamicParam(_a8, "MoveDstPos");
        }
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (_8c)
                setFailed();
            else
                setFinished();
        }
    } else if (isCurrentChild("スロー時移動")) {
        sub_71005DB41C(mActor);
        if (!isSlowTimeMaybe()) {
            m37();
            return;
        }
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
    }
    _78.update();
}

void SiteBossSwordApproachRoot::leave_() {
    sub_71007A3540(mActor);
    sub_71005DB434(mActor);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_14c8._30.isOnAll(6))
            act::SiteBoss::sub_71002D3498(boss, mActor);
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
        client->enable();
}

void SiteBossSwordApproachRoot::loadParams_() {
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveWidth_s, "MoveWidth");
    getStaticParam(&mBaseOffsetY_s, "BaseOffsetY");
    getStaticParam(&mPredictMoveFrame_s, "PredictMoveFrame");
    getStaticParam(&mIsCloseMove_s, "IsCloseMove");
    getStaticParam(&mIsPlayRunStartAS_s, "IsPlayRunStartAS");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mOldTargetPos_d, "OldTargetPos");
}

void SiteBossSwordApproachRoot::m34(sead::Vector3f* out) {
    *out = *mTargetPos_d;
}

void SiteBossSwordApproachRoot::m36() {
    changeChild("移動開始");
}

void SiteBossSwordApproachRoot::m37() {
    if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
        client->disable();
    sub_71007A36BC(mActor);
    act::SiteBoss::x_2(sead::DynamicCast<act::SiteBoss>(mActor), mActor);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(_90, "AfterImage0Pos", -1);
    params.addVec3(_9c, "AfterImage1Pos", -1);
    params.addVec3(_a8, "MoveDstPos", -1);
    params.addFloat(_78.value, "CurrentFrame", -1);
    params.addBool(*mIsCloseMove_s, "IsCloseMove", -1);
    changeChild("移動", &params);
}

void SiteBossSwordApproachRoot::m38() {
    sub_71007A3540(mActor);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_14c8._30.isOnAll(6))
            act::SiteBoss::sub_71002D3498(boss, mActor);
    }

    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(_90, "AfterImage0Pos", -1);
    params.addVec3(_9c, "AfterImage1Pos", -1);
    params.addVec3(_a8, "MoveDstPos", -1);
    params.addFloat(_78.value, "CurrentFrame", -1);
    changeChild("スロー時移動", &params);
}

// NON_MATCHING: the original loads the three actor position components before the target position
bool SiteBossSwordApproachRoot::m39() {
    return (mActor->getMtx().getTranslation() - *mTargetPos_d).squaredLength() >= 64.0f;
}

}  // namespace uking::ai

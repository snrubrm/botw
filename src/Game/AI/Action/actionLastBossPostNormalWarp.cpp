#include "Game/AI/Action/actionLastBossPostNormalWarp.h"
#include "math/seadMathCalcCommon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// 0x71002c67e8 (declaration only).
void sub_71002C67E8(f32 a1, ksys::act::Actor* actor, bool a3);
// 0x71002c67e8 (declared only): Actor::x_3(value) then the follow-up with the value or 0 (as the flag says).
void sub_71002C67E8(f32 value, ksys::act::Actor* actor, bool flag);

namespace uking::action {

void LastBossPostNormalWarp::m33(f32 value, ksys::act::Actor* actor, bool flag) {
    sub_71002C67E8(value, actor, flag);
}

LastBossPostNormalWarp::LastBossPostNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossPostNormalWarp::~LastBossPostNormalWarp() = default;

bool LastBossPostNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossPostNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossPostNormalWarp::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }

    if (!*mIsKeepDisableDraw_d) {
        if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
            client->enable();
        if (auto* client = mActor->getAttention()->getClientByName("AutoAim"))
            client->enable();
        m32();
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
    }

    if (!*mIsTurnToTarget_s)
        sub_71005DB434(mActor);
}

void LastBossPostNormalWarp::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mNoCryAnime_s, "NoCryAnime");
    getStaticParam(&mIsTurnToTarget_s, "IsTurnToTarget");
    getStaticParam(&mIsCheckDistFromTarget_s, "IsCheckDistFromTarget");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsKeepDisableDraw_d, "IsKeepDisableDraw");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossPostNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

bool LastBossPostNormalWarp::isFinished() const {
    if ((!_70 && isFinishedAS(0, 0) && *mWaitTime_s <= 0.0f) ||
        (_70 && _78 <= sead::Mathf::epsilon())) {
        if (!*mIsCheckDistFromTarget_s)
            return true;
        if ((mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f)
            return false;
        return true;
    }
    return false;
}

bool LastBossPostNormalWarp::isFailed() const {
    if ((!_70 && isFinishedAS(0, 0) && *mWaitTime_s <= 0.0f) || _78 <= sead::Mathf::epsilon()) {
        if (*mIsCheckDistFromTarget_s &&
            (mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f) {
            return true;
        }
    }
    return false;
}

void LastBossPostNormalWarp::m33(f32 a1, ksys::act::Actor* actor, bool a3) {
    sub_71002C67E8(a1, actor, a3);
}

}  // namespace uking::action

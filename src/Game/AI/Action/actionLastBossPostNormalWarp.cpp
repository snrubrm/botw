#include "Game/AI/Action/actionLastBossPostNormalWarp.h"
#include <random/seadGlobalRandom.h>
#include "math/seadMathCalcCommon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// 0x71002c67e8 (declaration only).
void sub_71002C67E8(f32 a1, ksys::act::Actor* actor, bool a3);
// 0x71002c65c8 (declaration only).
void sub_71002C65C8(ksys::act::Actor* actor, bool a2, bool a3);
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
    const f32 wait_time = *mWaitTime_s;
    const f32 time =
        wait_time != 0.0f ? wait_time + wait_time * sead::GlobalRandom::instance()->getF32() : 0.0f;
    _78 = ksys::Timer(time, time);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const ksys::act::MotionType motion_type = controller->sub_7100F5F0E4();
    if (int(motion_type) != int(ksys::act::MotionType::Hover))
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    if (!*mNoCryAnime_s)
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    if (!*mIsKeepDisableDraw_d) {
        _84 = ksys::Timer(30.0f, 30.0f);
        _74 = 30.0f;
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(mActor, 8, &query, 0, 0)) {
            sub_71002C65C8(mActor, false, true);
            _74 = query._10;
            _84 = ksys::Timer(_74, _74);
        }
    }
    _70 = *mNoCryAnime_s;
    if (!*mIsTurnToTarget_s) {
        sub_71005DB3EC(mActor);
        sub_71005DB41C(mActor);
    }
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
        (_70 && _78.value <= sead::Mathf::epsilon())) {
        if (!*mIsCheckDistFromTarget_s)
            return true;
        if ((mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f)
            return false;
        return true;
    }
    return false;
}

bool LastBossPostNormalWarp::isFailed() const {
    if ((!_70 && isFinishedAS(0, 0) && *mWaitTime_s <= 0.0f) || _78.value <= sead::Mathf::epsilon()) {
        if (*mIsCheckDistFromTarget_s &&
            (mActor->getMtx().getTranslation() - *mTargetPos_d).length() >= 140.0f) {
            return true;
        }
    }
    return false;
}

void LastBossPostNormalWarp::m32() {
    sub_71007A3540(mActor);
    if (!*mIsPartsActorTgOn_d)
        return;
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<act::Enemy>(actor))
        return;
    auto* enemy = static_cast<act::Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        auto& link = part->mLink;
        if (!link.hasProc())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateCalc()) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000030), nullptr, true);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000017), nullptr, true);
        }
    }
}

}  // namespace uking::action

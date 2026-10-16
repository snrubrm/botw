#include "Game/Actor/Action/actionLastBossPreNormalWarp.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"

// 0x71002c65c8 (declaration only).
void sub_71002C65C8(ksys::act::Actor* actor, bool a2, bool a3);
// 0x71002c67e8 (declaration only).
void sub_71002C67E8(f32 a1, ksys::act::Actor* actor, bool a3);
// 0x71002c67e8 (declared only): Actor::x_3(value) then the follow-up with the value or 0 (as the flag says).
void sub_71002C67E8(f32 value, ksys::act::Actor* actor, bool flag);

namespace uking::action {

void LastBossPreNormalWarp::m34(f32 value, ksys::act::Actor* actor, bool flag) {
    sub_71002C67E8(value, actor, flag);
}

LastBossPreNormalWarp::LastBossPreNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossPreNormalWarp::~LastBossPreNormalWarp() = default;

bool LastBossPreNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: store merging only (ours merges _64 / _68 into one stp, the original keeps them as separate stores
// around the _6c / _6e byte stores and the actor flag load)
void LastBossPreNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = ksys::Timer(*mPreWarpWaitTime_s, *mPreWarpWaitTime_s);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const ksys::act::MotionType motion_type = controller->sub_7100F5F0E4();
    if (int(motion_type) != int(ksys::act::MotionType::Hover))
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    playAS("Wait", true, 0, 0, -1.0f);
    auto* actor = mActor;
    _68 = 30.0f;
    _6c = false;
    _6e = false;
    _5c.rate = -1.0f;
    _6d = actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20);
    _5c.value = 30.0f;
    _5c.previous_value = 30.0f;
    if (auto* boss = sead::DynamicCast<act::LastBoss>(actor))
        boss->_14c8 = ksys::eft::searchAndEmitELink(boss, "WarpCharge");
}

void LastBossPreNormalWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossPreNormalWarp::loadParams_() {
    getStaticParam(&mPreWarpWaitTime_s, "PreWarpWaitTime");
    getStaticParam(&mPosReduce_s, "PosReduce");
    getStaticParam(&mIsDeleteEffect_s, "IsDeleteEffect");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
}

// NON_MATCHING: regalloc only (the original keeps the _6c load live across the _6e check).
void LastBossPreNormalWarp::calc_() {
    const auto check_warp_start = [this] {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(mActor, 8, &query, 0, 0)) {
            m32();
            m33();
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000);
            _68 = query._10;
            _5c = ksys::Timer(_68, _68);
        }
    };

    _50.update();
    if (!_6c && _50.value <= std::numeric_limits<f32>::epsilon()) {
        _6c = true;
        if (_6d || mASName_s.isEmpty())
            return;
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
        _6e = true;
        _5c = ksys::Timer(30.0f, 30.0f);
        _68 = 30.0f;
        check_warp_start();
        return;
    }

    if (_6e) {
        check_warp_start();
        if (sub_71005DD798(mActor, 8, nullptr, 0, 0)) {
            _5c.update();
            const f32 rate = sead::Mathf::clamp(1.0f - _5c.value / _68, 0.0f, 1.0f);
            m34(rate, mActor, *mIsPartsWarpEffectSync_d);
        }
    }

    if (_6c && (!_6e || isFinishedAS(0, 0))) {
        setFinished();
        if (!_6d) {
            sub_71002C65C8(mActor, true, *mIsPartsWarpEffectSync_d);
            if (*mIsDeleteEffect_s) {
                if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor))
                    boss->_14c8.fade();
                ksys::eft::searchAndEmitELink(mActor, "WarpFlash");
            }
            m32();
            m33();
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000);
        }
    }

    if (auto* controller = mActor->getCharacterController()) {
        sub_71007377D4(controller, *mPosReduce_s);
        controller->sub_7100F5FB24(sead::Vector3f(0.0f, 0.0f, 0.0f));
    }
}

void LastBossPreNormalWarp::m33() {
    if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
        client->disable();
    if (auto* client = mActor->getAttention()->getClientByName("AutoAim"))
        client->disable();
}

void LastBossPreNormalWarp::m32() {
    sub_71007A36BC(mActor);
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<act::Enemy>(actor))
        return;
    auto* enemy = static_cast<act::Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        auto& link = part->mLink;
        if (!link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateCalc()) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800002f), nullptr, true);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000018), nullptr, true);
        }
    }
}

}  // namespace uking::action

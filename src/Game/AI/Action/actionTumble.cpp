#include "Game/AI/Action/actionTumble.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: the original stores the zero members 0x90-0xdc one by one; ours merges them into a memset (the original's
// in-class initialisation must be interleaved with non-zero stores).
Tumble::Tumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Tumble::~Tumble() = default;

void Tumble::enter_(ksys::act::ai::InlineParamPack* params) {
    setDamageCallbackTiming(mActor, 0, &_68);
    for (s32 i = 0; i < 3; ++i) {
        for (s32 j = 0; j < 3; ++j)
            _9c(i, j) = mActor->getMtx()(i, j);
    }
    mActor->getCharacterController();
    _c0 = sead::Vector3f::zero;
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    const sead::Vector3f velocity = front * *mTumbleSpeed_s;
    _1c.value = _1c.prev_value = velocity.length();
    sead::Vector3f side;
    mActor->getMtx().getBase(side, 0);
    side *= 0.1f;
    _28.value = side;
    _28.prev_value = side;
    _90 = front;
    _10c = velocity;
    _108 = 0;
    playAS("DownBack", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        sub_710072C1B4(controller, _90);
        controller->sub_7100F5EF08(true);
    }
}

void Tumble::leave_() {
    sub_71005DA114(mActor, &_68);
}

void Tumble::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mTumblingTime_s, "TumblingTime");
    getStaticParam(&mGetUpTime_s, "GetUpTime");
    getStaticParam(&mLandCheckNode_s, "LandCheckNode");
    getStaticParam(&mTumbleAngle_s, "TumbleAngle");
    getStaticParam(&mTumbleSpeed_s, "TumbleSpeed");
}

bool Tumble::handleMessage_(const ksys::Message* message) {
    return true;
}

void Tumble::calc_() {
    if (_108 == 0) {
        _1c.updateStats();
        _28.updateStats();
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5E7F0(_1c.value * 30.0f);
            const sead::Vector3f angular_velocity = _28.value * 30.0f;
            controller->sub_7100F5FB24(angular_velocity);
        }
        if (std::acos(mActor->getMtx().m[1][1]) >= *mTumbleAngle_s) {
            _108 = 1;
            sub_710029D098();
        }
    } else if (_108 == 1) {
        mActor->getCharacterController();
        sub_710029D1BC();
        if (_58.value <= sead::Mathf::epsilon())
            setFinished();
        else
            _58.update();
    }
}

void Tumble::sub_710029D098() {
    playAS("DownBackWait", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    _58.reset(*mTumblingTime_s);
    mActor->getCharacterController();
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->_868)
            actor->_868->sub_71006ED484();
    }
    if (sub_71005D8B60(mActor))
        return;
    _10c.y += 0.4f;
    sub_71005D8748(mActor, _10c, false, false, nullptr, false);
}

// NON_MATCHING: stack layout only (the original keeps `offset` and `key` 8 bytes apart; frame 0x70 vs 0x60).
void Tumble::sub_710029D1BC() {
    if (!mActor->getCharacterController())
        return;
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    const auto key = mActor->getModel()->searchBone("Spine_1");
    const sead::Vector3f offset = sead::Vector3f::ey;
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Matrix34f mtx;
    if (actor->_868)
        actor->_868->sub_71006EE07C(&mtx, key, offset);
    else
        mtx = actor->getMtx();
    controller->sub_7100F5F938(mtx);
}

}  // namespace uking::action

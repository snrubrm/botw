#include "Game/AI/Action/actionTurnAndChargeAndShoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TurnAndChargeAndShoot::TurnAndChargeAndShoot(const InitArg& arg) : ChargeAndShoot(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
TurnAndChargeAndShoot::~TurnAndChargeAndShoot() {
    ;
}

bool TurnAndChargeAndShoot::init_(sead::Heap* heap) {
    return ChargeAndShoot::init_(heap);
}

void TurnAndChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ChargeAndShoot::enter_(params);
    _e8 = 0;
    sub_710073FA90(&_b8, mActor);
    const f32 speed = mActor->getAngVelocity().length();
    _dc.value = speed;
    _dc.prev_value = speed;
}

void TurnAndChargeAndShoot::leave_() {
    ChargeAndShoot::leave_();
}

void TurnAndChargeAndShoot::loadParams_() {
    ChargeAndShoot::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void TurnAndChargeAndShoot::calc_() {
    ChargeAndShoot::calc_();
}

void TurnAndChargeAndShoot::m34() {
    ShootArrow::sub_710024E90C();
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    sub_710073FA94(&_b8, actor);
    if (as_list && sub_71005DD798(actor, 41, nullptr, 0, 0) && _e8 == 0 &&
        actor->getAngVelocity().length() < sead::Mathf::deg2rad(1.0f)) {
        _e8 = sub_710029D8F8();
    }
    sub_710029DA28();
}

s32 TurnAndChargeAndShoot::sub_710029D8F8() {
    auto* actor = mActor;
    sead::Vector3f axis;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    to_target.normalize();
    const sead::Vector3f front = actor->getMtx().getBase(2);
    ksys::util::sub_71011EF10C(&axis, front, to_target, sead::Vector3f::ey);
    if (axis.x < 0.0f && axis.z < 0.0f)
        axis = -axis;
    return axis.y == 0.0f ? 0 : (axis.y > 0.0f ? 1 : -1);
}

void TurnAndChargeAndShoot::sub_710029DA28() {
    auto* actor = mActor;
    const s32 turn = _e8;
    if (turn) {
        if (!(sub_710029D8F8() * turn > 0))
            _e8 = 0;
        _dc.lerp(*mRotSpeed_s, 0.16f, *mRotSpeed_s / 10.0f);
        _dc.updateStats();
        const sead::Vector3f up = getUpDir(actor);
        const sead::Vector3f pos = actor->getMtx().getTranslation();
        sead::Vector3f to_target = *mTargetPos_d;
        to_target -= pos;
        to_target.normalize();
        sub_710074006C(&_b8, to_target, up, true, 0.12f, _dc.value, _dc.value / 10.0f);
        sub_7100740F1C(_b8, actor);
    } else {
        sub_7100738AA8(actor, *mStopRotSpeedRatio_s);
        const f32 speed = actor->getAngVelocity().length();
        _dc.value = speed;
        _dc.prev_value = speed;
    }
}

}  // namespace uking::action

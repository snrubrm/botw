#include "Game/AI/Action/actionBattleCloseMoveActionBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

BattleCloseMoveActionBase::BattleCloseMoveActionBase(const InitArg& arg) : BattleCloseAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BattleCloseMoveActionBase::~BattleCloseMoveActionBase() {
    ;
}

bool BattleCloseMoveActionBase::init_(sead::Heap* heap) {
    return BattleCloseAction::init_(heap);
}

void BattleCloseMoveActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseAction::enter_(params);
    auto* actor = mActor;
    const sead::Vector3f& vel = actor->getVelocity();
    const f32 speed = sead::Mathf::sqrt(vel.x * vel.x + vel.z * vel.z);
    _98.value = _98.prev_value = speed;
    if (auto* cc = actor->getCharacterController()) {
        cc->sub_7100F60AE0();
        cc->sub_7100F5E7F0(_98.value * 30.0f);
    }
}

void BattleCloseMoveActionBase::leave_() {
    BattleCloseAction::leave_();
}

void BattleCloseMoveActionBase::loadParams_() {
    BattleCloseAction::loadParams_();
}

void BattleCloseMoveActionBase::calc_() {
    BattleCloseAction::calc_();
}

bool BattleCloseMoveActionBase::m37(ksys::phys::CharacterController* controller, f32 speed,
                                    const sead::Vector3f& dir) {
    sead::Vector3f hit_pos;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);

    if (sub_710072FEC4(mActor, front, 2.0f, &hit_pos, true, nullptr) && !hit_pos.isNan()) {
        f32 dist = sead::Vector2f(hit_pos.x - pos.x, hit_pos.z - pos.z).length();
        if (dist < m35() * 0.1f)
            return false;
        dist *= 0.5f;
        _98.chase(dist, 1.0f);
        const f32 max_speed = m35();
        _98.setToMin(max_speed);
    } else {
        const f32 target = m35();
        _98.chase(target, sead::Mathf::abs(_98.value - m35()) * 0.1f);
        _98.setToMin(speed);
    }
    _98.updateStats();
    sub_7100737708(controller, _98.value);
    sub_710072C1B4(controller, front);
    return true;
}

}  // namespace uking::action

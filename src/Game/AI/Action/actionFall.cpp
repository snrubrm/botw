#include "Game/AI/Action/actionFall.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

Fall::Fall(const InitArg& arg) : ActionEx(arg) {}

Fall::~Fall() = default;

void Fall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);

    auto* actor = mActor;
    _44.value = actor->getAngVelocity();
    _44.prev_value = actor->getAngVelocity();
    _68 = actor->getVelocity();
    _68.y = 0.0f;
    const f32 length = _68.length();
    if (length > 0.0f)
        _68 *= 1.0f / length;
    _38.value = length;
    _38.prev_value = length;
    if (auto* controller = mActor->getCharacterController())
        sub_710072C1B4(controller, _68);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x40000);
}

void Fall::leave_() {
    ActionEx::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x40000);
}

void Fall::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mASName_s, "ASName");
}

void Fall::calc_() {
    _38 *= 0.992f;
    _38.updateStats();
    _44.lerp(sead::Vector3f::zero, 0.12f);
    _44.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_38.value * 30.0f);
        controller->sub_7100F5FB24(_44.value * 30.0f);
    }
}

bool Fall::isChangeable() const {
    return false;
}

bool Fall::isFinished() const {
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;
    if (*mInWaterDepth_s >= 0.0f) {
        f32 depth;
        if (actor->getCharacterController()) {
            depth = actor->getCharacterController()->_210;
        } else if (actor->get68f()) {
            const f32 y = actor->getMtx().m[1][3];
            depth = actor->get6f0() - y;
        } else {
            depth = 0.0f;
        }
        return depth >= *mInWaterDepth_s;
    }
    return false;
}

}  // namespace uking::action

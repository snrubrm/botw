#include "Game/AI/Action/actionFreeMoveToNearGround.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FreeMoveToNearGround::FreeMoveToNearGround(const InitArg& arg) : FreeMoveToTarget(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
FreeMoveToNearGround::~FreeMoveToNearGround() {
    ;
}

bool FreeMoveToNearGround::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

// NON_MATCHING: the original does not merge the Timer and VFRValue constant stores into 64-bit pairs
void FreeMoveToNearGround::enter_(ksys::act::ai::InlineParamPack* params) {
    _f8 = 0;
    FreeMoveToTarget::enter_(params);
    _e0 = ksys::Timer(45.0f, 45.0f);
    _ec.value = 1.0f;
    _ec.prev_value = 1.0f;
}

void FreeMoveToNearGround::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToNearGround::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mReduceSpeedRateWithWind_s, "ReduceSpeedRateWithWind");
    getStaticParam(&mWindVelocityLimit4Reduce_s, "WindVelocityLimit4Reduce");
}

// NON_MATCHING: the original keeps &_e0 in a callee-saved register (x20) across the Timer::update() call
// (same as AnmDrivenSpeedBackWalk::calc_); otherwise identical
void FreeMoveToNearGround::calc_() {
    FreeMoveToTarget::calc_();
    sead::Vector3f pos;
    if (sub_710016D7C0(&pos)) {
        _e0.update();
        if (_e0.value <= sead::Mathf::epsilon())
            setFailed();
        else if (_e0.value < 30.0f)
            _28 = pos;
    } else {
        _e0 = ksys::Timer(45.0f, 45.0f);
    }
}

f32 FreeMoveToNearGround::m36() {
    return _f8;
}

void FreeMoveToNearGround::m37(f32 speed, ksys::phys::CharacterController* controller) {
    FreeMoveToTarget::m37(speed, controller);
    if (controller && *mReduceSpeedRateWithWind_s < 1.0f) {
        if (auto* chemical = mActor->getChemicalStuff()) {
            const f32 limit =
                *mWindVelocityLimit4Reduce_s > 0.0f ? *mWindVelocityLimit4Reduce_s : 0.01f;
            const sead::Vector3f& wind =
                (chemical->_c & 0x1000000) ? sead::Vector3f::zero : chemical->_e4;
            const f32 rate = sead::Mathf::clamp(wind.length(), 0.0f, limit) / limit;
            const f32 target = rate * (*mReduceSpeedRateWithWind_s - 1.0f) + 1.0f;
            _ec.lerp(target, 0.22f);
            controller->sub_7100F5E7F0(_34.value * _ec.value);
        }
    }
}

bool FreeMoveToNearGround::m32(ksys::phys::CharacterController* controller) {
    if (!controller)
        return false;

    auto* actor = mActor;
    _28 = *mTargetPos_d - actor->getMtx().getTranslation();
    const f32 distance = _28.normalize();
    if (distance <= *mFinishRadius_s)
        _28 = controller->get64();
    _f8 = *mParams.mSpeed_s * sead::GlobalRandom::instance()->getF32Range(0.7f, 1.3f);
    sub_710016B114(controller->sub_7100F5EF00());
    return true;
}

}  // namespace uking::action

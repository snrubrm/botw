#include "Game/AI/Action/actionFreeMoveToNearGround.h"
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

void FreeMoveToNearGround::calc_() {
    FreeMoveToTarget::calc_();
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

}  // namespace uking::action

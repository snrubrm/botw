#include "Game/AI/Action/actionInsectLevelFlyMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

InsectLevelFlyMove::InsectLevelFlyMove(const InitArg& arg) : LevelFlyMove(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
InsectLevelFlyMove::~InsectLevelFlyMove() {
    ;
}

bool InsectLevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMove::init_(heap);
}

void InsectLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMove::enter_(params);
    _158.value = 1.0f;
    _158.prev_value = 1.0f;
}

void InsectLevelFlyMove::leave_() {
    LevelFlyMove::leave_();
}

void InsectLevelFlyMove::loadParams_() {
    LevelFlyMove::loadParams_();
    getStaticParam(&mReduceSpeedRateWithWind_s, "ReduceSpeedRateWithWind");
    getStaticParam(&mWindVelocityLimit4Reduce_s, "WindVelocityLimit4Reduce");
}

void InsectLevelFlyMove::calc_() {
    LevelFlyMove::calc_();
    if (*mReduceSpeedRateWithWind_s < 1.0f) {
        auto* controller = mActor->getCharacterController();
        if (!controller)
            return;
        auto* chemical = mActor->getChemicalStuff();
        if (!chemical)
            return;
        const f32 limit = *mWindVelocityLimit4Reduce_s > 0.0f ? *mWindVelocityLimit4Reduce_s : 0.01f;
        const sead::Vector3f* wind =
            (chemical->_c & 0x1000000) ? &sead::Vector3f::zero : &chemical->_e4;
        const f32 speed = sead::Mathf::clamp(wind->length(), 0.0f, limit);
        const f32 target = speed / limit * (*mReduceSpeedRateWithWind_s - 1.0f) + 1.0f;
        _158.lerp(target, 0.22f);
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        velocity.x *= _158.value;
        velocity.y *= _158.value;
        velocity.z *= _158.value;
        controller->sub_7100F5F6FC(velocity);
    }
}

}  // namespace uking::action

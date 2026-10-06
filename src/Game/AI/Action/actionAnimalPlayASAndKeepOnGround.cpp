#include "Game/AI/Action/actionAnimalPlayASAndKeepOnGround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

AnimalPlayASAndKeepOnGround::AnimalPlayASAndKeepOnGround(const InitArg& arg)
    : PlayASForAnimalUnit(arg) {}

AnimalPlayASAndKeepOnGround::~AnimalPlayASAndKeepOnGround() = default;

bool AnimalPlayASAndKeepOnGround::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AnimalPlayASAndKeepOnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsChangeableStateFreeFall_a = false;
    PlayASForAnimalUnit::enter_(params);
    _78.reset(15.0f);
}

void AnimalPlayASAndKeepOnGround::leave_() {
    *mIsChangeableStateFreeFall_a = true;
    PlayASForAnimalUnit::leave_();
}

void AnimalPlayASAndKeepOnGround::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mDownImpulseScale_s, "DownImpulseScale");
    getStaticParam(&mIsUseDownImpulse_s, "IsUseDownImpulse");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
}

// NON_MATCHING: same control flow, calls and arithmetic; the original loads the velocity vector as a whole (ldp/ldr) before
// the dot product with the ground normal and keeps four fp registers (we keep two), so the instruction order and the
// frame (0x60 vs 0x50) differ.
void AnimalPlayASAndKeepOnGround::calc_() {
    PlayASForAnimalUnit::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (!*mIsUseDownImpulse_s)
        return;

    if (controller->sub_7100F5F0E4().value() != ksys::act::MotionType::_1) {
        _78.reset(15.0f);
        return;
    }

    sead::Vector3f velocity;
    _78.update();
    if (_78.value <= sead::Mathf::epsilon()) {
        controller->sub_7100F5F598(&velocity);
        if (velocity.dot(controller->get7c()) >= 0.0f)
            return;
        controller->sub_7100F5F598(&velocity);
        const f32 length = velocity.length();
        sead::Vector3f dir = -velocity;
        dir.normalize();
        const f32 factor = controller->sub_7100F60370();
        velocity = length * (dir * factor) * 0.4f;
    } else {
        f32 scale = *mDownImpulseScale_s;
        controller->sub_7100F5F598(&velocity);
        const f32 down = sead::Mathf::clampMin(velocity.y, 0.0f);
        scale = sead::Mathf::max(scale, down);
        const f32 factor = controller->sub_7100F60370();
        velocity = scale * (controller->get7c() * factor);
    }
    controller->sub_7100F60398(velocity);
}

}  // namespace uking::action

#include "Game/AI/Behavior/behaviorReduceUpwardVelocity.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

ReduceUpwardVelocity::ReduceUpwardVelocity(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ReduceUpwardVelocity::~ReduceUpwardVelocity() = default;

bool ReduceUpwardVelocity::m6(sead::Heap* heap) {
    return true;
}

void ReduceUpwardVelocity::m8() {}

void ReduceUpwardVelocity::m9() {}

void ReduceUpwardVelocity::loadParams() {
    getStaticParam(&mImpulseScale_s, "ImpulseScale");
    getStaticParam(&mMinDownImpulse_s, "MinDownImpulse");
}

void ReduceUpwardVelocity::m7() {
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    if (cc->sub_7100F5F0E4() != ksys::act::MotionType::_1)
        return;
    sead::Vector3f vec;
    cc->sub_7100F5F598(&vec);
    const f32 up = sead::Mathf::clampMin(vec.y, 0.0f);
    const f32 min_down = *mMinDownImpulse_s;
    const f32 impulse = (min_down > up ? min_down : up) * *mImpulseScale_s;
    vec = impulse * (cc->sub_7100F60370() * cc->get7c());
    cc->sub_7100F60398(vec);
}

}  // namespace uking::behavior

#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

// Kept in its own translation unit: defined next to sub_7100130AA4 the compiler would inline that callee, which the
// original calls out of line.
// NON_MATCHING: same arithmetic; ours keeps an extra 16-byte stack slot (stack frame 0x90 vs 0x80) and multiplies the
// rise vector with the operands swapped.
void FlyingCharacterDamageBase::sub_7100130868(ksys::phys::CharacterController* controller,
                                              const sead::Vector3f& dir) {
    sead::Vector3f velocity;
    sead::Vector3f horizontal;
    ksys::util::sub_71011EFA00(&horizontal, dir, controller->get7c());
    horizontal.normalize();
    const sead::Vector3f impulse = horizontal * sub_7100130AA4();
    sead::Vector3f rise = controller->get7c();
    rise *= *mRiseSpeed_s;

    controller->sub_7100F5F598(&velocity);
    ksys::util::sub_71011EFA00(&velocity, velocity, controller->get7c());
    controller->sub_7100F5F6FC(velocity * *mLastSpeedRatio_s - rise * 30.0f + impulse * 30.0f);
}

}  // namespace uking::action

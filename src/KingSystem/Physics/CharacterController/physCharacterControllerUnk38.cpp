#include "KingSystem/Physics/CharacterController/physCharacterControllerUnk38.h"

namespace ksys::phys {

// 0x7100f652f8: stores the velocity, normalized and scaled to 20 when it is longer than 20.
void CharacterControllerUnk38::sub_7100F652F8(const sead::Vector3f& velocity) {
    if (velocity.squaredLength() > 400.0f) {
        sead::Vector3f clamped = velocity;
        clamped.normalize();
        _50 = clamped * 20.0f;
    } else {
        _50 = velocity;
    }
}

}  // namespace ksys::phys

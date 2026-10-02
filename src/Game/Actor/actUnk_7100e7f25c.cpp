// TU 0x7100e7f25c-: ridden anim-driven movement helpers (after Rideable's RTTI functions).
#include "Game/Actor/actRideable.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::act {

// NON_MATCHING: stack slot order (the original puts the matrix below the direction vector) and
// register allocation of x / z
void sub_7100E7F318(ksys::as::ASList* as_list, ksys::phys::CharacterController* controller,
                    f32 scale) {
    const sead::Vector3f& move = as_list->sub_710115D2D4();
    const f32 x = move.x;
    const f32 z = move.z;
    sead::Vector3f velocity = as_list->sub_710115D3B8();

    sead::Matrix34f mtx;
    controller->physicsXXXGetMtx_1(&mtx);
    sead::Vector3f dir = {mtx(0, 2), 0.0f, mtx(2, 2)};
    dir.normalize();

    f32 ratio_x;
    f32 ratio_z;
    f32 distance;
    if (sead::Mathf::abs(z) >= sead::Mathf::abs(x)) {
        ratio_x = 1.0f;
        ratio_z = z == 0.0f ? 0.0f : sead::Mathf::clamp(x / z, -1.0f, 1.0f);
        distance = z;
    } else {
        ratio_z = 1.0f;
        ratio_x = x == 0.0f ? 0.0f : sead::Mathf::clamp(z / x, -1.0f, 1.0f);
        distance = x;
    }

    controller->sub_7100F5EDD8(ratio_x);
    controller->sub_7100F5EDE0(ratio_z);
    controller->sub_7100F5EDBC(dir);
    controller->sub_7100F5E7F0(distance * 30.0f * scale);
    velocity *= 30.0f;
    controller->sub_7100F5FB24(velocity);
}

void sub_7100E7F698(RideableBase* rideable, ksys::as::ASList* as_list,
                    ksys::phys::CharacterController* controller) {
    f32 scale = 1.0f;
    if (rideable) {
        if (rideable->_8.load() & 4) {
            controller->sub_7100F5EDD8(1.0f);
            controller->sub_7100F5EDE0(0.0f);
            return;
        }
        scale = 1.0f / rideable->_18._24;
    }
    sub_7100E7F318(as_list, controller, scale);
}

}  // namespace uking::act

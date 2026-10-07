#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <math/seadMathCalcCommon.h>

// NON_MATCHING: scheduling and zero-vector stores differ.
bool Unk_7100000fd0::sub_71000010E0(ksys::as::ASList* as_list,
                                  const sead::Vector3f& direction,
                                  const sead::Vector3f& forward, f32 max_rotate) {
    sead::Vector3f forward_horizontal{forward.x, 0.0f, forward.z};
    sead::Vector3f direction_horizontal{direction.x, 0.0f, direction.z};
    forward_horizontal.normalize();
    const f32 length = direction_horizontal.normalize();
    f32 rotation = 0.0f;
    if (length < sead::Mathf::epsilon()) {
        _30.set(0.0f, 0.0f, 0.0f);
    } else {
        const f32 dot = sead::Mathf::clamp(forward_horizontal.dot(direction_horizontal), -1.0f, 1.0f);
        const f32 angle = sead::Mathf::acos(dot);
        const f32 cross = forward_horizontal.x * direction_horizontal.z -
                          forward_horizontal.z * direction_horizontal.x;
        const f32 sign = cross >= 0.0f ? 1.0f : -1.0f;
        rotation = sead::Mathf::clamp(sign * angle / max_rotate, -1.0f, 1.0f);
    }
    as_list->x_6(1, 0, _40.sub_7100E7277C(rotation));
    as_list->x_6(2, 0, 1.0f);
    as_list->x_6(9, 0, 0.0f);
    return false;
}

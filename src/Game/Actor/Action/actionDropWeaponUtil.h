#pragma once

#include <math/seadVector.h>

namespace uking::action {

/// inline-only in the original; name is a guess. Evidence: the same sequence (length of the vector,
/// `if (length > 0) v *= length_new / length`, with the new length loaded from the parameter after
/// the vector was built and before the length is computed) appears in DropWeapon::sub_71000F8798
/// and ForkDropWeapon::sub_710014CE28.
inline void setVectorLength(sead::Vector3f* v, f32 new_length) {
    const f32 length = v->length();
    if (length > 0.0f)
        *v *= new_length / length;
}

}  // namespace uking::action

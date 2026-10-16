#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

// Unnamed free helper (placeholder name; users: InvincibleNearTarget, ViewWait*).

// 0x71005e0788: casts a ray from 0.5 above `pos` to 49.5 below it; true (with the hit position in `out`) when it
// hits ground flatter than 45 degrees whose material passes sub_71006F1E70 (SunazarashiRoot: sand check).
bool sub_71005E0788(const sead::Vector3f& pos, sead::Vector3f* out);

// 0x71005e0aac: whether the camera looks at `actor` within `angle` (compares the dot product of the
// direction from the camera to the actor with the camera direction against cos(angle)); only when
// the actor's target (an Enemy's `_c48._8`) is the player and, depending on `a`, the player is in
// the states m180 / m181 (/ x_29 / m179).
bool sub_71005E0AAC(ksys::act::Actor* actor, bool a, f32 angle);

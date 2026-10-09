#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkMotionState;

namespace hkSweptTransformUtil {

// Native 0x71015828F0 through 0x7101582B14 update a complete hkMotionState.
// Motion slots 15 through 19 forward the matching vector, quaternion or transform.
void sub_7101582B14(const hkVector4& centerOfMass, hkMotionState& motionState);
void sub_7101582A2C(const hkVector4& position, hkMotionState& motionState);
void sub_7101582A8C(const hkQuaternion& rotation, hkMotionState& motionState);
void sub_71015828F0(const hkVector4& position, const hkQuaternion& rotation,
                    hkMotionState& motionState);
void sub_7101582984(const hkTransform& transform, hkMotionState& motionState);

void freezeMotionState(hkSimdFloat32Parameter time, hkMotionState& motionState);

}  // namespace hkSweptTransformUtil

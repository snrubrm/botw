#include <Havok/Common/Base/Math/SweptTransform/hkSweptTransformfUtil.h>
#include <Havok/Common/Base/Types/Physics/MotionState/hkMotionState.h>

namespace hkSweptTransformUtil {

// NON_MATCHING: one add in the second center update uses commuted operands.
void sub_7101582B14(const hkVector4& centerOfMass, hkMotionState& motionState) {
    hkSweptTransform& sweptTransform = motionState.getSweptTransform();
    hkVector4 localDisplacement;
    localDisplacement.setSub(centerOfMass, sweptTransform.m_centerOfMassLocal);
    hkVector4 worldDisplacement;
    worldDisplacement._setRotatedDir(motionState.getTransform().getRotation(), localDisplacement);
    sweptTransform.m_centerOfMassLocal = centerOfMass;
    hkVector4 center0;
    center0.setAdd(sweptTransform.m_centerOfMass0, worldDisplacement);
    sweptTransform.m_centerOfMass0.setXYZ(center0);
    hkVector4 center1;
    center1.setAdd(sweptTransform.m_centerOfMass1, worldDisplacement);
    sweptTransform.m_centerOfMass1.setXYZ(center1);
}

// NON_MATCHING: vector loads, zeroing and update scheduling differ.
void sub_7101582A2C(const hkVector4& position, hkMotionState& motionState) {
    hkSweptTransform& sweptTransform = motionState.getSweptTransform();
    motionState.m_deltaAngle.setZero();
    motionState.getTransform().getTranslation() = position;
    hkVector4 rotatedCenter;
    rotatedCenter._setRotatedDir(motionState.getTransform().getRotation(),
                                sweptTransform.m_centerOfMassLocal);
    hkVector4 center;
    center.setAdd(position, rotatedCenter);
    sweptTransform.m_rotation0 = sweptTransform.m_rotation1;
    sweptTransform.m_centerOfMass0.setXYZ(center);
    sweptTransform.m_centerOfMass1.setXYZ_W(center, hkSimdReal(0.0f));
}

}  // namespace hkSweptTransformUtil

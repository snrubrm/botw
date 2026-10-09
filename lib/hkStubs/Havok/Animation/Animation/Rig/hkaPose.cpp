#include <Havok/Animation/Animation/Rig/hkaPose.h>

const hkArray<hkQsTransform>& hkaPose::getSyncedPoseLocalSpace() const {
    syncLocalSpace();
    return m_localPose;
}

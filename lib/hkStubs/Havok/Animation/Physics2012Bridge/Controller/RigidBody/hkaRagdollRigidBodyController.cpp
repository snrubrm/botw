#include <Havok/Animation/Physics2012Bridge/Controller/RigidBody/hkaRagdollRigidBodyController.h>

// 0x710157D22C
void hkaRagdollRigidBodyController::reinitialize() {
    hkaKeyFrameHierarchyUtility::initialize(m_bodyData, m_internalData.data());
}

// 0x710157D430
void hkaRagdollRigidBodyController::setBoneWeights(const hkReal* boneWeights) {
    m_bodyData.m_boneWeights = boneWeights;
}

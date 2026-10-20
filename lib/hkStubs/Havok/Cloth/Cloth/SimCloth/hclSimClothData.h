#pragma once
#include <Havok/Common/Base/hkBase.h>

// Reflection1415e10: size180, ParticleData size10/member records2533ea8.
class hclSimClothData : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hclSimClothData)
    ~hclSimClothData() override;
    // Seven reflected members at2533d90; vector gravity establishes alignment.
    struct SimulationInfo {
        hkVector4 m_gravity;
        hkReal m_globalDampingPerSecond;
        hkReal m_collisionTolerance;
        hkUint32 m_subSteps;
        hkBool m_pinchDetectionEnabled;
        hkBool m_landscapeCollisionEnabled;
        hkBool m_transferMotionEnabled;
    };
    struct ParticleData {
        hkReal m_mass;
        hkReal m_invMass;
        hkReal m_radius;
        hkReal m_friction;
    };
    SimulationInfo m_simulationInfo;
    hkStringPtr m_name;
    hkArray<ParticleData> m_particleDatas;
private:
    hkUint8 _48[0x78 - 0x48];
public:
    // Reflected member record 0x7102534308: "totalMass", type hkReal, offset 0x78.
    hkReal m_totalMass;
private:
    hkUint8 _7c[0x180 - 0x7c];
};
static_assert(sizeof(hclSimClothData) == 0x180);
static_assert(sizeof(hclSimClothData::SimulationInfo) == 0x20);
static_assert(sizeof(hclSimClothData::ParticleData) == 0x10);
static_assert(offsetof(hclSimClothData, m_particleDatas) == 0x38);
static_assert(offsetof(hclSimClothData, m_totalMass) == 0x78);

#pragma once
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Cloth/Cloth/Collidable/hclCollidable.h>
#include <Havok/Cloth/Cloth/SimCloth/hclSimClothData.h>

// Real runtime object: factory14100f4 allocates1e0, constructor140c694/table25335a8.
// Its original class name is unrecovered. Constructor clones retained collidables
// into+d0; destructor140cae0 releases them. Other owned state remains unmodelled.
class Unk_71025335A8 : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(Unk_71025335A8)
    ~Unk_71025335A8() override;
    // 0x710140d5a4: an optional simulation-info override, otherwise the
    // data's embedded SimulationInfo at +0x10. The getter name is a guess.
    const hclSimClothData::SimulationInfo* getSimulationInfoMaybe() const;

    hclSimClothData* m_simClothData;
    // Constructor 0x710140c694 sizes these three hkVector4 arrays to the particle
    // count (m_particleDatas size). ClothWind::m3 0x71013086bc takes
    // (+0x18[i] - +0x28[i]) / timestep as the particle velocity, so these are the
    // current and previous particle positions. Names are guesses.
    hkArray<hkVector4> m_positionsMaybe;
    hkArray<hkVector4> m_prevPositionsMaybe;
private:
    hkArray<hkVector4> _38;
    hkUint8 _48[0xd0 - 0x48];
public:
    hkArray<hclCollidable*> m_collidables;
private:
    hkUint8 _e0[0x1d8 - 0xe0];
    // Zeroed by constructor 0x710140c694. The 17 simulation callers read
    // the same flags/floats as hclSimClothData::m_simulationInfo.
    const hclSimClothData::SimulationInfo* m_simulationInfoOverride;
};
static_assert(sizeof(Unk_71025335A8) == 0x1e0);
static_assert(offsetof(Unk_71025335A8, m_collidables) == 0xd0);

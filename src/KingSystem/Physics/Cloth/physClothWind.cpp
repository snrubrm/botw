#include "KingSystem/Physics/Cloth/physClothWind.h"
#include <Havok/Cloth/Cloth/SimCloth/hclSimClothInstance.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// NON_MATCHING: the original stores _3c and _40 separately (stp wzr, wzr); ours merges them.
ClothWind::ClothWind(ClothSet* set, s16 index) : ClothActionHandle(set, index) {
    mWind = sead::Vector3f::zero;
}

ClothWind::~ClothWind() = default;

// NON_MATCHING: the original loads the position array pointers before the particle data
// pointer and keeps the sim cloth data in another register; the loop body matches.
void ClothWind::m3(Unk_71025335A8* sim_cloth, hkVector4f* output, hkReal timestep) {
    if (timestep == 0)
        return;

    const hclSimClothData* data = sim_cloth->m_simClothData;
    if (data->m_totalMass == 0)
        return;

    const int num_particles = sim_cloth->m_positionsMaybe.getSize();
    const hkVector4f wind = toHkVec4(mWind);
    const hkSimdFloat32 inv_neg_timestep = -1.0f / timestep;
    const hkReal inv_total_mass = 1.0f / data->m_totalMass;

    const hkVector4f* positions = sim_cloth->m_positionsMaybe.begin();
    const hkVector4f* prev_positions = sim_cloth->m_prevPositionsMaybe.begin();
    const hclSimClothData::ParticleData* particles = data->m_particleDatas.begin();
    for (int i = 0; i < num_particles; ++i) {
        const hkSimdFloat32 scale = _30 * (inv_total_mass * particles->m_mass);
        hkVector4f force;
        force.setSub(*positions, *prev_positions);
        force.mul(inv_neg_timestep);
        force.add(wind);
        force.mul(scale);
        output->add(force);
        ++positions;
        ++prev_positions;
        ++particles;
        ++output;
    }
}

}  // namespace ksys::phys

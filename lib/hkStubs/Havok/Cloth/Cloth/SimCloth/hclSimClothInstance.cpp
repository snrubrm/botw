#include <Havok/Cloth/Cloth/SimCloth/hclSimClothInstance.h>

const hclSimClothData::SimulationInfo* Unk_71025335A8::getSimulationInfoMaybe() const {
    if (m_simulationInfoOverride)
        return m_simulationInfoOverride;
    return &m_simClothData->m_simulationInfo;
}

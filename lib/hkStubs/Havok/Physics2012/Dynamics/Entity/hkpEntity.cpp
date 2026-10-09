#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>
#include <Havok/Physics2012/Dynamics/World/hkpSimulationIsland.h>

// 0x71015fe6fc
int hkpEntity::getNumConstraints() const {
    return m_constraintsMaster.getSize() + m_constraintsSlave.getSize();
}

// NON_MATCHING: the active-mark extraction uses a 32-bit rather than 64-bit register.
// 0x71015fe12c
hkBool hkpEntity::isActive() const {
    return m_simulationIsland && m_simulationIsland->m_activeMark;
}

// 0x71015fe1d8
void hkpEntity::requestDeactivation() {
    if (isActive() && m_motion.isDeactivationEnabled())
        m_motion.requestDeactivation();
}

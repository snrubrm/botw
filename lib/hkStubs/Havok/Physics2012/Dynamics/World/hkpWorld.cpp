#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>

#include <Havok/Physics2012/Dynamics/World/Simulation/hkpSimulation.h>

hkTime hkpWorld::getCurrentTime() const {
    return m_simulation->getCurrentTime();
}

hkTime hkpWorld::getCurrentPsiTime() const {
    return m_simulation->getCurrentPsiTime();
}

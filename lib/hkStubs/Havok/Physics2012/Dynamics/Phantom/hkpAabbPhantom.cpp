#include <Havok/Physics2012/Dynamics/Phantom/hkpAabbPhantom.h>

hkpPhantomType hkpAabbPhantom::getType() const {
    return HK_PHANTOM_AABB;
}

void hkpAabbPhantom::calcAabb(hkAabb& aabb) {
    aabb.m_min = m_aabb.m_min;
    aabb.m_max = m_aabb.m_max;
}

void hkpAabbPhantom::setAabb(const hkAabb& newAabb) {
    m_aabb.m_min = newAabb.m_min;
    m_aabb.m_max = newAabb.m_max;
    updateBroadPhase(m_aabb);
}

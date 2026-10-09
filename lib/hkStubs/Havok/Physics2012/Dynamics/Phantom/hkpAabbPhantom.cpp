#include <Havok/Physics2012/Dynamics/Phantom/hkpAabbPhantom.h>

// Native 1607E14 sorts collidable pointers by unsigned broad-phase IDs; the
// complete 1607DD0 caller supplies the array and signed first/last indices.
void sub_7101607E14(hkpCollidable** collidables, int first, int last);

hkpAabbPhantom::hkpAabbPhantom(const hkAabb& aabb, hkUint32 collisionFilterInfo)
    : hkpPhantom(nullptr), m_orderDirty(false) {
    m_aabb = aabb;
    m_collidable.setCollisionFilterInfo(collisionFilterInfo);
}

// NON_MATCHING (D0 only): the generated deleting destructor schedules its object argument earlier.
hkpAabbPhantom::~hkpAabbPhantom() = default;

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

hkBool hkpAabbPhantom::isOverlappingCollidableAdded(const hkpCollidable* collidable) {
    for (int i = 0; i < m_overlappingCollidables.getSize(); ++i) {
        if (m_overlappingCollidables[i] == collidable)
            return true;
    }
    return false;
}

void hkpAabbPhantom::addOverlappingCollidable(hkpCollidable* collidable) {
    if (fireCollidableAdded(collidable) == HK_COLLIDABLE_ACCEPT) {
        m_overlappingCollidables.pushBack(collidable);
        m_orderDirty = true;
    }
}

// NON_MATCHING: the existing array removal API schedules its comparison before the size store.
void hkpAabbPhantom::removeOverlappingCollidable(hkpCollidable* collidable) {
    const int index = m_overlappingCollidables.indexOf(collidable);
    fireCollidableRemoved(collidable, index >= 0);
    if (index < 0)
        return;
    m_overlappingCollidables.removeAt(index);
    m_orderDirty = true;
}

void hkpAabbPhantom::ensureDeterministicOrder() {
    if (m_orderDirty) {
        const int count = m_overlappingCollidables.getSize();
        if (count > 1)
            sub_7101607E14(m_overlappingCollidables.begin(), 0, count - 1);
        m_orderDirty = false;
    }
}

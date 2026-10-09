#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>

// 0x7101615ED8
void hkpConstraintInstance::setPriority(ConstraintPriority priority) {
    m_priority = priority;
    if (m_internal)
        m_internal->m_priority = priority;
}

// 0x7101615EEC
hkpSimulationIsland* hkpConstraintInstance::getSimulationIsland() {
    hkpEntity* entity = m_entities[0];
    if (entity->isFixed())
        entity = m_entities[1];
    return entity->getSimulationIsland();
}

// 0x7101616648
hkBool hkpConstraintInstance::isEnabled() {
    return hkpWorldConstraintUtil::findModifier(
               this, hkpConstraintAtom::TYPE_MODIFIER_IGNORE_CONSTRAINT) == nullptr;
}

void hkpConstraintInstance::enable() {
    hkpResponseModifier::enableConstraint(this, *m_owner);
}

void hkpConstraintInstance::disable() {
    hkpResponseModifier::disableConstraint(this, *m_owner);
}

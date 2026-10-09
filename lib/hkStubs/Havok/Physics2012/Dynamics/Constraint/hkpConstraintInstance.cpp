#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpEntity.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// NON_MATCHING: the second entity reference uses a longer existing atomic retry-loop branch layout.
// 0x7101615d30
hkpConstraintInstance::hkpConstraintInstance(hkpEntity* entityA, hkpEntity* entityB,
                                           hkpConstraintData* data, ConstraintPriority priority)
    : m_owner(nullptr), m_data(data), m_priority(priority), m_wantRuntime(true),
      m_destructionRemapInfo(ON_DESTRUCTION_REMAP), m_userData(0), m_internal(nullptr),
      m_uid(0xfffffff0) {
    m_entities[0] = entityA;
    m_entities[1] = entityB;
    m_constraintModifiers = nullptr;
    hkReferencedObject::lockAll();
    m_entities[0]->addReference();
    if (m_entities[1])
        m_entities[1]->addReference();
    m_data->addReference();
    hkReferencedObject::unlockAll();
}

// 0x7101615e6c. The data and entity pointers are supplied by the embedded-instance owner.
hkpConstraintInstance::hkpConstraintInstance(ConstraintPriority priority)
    : m_owner(nullptr), m_constraintModifiers(nullptr), m_priority(priority), m_wantRuntime(true),
      m_destructionRemapInfo(ON_DESTRUCTION_REMAP), m_userData(0), m_internal(nullptr),
      m_uid(0xfffffff0) {}

// 0x7101615f08
void hkpConstraintInstance::entityAddedCallback(hkpEntity*) {}

// 0x7101615f0c
void hkpConstraintInstance::entityDeletedCallback(hkpEntity*) {}

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

// NON_MATCHING: the existing reference-count helpers emit longer retry-loop branch layouts.
void hkpConstraintInstance::replaceEntity(hkpEntity* oldEntity, hkpEntity* newEntity) {
    const int index = oldEntity == m_entities[0] ? 0 : 1;
    newEntity->addReference();
    if (oldEntity)
        oldEntity->removeReference();
    m_entities[index] = newEntity;
}

// NON_MATCHING: the original shares the true return path and uses different register allocation.
// 0x7101616168
hkBool hkpConstraintInstance::isConstrainedToWorld() const {
    if (!m_entities[1])
        return true;
    hkpWorld* world = m_entities[0]->getWorld();
    return world && m_entities[1] == world->getFixedRigidBody();
}

// NON_MATCHING: the existing reference-count helper emits longer retry-loop branch layouts.
// 0x7101616740
void hkpConstraintInstance::setFixedRigidBodyPointersToZero(hkpWorld* world) {
    for (hkpEntity*& entity : m_entities) {
        if (entity == world->getFixedRigidBody()) {
            entity->removeReference();
            entity = nullptr;
        }
    }
}

// NON_MATCHING: the search index and not-found branch use different register allocation and layout.
// 0x710161647c
void hkpConstraintInstance::removeConstraintListener(hkpConstraintListener* listener) {
    int index = -1;
    for (int i = 0; i < m_listeners.getSize(); ++i) {
        if (m_listeners[i] == listener) {
            index = i;
            break;
        }
    }
    m_listeners[index] = nullptr;
}

// NON_MATCHING: endpoint null branches and existing reference-count retry loops have different layouts.
// 0x71016164c4
void hkpConstraintInstance::pointNullsToFixedRigidBody() {
    for (int i = 0; i < 2; ++i) {
        if (m_entities[i])
            continue;
        hkpEntity* other = m_entities[1 - i];
        if (!other)
            continue;
        hkpWorld* world = other->getWorld();
        if (!world)
            continue;
        m_entities[i] = world->getFixedRigidBody();
        m_entities[i]->addReference();
    }
}

// NON_MATCHING: the search branch, packed count/capacity loads and append stores have different layouts.
// 0x71016163ec
void hkpConstraintInstance::addConstraintListener(hkpConstraintListener* listener) {
    const int index = m_listeners.indexOf(nullptr);
    if (index < 0)
        m_listeners.pushBack(listener);
    else
        m_listeners[index] = listener;
}

void hkpConstraintInstance::entityRemovedCallback(hkpEntity* entity) {
    if (m_owner)
        entity->getWorld()->sub_710160956C(this, true);
}

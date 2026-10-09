#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h>

// 0x7101615ED8
void hkpConstraintInstance::setPriority(ConstraintPriority priority) {
    m_priority = priority;
    if (m_internal)
        m_internal->m_priority = priority;
}

// 0x7101616648
hkBool hkpConstraintInstance::isEnabled() {
    return hkpWorldConstraintUtil::findModifier(
               this, hkpConstraintAtom::TYPE_MODIFIER_IGNORE_CONSTRAINT) == nullptr;
}

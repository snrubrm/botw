#include <Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h>
#include <Havok/Physics2012/Dynamics/Constraint/Atom/hkpModifierConstraintAtom.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

// NON_MATCHING: the modifier type threshold and loop-entry branch are encoded differently.
// 0x7101613efc
hkpModifierConstraintAtom* hkpWorldConstraintUtil::findModifier(
    hkpConstraintInstance* instance, hkpConstraintAtom::AtomType type) {
    hkpModifierConstraintAtom* modifier = instance->getConstraintModifiers();
    while (modifier) {
        if (modifier->getType() == type)
            return modifier;
        hkpConstraintAtom* child = modifier->m_child;
        if (!child->isModifierType())
            return nullptr;
        modifier = static_cast<hkpModifierConstraintAtom*>(child);
    }
    return nullptr;
}

// NON_MATCHING: the compiler merges the internal-atom update paths differently.
// 0x7101613f28
void hkpWorldConstraintUtil::updateFatherOfMovedAtom(
    hkpConstraintInstance* instance, const hkpConstraintAtom* oldAtom,
    const hkpConstraintAtom* updatedAtom, int updatedSizeOfAtom) {
    hkConstraintInternal* internal = instance->m_internal;
    hkpModifierConstraintAtom* modifier = instance->m_constraintModifiers;
    // The existing API accepts const views of the relocated atom; the owner's chain is mutable.
    hkpConstraintAtom* movedAtom = const_cast<hkpConstraintAtom*>(updatedAtom);
    if (modifier) {
        if (modifier == oldAtom) {
            // Replacing the head of the modifier chain preserves the relocated atom's kind.
            instance->m_constraintModifiers = static_cast<hkpModifierConstraintAtom*>(movedAtom);
        } else {
            while (modifier->m_child != oldAtom)
                modifier = static_cast<hkpModifierConstraintAtom*>(modifier->m_child);
            modifier->m_child = movedAtom;
            modifier->m_childSize = updatedSizeOfAtom;
            return;
        }
    }
    if (internal) {
        internal->m_atoms = movedAtom;
        internal->m_atomsSize = updatedSizeOfAtom;
    }
}

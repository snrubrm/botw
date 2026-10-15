#include <Havok/Physics/Constraint/Util/hkpConstraintUtils.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

// NON_MATCHING: loop comparison operand order and induction condition differ.
void sub_71015FBE7C(const hkArray<hkpConstraintInstance*>& instances,
                   hkpConstraintAtom::SolvingMethod method) {
    const int count = instances.getSize();
    // getData exposes a const view; both native factories created mutable data for this update.
    for (int i = 0; i < count; ++i)
        const_cast<hkpConstraintData*>(instances[i]->getData())->setSolvingMethod(method);
}

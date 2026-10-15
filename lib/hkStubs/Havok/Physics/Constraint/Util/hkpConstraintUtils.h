#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>

class hkpConstraintInstance;

// Address name: full BAndSCs and BAndSLimitAngYCs factories pass a borrowed instance array.
// The complete native utility sets each data object's existing solving method.
void sub_71015FBE7C(const hkArray<hkpConstraintInstance*>& instances,
                   hkpConstraintAtom::SolvingMethod method);

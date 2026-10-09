#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>

// Reflection 17bc55c proves the hkpConstraintData parent and extent 0x20.
// Constructor 17bc15c retains constraintData at +18; both destructor paths
// release the same child. Unresolved base virtual slots remain undeclared.
class hkpWrappedConstraintData : public hkpConstraintData {
public:
    explicit hkpWrappedConstraintData(hkpConstraintData* constraintData);
    ~hkpWrappedConstraintData() override;
    void getConstraintInfo(ConstraintInfo& infoOut) const override;
    hkBool isValid() const override;
    // Native 17bc1f4 forwards the existing runtime bool/output pair. The base
    // virtual slot order is incomplete; this declaration does not repair it.
    void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const override;

protected:
    hkpConstraintData* m_constraintData;
};

static_assert(sizeof(hkpWrappedConstraintData) == 0x20);

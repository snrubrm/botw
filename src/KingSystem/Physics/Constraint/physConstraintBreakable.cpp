#include "KingSystem/Physics/Constraint/physConstraint.h"
#include <heap/seadHeap.h>
#include <Havok/Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>

namespace ksys::phys {

u32 sub_7100F6C5AC() {
    return 0x28;
}

ConstraintUnk18::~ConstraintUnk18() = default;

ConstraintUnk18* ConstraintUnk18::sub_7100F6C5B4(hkpConstraintData* data, const Param& param,
                                                sead::Heap* heap) {
    auto* holder = new (heap->alloc(sizeof(ConstraintUnk18), 16)) ConstraintUnk18;
    auto* breakable = new (heap->alloc(sizeof(hkpBreakableConstraintData), 16))
        hkpBreakableConstraintData(data);
    holder->_8 = breakable;
    breakable->m_solverResultLimit = param.mSolverResultLimit;
    return holder;
}

void ConstraintUnk18::sub_7100F6C64C(f32 value) {
    _8->m_solverResultLimit = value;
}

}  // namespace ksys::phys

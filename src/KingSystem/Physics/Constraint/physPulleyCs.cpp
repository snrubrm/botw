#include "KingSystem/Physics/Constraint/physMotorcycleType1Cs.h"
#include "KingSystem/Physics/Constraint/physPulleyCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"

namespace ksys::phys {

// Adjacent constraint lifetime families at 0x7100f6ee80 and 0x7100f6f7c8.
MotorcycleType1Cs::~MotorcycleType1Cs() = default;

void MotorcycleType1Cs::sub_7100F6F1B4(f32 value) {
    mData->_b4 = value;
}
PulleyCs::~PulleyCs() = default;

void PulleyCs::sub_7100F6F7F0(f32 length) {
    mData->mRopeLength = length;
}

void PulleyCs::sub_7100F6F7FC(f32 leverage) {
    mData->mLeverageOnBodyB = leverage;
}

f32 PulleyCs::sub_7100F6F808() const {
    return mData->mLeverageOnBodyB;
}
Unk_71024f65c8::~Unk_71024f65c8() = default;

u32 sub_7100F6F790(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x1a0 : 0x170);
}

}  // namespace ksys::phys

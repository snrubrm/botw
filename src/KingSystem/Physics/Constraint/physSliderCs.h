#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpPrismaticConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f70d60 allocates 0x120, constructs Constraint, and
// installs the four-slot 0x71024f6700. Library data and frames stay opaque.
class SliderCs : public Constraint {
    SEAD_RTTI_OVERRIDE(SliderCs, Constraint)
public:
    // Whole factory and independent action/map initializers use this 0x78-byte record.
    struct Param : Constraint::Param {
        bool _20 = true;
        sead::Vector3f pivot_a = sead::Vector3f::ex;
        sead::Vector3f pivot_b = sead::Vector3f::ex;
        sead::Vector3f axis_a = sead::Vector3f::ez;
        sead::Vector3f axis_b = sead::Vector3f::ez;
        sead::Vector3f perpendicular_a = sead::Vector3f::ey;
        sead::Vector3f perpendicular_b = sead::Vector3f::ey;
        f32 min = -10.0f;
        f32 max = 10.0f;
        f32 friction = 0.0f;
    };
    static_assert(sizeof(Param) == 0x78);
    static SliderCs* make(const Param& param, sead::Heap* heap);

    ~SliderCs() override;
    void setMinMaxLimit(f32 min, f32 max);
    void sub_7100F71028(f32 friction);
    void sub_7100F7104C(bool allow_rotation);
    // Independent factory and SwitchStepSliderConstraint supply both pivots and both frame axes.
    void sub_7100F71058(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b,
                      const sead::Vector3f& axis_a, const sead::Vector3f& axis_b,
                      const sead::Vector3f& perpendicular_a, const sead::Vector3f& perpendicular_b);
    // 223114 uses SliderCs's typeInfo at 0x71025b5228 before these data queries.
    f32 sub_7100F71034();
    f32 sub_7100F71040();

private:
    // Factory 0x7100f70d60 stores the independently constructed prismatic data here.
    hkpPrismaticConstraintData* mData;
    u8 _c0[0x120 - 0xc0];
};
KSYS_CHECK_SIZE_NX150(SliderCs, 0x120);

u32 sub_7100F70FB4(bool breakable, bool extra);

}  // namespace ksys::phys

#pragma once

#include "KingSystem/Physics/System/physUnk_71012a6844.h"

namespace ksys::phys {

// Whole LimitHingeCs factory 0x7100f6e06c allocates 0x20, calls ItemA's
// constructor with its Constraint, and installs the seven-slot 0x71024f6420.
struct Unk_71024f6420 : Unk_71012a6844::ItemA {
    SEAD_RTTI_OVERRIDE(Unk_71024f6420, Unk_71012a6844::ItemA)
    ~Unk_71024f6420() override;
    // Native 0x7100f6e660 / 0x7100f6e83c require the library data interface.
    bool m0() const override;
    void sub_7100F6FF60(sead::Vector3f* a, sead::Vector3f* b) const override;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6420, 0x20);

// Whole PulleyCs factory 0x7100f6f33c constructs ItemA at a 0x20 allocation
// with its Constraint and then installs the seven-slot 0x71024f65c8.
struct Unk_71024f65c8 : Unk_71012a6844::ItemA {
    SEAD_RTTI_OVERRIDE(Unk_71024f65c8, Unk_71012a6844::ItemA)
    ~Unk_71024f65c8() override;
    // Native 0x7100f6fbb4 requires the library data interface.
    bool m0() const override;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f65c8, 0x20);

}  // namespace ksys::phys

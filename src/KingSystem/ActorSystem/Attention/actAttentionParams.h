#pragma once

#include <math/seadVector.h>

namespace ksys::act {

// Placeholder names = vtable addresses. The three classes are members of Attention (0x7100d73b28
// constructs them at +0xb88 / +0xbd0 / +0xc38); their constructors are emitted in the AttCheck TU
// (0x710108b2b0 / 0x710108c3ac / 0x710108dfac). Each class holds four per-attention-type values and
// has a virtual destructor.

// One f32 value (vtable 0x7102505000).
class Unk_7102505000 {
public:
    virtual ~Unk_7102505000() = default;

    f32 mValue;
};

// Four f32 values (vtable 0x7102505020), default 0.1 / 1 / 1 / 1.
class Unk_7102505020 {
public:
    Unk_7102505020();
    virtual ~Unk_7102505020() = default;

    Unk_7102505000 mValues[4];
};

// One Vector3f value (vtable 0x7102505040).
class Unk_7102505040 {
public:
    virtual ~Unk_7102505040() = default;

    sead::Vector3f mValue;
};

// Four Vector3f values (vtable 0x7102505060), default 0.1 / 1 / 1 / 1.
class Unk_7102505060 {
public:
    Unk_7102505060();
    virtual ~Unk_7102505060() = default;

    Unk_7102505040 mValues[4];
};

// Two Vector3f values (vtable 0x7102505080).
class Unk_7102505080 {
public:
    virtual ~Unk_7102505080() = default;

    sead::Vector3f mA;
    sead::Vector3f mB;
};

// Four two-Vector3f values (vtable 0x71025050a0), default 0.1 / 1 / 1 / 1 per component.
class Unk_71025050a0 {
public:
    Unk_71025050a0();
    virtual ~Unk_71025050a0() = default;

    Unk_7102505080 mValues[4];
};

}  // namespace ksys::act

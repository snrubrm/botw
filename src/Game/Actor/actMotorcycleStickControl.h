#pragma once

#include <aal/aalTimedFader.h>
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace uking::act {

// Placeholder names (the objects have no vtable and no out-of-line constructor: the Motorcycle
// constructor initializes them inline). Both are "approach the target value" controllers used for
// the stick values of the Motorcycle: `_0` is the rate used when the value moves towards zero (or
// the target is within epsilon of zero), `_4` the rate when it moves away from zero, `_8` the
// current value.

// CSV (unnamed) 0x71002c8918, Motorcycle +0xb90.
struct Unk_71002c8918 {
    f32 sub_71002C8918(f32 target);

    f32 _0;
    f32 _4;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8918, 0xc);

// CSV motorcycleStickControlStuff 0x7100e72ac0, Motorcycle +0xb9c (X) and +0xba8 (Y).
struct Unk_7100e72ac0 {
    f32 motorcycleStickControlStuff(f32 target);

    f32 _0;
    f32 _4;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e72ac0, 0xc);

// CSV (unnamed) ctor 0x71002c8e10 (update 0x71002c8e44), Motorcycle +0xe8c and MotorcycleStruct0 +0x178.
// A rate pair like the two stick controllers above: `_4` is the first rate, `_8` the second one (both
// at least 0.008) and `_0` is `_8` when `flag` is set and `-_4` otherwise. Placeholder name.
struct Unk_71002c8e10 {
    Unk_71002c8e10(f32 a, f32 b, bool flag);

    // 0x71002c8e44: `flag` ramps `_0` up to `_8` (flag set) or down to `-_4` (flag cleared), moving by
    // the delta time on every call.
    void sub_71002C8E44(bool flag);

    f32 _0;
    f32 _4;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8e10, 0xc);

// CSV (unnamed) 0x71002c8b5c, MotorcycleStruct0 +0x58 (the engine sound pitch): approaches `target`
// with the rate `mRates.y` going down and `mRates.x` going up; `_8` is the current value. Placeholder
// name.
struct Unk_71002c8b5c {
    f32 sub_71002C8B5C(f32 target);

    sead::Vector2f mRates;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8b5c, 0xc);

// Placeholder names (MotorcycleStruct0 +0x98 / +0xd0, no vtable and no out-of-line constructor): a fader
// that alternates between 1 and 0 by itself (moveTo(1, _2c) / moveTo(0, _30) once it has arrived) with
// a scale `_28` for its value. Methods 0x71002c8c58 / 0x71002c8cac.
struct Unk_71002c8c58 {
    // Starts the next fade once the previous one is over, then advances the fader.
    void sub_71002C8C58();
    // Resets the fader to 0 and sets the three floats.
    void sub_71002C8CAC(f32 a, f32 b, f32 c);

    /* 0x00 */ aal::TimedFader mFader{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x28 */ f32 _28 = 0.0f;
    /* 0x2c */ f32 _2c = 1.0f;
    /* 0x30 */ f32 _30 = 1.0f;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8c58, 0x38);

// Placeholder name (MotorcycleStruct0 +0x108): like the type above, but it has two sets of
// {scale, fade in time, fade out time}; the second set (_34/_38/_3c) is used whenever `_44` (a counter
// running from 0 to `_40`) has reached `_40`. Methods 0x71002c8cf8 / 8d88 / 8dd4 / 8dec.
struct Unk_71002c8cf8 {
    void sub_71002C8CF8();
    void sub_71002C8D88(f32 a, f32 b, f32 c);
    void sub_71002C8DD4(f32 a, f32 b, f32 c, f32 count);
    f32 sub_71002C8DEC() const;

    /* 0x00 */ aal::TimedFader mFader{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x28 */ f32 _28 = 0.0f;
    /* 0x2c */ f32 _2c = 1.0f;
    /* 0x30 */ f32 _30 = 1.0f;
    /* 0x34 */ f32 _34 = 0.0f;
    /* 0x38 */ f32 _38 = 1.0f;
    /* 0x3c */ f32 _3c = 1.0f;
    /* 0x40 */ s32 _40 = 3;
    /* 0x44 */ s32 _44 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8cf8, 0x48);

}  // namespace uking::act

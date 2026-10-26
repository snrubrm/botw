#pragma once

#include <basis/seadTypes.h>
#include <prim/seadDelegate.h>

namespace sead {
class Heap;
}

namespace gsys {

class ModelUnit;
class ModelRenderUnitNWOverride;

// The 0x48-byte shape override GrudgeRenderer holds three of (ctor 0x71014099f8, which the
// GrudgeRenderer constructor 0x710128d348 calls at + 0x290 / + 0x2d8 / + 0x320). Its vtable
// (0x7102533118) has only the destructor pair, so the class adds no other virtuals; the two
// 0x20-byte members are unbound delegates (the ctor's stores at + 0x08 and + 0x28 are the
// UnbindDummy vtables).
class ModelProceduralShape {
public:
    struct Arg;
    struct ResetArg;

    ModelProceduralShape();
    virtual ~ModelProceduralShape();

    // 0x7101409a30 (declared only).
    ModelRenderUnitNWOverride* overrideShapeDraw(ModelUnit* unit, int index, sead::Heap* heap);

private:
    sead::AnyDelegate1<const Arg&> mDrawDelegate;      // 0x08
    sead::AnyDelegate1<const ResetArg&> mResetDelegate;  // 0x28
};
static_assert(sizeof(ModelProceduralShape) == 0x48);

}  // namespace gsys

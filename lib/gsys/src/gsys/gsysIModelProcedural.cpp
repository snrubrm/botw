#include "gsys/gsysIModelProcedural.h"
#include <basis/seadNew.h>
#include <new>

namespace gsys {

IModelProcedural::IModelProcedural() = default;

// NON_MATCHING: the original keeps the RenderUnit vtable store before each element's base destructor; our
// RenderUnit destructor has a trivial body, so Clang skips it. What makes the original body non-trivial is unknown.
IModelProcedural::~IModelProcedural() {
    mRenderUnits.freeBuffer();
}

void IModelProcedural::initRenderUnits_(s32 count, s32 value, sead::Heap* heap) {
    if (count >= 1) {
        auto* units = new (heap, 8, std::nothrow) RenderUnit[count];
        if (units)
            mRenderUnits.setBuffer(count, units);
    }

    _c8 = value;

    const u32 num = mRenderUnits.size();
    RenderUnit* unit = mRenderUnits.getBufferPtr();
    for (size_t i = 0; i != num; ++i, ++unit)
        unit->initialize(this, i, heap);

    sub_7100C3D634(heap);
    setLodThreshold(-1.0f, -1, mNumLods - 1);
    mCalcWeight = 1000;
}

}  // namespace gsys

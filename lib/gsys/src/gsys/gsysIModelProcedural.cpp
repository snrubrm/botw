#include "gsys/gsysIModelProcedural.h"

namespace gsys {

IModelProcedural::IModelProcedural() = default;

// NON_MATCHING: the original keeps the RenderUnit vtable store before each element's base destructor; our
// RenderUnit destructor has a trivial body, so Clang skips it. What makes the original body non-trivial is unknown.
IModelProcedural::~IModelProcedural() {
    mRenderUnits.freeBuffer();
}

}  // namespace gsys

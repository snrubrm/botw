#pragma once

#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelRenderUnit.h"
#include "gsys/gsysModelUnit.h"

namespace gsys {

// Destructor 0x7100c7fc2c installs vtable 0x71024d1af8 and ends with ~ModelUnit. Its RTTI functions
// 0x7100c1444c / 0x7100c14518 are shared by the game subclass with vtable 0x71024f4720.
class IModelProcedural : public ModelUnit {
    SEAD_RTTI_OVERRIDE(IModelProcedural, ModelUnit)
public:
    // 0x7100c7fbec: ModelUnit ctor 0x7100c3d4b0, then _c8 = 1 and an empty pass array.
    IModelProcedural();
    ~IModelProcedural() override;

    void setProcedualPassName(int index, const sead::SafeString& name);
    void setProcedualPassPriority(int index, int a, int b);
    void setMaterialVisible(int index, bool visible);

    // The pass array elements: 0x38 bytes (array stride in the destructor), vtable 0x71024d1da8.
    // The destructor 0x7100c7fc2c inlines their destructor (vtable store, then the base D2).
    class RenderUnit : public ModelRenderUnit {
    public:
        ~RenderUnit() override {}

    private:
        u8 _18[0x38 - 0x18];
    };
    static_assert(sizeof(RenderUnit) == 0x38);

private:
    s32 _c8 = 1;
    sead::Buffer<RenderUnit> mRenderUnits;
};

static_assert(sizeof(IModelProcedural) == 0xe0);

}  // namespace gsys

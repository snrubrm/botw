#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelUnit.h"

namespace gsys {

// Destructor 0x7100c7fc2c installs vtable 0x71024d1af8 and ends with ~ModelUnit. Its RTTI functions
// 0x7100c1444c / 0x7100c14518 are shared by the game subclass with vtable 0x71024f4720.
class IModelProcedural : public ModelUnit {
    SEAD_RTTI_OVERRIDE(IModelProcedural, ModelUnit)
public:
    ~IModelProcedural() override;

    void setProcedualPassName(int index, const sead::SafeString& name);
    void setProcedualPassPriority(int index, int a, int b);
    void setMaterialVisible(int index, bool visible);
};

}  // namespace gsys

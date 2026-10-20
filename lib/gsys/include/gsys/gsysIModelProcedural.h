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

    // 0x7100c145e0: the render unit count.
    int getMaterialNum() const override;
    // 0x7100c146f0: the same render-unit count (the original body loads the buffer size at +0xd0).
    int getShapeNum() const override;

    // 0x7100c14710: the render-unit count stored by initRenderUnits_ at +0xc8.
    int getViewNum() const;

    void setProcedualPassName(int index, const sead::SafeString& name);
    // 0x7100c7ffb4: the low bit of the render unit's +0x30 word.
    bool isMaterialVisible(int index) const override;
    void setProcedualPassPriority(int index, int a, int b);
    void setMaterialVisible(int index, bool visible);

    // The pass array elements: 0x38 bytes (array stride in the destructor), vtable 0x71024d1da8.
    // The destructor 0x7100c7fc2c inlines their destructor (vtable store, then the base D2).
    // 0x7100c7fd68 constructs an array of these: base ModelRenderUnit ctor, the RenderUnit
    // vtable, then the name "Proc(unnamed)" (+0x20) and the word 1 (+0x30).
    class RenderUnit : public ModelRenderUnit {
        friend class IModelProcedural;
    public:
        // `{ ; }` keeps the original's vtable store in D2/D0 (the defaulted body drops it);
        // precedent: upstream GameDataFlagSelector::~GameDataFlagSelector().
        ~RenderUnit() override { ; }

    private:
        sead::SafeString mName{"Proc(unnamed)"};
        s32 _30 = 1;
        u8 _34[0x38 - 0x34];
    };
    static_assert(sizeof(RenderUnit) == 0x38);

    /// 0x7100c7fd68 (name is a guess): replaces the pass array with `count` render units and
    /// initializes each with (this, index, heap); a non-positive count keeps the current array.
    void initRenderUnits_(s32 count, s32 value, sead::Heap* heap);

private:
    s32 _c8 = 1;
    sead::Buffer<RenderUnit> mRenderUnits;
};

static_assert(sizeof(IModelProcedural) == 0xe0);

}  // namespace gsys

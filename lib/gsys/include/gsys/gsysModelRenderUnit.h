#pragma once

#include <basis/seadTypes.h>

namespace agl::cull {
class ViewFrustumCulling;
}

namespace nn::g3d {
class ViewVolume;
}

namespace sead {
class Heap;
}

namespace gsys {

class ModelUnit;

// Abstract base of the render units (vtable 0x71024d1f48): D2 0x7100c82cbc is empty, D0 0x7100c82cc0
// deletes, slot 2 is initialize 0x7100c82cc4.
class ModelRenderUnit {
public:
    // 0x7100c82ca0: zeroes mModelUnit, _10 and the byte at +0x18, then installs the vtable.
    // The original emits this ctor out of line (IModelProcedural::RenderUnit's array ctor calls it).
    ModelRenderUnit();
    virtual ~ModelRenderUnit();
    // 0x7100c82cc4: stores the unit at +8 and the index at +0x14 and +0x16; returns true.
    virtual bool initialize(const ModelUnit* unit, int index, sead::Heap* heap);
    // 0x7100c800d8: the base default accepts every view volume.
    bool calcViewFrustumCulling(int, int, int, const agl::cull::ViewFrustumCulling&,
                                const nn::g3d::ViewVolume&, float*);

    const ModelUnit* getModelUnit() const { return mModelUnit; }
    // Graphics 0x7100f2e0f4 compares +0x16 of ModelNW's render units with a material index.
    u16 getMaterialIndex() const { return mMaterialIndex; }

    // Render-unit option word at +0x10. ksys::gfx 0x7100f1ed8c clears bits 26/31 and sets bit 27.
    u32& getFlags10() { return _10; }
    const u32& getFlags10() const { return _10; }

protected:
    const ModelUnit* mModelUnit = nullptr;
    u32 _10 = 0;
    u16 mIndex = 0;
    u16 mMaterialIndex = 0;
    // Zeroed by the ctor 0x7100c82ca0; the derived RenderUnit's first own byte follows it.
    u8 _18 = 0;
};
static_assert(sizeof(ModelRenderUnit) == 0x20, "gsys::ModelRenderUnit size mismatch");

}  // namespace gsys

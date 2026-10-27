#pragma once

#include <basis/seadTypes.h>
#include <geom/seadSphere.h>
#include <math/seadBoundBox.h>
#include <prim/seadSafeString.h>

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

class ModelRenderCache;
class ModelUnit;

// Abstract base of the render units (vtable 0x71024d1f48): D2 0x7100c82cbc is empty, D0 0x7100c82cc0
// deletes, slot 2 is initialize 0x7100c82cc4. The slots after it (order of the vtable; getType, getName,
// resetShader and draw are pure) are the same in ModelRenderUnitNW 0x71024ca530 and
// ModelRenderUnitProcedural 0x71024d1da8.
class ModelRenderUnit {
public:
    // 0x7100c82ca0: zeroes mModelUnit, _10 and the byte at +0x18, then installs the vtable.
    // The original emits this ctor out of line (IModelProcedural::RenderUnit's array ctor calls it).
    ModelRenderUnit();
    virtual ~ModelRenderUnit();
    // 0x7100c82cc4: stores the unit at +8 and the index at +0x14 and +0x16; returns true.
    virtual bool initialize(const ModelUnit* unit, int index, sead::Heap* heap);

    const ModelUnit* getModelUnit() const { return mModelUnit; }
    // Graphics 0x7100f2e0f4 compares +0x16 of ModelNW's render units with a material index.
    u16 getMaterialIndex() const { return mMaterialIndex; }

    virtual s32 getType() const = 0;
    virtual sead::SafeString getName() const = 0;
    // Base defaults of the render-unit virtuals: one mesh and one sub-mesh, no sub-mesh
    // bounds, no pass texture and always visible.
    virtual bool isVisible() const;
    virtual s32 getMeshNum() const;
    virtual s32 getSubMeshNum(int) const;
    virtual bool getSubMeshBoundAABB(int, int, sead::BoundBox3f* aabb) const;
    // 0x7100c800a0: the default bound is centered at zero with the maximum finite radius.
    virtual void getBoundSphereImpl(sead::Sphere3f* sphere) const;
    // 0x7100c82cdc: uses the model unit's override sphere when it has one, otherwise the unit's
    // own getBoundSphereImpl.
    void getBoundSphere(sead::Sphere3f* sphere) const;
    virtual s32 getPassTextureBit() const;
    virtual bool resetShader(sead::Heap* heap) = 0;
    // 0x7100c800d8: the base default accepts every view volume.
    virtual bool calcViewFrustumCulling(int, int, int, const agl::cull::ViewFrustumCulling&,
                                        const nn::g3d::ViewVolume&, float*);
    virtual void draw(ModelRenderCache* cache, int, u32) const = 0;

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

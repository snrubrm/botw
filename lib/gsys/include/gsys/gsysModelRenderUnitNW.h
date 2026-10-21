#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelRenderUnit.h"

namespace sead {
class Heap;
}

namespace nn::g3d {
class MaterialObj;
class ShapeObj;
}

namespace gsys {

namespace ModelEnum {
enum class PriorityHintType : int;
}

class ModelAssignRenderInfo;
class G3dResShapeEx;

// Native 0x298-byte game subclass created by 0x7101409a30 over this 0x238-byte base. The vtable is
// 0x71024ca530 (vptr 0x71024ca540); the fourteen slots from vptr+0 to vptr+0x68 are listed below in
// their original order (the ModelRenderUnit virtuals).
//
// Fields come from the constructor 0x7100c09ad0, initialize 0x7100c09c24, the destructor
// 0x7100c09b2c and the render loops 0x7100c09de4 / 0x7100c0a0b4.
class ModelRenderUnitNW : public ModelRenderUnit {
public:
    // 0x7100c09ad0 (unnamed CSV row): base constructor, clears the state below and installs the vtable.
    ModelRenderUnitNW();
    ~ModelRenderUnitNW() override;

    // 0x7100c09c24: stores the shape count, the per-shape render info and the shape display lists.
    bool initialize(const ModelUnit* unit, int index, sead::Heap* heap) override;

    // vptr+0x18, 0x7100c0a8c8: the type word is always 0.
    s32 getType() const override;
    // 0x7100c09fb4: the per-type priority hint, negated when `invert` is set.
    static s32 getPriorityHintFromType(ModelEnum::PriorityHintType type, bool invert);
    // vptr+0x20, 0x7100c09d40: returns the name of the model unit's model (unit +0x20 -> +0xf50).
    sead::SafeString getName() const override;
    // vptr+0x28, 0x7100c09d74: tests the unit's shape visibility masks.
    bool isVisible() const override;
    // vptr+0x30, 0x7100c0a8d0: byte +0x67 of the indexed shape.
    s32 getMeshNum() const override;
    // vptr+0x38, 0x7100c0a8f0: u16 at +0x34 of the indexed shape option record.
    s32 getSubMeshNum(int index) const override;
    // vptr+0x40, 0x7100c0a568: writes the bounds of the indexed shape/option.
    bool getSubMeshBoundAABB(int, int, sead::BoundBox3f* aabb) const override;
    // vptr+0x48, 0x7100c0a530: copies the bounding sphere of the indexed shape.
    void getBoundSphereImpl(sead::Sphere3f* sphere) const override;
    // vptr+0x50, 0x7100c0a91c: the s32 at +0x220 (named by the CSV row).
    s32 getPassTextureBit() const override;
    // vptr+0x58, 0x7100c09de4: rebuilds the display lists and shader assignment of this unit.
    bool resetShader(sead::Heap* heap) override;
    // vptr+0x60, 0x7100c0a3e4
    bool calcViewFrustumCulling(int, int, int, const agl::cull::ViewFrustumCulling&,
                                const nn::g3d::ViewVolume&, float*) override;
    // vptr+0x68, 0x7100c0a664: draws one shape.
    void draw(ModelRenderCache* cache, int, u32) const override;

    // 0x7100c0a098: sets mCalcDisplayListMask to (1 << the unit's buffer count) - 1.
    void updateCalcDisplayListMask();
    // 0x7100c0a65c: stores the polygon control byte at +0x30.
    void setPolygonCtrl(u32 value);
    // 0x7100c09fcc: allocates and clears one ShapeRecord per shape of the owning unit.
    void createShapeRecords(sead::Heap* heap);
    // 0x7100c09d28: the shape object at mModelObj's 0x68-byte shape array at mIndex.
    nn::g3d::ShapeObj* getShape() const;
    // 0x7100c09d60: the material object of mModelObj's 0x80-byte material array at mMaterialIndex.
    nn::g3d::MaterialObj* getMaterial() const;

protected:
    // initialize 0x7100c09c24 loads the user pointer (+0x50) of the shape's ResShape; the destructor
    // passes it to G3dResShapeEx::destroyShapeDL.
    /* 0x20 */ const G3dResShapeEx* mResShapeEx = nullptr;
    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ u8 mPolygonCtrl = 0;  // setPolygonCtrl 0x7100c0a65c stores one byte
    /* 0x31 */ u8 _31 = 0;
    /* 0x32 */ u8 mFlags32 = 0;
    /* 0x33 */ u8 _33 = 1;
    // Not written by the constructor 0x7100c09ad0.
    /* 0x34 */ u16 _34;
    /// One entry per shape; destroyShapeDL 0x7100c70794 takes exactly this type. initialize fills all
    /// sixty entries with the empty display-list record at 0x71025fcd18.
    /* 0x38 */ sead::UnsafeArray<ModelAssignRenderInfo*, 60> mShapeRenderInfos;
    /// Fifteen two-bit fields; initialize 0x7100c09ce4 clears them and resetShader rewrites them.
    /* 0x218 */ u32 m_218[2] = {};
    // Not written by the constructor.
    /* 0x220 */ s32 _220;
    /* 0x224 */ u8 _224[4];
    /// Array of 0x18-byte records, one per shape (getShapeNum()); the destructor frees each record's
    /// pointer at +0 and then the array.
    struct ShapeRecord {
        // Freed with a plain delete by the destructor; the element type is unknown.
        u8* _0;
        void* _8;
        u8 _10;
        u8 _11[7];
    };
    static_assert(sizeof(ShapeRecord) == 0x18);
    /* 0x228 */ ShapeRecord* mShapeRecords = nullptr;
    /// Bit mask of the shapes whose display lists were calculated (calcDisplayList 0x7100c0a0b4).
    /* 0x230 */ u8 mCalcDisplayListMask = 0;
    /// Bit 0: the shape display lists were created; bit 1: they are currently owned by the unit.
    /* 0x231 */ u8 mDisplayListFlags = 0;
    /* 0x232 */ u8 _232 = 0;
    /* 0x233 */ u8 _233;
    /* 0x234 */ s32 _234 = -1;
};
static_assert(sizeof(ModelRenderUnitNW) == 0x238);

}  // namespace gsys

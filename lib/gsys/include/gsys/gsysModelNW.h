#pragma once

#include <gsys/gsysModelUnit.h>
#include <gsys/gsysG3dResModelEx.h>
#include <nn/g3d/ModelObj.h>
#include <nn/gfx/gfx_MemoryPool.h>
#include <nn/gfx/gfx_Types.h>
#include <prim/seadDelegate.h>

namespace agl::lght {
class LocalLightMapObj;
}

namespace agl {
class DrawContext;
}

namespace gsys {

class ModelAutoAnimation;
class Model;
class ModelDynamicEnvInfo;
class ModelRenderUnitNW;

// XXX: bad name. This doesn't reflect the fact that ModelNW is a ModelUnit, not a Model.
// TODO
class ModelNW : public ModelUnit,
                public nn::g3d::ICalculateWorldCallback,
                public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ModelNW, ModelUnit)

public:
    // 0x7100c030dc (unnamed row): the unit constructor (ModelUnit base setup and vtable stores).
    ModelNW();

    // Constructor c030bc and initialize wrapper c03308 prove this 0x20-byte argument.
    struct CreateArg {
        CreateArg();
        nn::g3d::ResModel* model;
        s32 buffer_num;
        s32 _c;
        void* _10;
        bool _18;
        bool _19;
    };
    bool initialize(nn::g3d::ResModel* model, s32 buffer_num, sead::Heap* heap);
    bool initialize(const CreateArg& arg, sead::Heap* heap);

    /// State carried over when a render unit is recreated at the same index. createRenderUnit_
    /// fills the flag and the fields from the unit it recycles; initRenderUnit_ restores them.
    struct RenderUnitInitData {
        bool reuse = false;
        u32 flags;
        /// One two-bit shader-variation field per ModelEnum::ShaderAssignType.
        u8 variations[15];
    };

    // initialize c0334c allocates 0x10-byte records, stores this at +0 and
    // the material index at +8, then installs each record as MaterialObj user data.
    struct MaterialUserData {
        ModelNW* model;
        u16 material_index;
    };
    static void getMaterialUserData(ModelNW** model, u16* material_index, const void* user_data);

    struct BoneCallbackArg;

    static s32 getSubMeshRangeNum(s32 type, s32 count);
    agl::lght::LocalLightMapObj* getReferenceLocalLightMapObj() const;

    void calcBounding() override;
    static void BoneVisibilityCallback(nn::g3d::ModelObj*, int);
    static void MaterialVisibilityCallback(nn::g3d::ModelObj*, int);

    using BoneCallback = sead::IDelegate1<BoneCallbackArg*>;
    using BoneCallbackStorage = sead::AnyDelegate1<BoneCallbackArg*>;

    const nn::g3d::SkeletonObj* getSkeletonObj() const { return mModelObj.GetSkeleton(); }
    // Graphics 0x7100f2e0f4 reads the material array of the model object at +0xe0.
    nn::g3d::ModelObj* getModelObj() { return &mModelObj; }
    // Inline-only in the original; name is a guess. The extension object initialize stored at the
    // resource's +0x60; the AS bone lookups go through it (ModelObj m_ResModel -> ResModel +0x60).
    G3dResModelEx* getResModelEx() const {
        return G3dResModelEx::getFromResModel(mModelObj.GetResource());
    }

    // 0x7100c03df8 / 0x7100c04230 (declaration only): mark the display lists of all shapes / one shape dirty.
    void setDisplayListDirty();
    void setDisplayListDirty(int shape_idx);

    // 0x7100c03cd0 (declared only): writes the shape instance value through the render-data record
    // of every shape. The row's mangled name is ModelNW and the body reads ModelNW's own shape
    // fields (+0x120 / +0x172), so the owner stays ModelNW; ksys::gfx 0x7100f1ef4c calls it on the
    // map unit's ModelUnit base pointer.
    void setShapeInstanceValue(f32 value);

    // 0x7100f1d514: looks the material name up in the dictionary at ModelUnit+0x60.
    // The native body takes a raw name (it calls strlen on the argument).
    int searchMaterialIndex(const char* material_name) const;

    // Native C03E8C selects the skeleton callback bone; -1 disables the callback.
    void setCallbackBoneIndex(int bone_idx);

    // ModelUnit slot 5 at 0x7100c06bc0 returns the actual resource name.
    sead::SafeString getName() const override;

    // ModelUnit overrides (0x7100c06d30 / 0x7100c06dd8).
    sead::SafeString getBoneName(int bone_idx) const override;
    // 0x7100c04b2c: counts the model resource's extension object in.
    void bindResource() override;
    // 0x7100c04e70
    int getBoneParentIndex(int bone_idx) const override;
    void clearBoneLocalMatrix() override;
    // The remaining ModelUnit pure virtuals have unnamed implementations in the original; declared only.
    int getMaterialNum() const override;
    // 0x7100c07b80: the u16 render-unit count at ModelNW+0x110.
    int getModelRenderUnitNum() const override;
    int getShapeNum() const override;
    // 0x7100c05248: clears the texture slots of material `index`.
    void clearTexture(int index) override;
    // 0x7100c06f30
    sead::SafeString getMaterialName(int index) const override;
    // 0x7100c06950: the two per-buffer ready bits at +0x170.
    bool check(BoolType type) const override;
    // 0x7100c07b88: the byte at ModelObj +0x18.
    int getViewNum() const;
    ModelRenderUnit* getModelRenderUnit(int idx) override;
    const ModelRenderUnit* getModelRenderUnit(int idx) const override;
    // Native vtable AP24ca120 +70 is c04df8; +80 is c04e48, which
    // dispatches to +70. Both are distinct from the pointer-return slot +78.
    void getBoneWorldMatrix(sead::Matrix34f* matrix, int bone_idx) const override;
    void safeGetBoneWorldMatrix(sead::Matrix34f* matrix, int bone_idx) const override;
    // 0x7100c04e54: sets the world-matrix dirty flag and returns the 0x40-byte bone matrix.
    sead::Matrix34f* getBoneWorldMatrixPtr(int bone_idx) const override;

    // 0x7100c06be0 / 0x7100c06db4 / 0x7100c07b5c: the model object's skeleton bone count and
    // the per-bone / per-material visibility bits.
    int getBoneNum() const override;
    bool isBoneVisible(int bone_idx) const override;
    bool isMaterialVisible(int material_idx) const override;
    // 0x7100c06d60 / 0x7100c07b08: update the visibility bit and call the model's callback.
    void setBoneVisible(int bone_idx, bool visible) override;
    void setMaterialVisible(int material_idx, bool visible) override;

    // 0x7100c070d0 .. 0x7100c07a08: read the material object's runtime parameter buffer.
    bool getMaterialParamBool(int material_idx, int param_idx) const override;
    int getMaterialParamInt(int material_idx, int param_idx) const override;
    u32 getMaterialParamU32(int material_idx, int param_idx) const override;
    float getMaterialParamF32(int material_idx, int param_idx) const override;
    const sead::Vector2f& getMaterialParamVector2f(int material_idx, int param_idx) const override;
    const sead::Vector3f& getMaterialParamVector3f(int material_idx, int param_idx) const override;
    const sead::Vector4f& getMaterialParamVector4f(int material_idx, int param_idx) const override;
    const sead::Color4f& getMaterialParamColor4f(int material_idx, int param_idx) const override;
    sead::Color4f getMaterialParamColor3f(int material_idx, int param_idx) const override;
    sead::Matrix34f* getMaterialParamEffectMatrixPtr(int material_idx, int param_idx) const override;
    float getMaterialParamXluAlpha(int material_idx, int param_idx) const override;
    void getMaterialParamTexSRT(int material_idx, int param_idx, sead::Vector2f* scale,
                                float* rotate, sead::Vector2f* translate) const override;
    sead::SafeString getMaterialParamName(int material_idx, int param_idx) const override;

protected:
    // 0x7100c042e0 (declared here because ModelProceduralShape also calls it): recycles the render
    // unit at `index` into `init` and allocates an unconstructed unit of `size` bytes.
    void* createRenderUnit_(int index, RenderUnitInitData* init, size_t size, sead::Heap* heap);
    // 0x7100c043a4: initializes `unit` and restores the recycled state. Returns false on failure.
    bool initRenderUnit_(ModelRenderUnitNW* unit, int index, const RenderUnitInitData& init,
                         sead::Heap* heap);
    // 0x7100c07b94 (declared only): creates and initializes the plain render unit `index`;
    // createRenderUnitNW forwards to it.
    ModelRenderUnitNW* allocAndInitRenderUnitNW(int index, sead::Heap* heap);
    virtual void drawDetail(agl::DrawContext* context) const;
    virtual void createRenderUnitNW(int, sead::Heap* heap);

    virtual void calcBounding_();  // NOLINT(bugprone-virtual-near-miss)
    virtual void calcGPUSkinning_();

    void Exec(nn::g3d::ICalculateWorldCallback::CallbackArg& arg,
              nn::g3d::WorldMtxManip& world_mtx_manip) override;

private:
    friend class Model;
    friend class ModelRenderUnitNW;
    friend class ModelProceduralShape;
    friend class ModelRenderCache;

    u8 _168;
    nn::g3d::ModelObj mModelObj;
    mutable u8 _200;
    u8 _201;
    u8 mBufferNum;
    u8 _203;
    u8 _204;
    u8 _205;
    u8 _206;
    u8 _207;
    u32 _208;
    ModelRenderUnitNW** mRenderUnits;
    ModelAutoAnimation* mAutoAnimation;
    ModelDynamicEnvInfo* mDynamicEnvInfo;
    void* _228;
    /// 0x40-byte per-bone world matrix slots; getBoneWorldMatrixPtr indexes this array.
    /// getBoneWorldMatrix 0x7100c04df8 loads a full 4x4 from the same slot.
    struct BoneWorldMatrix {
        sead::Matrix34f mMatrix;
        f32 _30[4];
    };
    static_assert(sizeof(BoneWorldMatrix) == 0x40);
    BoneWorldMatrix* mBoneWorldMatrices;
    void* _238;
    BoneCallbackStorage mBoneCallback;
    void* _260;
    int _268;
    void* _270;
    nn::gfx::MemoryPool mMemoryPool;
};

}  // namespace gsys

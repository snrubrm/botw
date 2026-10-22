#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace nn::g3d {
class ResMaterial;
}

namespace gsys {

namespace ModelEnum {
enum class ShaderAssignType;
}

// G3dResModelEx +0x18 is an array with stride 0x440 (ksys::tera 0x71011413b4); the destructor
// 0x7100c6d0fc is in a vtable and stores the vtable at +0.
class G3dResMaterialEx : public sead::hostio::Node {
public:
    virtual ~G3dResMaterialEx();

    // 0x7100c6d228: the record size, 0x440.
    static s32 calcRequiredMemorySize(const nn::g3d::ResMaterial* res_material);

    // 0x7100c6d21c: stores the material and its owner.
    void setResMaterial(nn::g3d::ResMaterial* res_material);

    // ModelResource::searchModelShader 0x7100c0c20c passes this to the shader archives.
    const nn::g3d::ResMaterial* getResMaterial() const { return mResMaterial; }

    // The 0xb8-byte shading-model record selected by the mask at +0xd8; internals unrecovered.
    struct ShadingModelInfo {
        u8 _0[0xb8];
    };
    // 0x7100c6d958
    const ShadingModelInfo* getShadingModelObj(ModelEnum::ShaderAssignType assign_type) const;
    // 0x7100c6d9cc (declared only)
    const char* getShaderOption(const sead::SafeString& name) const;
    // 0x7100c6d974
    bool isShaderOptionBool(const sead::SafeString& name) const;

private:
    u8 _8[0x10 - 0x8];
    const nn::g3d::ResMaterial* mResMaterial;
    u8 _18[0x20 - 0x18];
    ShadingModelInfo mShadingModel;
    /* 0xd8 */ u32 mMask;
    u8 _dc[0x440 - 0xdc];
};
static_assert(sizeof(G3dResMaterialEx) == 0x440);

}  // namespace gsys

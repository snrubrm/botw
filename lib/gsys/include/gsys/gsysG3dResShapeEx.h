#pragma once

#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelShaderProgram.h"

namespace agl {
class DrawContext;
namespace g3d {
class ModelShaderAttribute;
class ModelShaderSampler;
}  // namespace g3d
}  // namespace agl

namespace nn::g3d {
class ResShape;
}

namespace gsys {

namespace ModelEnum {
enum class ShaderAssignType;
}

class ModelAssignRenderInfo;
class ModelRenderCache;
class G3dResMaterialEx;

// C6DD78 allocates arrays with stride 0x1190. Native table 24D0D50 has
// Node::getNodeClassType followed by the class's own D1/D0.
class G3dResShapeEx : public sead::hostio::Node {
public:
    G3dResShapeEx();
    virtual ~G3dResShapeEx();

    // Inline-only in the original; name is a guess. C6F3CC stores the resource
    // and independently formats its name, also consumed by callback 1200AC0.
    const nn::g3d::ResShape* getResShape() const { return mResShape; }

    // 0x7100c6f580: stores the shape and its owner.
    void setResShape(nn::g3d::ResShape* res_shape);

    friend class ModelRenderCache;

    // One 0x40-byte record per shader assignment and variation, four per pass. The constructor
    // 0x7100c6ee78 clears the first byte of each and constructs the ModelShaderProgram at +0x10;
    // bindShader fills the attribute at +0x20.
    struct ShaderRecord {
        u8 _0;
        u8 _1[0xf];
        /* 0x10 */ ModelShaderProgram mShaderProgram;
        /* 0x20 */ agl::g3d::ModelShaderAttribute* mAttribute;
        /* 0x28 */ const agl::g3d::ModelShaderSampler* mSampler;
        u8 _30[0x10];
    };
    static_assert(sizeof(ShaderRecord) == 0x40);

    // Inline-only in the original; name is a guess. ksys::tera 0x71011413b4 reads the attribute of
    // each of the 15 passes at +0x30 + pass * 0x100, i.e. record pass * 4.
    agl::g3d::ModelShaderAttribute* getShaderAttribute(s32 pass) const {
        return mShaderRecords[pass * 4].mAttribute;
    }

    // 0x7100c701c4: activates the material resource and shader state for this shape.
    void activateResource(agl::DrawContext* context, const G3dResMaterialEx* material,
                          ModelEnum::ShaderAssignType assign_type, int variation) const;

    // 0x7100c70794 (declared only): called by ~ModelRenderUnitNW 0x7100c09b2c.
    void destroyShapeDL(sead::UnsafeArray<ModelAssignRenderInfo*, 60>* infos) const;

    // The 0x14-byte shader information record cleared by calcShaderInfo.
    struct ShaderInfo {
        u8 _0[0x14];
    };
    // 0x7100c70564: clears the record.
    void calcShaderInfo(ModelEnum::ShaderAssignType assign_type, int variation,
                        ShaderInfo* info) const;
    // ModelRenderUnitNW::getName 0x7100c09d40 returns the string that
    // updateShapeName 0x7100c6f58c formats at +0xf48.
    const sead::BufferedSafeString& getShapeName() const { return mShapeName; }

private:
    nn::g3d::ResShape* mResShape;
    /* 0x10 */ ShaderRecord mShaderRecords[60];
    u8 _f10[0xf48 - 0xf10];
    /* 0xf48 */ sead::BufferedSafeString mShapeName;
    u8 _f60[0x1190 - 0xf60];
};
static_assert(sizeof(G3dResShapeEx) == 0x1190);
}  // namespace gsys

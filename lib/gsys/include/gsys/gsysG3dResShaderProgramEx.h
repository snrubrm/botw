#pragma once

#include <basis/seadTypes.h>
#include <common/aglShaderEnum.h>
#include <common/aglShaderLocation.h>

namespace agl {
class DrawContext;
}  // namespace agl

namespace nn::g3d {
class ResShaderProgram;
}

namespace gsys {

class ModelRenderCache;

// The render-state extension of a g3d shader program. Constructor 0x7100c6e820 zeroes the
// prefix, stores -1 in the two id words at +0x10, then fills the 0xbc-byte location block at
// +0x1c with 0xff. The first 29 words of the block are the texture sampler locations, the last
// fifteen (+0x9c) are the uniform block locations that isSameUniformBlockLocation
// 0x7100c6ede4 compares.
// TODO: incomplete. Only the fields the render cache reads are modelled.
class G3dResShaderProgramEx {
public:
    // 0x7100c6ee24
    void load(agl::DrawContext*, const nn::g3d::ResShaderProgram*, agl::ShaderOptimizeType,
              bool) const;

private:
    friend class ModelRenderCache;

    u64 _0;
    // The shader mode is bits 14-15 of this halfword.
    u16 mFlags;
    u8 _a[6];
    /* 0x10 */ s32 mProgramId;
    /* 0x14 */ s32 mRenderState;
    /* 0x18 */ u32 mTextureMask;
    /* 0x1c */ agl::ShaderLocation mSamplerLocations[29];
    /* 0x90 */ agl::ShaderLocation _90[3];
    /* 0x9c */ agl::ShaderLocation mUniformBlockLocations[15];
    /* 0xd8 */ u32 _d8;
};

}  // namespace gsys

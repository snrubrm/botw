#include <gsys/gsysShaderContext.h>
#include <common/aglRenderBuffer.h>
#include <gfx/seadViewport.h>

namespace gsys {

ShaderContext::ShaderContext() : _48(0), mSceneMaterial(nullptr) {}

void ShaderContext::setSceneMaterial(ModelNW* model) {
    mSceneMaterial = model;
}

void ShaderContext::setEnvStruct(int index, void* ptr, u64 size) {
    mRenderUBOs[index].mEnvStruct = ptr;
    mRenderUBOs[index].mEnvStructSize = size;
}

void ShaderContext::setAreaOverride(int index, f32 value, int first, int second) {
    auto& ubo = mRenderUBOs[index];
    ubo._78 = first;
    ubo._7a = second;
    ubo._7c = value;
}

void ShaderContext::calcGpuRenderBuffer(const agl::RenderBuffer& buffer,
                                      const sead::Viewport& viewport) {
    sead::Vector2f size;
    viewport.getOnFrameBufferSize(&size, buffer);
    const f32 width = viewport.getSizeX();
    const f32 height = viewport.getSizeY();
    const sead::Vector4f physical(size.x, size.y, size.x > 0 ? 1.0f / size.x : 0.0f,
                                size.y > 0 ? 1.0f / size.y : 0.0f);
    const sead::Vector4f virtual_size(width, height, width > 0 ? 1.0f / width : 0.0f,
                                    height > 0 ? 1.0f / height : 0.0f);
    auto& block = mViewUBOs.front().block;
    block.setData(8, &physical);
    block.setData(9, &virtual_size);
}

// NON_MATCHING: complete parameter writes, with different payload register allocation.
void ShaderContext::calcGpuDepthShadow(f32 a, f32 b, f32 c, f32 d,
                                     const sead::Vector2f& offset) {
    const sead::Vector4f values(a, b, c, d);
    auto& block = mViewUBOs.front().block;
    block.setData(18, &values);
    const sead::Vector4f offset4(offset.x, offset.y, 0, 0);
    block.setData(19, &offset4);
}

void ShaderContext::calcGpuDepthShadowCascade(int index, const sead::Matrix44f& matrix) {
    if (index > 3)
        return;
    mViewUBOs.front().block.setData(17, &matrix, 4 * index, 4);
}

}  // namespace gsys

#include <gsys/gsysShaderContext.h>

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

}  // namespace gsys

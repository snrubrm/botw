#include "gsys/gsysModelShaderHolder.h"
#include <nn/g3d/ResMaterial.h>
#include <nn/g3d/ResShaderFile.h>

namespace gsys {

// 0x7100c3cea0
void ModelShaderArchive::setBinary(void* binary) {
    mBinary = binary;
    mShaderArchive = static_cast<ShaderArchive*>(
        nn::g3d::ResShaderFile::ResCast(binary)->mShaderArchive);
}

// 0x7100c3d3a0
const ModelShaderRecord* ModelShaderArchive::getModelShader(int index) const {
    return &mShaderArchive->mRecords[index];
}

// 0x7100c3d244
const ModelShaderRecord* ModelShaderArchive::searchModelShader(const sead::SafeString& name) const {
    const ShaderArchive* archive = mShaderArchive;
    const char* key = name.cstr();
    const nn::util::ResDic* dic = archive->mDic;
    if (!dic)
        return nullptr;
    const int index = dic->FindIndex(key);
    if (index == nn::util::ResDic::Npos)
        return nullptr;
    return &archive->mRecords[index];
}

// NON_MATCHING: the original loads SafeStringBase<char>::cNullChar and the SafeStringBase vtable
// directly; our sead objects are reached through the GOT. The instruction count and body agree.
// 0x7100c3d3b4
const ModelShaderRecord* ModelShaderArchive::searchModelShader(
    const nn::g3d::ResModel* model, const nn::g3d::ResMaterial* material) const {
    const auto* assign = material->mShaderAssign;
    if (!assign)
        return nullptr;
    if (!mName.isEqual(assign->mShadingModelName.Get()->GetData()))
        return nullptr;
    return searchModelShader(assign->mShaderName.Get()->GetData());
}

}  // namespace gsys

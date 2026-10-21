#include "gsys/gsysModelShaderHolder.h"
#include <nn/g3d/ResShaderFile.h>
#include "gsys/gsysORUtil.h"

namespace gsys {

ModelShaderHolder::ModelShaderHolder() = default;

ModelShaderHolder::~ModelShaderHolder() = default;

void ModelShaderHolder::initialize(sead::Heap* heap, sead::Heap* debug_heap) {
    mArchives.allocBuffer(0x80, heap);
    ORUtil::setNodeMeta(this, ORUtil::Category::_0, ORUtil::Attribute::_2, debug_heap);
}

ModelShaderArchive* ModelShaderHolder::addModelShaderArchive(void* binary, sead::Heap* heap,
                                                             sead::Heap* debug_heap) {
    if (!nn::g3d::ResShaderFile::IsValid(binary))
        return nullptr;

    auto* archive = new (heap) ModelShaderArchive;
    mArchives.pushBack(archive);
    if (binary) {
        archive->setBinary(binary);
        archive->setup(heap, debug_heap);
    }
    return archive;
}

void ModelShaderHolder::setInvalidModelShaderArchive(ModelShaderArchive* archive) {
    mInvalidArchive = archive;
}

// NON_MATCHING: register allocation around the archive name.
const ModelShader* ModelShaderHolder::searchModelShader(const sead::SafeString& archive_name,
                                                        const sead::SafeString& shader_name) const {
    for (auto& archive : mArchives) {
        if (archive_name == archive.getName()) {
            if (const ModelShader* shader = archive.searchModelShader(shader_name))
                return shader;
        }
    }
    return nullptr;
}

}  // namespace gsys

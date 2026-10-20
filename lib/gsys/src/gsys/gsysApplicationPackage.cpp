#include "gsys/gsysApplicationPackage.h"
#include "gsys/gsysORUtil.h"

namespace gsys {

SEAD_SINGLETON_DISPOSER_IMPL(ApplicationPackage)

static_assert(offsetof(ApplicationPackage::Package, mModelSceneConfigList) == 0x4e0);
static_assert(offsetof(ApplicationPackage::Package, mModelShaderHolder) == 0x54648);
static_assert(offsetof(ApplicationPackage::Package, mParticleConfig) == 0x54668);

ApplicationPackage::~ApplicationPackage() {
    if (mPackage)
        delete mPackage;
}

void ApplicationPackage::initialize(sead::Heap*, sead::Heap* debug_heap) {
    ORUtil::setNodeMeta(this, ORUtil::Category::_0, debug_heap);
}

const ModelShader* ApplicationPackage::searchModelShader(const sead::SafeString& archive_name,
                                                         const sead::SafeString& shader_name) const {
    return mPackage->mModelShaderHolder.searchModelShader(archive_name, shader_name);
}

const ModelShader* ApplicationPackage::getInvalidModelShader() const {
    ModelShaderArchive* archive = mPackage->mModelShaderHolder.getInvalidModelShaderArchive();
    if (!archive)
        return nullptr;
    return archive->getModelShader(0);
}

ParticleConfig* ApplicationPackage::getParticleConfig() const {
    return &mPackage->mParticleConfig;
}

bool ApplicationPackage::searchAglShaderFile(void** binary, void** source,
                                             const sead::SafeString& name) {
    return mPackage->searchAglShaderFile(binary, source, name);
}

void ApplicationPackage::setSystemModelShader(sead::ArchiveRes* archive) {
    mSystemModelShader = archive;
}

// NON_MATCHING: the original calls setup and returns instead of tail-calling it.
void ApplicationPackage::setupModelSceneConfig(const sead::SafeString& config_name) {
    mPackage->mModelSceneConfigList.setup(config_name);
}

}  // namespace gsys

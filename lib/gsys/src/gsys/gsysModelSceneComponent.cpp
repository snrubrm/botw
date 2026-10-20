#include <gsys/gsysModelSceneComponent.h>

namespace gsys {

ModelSceneComponent::ModelSceneComponent() : _8(nullptr) {}


void ModelSceneComponent::bind() {}
void ModelSceneComponent::unbind(Model*) {}
void ModelSceneComponent::preCalcView(ModelSceneContext*) {}
void ModelSceneComponent::calcViewGPU(const ModelSceneContext&) {}
void ModelSceneComponent::attachHostIO(sead::hostio::Node*) {}
void ModelSceneComponent::drawDebug(agl::DrawContext*, const ModelSceneContext&) const {}

void ModelSceneComponent::initializeComponent(const ModelSceneConfig* config, sead::Heap*) {
    _8 = config;
}

// NON_MATCHING: the original copies cEmptyString into a stack temporary and keeps the vtable
// and the string pointer in two registers; our build reuses one register, so only the register
// allocation of the temporary differs.
void ModelSceneComponent::setUpComponent(int index, sead::Heap*, sead::Heap* heap) {
    const sead::SafeString empty = sead::SafeString::cEmptyString;
    mDebugTexturePage.setUp(index, empty, heap);
}

}  // namespace gsys

#include <gsys/gsysModelSceneComponent.h>

namespace gsys {

void ModelSceneComponent::bind() {}
void ModelSceneComponent::unbind(Model*) {}
void ModelSceneComponent::preCalcView(ModelSceneContext*) {}
void ModelSceneComponent::calcViewGPU(const ModelSceneContext&) {}
void ModelSceneComponent::attachHostIO(sead::hostio::Node*) {}

void ModelSceneComponent::initializeComponent(const ModelSceneConfig* config, sead::Heap*) {
    _8 = config;
}

}  // namespace gsys

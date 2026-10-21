#include <gsys/gsysLayer3D.h>
#include <gsys/gsysModelScene.h>
#include <common/aglDrawContext.h>
#include <layer/aglRenderInfo.h>

namespace gsys {
// The original calls isRenderStepGPUCalc in these hooks and discards the result.
void Layer::preDrawRenderStepImpl(const agl::lyr::RenderInfo& info) const {
    agl::DrawContext* context = info.getDrawContext();
    isRenderStepGPUCalc(info.getStepIndexMaybe());
    context->changeShaderMode(agl::cShaderMode_UniformRegister, agl::ShaderOptimizeType(0));
}

void Layer::preDrawRenderStepMethodImpl(const agl::lyr::RenderInfo& info,
                                        const agl::lyr::DrawMethod& method) const {
    isRenderStepGPUCalc(info.getStepIndexMaybe());
}

void Layer::postDrawRenderStepMethodImpl(const agl::lyr::RenderInfo& info,
                                         const agl::lyr::DrawMethod& method) const {
    isRenderStepGPUCalc(info.getStepIndexMaybe());
}

void Layer::postDrawRenderStepImpl(const agl::lyr::RenderInfo& info) const {
    isRenderStepGPUCalc(info.getStepIndexMaybe());
}

bool Layer::checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type) const {
    return checkDerivedRuntimeTypeInfoStatic(type);
}
const sead::RuntimeTypeInfo::Interface* Layer::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}
Layer3D::~Layer3D() {
    if (mModelScene) {
        mModelScene->remove_(this);
        mModelScene = nullptr;
    }
}

s32 Layer3D::setModelScene(ModelScene* scene) {
    if (mModelScene) {
        mModelScene->remove_(this);
        mSceneIndex = -1;
    }
    if (scene)
        mSceneIndex = scene->add_(this);
    mModelScene = scene;
    return mSceneIndex;
}

bool Layer3D::isRenderStepNoDependency(s32 step) const {
    if (step == 2)
        return _ef1 >> 1 & 1;
    return false;
}

bool Layer3D::checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type) const {
    return checkDerivedRuntimeTypeInfoStatic(type);
}
const sead::RuntimeTypeInfo::Interface* Layer3D::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}
}

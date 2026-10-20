#pragma once

#include <gsys/gsysLayer.h>
#include <layer/aglDrawMethod.h>

namespace gsys {

class ModelScene;

// Constructor BF51A4 initializes the model scene and draw method after Layer.
class Layer3D : public Layer {
public:
    Layer3D();
    ~Layer3D() override;
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<Layer> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo) {
        return typeInfo == getRuntimeTypeInfoStatic() ||
               Layer::checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const override;
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;
    s32 getRenderStepNum() const override;
    sead::SafeString getRenderStepName(s32 step) const override;
    bool isRenderStepGPUCalc(s32 step) const override;
    bool isRenderStepNoDependency(s32 step) const override;
    bool isForceDisableClear() const override;
    void calcJobWeight() override;
    void doInitialize(sead::Heap* heap) override;
    void draw_(const agl::lyr::RenderInfo& info) const;
private:
    ModelScene* mModelScene;
    agl::lyr::DrawMethod mDrawMethod;
    u8 _ef0[8];
};
static_assert(sizeof(Layer3D) == 0xef8);

}  // namespace gsys

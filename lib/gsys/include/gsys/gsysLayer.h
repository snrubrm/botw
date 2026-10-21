#pragma once

#include <layer/aglLayer.h>
#include <prim/seadSafeString.h>
#include <utility/aglDebugTexturePage.h>

namespace gsys {

class Layer : public agl::lyr::Layer {
public:
    Layer();
    ~Layer() override;
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<agl::lyr::Layer> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo) {
        return typeInfo == getRuntimeTypeInfoStatic() ||
               agl::lyr::Layer::checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface*) const override;
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override;
    void initializeImpl(sead::Heap* heap) override;
    void calcImpl() override;
    void postCalcCommandImpl() override;
    void preDrawImpl(const agl::lyr::RenderInfo& info) const override;
    void preDrawRenderStepImpl(const agl::lyr::RenderInfo& info) const override;
    void preDrawRenderStepMethodImpl(const agl::lyr::RenderInfo& info,
                                    const agl::lyr::DrawMethod& method) const override;
    void postDrawRenderStepMethodImpl(const agl::lyr::RenderInfo& info,
                                     const agl::lyr::DrawMethod& method) const override;
    void postDrawRenderStepImpl(const agl::lyr::RenderInfo& info) const override;
    void postDrawImpl(const agl::lyr::RenderInfo& info) const override;
    // Inline in the original (emitted at 0x71008bf300..0x71008bf320, outside this TU).
    bool isForceInvisible() const override { return mFlags >> 1 & 1; }
    void calcJobWeight() override {}
    virtual void doInitialize(sead::Heap* heap);
    virtual void doCalc() {}
    virtual void doPreDraw(const agl::lyr::RenderInfo& info) const {}
    virtual void doPostDraw(const agl::lyr::RenderInfo& info) const {}

private:
    // Constructor BF4378 initializes components through the E88-byte extent.
    u8 _208[0x3b0 - 0x208];
    // initializeImpl formats the layer name into this string and passes it to the debug page.
    sead::FixedSafeString<32> mDebugName;
    u8 _3e8[0xc44 - 0x3e8];
    // Bit 1: force invisible.
    u8 mFlags;
    u8 _c45[0xc48 - 0xc45];
    agl::utl::DebugTexturePage mDebugTexturePage;
};
static_assert(sizeof(agl::lyr::Layer) == 0x208);
static_assert(sizeof(Layer) == 0xe88);

}  // namespace gsys

#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <common/aglUniformBlock.h>

namespace sead {
namespace hostio {
class Context;
class PropertyEvent;
}  // namespace hostio
class Heap;
namespace RuntimeTypeInfo {
class Interface;
}  // namespace RuntimeTypeInfo
}  // namespace sead

namespace agl {
class UniformBlock;
namespace lght {
class LightPrePass;
}  // namespace lght
}  // namespace agl

namespace ksys::gfx {

// Name from the CSV rows at 0x7100f0bc9c .. 0x7100f15930 (initialize, destroy, calc, draw,
// getDrawLightNum, genMessage, ...). The class is the terrain pass's pre-pass light manager.
// Vtable 0x71024f3cd0 (vptr 0x71024f3ce0), 44 slots, first three from sead::hostio::Node.
// The per-light records at +0x10 hold one 0x80-byte light data object per view; initialize
// allocates them and each record's data array.
class PrePassLightMgr : public sead::hostio::Node {
public:
    // One per-view light. The 8-byte prefix is zeroed by initialize; the agl::UniformBlock
    // at +8 is the actual uniform block (0x78 bytes).
    struct LightData {
        u32 mFlags;
        u8 _4[4];
        agl::UniformBlock mUniformBlock;
    };
    static_assert(sizeof(LightData) == 0x80);

    // One 0x18-byte light record of the buffer at +0x10. +0 holds the enable bit, +4 the
    // per-view visibility mask used by the setVisible / isVisible pair, +8 the per-view
    // light data buffer.
    struct DrawLight {
        u16 mEnabled;
        u8 _2[2];
        u32 mVisibleMask;
        sead::Buffer<LightData> mLightData;
    };
    static_assert(sizeof(DrawLight) == 0x18);

    // Slots 1 and 2 of the vtable (the sead RTTI pair).
    virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* type_info) const;
    virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const;

    // 0x7100f0bc9c: stores the context, allocates the 0x18-byte records and each record's
    // per-view array, then creates the uniform blocks.
    virtual void initialize(agl::lght::LightPrePass* pre_pass, s32 light_num, s32 view_num,
                            sead::Heap* heap);
    // 0x7100f14e2c: destroys the uniform blocks, releases the per-view arrays and the records.
    virtual void destroy();
    // 0x7100f14f30: calls m31 once, then for every enabled light below min(light num, valid
    // num) calls m32 with the record.
    virtual void calc();
    virtual void calcView(s32 view, const void* context, s32 a);
    virtual void updateGPU() const;
    virtual void updateViewGPU(s32 view, const void* context) const;
    virtual void draw(void* draw_context, s32 view, const void* context, void* callback) const;
    virtual void drawDebug(void* draw_context, s32 view, const void* context) const;
    virtual void drawDebugTest(void* draw_context, s32 view, const void* context) const;
    virtual s32 getLightMax() const;
    virtual void m20();
    virtual void setValidNum(s32 num);
    virtual s32 getValidNum() const;
    virtual s32 getRecordNum() const;
    // 0x7100f15738: the draw-light count of view `index` (with the buffer's bounds fallback).
    virtual u32 getDrawLightNum(s32 index) const;
    // The wrappers below follow the agl::lght::LightPrePassLightMgr template (their ksys copies
    // are at 0x7100f15754 .. 0x7100f15834 and keep the template's order and sizes).
    // 0x7100f15754: sets or clears bit 0 of the record's +0 word.
    virtual void enableLight(s32 index, bool on);
    // 0x7100f15788: bit 0 of the record's +0 word.
    virtual bool isLightEnabled(s32 index) const;
    // 0x7100f157ac: sets or clears bit `bit` of the record's +4 mask.
    virtual void setVisible(s32 index, s32 bit, bool on);
    // 0x7100f157f0: writes the whole +4 mask.
    virtual void setVisibleDirect(s32 index, u32 mask);
    // 0x7100f15810: writes all ones or all zeros to the +4 mask.
    virtual void setVisibleAll(s32 index, bool on);
    // 0x7100f15834: bit `bit` of the record's +4 mask.
    virtual bool isVisible(s32 index, s32 bit) const;
    virtual void genMessage(sead::hostio::Context* context);
    virtual void listenPropertyEvent(const sead::hostio::PropertyEvent* event);

    // Tail slots of the vtable (0xd0 .. 0x158). m29 is the per-record release called by
    // destroy, m31 / m32 are the two calc callbacks, m34 / m35 the two GPU update callbacks.
    virtual void m26();
    virtual void m27(DrawLight* light);
    // 0x7100f14c68: declares a per-view light's single uniform block.
    virtual void m28(agl::UniformBlock* block, sead::Heap* heap);
    virtual void m29(DrawLight* light);
    virtual void m30();
    virtual void m31();
    virtual void m32(DrawLight* light);
    virtual void m33();
    virtual void m34() const;
    virtual void m35(const DrawLight* light) const;
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();

private:
    // vptr from sead::hostio::Node, then the context pointer.
    u8 _0[8];
    sead::Buffer<DrawLight> mLights;
    s32 mValidNum;
    u8 _24[4];
    sead::Buffer<u32> mDrawLightNums;
};

}  // namespace ksys::gfx

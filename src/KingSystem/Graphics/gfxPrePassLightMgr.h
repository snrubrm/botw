#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>

namespace ksys::gfx {

// Name from the CSV rows at 0x7100f0bc9c .. 0x7100f15930 (initialize, destroy, calc, draw,
// getDrawLightNum, genMessage, ...). The class is the terrain pass's pre-pass light manager; only
// the part the light accessors need is modelled so far. The other members keep their offsets.
class PrePassLightMgr {
public:
    // One 0x18-byte light record of the buffer at +0x10. +0 holds the enable bit, +4 the
    // per-view visibility mask used by the setVisible / isVisible pair.
    struct DrawLight {
        u16 mEnabled;
        u8 _2[2];
        u32 mVisibleMask;
        u8 _8[0x10];
    };
    static_assert(sizeof(DrawLight) == 0x18);

    // 0x7100f15738 (CSV name): the draw-light count of view `index` (with the buffer's bounds
    // fallback).
    u32 getDrawLightNum(s32 index) const;
    // The wrappers below follow the agl::lght::LightPrePassLightMgr template (their ksys copies are
    // at 0x7100f15754 .. 0x7100f15834 and keep the template's order and sizes).
    // 0x7100f15754: sets or clears bit 0 of the record's +0 word.
    void enableLight(s32 index, bool on);
    // 0x7100f15788: bit 0 of the record's +0 word.
    bool isLightEnabled(s32 index) const;
    // 0x7100f157ac: sets or clears bit `bit` of the record's +4 mask.
    void setVisible(s32 index, s32 bit, bool on);
    // 0x7100f157f0: writes the whole +4 mask.
    void setVisibleDirect(s32 index, u32 mask);
    // 0x7100f15810: writes all ones or all zeros to the +4 mask.
    void setVisibleAll(s32 index, bool on);
    // 0x7100f15834: bit `bit` of the record's +4 mask.
    bool isVisible(s32 index, s32 bit) const;

private:
    u8 _0[0x10];
    sead::Buffer<DrawLight> mLights;
    u8 _20[8];
    sead::Buffer<u32> mDrawLightNums;
};

}  // namespace ksys::gfx

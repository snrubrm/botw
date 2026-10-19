#include "KingSystem/Graphics/gfxPrePassLightMgr.h"

namespace ksys::gfx {

u32 PrePassLightMgr::getDrawLightNum(s32 index) const {
    return mDrawLightNums[index];
}

// NON_MATCHING: the compiler emits the and / orr pair in the opposite order (both branches are
// computed and selected, as in the original).
void PrePassLightMgr::enableLight(s32 index, bool on) {
    DrawLight& light = mLights[index];
    light.mEnabled = on ? u16(light.mEnabled | 1) : u16(light.mEnabled & ~u16(1));
}

bool PrePassLightMgr::isLightEnabled(s32 index) const {
    return (mLights[index].mEnabled & 1) != 0;
}

void PrePassLightMgr::setVisible(s32 index, s32 bit, bool on) {
    DrawLight& light = mLights[index];
    const u32 mask = u32(1) << bit;
    if (on)
        light.mVisibleMask |= mask;
    else
        light.mVisibleMask &= ~mask;
}

void PrePassLightMgr::setVisibleDirect(s32 index, u32 mask) {
    mLights[index].mVisibleMask = mask;
}

// NON_MATCHING: the compiler computes the all-ones mask before the buffer bounds select; the
// original computes it after.
void PrePassLightMgr::setVisibleAll(s32 index, bool on) {
    mLights[index].mVisibleMask = u32(-s32(on));
}

bool PrePassLightMgr::isVisible(s32 index, s32 bit) const {
    return (mLights[index].mVisibleMask & (u32(1) << bit)) != 0;
}

}  // namespace ksys::gfx

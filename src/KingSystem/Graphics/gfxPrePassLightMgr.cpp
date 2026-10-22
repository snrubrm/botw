#include "KingSystem/Graphics/gfxPrePassLightMgr.h"

#include <common/aglUniformBlock.h>
#include <math/seadMathCalcCommon.h>

namespace ksys::gfx {

void PrePassLightMgr::destroy() {
    for (DrawLight& light : mLights) {
        for (LightData& data : light.mLightData)
            data.mUniformBlock.destroy();
        m29(&light);
        light.mLightData.freeBuffer();
    }
    mDrawLightNums.freeBuffer();
    mLights.freeBuffer();
}

void PrePassLightMgr::calc() {
    if (mValidNum == 0)
        return;

    m31();

    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    DrawLight* light = &mLights(0);
    for (u32 i = 0; i != num; ++i) {
        if (isLightEnabled(s32(i)))
            m32(light);
        ++light;
    }
}

void PrePassLightMgr::updateGPU() const {
    if (mValidNum == 0)
        return;

    m34();

    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    const DrawLight* light = &mLights(0);
    for (u32 i = 0; i != num; ++i) {
        if (isLightEnabled(s32(i)))
            m35(light);
        ++light;
    }
}

s32 PrePassLightMgr::getLightMax() const {
    return -1;
}

sead::SafeString PrePassLightMgr::m20() const {
    return "LocationalLightMgr";
}

s32 PrePassLightMgr::getValidNum() const {
    return mValidNum;
}

s32 PrePassLightMgr::getRecordNum() const {
    return mLights.size();
}

void PrePassLightMgr::m28(agl::UniformBlock* block, sead::Heap* heap) {
    block->startDeclare(1, heap);
    block->declare_(agl::UniformBlock::cType_6, 1, 0, 1);
}

// NON_MATCHING: the record address is strength-reduced to a byte offset in the target (x24), ours
// keeps an smaddl index multiply; the flush-block tail otherwise matches.
void PrePassLightMgr::updateViewGPU(s32 view, const void* context) const {
    if (mValidNum == 0)
        return;
    if (mDrawLightNums[view] == 0)
        return;

    m36(view, context);

    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    for (u32 i = 0; i != num; ++i) {
        if (!isLightEnabled(s32(i)))
            continue;
        if (!isVisible(s32(i), view))
            continue;
        const DrawLight& light = mLights[s32(i)];
        const LightData& data = light.mLightData[view];
        if (data.mFlags & 1)
            continue;
        m37(&light, view, context);
        m38(&light, view, context);
        data.mUniformBlock.flushCPUCache();
    }
}

// NON_MATCHING: record-address strength reduction (the target keeps a byte offset and saves x27 in a
// 0x60 frame; ours recomputes the record address with madd in a 0x50 frame).
void PrePassLightMgr::drawDebug(void* draw_context, s32 view, const void* context) const {
    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    for (u32 i = 0; i != num; ++i) {
        if (!isLightEnabled(s32(i)))
            continue;
        if (!isVisible(s32(i), view))
            continue;
        const DrawLight& light = mLights[s32(i)];
        const LightData& data = light.mLightData[view];
        if ((data.mFlags & 1) == 0)
            m41(draw_context, &light, view, context);
    }
}

u32 PrePassLightMgr::getDrawLightNum(s32 index) const {
    return mDrawLightNums[index];
}

void PrePassLightMgr::enableLight(s32 index, bool on) {
    DrawLight& light = mLights[index];
    if (!on)
        light.mEnabled &= ~u16(1);
    else
        light.mEnabled |= 1;
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

void PrePassLightMgr::setVisibleAll(s32 index, bool on) {
    DrawLight& light = mLights[index];
    light.mVisibleMask = on ? ~u32(0) : 0;
}

bool PrePassLightMgr::isVisible(s32 index, s32 bit) const {
    return (mLights[index].mVisibleMask & (u32(1) << bit)) != 0;
}

}  // namespace ksys::gfx

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

#include "KingSystem/Graphics/gfxPrePassLightMgr.h"

#include <common/aglUniformBlock.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>

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

// The two debug strings are built and discarded in the original (the hostio group header calls that
// consumed them were compiled out of the release build), as in LocationalLightRig::genMessage.
// NON_MATCHING: the original builds both discarded FormatFixedSafeString<256> objects in one stack
// slot (sp+8, frame 0x170); clang 4 gives each temporary its own slot (frame 0x230), because the
// varargs constructor call leaves the slot without memory operands, so the two slots are not merged
// (two plain 256-byte arrays in the same scopes do merge). The vtable calls and the loop match.
void PrePassLightMgr::genMessage(sead::hostio::Context* context) {
    sead::FormatFixedSafeString<256>("Min=0, Max=%d", mLights.size() - 1);
    genMessagePrepareImpl_(context);

    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    DrawLight* light = &mLights(0);
    for (u32 i = 0; i != num; ++i) {
        sead::FormatFixedSafeString<256>("GroupHeader = %d", i);
        genMessageImpl_(context, *light, s32(i));
        ++light;
    }
}

void PrePassLightMgr::listenPropertyEvent(const sead::hostio::PropertyEvent* event) {
    listenPropertyEventPrepareImpl_(event);

    const u32 valid_num = mValidNum;
    const u32 record_num = mLights.size();
    const u32 num = sead::Mathu::min(record_num, valid_num);
    if (num == 0)
        return;

    DrawLight* light = &mLights(0);
    for (u32 i = 0; i != num; ++i) {
        listenPropertyEventImpl_(event, *light, s32(i));
        ++light;
    }
}

// NON_MATCHING: the record address is strength-reduced to a byte offset in the target (x24), ours
// keeps an smaddl index multiply; the flush-block tail otherwise matches.
// NON_MATCHING: same record-address strength reduction as drawDebug (target byte offset, ours madd).
void PrePassLightMgr::draw(void* draw_context, s32 view, const void* context, void* callback) const {
    if (mValidNum == 0)
        return;
    if (mDrawLightNums[view] == 0)
        return;

    m39(view, context, callback);

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
            m40(draw_context, &light, view, context, callback);
    }
}

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

// NON_MATCHING: same record-address strength reduction as drawDebug (target byte offset, ours madd).
void PrePassLightMgr::drawDebugTest(void* draw_context, s32 view, const void* context) const {
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
            m42(draw_context, &light, view, context);
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

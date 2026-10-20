#include "gsys/gsysModelRenderCache.h"
#include "gsys/gsysModelRenderContext.h"
#include "gsys/gsysShaderContext.h"

namespace gsys {

void ModelRenderCache::setBlendMask(u32 mask) {
    mBlendMask = mask;
}

void ModelRenderCache::setChannelMask(u32 mask) {
    mChannelMask = mask;
}

void ModelRenderCache::setPassViewProjIndex(int index) {
    if (mPassViewProjIndex != index) {
        mPassViewProjIndex = index;
        mRenderUBO = mContext->mShaderContext->getContextRenderUBO(mPassViewProjIndex);
        _148 = -1;
    }
}

void ModelRenderCache::setForceBlendColor(const sead::Color4f& color) {
    mForceBlendColor.r = color.r * color.a;
    mForceBlendColor.g = color.g * color.a;
    mForceBlendColor.b = color.b * color.a;
    mForceBlendColor.a = color.a;
}

}  // namespace gsys

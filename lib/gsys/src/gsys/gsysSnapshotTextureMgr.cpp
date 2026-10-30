#include <gsys/gsysSnapshotTextureMgr.h>
#include <math/seadMathCalcCommon.h>

namespace gsys {

void SnapshotTextureMgr::setUpViewInfo(const SnapshotTexture* texture) {
    const auto* target = texture->mTexture;
    const u32 width = target->getWidth();
    const u32 min_height = target->getMinHeight_();
    if (texture->mUseDirectView) {
        mProjection.setProjectionMatrix(texture->mDirectProjection, sead::Graphics::cDevicePosture_Same);
        mCamera.setDirectMatrix(texture->mDirectView);
    } else {
        const u32 height = sead::Mathi::max(min_height, target->getHeight());
        const f32 aspect = f32(sead::Mathu::max(width, 1u)) / f32(height);
        sead::PerspectiveProjection projection;
        projection.set(texture->mNear, texture->mFar, texture->mFovy, aspect);
        mProjection.setProjectionMatrix(projection.getProjectionMatrix(), sead::Graphics::cDevicePosture_Same);
        mCamera.setDirectMatrix(texture->mCamera.getMatrix());
    }
    mCamera.updateViewMatrix();
}

// 0x7100c60824
SnapshotTextureMgr::SnapshotTextureMgr() {}

// The original keeps the vptr store that a defaulted body drops.
SnapshotTextureMgr::ExpansionColor::~ExpansionColor() { ; }

// 0x7100c60dac
void SnapshotTextureMgr::setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1) {
    mRenderQueues[0] = queue0;
    mRenderQueues[1] = queue1;
}

void SnapshotTextureMgr::entry(SnapshotTexture* texture) {
    texture->initialize();
    mTextures.pushBack(&texture->mNode);
    if (!texture->mManager) {
        mUnk38.pushBack(&texture->mOtherNode);
        texture->mManager = this;
    }
}

// 0x7100c60c94
void SnapshotTextureMgr::updateGPU() {
    if (!mLightMapUpdated)
        return;

    mLightMapMgr.updateGPU();
    mLightMapMgr.updateViewGPU(0, true, mCamera.getMatrix());
}

}  // namespace gsys

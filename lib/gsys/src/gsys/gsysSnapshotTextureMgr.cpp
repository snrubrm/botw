#include <gsys/gsysSnapshotTextureMgr.h>

namespace gsys {

// 0x7100c60824
SnapshotTextureMgr::SnapshotTextureMgr() {}

// The original keeps the vptr store that a defaulted body drops.
SnapshotTextureMgr::ExpansionColor::~ExpansionColor() { ; }

// 0x7100c60dac
void SnapshotTextureMgr::setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1) {
    mRenderQueues[0] = queue0;
    mRenderQueues[1] = queue1;
}

// 0x7100c84618
bool SnapshotTexture::checkEnableToDraw() {
    return true;
}

// 0x7100c60c94
void SnapshotTextureMgr::updateGPU() {
    if (!mLightMapUpdated)
        return;

    mLightMapMgr.updateGPU();
    mLightMapMgr.updateViewGPU(0, true, mCamera.getMatrix());
}

}  // namespace gsys

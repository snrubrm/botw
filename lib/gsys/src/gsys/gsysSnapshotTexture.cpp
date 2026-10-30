#include <gsys/gsysSnapshotTextureMgr.h>

namespace gsys {

void SnapshotTexture::initialize() {
    _28 = false;
    mNode.erase();
}

void SnapshotTexture::retake() {
    mManager->entry(this);
    mCamera.setPos(mPosition);
    mCamera.setAt(mTarget);
    mCamera.updateViewMatrix();
}

// 0x7100c84618
bool SnapshotTexture::checkEnableToDraw() {
    return true;
}

}  // namespace gsys

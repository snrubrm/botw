#include <gsys/gsysSnapshotTextureMgr.h>

namespace gsys {

// 0x7100c60dac
void SnapshotTextureMgr::setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1) {
    mRenderQueues[0] = queue0;
    mRenderQueues[1] = queue1;
}

}  // namespace gsys

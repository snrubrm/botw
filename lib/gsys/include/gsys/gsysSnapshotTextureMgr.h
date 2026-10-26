#pragma once

#include <basis/seadTypes.h>

namespace gsys {

class ModelRenderQueue;

// TODO: incomplete. Only the render-queue slots used by setRenderQueue 0x7100c60dac are
// modelled; the rest of the snapshot texture manager is not.
class SnapshotTextureMgr {
public:
    // 0x7100c60dac
    void setRenderQueue(ModelRenderQueue* queue0, ModelRenderQueue* queue1);

private:
    u8 _0[0x50];
    /* 0x50 */ ModelRenderQueue* mRenderQueues[2];
};

}  // namespace gsys

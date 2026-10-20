#include "KingSystem/Terrain/teraRoute.h"

namespace ksys::tera {

Unk_710110e390::Unk_710110e390() = default;

// 0x710110e408: releases the two texture images of the route and the point / node buffers.
void Unk_710110e390::sub_710110E408() {
    if (_340.mFlags & 8) {
        if (mSamplers[0].getTextureData().getImagePtr().isValid())
            mSamplers[0].getTextureData().getImagePtr().deleteGPUMemBlock();
        if (mSamplers[1].getTextureData().getImagePtr().isValid())
            mSamplers[1].getTextureData().getImagePtr().deleteGPUMemBlock();
    }
    mSegments.freeBuffer();
    mNodes.freeBuffer();
    _340.mFlags = 0;
}

}  // namespace ksys::tera

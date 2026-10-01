#include "KingSystem/System/PlayerTrackReporter.h"

namespace ksys {

PlayerTrackReporter::PlayerTrackReporter() = default;

PlayerTrackReporter::~PlayerTrackReporter() {
    mBlocks.freeBuffer();
}

void PlayerTrackReporter::init(sead::Heap* heap) {
    mBlocks.tryAllocBuffer(4, heap, 0x40);
}

}  // namespace ksys

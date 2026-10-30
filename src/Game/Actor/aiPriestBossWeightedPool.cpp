#include "Game/Actor/aiPriestBossWeightedPool.h"

Unk_7102451280::Unk_7102451280() = default;

Unk_7102451280::~Unk_7102451280() {
    mRecords.freeBuffer();
}

bool Unk_7102451280::sub_710072B254(const InitArg& arg, sead::Heap* heap) {
    _38 = arg._0;
    mRecords.allocBuffer(arg.mCapacity, heap, 8);
    return true;
}

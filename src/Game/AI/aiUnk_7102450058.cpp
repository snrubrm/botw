#include "Game/AI/aiUnk_7102450058.h"

// NON_MATCHING: scheduling only (the original materialises 10.0f / -1.0f after the stores to
// +0x20 / +0x2c)
CarriedData::CarriedData(ksys::act::Actor* actor) : mActor(actor) {}

bool Unk_7102450298::init(sead::Heap* heap) {
    _30 = sub_7100F6D358(heap);
    return _30 != nullptr;
}

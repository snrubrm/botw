#include "Game/UI/uiScreens.h"

namespace uking::ui {

Unk_71024746b0::Unk_71024746b0() = default;

// NON_MATCHING (D0 only): the original orders `sub x21, x21, #1` after the pointer increment of the delete loop (D1 matches)
// 0x710092fcb4 (D1) / 0x710092fd34 (D0)
Unk_71024746b0::~Unk_71024746b0() {
    if (mItems.isBufferReady()) {
        for (auto& item : mItems) {
            if (item) {
                delete item;
                item = nullptr;
            }
        }
        mItems.freeBuffer();
    }
}

// 0x710092fdb0
void Unk_71024746b0::setHeap(sead::Heap* heap) {
    mHeap = heap;
}

// 0x710092fdb8
void Unk_71024746b0::update() {
    if (!mScreen || !mConfig || !mItems.isBufferReady())
        return;
    for (auto& item : mItems) {
        if (item)
            item->sub_710092F374(_30);
    }
}

}  // namespace uking::ui

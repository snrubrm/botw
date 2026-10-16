#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x71009300e8 (placeholder name; not decompiled): DynamicCast of the pane to eui::PartsEx (a second copy of
// eui::sub_7100945088 in this TU)
eui::PartsEx* sub_71009300E8(nn::ui2d::Pane* pane);

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

// 0x710092fe18
// NON_MATCHING: the original loads mItems[i] before calling sub_71009300E8 (C++14 order of the last assignment), which
// also changes which constants stay in registers across the loop
void Unk_71024746b0::initialize(Screen* screen, eui::LayoutEx* layout,
                                const sead::Buffer<ButtonPanePath>* config) {
    if (!mHeap)
        return;
    mScreen = screen;
    mConfig = config;
    if (!screen || !layout || !config)
        return;

    const s32 num = config->size();
    mItems.tryAllocBuffer(num, mHeap);
    if (!mItems.isBufferReady())
        return;
    mItems.fill(nullptr);

    for (s32 i = 0; i < num; ++i) {
        auto* pane = sub_7100AA0CB4(layout, (*mConfig)[i].entries, 5);
        if (!pane)
            continue;
        mItems[i] = new (mHeap) Unk_71024746b0Item;
        if (auto* item = mItems[i]) {
            item->_1c |= 1;
            item->_18 |= 1;
            mItems[i]->mScreen = mScreen;
            mItems[i]->mParts = sub_71009300E8(pane);
        }
    }
}

// 0x71009301f4
Unk_71024746b0Item* Unk_71024746b0::sub_71009301F4(s32 index) {
    if (mItems.isBufferReady() && static_cast<u32>(index) < static_cast<u32>(mItems.size()))
        return mItems(index);
    return nullptr;
}

}  // namespace uking::ui

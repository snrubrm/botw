#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100932ea4
void ButtonEventQueue::push(eui::AnimButton* button, s32 kind) {
    if (!mRecords.isBufferReady() || mRecords.isFull())
        return;

    auto* record = new (mFreeRecords.alloc()) Record;
    mRecords.pushBack(record);
    if (record) {
        record->button = button;
        record->kind = kind;
    }
}

}  // namespace uking::ui

#include "Game/UI/uiButtonEventQueue.h"
#include <new>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// The control's name (a constant object in the original, .data.rel.ro 0x7102474af0).
static const sead::SafeString sUnk_7102474af0 = "ButtonCallback";

// 0x7100932a14
ButtonEventQueue::ButtonEventQueue() {
    mName = sUnk_7102474af0.cstr();
}

// NON_MATCHING (D2 / D0): everything matches except the final reset: the original zeroes the pool fields (max count,
// pointer array, free list head, work area) with four inline stores where ours calls the out-of-line
// PtrArrayImpl::setBuffer(0, nullptr) and FreeList::reset (the fields are protected in lib/sead).
// 0x7100932a6c
ButtonEventQueue::~ButtonEventQueue() {
    if (mRecords.isBufferReady()) {
        releaseRecords();
        if (mRecords.isBufferReady()) {
            delete[] reinterpret_cast<u8*>(mFreeRecords.work());
            mRecords.setBuffer(0, nullptr);
            mFreeRecords.reset();
        }
    }
}

// NON_MATCHING: same code and loops; the original keeps the (64-bit) record count in a different callee-saved register
// and stores the free list terminator after computing the pointer array address.
// 0x7100932bbc
void ButtonEventQueue::init(sead::Heap* heap, s32 count) {
    if (count == 0)
        return;

    if (count > 0) {
        const size_t size = count;
        auto* work = new (heap, 8, std::nothrow) u8[size * (sizeof(Record) + sizeof(Record*))];
        if (work) {
            mFreeRecords.setWork(work, sizeof(Record), count);
            mRecords.setBuffer(count, work + size * sizeof(Record));
        }
    }
    if (mRecords.isBufferReady())
        releaseRecords();
}

// 0x7100932cfc
void ButtonEventQueue::Update(f32) {
    for (auto it = mRecords.begin(), end = mRecords.end(); it != end; ++it) {
        eui::AnimButton* button = it->button;
        if (!button)
            continue;
        auto* screen = sead::DynamicCast<ScreenEx>(button->mLayout->mScreen);
        if (!screen)
            continue;
        switch (it->kind) {
        case 1:
            screen->sub_71010AB97C(button);
            break;
        case 2:
            screen->sub_71010ABAA8(button);
            break;
        case 3:
            screen->sub_71010ABB68(button);
            break;
        case 4:
            screen->sub_71010ABC28(button);
            break;
        case 5:
            screen->sub_71010ABCE8(button);
            break;
        case 6:
            screen->sub_71010ABDA8(button);
            break;
        case 7:
            screen->sub_71010ABE68(button);
            break;
        case 8:
            screen->sub_71010ABF28(button);
            break;
        }
    }
    releaseRecords();
}

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

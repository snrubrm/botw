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

// NON_MATCHING: identical code, but the original calls separate out-of-line copies of uking::ui::Screen::doButton*_
// (0x71010ab97c / aa8 / b68 / c28 / ce8 / da8 / e68 / f28: the CSV names only the copies at the odd addresses between them,
// which are the ones in the vtable); we can only reference the one symbol.
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
            screen->Screen::doButtonOnStart_(button);
            break;
        case 2:
            screen->Screen::doButtonOnEnd_(button);
            break;
        case 3:
            screen->Screen::doButtonOffStart_(button);
            break;
        case 4:
            screen->Screen::doButtonOffEnd_(button);
            break;
        case 5:
            screen->Screen::doButtonDownStart_(button);
            break;
        case 6:
            screen->Screen::doButtonDownEnd_(button);
            break;
        case 7:
            screen->Screen::doButtonCancelStart_(button);
            break;
        case 8:
            screen->Screen::doButtonCancelEnd_(button);
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

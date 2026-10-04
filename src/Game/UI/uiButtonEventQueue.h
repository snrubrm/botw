#pragma once

#include <container/seadFreeList.h>
#include <container/seadPtrArray.h>
#include "Game/UI/euiButton.h"
#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace uking::ui {

// ScreenEx::mButtonEvents (0x368): a control of the screen (its name is "ButtonCallback"; vtable 0x7102474b00; the
// runtime type info is ControlBase's) that queues the button state changes reported to ScreenEx::doButton{OnStart, OnEnd, ..., CancelEnd}_
// (event kinds 1-8) and replays them in its per-frame Update through uking::ui::Screen's implementations. The
// records come from a free list (the work area of init holds the records followed by the pointer array).
class ButtonEventQueue : public eui::ControlBase {
public:
    struct Record {
        eui::AnimButton* button = nullptr;
        s32 kind = 0;
    };

    // 0x7100932a14
    ButtonEventQueue();
    // 0x7100932a6c (D1) / 0x7100932b10 (D0)
    ~ButtonEventQueue() override;
    // 0x7100932cfc
    void Update(f32 dt) override;

    // 0x7100932bbc: allocates room for `count` pending events
    void init(sead::Heap* heap, s32 count);
    // 0x7100932ea4
    void push(eui::AnimButton* button, s32 kind);

private:
    // inline-only in the original; name is a guess. Evidence: the same loop (reset every pending record and give it back to
    // the free list) is repeated in the destructors, init and Update.
    void releaseRecords() {
        for (s32 i = 0; i < mRecords.size(); ++i) {
            Record* record = mRecords(i);
            new (record) Record;
            mFreeRecords.free(record);
        }
        mRecords.clear();
    }

    /* 0x28 */ sead::PtrArray<Record> mRecords;
    /* 0x38 */ sead::FreeList mFreeRecords;
};
static_assert(sizeof(ButtonEventQueue) == 0x48);

}  // namespace uking::ui

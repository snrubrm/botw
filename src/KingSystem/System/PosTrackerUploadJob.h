#pragma once

#include <basis/seadTypes.h>
#include <prim/seadDelegate.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

// Placeholder name: upload job constructed at 0x7100a8f2dc (CSV mislabelled GameScene::sa).
// The callback loads game_data.sav or tracker blocks; sub_7100A8F9F0 submits their buffers to PosTrackerUploader.
class Unk_7100a8f2dc {
public:
    Unk_7100a8f2dc();
    bool sub_7100A8F310(void* arg);
    bool sub_7100A8F9F0(u64 nex_id);
    // The file-loading callbacks are declaration-only.
    bool sub_7100A8FAA4();
    bool sub_7100A8FCE4();

private:
    sead::Heap* mHeap = nullptr;
    void* mBuffer = nullptr;
    u32 mSize = 0;
    s32 mBlock = 0;
    bool mHardMode = false;
    bool _19 = false;
    s32 mState = 0;
    sead::Delegate1R<Unk_7100a8f2dc, void*, bool> mDelegate;
    // 0x7100a8faa4: exclusive-loop bit updates to this+0x40 at 0xa8fca0 and 0xa8fcb4.
    sead::Atomic<u32> mFlags{0};
};
KSYS_CHECK_SIZE_NX150(Unk_7100a8f2dc, 0x48);

}  // namespace ksys

#include "Game/UI/uiTexSlots.h"
#include "Game/UI/euiAnimator.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::ui {

// 0x7100a81208
UiTexSlots::UiTexSlots() = default;

// NON_MATCHING: same code, the original keeps the entry pointer of the second lookup in x8 (the register of the size)
// where ours uses a fresh register (register allocation only; the destructor below shows the same difference)
// 0x7100a813e0
void UiTexSlots::unload(s32 index) {
    if (eui::Animator* animator = mEntries[index].animator)
        animator->StopAtMin();
    Entry& entry = mEntries[index];
    if (entry.handle && entry.material)
        entry.material->GetTexMapArray()[entry.texMapIndex].ReplaceTextureInfo(&mTexInfo);
    if (mEntries[index].handle->requestedLoad())
        mEntries[index].handle->requestUnload2();
}

// NON_MATCHING: inlines unload() above (same register allocation difference)
// 0x7100a812a8
UiTexSlots::~UiTexSlots() {
    s32 i = 0;
    for (Entry& entry : mEntries) {
        if (entry.handle) {
            unload(i);
            delete entry.handle;
            entry.handle = nullptr;
        }
        ++i;
    }
    mEntries.freeBuffer();
}

}  // namespace uking::ui

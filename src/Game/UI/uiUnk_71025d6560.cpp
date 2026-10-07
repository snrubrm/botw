#include "Game/UI/uiUnk_71025d6560.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_71025d6560)

// D1 0x7100949808, D0 0x71009498c0
Unk_71025d6560::~Unk_71025d6560() {
    if (mEntries.isBufferReady()) {
        for (s32 i = 0, n = mEntries.size(); i < n; ++i)
            mEntries(i) = nullptr;
        mEntries.freeBuffer();
    }
}

// 0x7100949a60
void Unk_71025d6560::sub_7100949A60(s32 index, void* value) {
    if (mEntries.isBufferReady() && u32(index) < u32(mEntries.size()))
        mEntries(index) = value;
}

}  // namespace uking::ui

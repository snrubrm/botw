// The TU at 0x71012c7350 .. 0x71012c8800: SoundMgr::_b0 (Unk_710251b2e8).
#include "KingSystem/Sound/sndSoundMgrB0.h"
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>

namespace ksys::snd {

namespace {
// 0x710251b308 (in .data in the original)
Unk_710251b2e8::KindInfo sKindInfos[11] = {
    {2, 1, 1, 1, 2, 5, 1}, {1, 3, 0, 0, 0, 0, 0}, {1, 3, 0, 0, 0, 0, 0}, {1, 2, 0, 0, 0, 0, 0},
    {1, 3, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0}, {1, 3, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0},
    {1, 5, 0, 0, 0, 0, 0}, {1, 4, 0, 1, 4, 6, 1}, {1, 4, 0, 0, 0, 0, 0},
};
}  // namespace

// NON_MATCHING: the member initialisation stores are scheduled differently.
Unk_710251b2e8::Unk_710251b2e8() = default;

Unk_710251b2e8::~Unk_710251b2e8() {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        mEntries[i].mList1.clear();
        mEntries[i].mList1.freeBuffer();
        mEntries[i].mList2.clear();
        mEntries[i].mList2.freeBuffer();
    }
}

// NON_MATCHING: the table is constant here, so clang drops the size checks of the first lists; the original
// loads it as data (it is in .data, not .rodata).
void Unk_710251b2e8::init(sead::Heap* heap, sead::Heap* heap2) {
    for (s32 i = 0; i < 11; ++i) {
        mEntries[i].mList1.allocBuffer(sKindInfos[i].num1, heap);
        mEntries[i].mList2.allocBuffer(sKindInfos[i].num2, heap);
        mEntries[i]._60 = 0;
    }
    mHeap = heap2;
    mInitialized = true;
}

// NON_MATCHING: the original hoists the entry stride (0x68) out of the loop and indexes the kind table through
// a stack slot; ours rematerialises the stride before each entry and folds the retry counter decrement.
void Unk_710251b2e8::calc() {
    if (!mInitialized)
        return;

    auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < 11; ++i) {
        auto& entry = mEntries[i];
        if (entry.mList1.size() == 0)
            entry._60 = 0;
        else if (entry._60 > 0)
            --entry._60;
        else
            entry.mList1.clear();

        for (auto it = entry.mList2.robustBegin(), end = entry.mList2.robustEnd(); it != end; ++it) {
            auto& item = *it;
            if (--item._18 > 0)
                continue;
            if (!sub_71012C7C18(i, &item)) {
                if (--item._14 > 0) {
                    item._18 = sead::GlobalRandom::instance()->getS32Range(sKindInfos[i]._10,
                                                                           sKindInfos[i]._14 + 1);
                    continue;
                }
                item.handle.stop(-1.0f, 0.0f);
            }
            entry.mList2.erase(&item);
        }
    }
}

}  // namespace ksys::snd

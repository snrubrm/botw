#include "KingSystem/Physics/System/physUnk_71012a6844.h"
#include <prim/seadScopedLock.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::phys {

void Unk_71012a6844::sub_71012A69E0(ItemA* item) {
    auto lock = sead::makeScopedLock(mMutexA);
    if (!item->isLinked())
        mListA.pushBack(item);
}

void Unk_71012a6844::sub_71012A6A44(ItemA* item) {
    auto lock = sead::makeScopedLock(mMutexA);
    if (item->isLinked())
        mListA.erase(item);
}

void Unk_71012a6844::sub_71012A6AA4(ItemB* item) {
    auto lock = sead::makeScopedLock(mMutexB);
    mListB.pushBack(item);
}

void Unk_71012a6844::sub_71012A6AF8(ItemB* item) {
    auto lock = sead::makeScopedLock(mMutexB);
    mListB.erase(item);
}

void Unk_71012a6844::sub_71012A6B48() {
    auto lock = sead::makeScopedLock(mMutexA);
    _c8 = 0;
    for (auto& item : mListB)
        item._18 = 0;
}

// NON_MATCHING: when the record buffer is full the original also performs a discarded load of _c8 (one
// instruction).
void Unk_71012a6844::sub_71012A6BB0() {
    for (auto& item : mListA) {
        Record record;
        record._38 = item.m0();
        item.sub_7100F6EC20(&record._0, &record._c);
        item.sub_7100F6FF60(&record._18, &record._24);
        record._30 = item.mConstraint;
        for (auto& consumer : mListB) {
            if (_c8 >= mRecords.size() - 1)
                continue;
            const s32 index = _c8.increment();
            if (index == -1)
                continue;
            auto* stored = &mRecords[index];
            *stored = record;
            if (consumer._18 < consumer._8.size()) {
                const s32 slot = consumer._18.increment();
                consumer._8[slot] = stored;
            }
        }
    }
}

}  // namespace ksys::phys

// NON_MATCHING: placeholder destructor; the original (0x71012a67c8) also destroys members or bases
// this class does not declare yet.
Unk_7102519a68::~Unk_7102519a68() = default;

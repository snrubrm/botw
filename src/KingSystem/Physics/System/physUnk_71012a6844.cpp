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

}  // namespace ksys::phys

// NON_MATCHING: placeholder destructor; the original (0x71012a67c8) also destroys members or bases
// this class does not declare yet.
Unk_7102519a68::~Unk_7102519a68() = default;

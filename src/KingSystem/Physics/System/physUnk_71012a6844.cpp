#include "KingSystem/Physics/System/physUnk_71012a6844.h"
#include <prim/seadScopedLock.h>

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

}  // namespace ksys::phys

#include "gsys/gsysModelJobQueue.h"
#include <prim/seadScopedLock.h>

namespace gsys {

// NON_MATCHING: the original zeroes +0x10c..+0x11b with two unaligned 8-byte stores; the fields are
// stored one by one here and the store order differs.
ModelJobQueue::ModelJobQueue() = default;

void ModelJobQueue::bind(Model* model) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bound : mModels) {
        if (&bound == model)
            return;
    }
    mModels.pushBack(model);
}

void ModelJobQueue::unbind(Model* model) {
    auto lock = sead::makeScopedLock(mCS);
    s32 index = 0;
    for (auto& bound : mModels) {
        if (&bound == model) {
            mModels.erase(index);
            return;
        }
        ++index;
    }
}

void ModelJobQueue::clear() {
    mDrawList.clear();
}

void ModelJobQueue::swapDrawList() {
    _108.clear();
}

void ModelJobQueue::calc(bool enable) {
    _120 = 0;
    mFlags = enable ? (mFlags | 2) : (mFlags & ~2);
}

void ModelJobQueue::Job::invoke() {
    mQueue->invoke_(mArg0, mArg1, mArg2, mArg3);
}

}  // namespace gsys

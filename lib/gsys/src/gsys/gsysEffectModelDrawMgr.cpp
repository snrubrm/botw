#include <gsys/gsysEffectModelDrawMgr.h>

#include <new>

#include <gsys/gsysModel.h>

namespace gsys {

inline void EffectModelDrawMgr::Entry::clear() {
    mFlags &= ~1;
    if (_28)
        _28 = nullptr;
    if (_30)
        _30 = nullptr;
    if (_8)
        _8 = nullptr;
    if (_10)
        _10 = nullptr;
    if (mModel) {
        Model::sub_7100BF69F8(mModel);
        mModel = nullptr;
    }
    if (_40) {
        ::operator delete(_40);
        _40 = nullptr;
    }
}

EffectModelDrawMgr::EffectModelDrawMgr() : mCapacity(0), _4(0), _8(0), _20(nullptr) {}

bool EffectModelDrawMgr::requestDeleteModel(u32 id) {
    if (mCapacity <= id)
        return false;

    mCS2.lock();
    mEntries[id].mFlags |= 2;
    mCS2.unlock();
    return true;
}

bool EffectModelDrawMgr::execDeleteModel(u32 id) {
    mCS2.lock();

    bool result = false;
    if (!(mEntries[id].mFlags & 2)) {
        // Nothing was requested for this record.
        result = true;
    } else if (mEntries[id].mFlags & 1) {
        mEntries[id].mFlags &= ~1;
        mEntries[id].mFlags &= ~2;

        mEntries[id].clear();
        result = true;
    }

    mCS2.unlock();
    return result;
}

}  // namespace gsys

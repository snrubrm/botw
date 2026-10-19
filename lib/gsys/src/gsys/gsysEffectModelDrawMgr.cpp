#include <gsys/gsysEffectModelDrawMgr.h>

#include <new>

#include <gsys/gsysModel.h>
#include <gsys/gsysModelDrawObj.h>

namespace gsys {

inline void EffectModelDrawUnit::clear() {
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

EffectModelDrawUnit::~EffectModelDrawUnit() {
    clear();
}

EffectModelDrawMgr::EffectModelDrawMgr() : mCapacity(0), _4(0), _8(0), mModelDrawObjs(nullptr) {}

EffectModelDrawMgr::~EffectModelDrawMgr() {
    ModelDrawObj::freeBuffer(mModelDrawObjs, _4);
    if (mModelDrawObjs)
        ::operator delete(mModelDrawObjs);
    mEntries.freeBuffer();
}

int EffectModelDrawMgr::addModel(EffectModelDrawUnit::CreateArg arg, sead::Heap* heap) {
    mCS2.lock();

    for (u32 i = 0; i < mCapacity; ++i) {
        if (mEntries[i].mFlags & 5)
            continue;

        mEntries[i].mFlags |= 4;
        mCS2.unlock();

        bool result = mEntries[i].initialize(arg, heap);

        mCS2.lock();
        if (result) {
            mEntries[i].mFlags |= 1;
            mEntries[i].mFlags &= ~4;
            mCS2.unlock();
            return i;
        }

        mEntries[i].mFlags &= ~1;
        mEntries[i].mFlags &= ~4;
        break;
    }

    mCS2.unlock();
    return -1;
}

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

void EffectModelDrawMgr::preCalc() {
    mCS2.lock();

    _8 = 0;
    for (u32 i = 0; i < mCapacity; ++i) {
        EffectModelDrawUnit& entry = mEntries[i];
        if ((entry.mFlags & 3) != 1)
            continue;

        entry._20 = 0;
        for (u32 j = 0; j < entry.mUnkCount2; ++j)
            entry._28[j] = 0;
    }

    mCS2.unlock();
}

void EffectModelDrawMgr::postCalc() {
    mCS2.lock();

    for (u32 i = 0; i < mCapacity; ++i) {
        if ((mEntries[i].mFlags & 3) != 1)
            continue;

        mEntries[i].pushBack(this);
    }

    mCS2.unlock();
}

bool EffectModelDrawMgr::addInstance(u32 id, u32 type, const sead::Matrix34f& matrix,
                                     const sead::Vector3f& pos,
                                     const agl::lght::LocalLightMapObj* light, u16 a) {
    bool result = false;

    if (id < mCapacity) {
        mCS2.lock();
        if (mEntries[id].mFlags & 2) {
            mCS2.unlock();
        } else {
            if (mEntries[id].mFlags & 1) {
                mCS.lock();
                result = mEntries[id].addInstance(this, type, matrix, pos, light, a);
                mCS.unlock();
            }
            mCS2.unlock();
        }
    }

    return result;
}

}  // namespace gsys

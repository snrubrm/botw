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

bool EffectModelDrawUnit::createModel(const CreateArg& arg, sead::Heap* heap) {    Model::CreateArg model_arg;
    model_arg._4 = arg._0;

    if (arg.mNames && arg.mCount)
        mModel = Model::create(arg.mResource, arg.mNames, arg.mCount, "EffectModelDrawUnit",
                               model_arg, heap, nullptr);
    else
        mModel = Model::create(arg.mResource, "EffectModelDrawUnit", model_arg, heap, nullptr);

    mModel->bind(arg.mModelScene);

    for (s32 i = 0; i < mModel->getUnits().size(); ++i) {
        ModelUnit* unit = mModel->getUnits()[i]->mModelUnit;
        ModelUnitDrawArray::CreateArg draw_arg;
        draw_arg._0 = 0;
        draw_arg._4 = 0;
        unit->createDrawArray(draw_arg, heap);
    }

    return true;
}

void EffectModelDrawUnit::pushBack(EffectModelDrawMgr* mgr) {
    for (u32 i = 0; i < mUnkCount2; ++i)
        mModel->getUnits()[i]->mModelUnit->getDrawArray()->mSize = 0;

    if (_20) {
        bool any = false;
        for (u32 i = 0; i < _20; ++i) {
            u16 record = _10[i];
            s32 index = record & 0xfff;
            u16 group = record >> 12;
            ModelUnit* unit = _30[group];

            mgr->mCS2.lock();
            ModelDrawObj* obj = nullptr;
            if (index < mgr->_4)
                obj = &mgr->mModelDrawObjs[index];
            mgr->mCS2.unlock();

            if (obj) {
                ModelUnitDrawArray* draw_array = unit->getDrawArray();
                s32 n = draw_array->mSize;
                draw_array->mSize = n + 1;
                draw_array->mUnits[n] = obj;
                any = true;
            }
        }

        if (any)
            mModel->requestDraw();
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

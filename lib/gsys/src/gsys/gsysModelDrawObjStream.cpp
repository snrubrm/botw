#include "gsys/gsysModelDrawObjStream.h"
#include "gsys/gsysModelDrawObj.h"
#include "gsys/gsysModelWorkBuffer.h"

namespace gsys {

ModelDrawObjStream::ModelDrawObjStream() : mCount(0), mObjs(nullptr), mFlags(0) {}

ModelDrawObjStream::~ModelDrawObjStream() = default;

// NON_MATCHING: the original keeps both pointer stores in each branch (one paired store).
void ModelDrawObjStream::begin(bool use_entries, bool flag, s32 core) {
    mFlags.changeBit(1, use_entries);
    mFlags.changeBit(0, flag);
    mCount = 0;
    u8* ptr = *ModelWorkBuffer::instance()->getBufferPtr(core);
    if (mFlags.isOnBit(1)) {
        mEntries = reinterpret_cast<Entry*>(ptr);
        mObjs = nullptr;
    } else {
        mEntries = nullptr;
        mObjs = reinterpret_cast<const ModelDrawObj**>(ptr);
    }
}

void ModelDrawObjStream::add(const ModelDrawObj* obj, u32 value, s32 param) {
    if (!mFlags.isOnBit(1)) {
        mObjs[mCount++] = obj;
        return;
    }
    Entry& entry = mEntries[mCount++];
    entry._0 = value;
    entry._6 = param;
    entry._4 = obj->_10;
    entry.mLocalLightMapObj = obj->getReferenceLocalLightMapObj();
    entry._10 = obj->_20;
    entry._20 = obj->_8 * obj->_c + obj->_b;
    entry.mOcclusionQuery = &obj->mOcclusionQuery;
}

// NON_MATCHING: the size select has its operands swapped.
void ModelDrawObjStream::end(s32 core) {
    u8** ptr = ModelWorkBuffer::instance()->getBufferPtr(core);
    if (!mFlags.isOnBit(1))
        *ptr += sizeof(const ModelDrawObj*) * mCount;
    else
        *ptr += sizeof(Entry) * mCount;
    ModelWorkBuffer::instance()->roundUpBuffer(core, 0x20);
}

const ModelDrawObjStream::Entry* ModelDrawObjStream::mount() const {
    return mEntries;
}

}  // namespace gsys

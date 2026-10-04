#include "KingSystem/ActorSystem/AS/asElement.h"

// Frame / Record of the AS runtime context (its own TU in the original: the Context functions in asContext.cpp
// call these out of line).
namespace ksys::as {

static ElementParams sUnk_71026531e8;

ElementParams* Context::Record::sub_7101257DF4(Frame* frame, bool a2) {
    if (!(_3 & 8))
        return &sUnk_71026531e8;
    const s32 index = _1;
    if (frame->mEntries.size() <= index)
        return &sUnk_71026531e8;
    return &frame->mEntries[index];
}

Context::Frame::~Frame() {
    mRecords.freeBuffer();
    mIndexMap.freeBuffer();
    mEntries.freeBuffer();
}

template <typename T>
static void copyBuffer(sead::Buffer<T>& dst, const sead::Buffer<T>& src) {
    if (0 < src.size() && &dst != &src) {
        const s32 n = sead::Mathi::min(dst.size(), src.size());
        T* dst_ptr = dst.getBufferPtr();
        const T* src_ptr = src.getBufferPtr();
        for (s32 i = 0; i < n; ++i)
            dst_ptr[i] = src_ptr[i];
    }
}

// NON_MATCHING: the original loads the sizes into registers once (the three equal-size checks keep no Buffer
// addresses alive) and selects the smaller *Buffer* by address before reading its size; ours keeps `&buffer + 0x20`
// pre-indexed registers across the checks and selects the size value
bool Context::Frame::sub_71012580E0(const Frame& other) {
    if (other.mRecords.size() != mRecords.size() || other.mIndexMap.size() != mIndexMap.size() ||
        other.mEntries.size() != mEntries.size()) {
        return false;
    }
    copyBuffer(mRecords, other.mRecords);
    copyBuffer(mIndexMap, other.mIndexMap);
    copyBuffer(mEntries, other.mEntries);
    mAS = other.mAS;
    return true;
}

Context::Frame::Frame() {}

bool Context::Frame::sub_7101257F0C(const Sizes& sizes, sead::Heap* heap) {
    const s32 num_records = sizes.mNumRecords > 1 ? sizes.mNumRecords : 1;
    const s32 num_indices = sizes.mNumIndices > 1 ? sizes.mNumIndices : 1;
    const s32 num_entries = sizes.mNumEntries > 1 ? sizes.mNumEntries : 1;
    if (u32(num_records - 1) < 0xfe) {
        if (!mRecords.tryAllocBuffer(num_records, heap))
            return false;
        if (num_indices >= 1) {
            if (!mIndexMap.tryAllocBuffer(num_indices, heap))
                return false;
            mIndexMap.fill(0xff);
            if (num_entries >= 1)
                return mEntries.tryAllocBuffer(num_entries, heap);
        }
    }
    return false;
}

void Context::Frame::finalize() {
    mRecords.freeBuffer();
    mIndexMap.freeBuffer();
    mEntries.freeBuffer();
}

void Context::Record::sub_7101257D90(Frame* frame) {
    if (_3 & 8) {
        sub_7101257DF4(frame, false)->_0 &= ~1u;
        _3 &= ~8;
    }
    _0 = 0xff;
    _1 = 0xff;
    _3 &= ~1;
}

void Context::Frame::sub_7101258398() {
    for (Record& record : mRecords)
        record.sub_7101257D90(this);
    const s32 size = mIndexMap.size();
    for (s32 i = 0; i < size; ++i)
        mIndexMap(i) = 0xff;
}

void Context::Frame::sub_710125848C(int element, int hint) {
    const s32 size = mRecords.size();
    for (s32 n = 0; n < size; ++n) {
        const s32 index = hint < size ? hint : 0;
        Record& record = mRecords[index];
        if (!(record._3 & 1)) {
            if (mIndexMap[element] != index)
                record.sub_7101257D90(this);
            mIndexMap[element] = index;
            return;
        }
        hint = index + 1;
    }
}

void Context::Frame::sub_7101258570(int element) {
    Record& record = mRecords[mIndexMap[element]];
    const s32 size = mEntries.size();
    for (s32 i = 0; i < size; ++i) {
        ElementParams& entry = mEntries[i];
        if (!(entry._0 & 1)) {
            entry._0 |= 1;
            record._3 |= 8;
            record._1 = i;
            return;
        }
    }
}

}  // namespace ksys::as

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

Context::Frame::Frame() {}

Context::Frame::~Frame() {
    mRecords.freeBuffer();
    mIndexMap.freeBuffer();
    mEntries.freeBuffer();
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

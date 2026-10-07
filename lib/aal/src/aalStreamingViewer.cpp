#include "aal/aalStreamingViewer.h"

namespace aal {

// NON_MATCHING: same stores; the original stores the two flags and the member at 0x28 before the vtable pointer and the
// zeroed block (0xc..0x24) after it.
// 0x7100b7d6f8
StreamingViewer::StreamingViewer() : _8(false), _9(false), _c(), _28(0), mRecordNum(0), _234() {}

// 0x7100b7d9b4 (D2) / 0x7100b7d9b8 (D0)
StreamingViewer::~StreamingViewer() = default;

// 0x7100b7d948
void StreamingViewer::BeginRead(void* stream) {
    if (mRecordNum.load() <= 30) {
        const s32 index = mRecordNum++;
        mRecords[index].stream = stream;
        mRecords[index].state = 0;
    }
}

// 0x7100b7d97c
void StreamingViewer::EndRead(void* stream) {
    if (mRecordNum.load() <= 30) {
        const s32 index = mRecordNum++;
        mRecords[index].stream = stream;
        mRecords[index].state = 1;
    }
}

}  // namespace aal

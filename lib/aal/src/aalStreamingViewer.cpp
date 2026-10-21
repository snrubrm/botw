#include "aal/aalStreamingViewer.h"

namespace aal {

// 0x7100b7d6f8
StreamingViewer::StreamingViewer()
    : mEnabled(false), _9(false), mStreamSoundNum(0), mMaxStreamSoundNum(0), mStreamTrackNum(0),
      mMaxStreamTrackNum(0), mStreamChannelNum(0), mMaxStreamChannelNum(0), _28(0), mRecordNum(0), _234() {}

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

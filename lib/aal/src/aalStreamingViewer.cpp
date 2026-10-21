#include "aal/aalStreamingViewer.h"
#include <nn/atk/SoundArchive.h>
#include <nn/atk/SoundArchivePlayer.h>
#include "aal/aalATKAccessor.h"

namespace aal {

// 0x7100b7d6f8
StreamingViewer::StreamingViewer()
    : mEnabled(false), _9(false), mStreamSoundNum(0), mMaxStreamSoundNum(0), mStreamTrackNum(0),
      mMaxStreamTrackNum(0), mStreamChannelNum(0), mMaxStreamChannelNum(0), mStreamInfos(nullptr), mRecordNum(0), _234() {}

// 0x7100b7d9b4 (D2) / 0x7100b7d9b8 (D0)
StreamingViewer::~StreamingViewer() = default;

// NON_MATCHING: the original tests the capacity as mMaxStreamSoundNum < -1 (folded), ours as capacity < 1.
// 0x7100b7d730
void StreamingViewer::initialize(sead::Heap* heap) {
    nn::atk::SoundArchivePlayer* player = ATKAccessor::getSoundArchivePlayer();
    if (!player)
        return;

    nn::atk::SoundArchive::SoundArchivePlayerInfo info;
    if (!player->GetSoundArchive()->ReadSoundArchivePlayerInfo(&info))
        return;

    mMaxStreamSoundNum = info.streamSoundCount;
    mMaxStreamTrackNum = info.streamTrackCount;
    mMaxStreamChannelNum = info.streamChannelCount;
    mStreamInfos = new (heap) sead::ObjList<StreamInfo>;
    mStreamInfos->allocBuffer(mMaxStreamSoundNum + 2, heap);
    for (auto& stream_info : *mStreamInfos)
        stream_info.reset();
}

// 0x7100b7d88c
void StreamingViewer::calc() {
    if (!mEnabled && !_9)
        return;

    if (!ATKAccessor::getSoundArchivePlayer())
        return;

    for (auto it = mStreamInfos->robustBegin(), end = mStreamInfos->robustEnd(); it != end; ++it) {
        if (it->_d) {
            it->_d = false;
        } else {
            it->reset();
            mStreamInfos->erase(&*it);
        }
    }

    if (mRecordNum.load() > 0)
        mRecordNum = 0;
}

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

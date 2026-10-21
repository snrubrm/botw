#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadAtomic.h>

namespace sead {
class Heap;
}

namespace aal {

/// The debug viewer of the streaming sounds: the file streams of the sound library report the reads to it.
/// TODO: only the constructor and the read callbacks are declared.
class StreamingViewer : public sead::hostio::Node {
public:
    StreamingViewer();
    virtual ~StreamingViewer();

    /// 0x7100b7d730 / 0x7100b7d88c
    void initialize(sead::Heap* heap);
    void calc();

    /// Records that a read of the stream `stream` begins / ends (the records are consumed by calc).
    virtual void BeginRead(void* stream);
    virtual void EndRead(void* stream);

    /// The game's sound status init 0x7101048ae8 sets it; calc only runs while it (or +0x9) is set.
    void setEnabled(bool enabled) { mEnabled = enabled; }
    /// The current numbers of stream sounds / tracks / channels (read by the game's sound status report 0x7101048b94).
    s32 getStreamSoundNum() const { return mStreamSoundNum; }
    s32 getStreamTrackNum() const { return mStreamTrackNum; }
    s32 getStreamChannelNum() const { return mStreamChannelNum; }

private:
    /// An entry of the stream list (the members are unknown; initialize and calc clear the 14 bytes before the
    /// list node).
    struct StreamInfo {
        // inline-only in the original; name is a guess (the same clearing in initialize and calc).
        void reset() {
            _0 = nullptr;
            _8 = 0;
            _c = 0;
            _d = false;
        }

        void* _0;
        u32 _8;
        u8 _c;
        /// calc keeps (and clears) the entries that have it set and removes the others.
        bool _d;
    };

    struct ReadRecord {
        void* stream;
        s32 state;
    };

    bool mEnabled;
    bool _9;
    s32 mStreamSoundNum;
    /// initialize copies the stream sound / track / channel counts of nn::atk::SoundArchive::SoundArchivePlayerInfo.
    s32 mMaxStreamSoundNum;
    s32 mStreamTrackNum;
    s32 mMaxStreamTrackNum;
    s32 mStreamChannelNum;
    s32 mMaxStreamChannelNum;
    u32 _24;
    /// Allocated by initialize with room for the maximum number of stream sounds plus two.
    sead::ObjList<StreamInfo>* mStreamInfos;
    ReadRecord mRecords[32];
    sead::Atomic<s32> mRecordNum;
    u32 _234[2];
};
static_assert(sizeof(StreamingViewer) == 0x240, "aal::StreamingViewer size mismatch");

}  // namespace aal

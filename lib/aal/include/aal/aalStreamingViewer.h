#pragma once

#include <basis/seadTypes.h>
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

    /// 0x7100b7d730 / 0x7100b7d88c (declared only)
    void initialize(sead::Heap* heap);
    void calc();

    /// Records that a read of the stream `stream` begins / ends (the records are consumed by calc).
    virtual void BeginRead(void* stream);
    virtual void EndRead(void* stream);

private:
    struct ReadRecord {
        void* stream;
        s32 state;
    };

    bool _8;
    bool _9;
    f32 _c[6];
    u32 _24;
    u64 _28;
    ReadRecord mRecords[32];
    sead::Atomic<s32> mRecordNum;
    u32 _234[2];
};
static_assert(sizeof(StreamingViewer) == 0x240, "aal::StreamingViewer size mismatch");

}  // namespace aal

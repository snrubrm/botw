#pragma once

#include <basis/seadTypes.h>
#include <container/seadRingBuffer.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys {

// TODO
class PlayerTrackReporter {
public:
    struct Record {
        s32 play_time;
        s32 all_play_time;
        u8 _8[8];
        sead::SafeArray<u32, 300> positions;
    };
    KSYS_CHECK_SIZE_NX150(Record, 0x4c0);

    struct Block {
        u8 _0;
        u8 _1;
        u8 _2;
        u16 _4;
        s32 _8 = 0;
        u8 _c[0x40 - 0xc];
        sead::SafeArray<Record, 48> records;
        u8 _e440[0x40];
    };
    KSYS_CHECK_SIZE_NX150(Block, 0xe480);

    PlayerTrackReporter();
    virtual ~PlayerTrackReporter();
    void init(sead::Heap* heap);
    void setPosTrackEnd();

    sead::RingBuffer<Block> mBlocks;
    s32 _20 = 0;
    s32 _24 = 0;
    bool _28 = false;
    bool _29 = false;
    bool _30 = false;  // at 0x2a
    bool _2b = false;
};
KSYS_CHECK_SIZE_NX150(PlayerTrackReporter, 0x30);

}  // namespace ksys

#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>
#include <time/seadTickSpan.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

struct DebugMessage {
    // Log entry returned by log(). Only its tail is known: 36 tera debug paths (e.g. 0x71011320b4,
    // 0x71011369d0, 0x7101144b10) store 0 to +0x30 and a display time to +0x38 after log(),
    // and Buffer's destructor sets +0x44.
    struct Entry {
        // Display time = cFrequency x seconds. sead has no float-seconds maker yet; makeFromSeconds(1) * s
        // gives the same (s64)((f32)cFrequency * s).
        void setDisplayTime(f32 seconds) { display_time = sead::TickSpan::makeFromSeconds(1) * seconds; }

        u8 _0[0x28];
        // uking::action::TerrainHideCenter::calc_ 0x7100e176d0 stores 100 here.
        s64 _28;
        u32 _30;
        sead::TickSpan display_time;
        u32 _40;
        bool _44;
    };

    struct Buffer {
        ~Buffer() {
            if (buffer && _8)
                buffer->_44 = true;
        }

        Entry* buffer;
        bool _8;
    };

    DebugMessage() = default;
    explicit DebugMessage(const sead::SafeString& msg) : message(msg) {}

    virtual ~DebugMessage() { ; }

    Buffer log(const char* format, ...);

    u64 _8 = 0;
    sead::FixedSafeString<64> message;
    sead::Color4f color = sead::Color4f::cWhite;
    f32 _78 = 0.3;
    f32 _7c = 0.3;
    f32 _80 = 0.3;
    f32 _84 = 0.8;
    bool _88 = true;
    bool _89 = true;
};
KSYS_CHECK_SIZE_NX150(DebugMessage, 0x90);

}  // namespace ksys

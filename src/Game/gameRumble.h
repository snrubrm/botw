#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <thread/seadMutex.h>
#include <time/seadTickTime.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Placeholder names: the rumble pattern index. A SEAD_ENUM: it is read through `operator int() const volatile`
// (the callees store / reload it through a stack slot), and the pattern tables in gameRumble.cpp have six entries.
SEAD_ENUM(RumblePattern, _0, _1, _2, _3, _4, _5)

// Name from the CSV (Rumble::createInstance 0x7100897b74, deleteInstance 0x7100897c28). A sead singleton
// (size 0xa0) that plays controller rumble patterns ("*--*-" strings, see gameRumble.cpp).
class Rumble {
    SEAD_SINGLETON_DISPOSER(Rumble)
    Rumble() = default;
    virtual ~Rumble() = default;

public:
    // lane4 s85 (placeholder names): the pattern state at +0x28; 0x7100898990 (calc) and 0x7100898794 (stop)
    // take its address.
    struct State {
        // 0x7100898990: stops the pattern once `mDurationSeconds` have passed, starts a requested pattern on the
        // controller rumble addon and records whether the addon is still playing.
        void calc();
        // 0x7100898794 (444 B, not decompiled): stops the pattern on the controller rumble addon(s).
        void stop();

        bool mIsPlaying = false;
        bool mStartRequested = false;
        const char* mPattern = nullptr;
        u32 mPatternDuration = 0;
        u32 _3c = 0;
        sead::TickTime mStartTime;
        u32 mDurationSeconds = 0;
    };

    // 0x7100897fe4 (CSV Rumble::__auto0; placeholder name): plays `pattern` `count` times unless a pattern with a
    // higher index is already playing.
    void sub_7100897FE4(RumblePattern pattern, s32 count);
    // 0x710089813c (placeholder name): plays `pattern` for `seconds` seconds (TimeSpecControllerRumble::enter_).
    void sub_710089813C(RumblePattern pattern, s32 seconds);
    // 0x710089829c (CSV Rumble::init): copies the default pattern strings into the pattern buffers.
    void init();
    // 0x710089878c (CSV Rumble::__auto1; placeholder name): stops the running rumble.
    void sub_710089878C();
    // 0x7100899108 (placeholder name): the duration of `pattern` in seconds (one character per 1/120 s; 0.5 without a
    // pattern string).
    f32 sub_7100899108(RumblePattern pattern) const;
    // 0x7100898950 (CSV Rumble::calc)
    void calc();

private:
    // 0x7100898a20 (1768 B, not decompiled)
    void sub_7100898A20();

    State mState;
    RumblePattern mCurrentPattern;
    sead::Mutex mMutex;
    u32 _98 = 0;
};
KSYS_CHECK_SIZE_NX150(Rumble, 0xa0);

}  // namespace uking

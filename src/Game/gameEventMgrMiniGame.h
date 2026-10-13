#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/System/Timer.h"

// Native timer base: ctor E499C4 and independent Action/Query consumers establish extent 0x20.
class Unk_71024e8128 {
    SEAD_RTTI_BASE(Unk_71024e8128)
public:
    Unk_71024e8128();
    // Both native tables share the empty D1; Timer and POD need no owned cleanup.
    virtual ~Unk_71024e8128() = default;

    void reset();
    void startCountup(s32 max_time_ms);
    void startCountdown(s32 start_time_ms);
    s32 getTimerMs() const;
    // Full E499EC updater; the singleton calc calls this timer update.
    void sub_7100E499EC();

    s32 getMode() const { return mMode; }
    void setMode(s32 mode) { mMode = mode; }

protected:
    /* 0x08 */ ksys::Timer mTimer{0.0f, 0.0f, 0.0f};
    /* 0x14 */ s32 mMaxTimeMs = 5999999;
    /* 0x18 */ f32 mInitialTime = 0.0f;
    /* 0x1c */ s32 mMode = 0;  // 0: disabled, 1: running, 2: stopped
};
static_assert(sizeof(Unk_71024e8128) == 0x20);

// E493F0 allocates 0x40: base timer plus the standard raw singleton disposer buffer at 0x20.
class Unk_71024e80e0 : public Unk_71024e8128 {
    SEAD_RTTI_OVERRIDE(Unk_71024e80e0, Unk_71024e8128)
    SEAD_SINGLETON_DISPOSER(Unk_71024e80e0)
public:
    Unk_71024e80e0() = default;
    ~Unk_71024e80e0() override;
    void init();
    void initBeforeStageGenB();
    void calc();
};
static_assert(sizeof(Unk_71024e80e0) == 0x40);

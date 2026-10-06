#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <thread/seadSpinLock.h>

namespace ksys::act {
class Actor;
}

// Partial pointer-use interface. The source namespace is unknown; the class name follows the CSV.
// The original singleton allocation has additional unmodeled state.
class PlayerResetPosMgr {
    SEAD_SINGLETON_DISPOSER(PlayerResetPosMgr)

public:
    void addResetPos(const sead::Vector3f& position, f32 yaw);
    void setResetPos(const sead::Vector3f& position, f32 yaw, ksys::act::Actor* actor);
    void sub_71007A6620(ksys::act::Actor* actor);
    // 0x71007a5d68 (CSV: resetSmallKeyFlags): resets the small key counters in the game data.
    void resetSmallKeyFlags();
    // 0x71007a6668 (CSV: PlayerResetPosMgr::clearResetPos).
    void clearResetPos();

protected:
    // Partial layout: only the members the decompiled functions touch.
    /* 0x020 */ u32 _20 = 0;
    u8 _24[0x428 - 0x24];
    /* 0x428 */ void* _428;
    /* 0x430 */ bool _430;
    u8 _431[0x448 - 0x431];
    /* 0x448 */ sead::SpinLock mLock;
};

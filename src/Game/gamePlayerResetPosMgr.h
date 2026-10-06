#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <thread/seadSpinLock.h>

namespace ksys::act {
class Actor;
}

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
    // 0x71007a5d58
    bool isNotResetting() const;

protected:
    struct ResetPos {
        sead::Vector3f position{0, 0, 0};
        f32 yaw = 0;
    };

    PlayerResetPosMgr() = default;

    // Partial layout: only the members the decompiled functions touch.
    /* 0x020 */ s32 mNumResetPos = 0;
    /* 0x024 */ sead::SafeArray<ResetPos, 64> mResetPositions;
    u8 _424[0x428 - 0x424];
    /* 0x428 */ ksys::act::Actor* mActor = nullptr;
    /* 0x430 */ bool mHasResetPos = false;
    /* 0x434 */ ResetPos mResetPos;
    u8 _444[0x448 - 0x444];
    /* 0x448 */ sead::SpinLock mLock;
    /* 0x458 */ s32 mStatus = 0;
    u8 _45c[0x478 - 0x45c];
};

#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

// Partial pointer-use interface. The source namespace is unknown; the class name follows the CSV.
// The original singleton allocation has additional unmodeled state.
class PlayerResetPosMgr {
    SEAD_SINGLETON_DISPOSER(PlayerResetPosMgr)

public:
    void addResetPos(const sead::Vector3f& position, f32 yaw);
};

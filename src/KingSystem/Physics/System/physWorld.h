#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/Types.h"

class hkpWorld;

namespace ksys::phys {

// TODO: incomplete
class World {
    SEAD_RTTI_BASE(World)
public:
    virtual ~World();

    hkpWorld* getHavokWorld() const { return mHavokWorld; }

    void lockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed);
    void unlockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed);

    void sub_71012B3FB0();
    void sub_71012B3FC8();

private:
    hkpWorld* mHavokWorld;
    u8 _10[0x30 - 0x10];
    sead::CriticalSection mCS;
    u32 _70;
    sead::Atomic<s32> _74;
};

}  // namespace ksys::phys

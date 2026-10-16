#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/Types.h"

class hkpWorld;

namespace ksys::phys {

class ContactListener;
class GroupFilter;

// Placeholder name: the world settings System::createWorld passes to World::make (only the first fields are known).
struct WorldArg {
    ContactListener* contact_listener;
    GroupFilter* group_filter;
    ContactLayerType layer_type;
};

// TODO: incomplete
class World {
    SEAD_RTTI_BASE(World)
public:
    explicit World(ContactLayerType layer_type) : mLayerType(layer_type) {}
    virtual ~World();

    // 0x71012b370c (CSV phys::createHkpWorldStuff_0)
    static World* make(const WorldArg& arg, sead::Heap* heap);
    // 0x71012b37a4 / 0x71012b3948 (CSV havokThreadsStuff_0 / phys::createHkpWorldStuff; declared only).
    void sub_71012B37A4(sead::Heap* heap);
    void sub_71012B3948(const WorldArg& arg, sead::Heap* heap);

    hkpWorld* getHavokWorld() const { return mHavokWorld; }
    sead::CriticalSection& getCS() { return mCS; }

    void lockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed);
    void unlockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed);

    // 0x71012b3f50 (declared only; placeholder name): starts a multithreaded Havok step (hkpWorld::initMtStep).
    void sub_71012B3F50(f32 delta_time);
    void sub_71012B3FB0();
    void sub_71012B3FC8();

private:
    hkpWorld* mHavokWorld{};
    ContactListener* mContactListener{};
    GroupFilter* mGroupFilter{};
    u64 _20{};
    u64 _28{};
    sead::CriticalSection mCS;
    u32 _70{};
    sead::Atomic<s32> _74{0};
    ContactLayerType mLayerType;
};
KSYS_CHECK_SIZE_NX150(World, 0x80);

}  // namespace ksys::phys

#include "KingSystem/Physics/System/physWorld.h"
#include <thread/seadThread.h>

namespace ksys::phys {

World* World::make(const WorldArg& arg, sead::Heap* heap) {
    auto* world = new (heap) World(arg.layer_type);
    world->mContactListener = arg.contact_listener;
    world->mGroupFilter = arg.group_filter;
    world->sub_71012B37A4(heap);
    world->sub_71012B3948(arg, heap);
    return world;
}

World::~World() = default;

void World::lockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed) {
    if (only_lock_if_needed == OnlyLockIfNeeded::Yes &&
        sead::ThreadMgr::instance()->getCurrentThread()->getPriority() <=
            sead::Thread::cDefaultPriority + 1) {
        return;
    }
    mCS.lock();
}

void World::unlockCS(const char* description, int b, OnlyLockIfNeeded only_lock_if_needed) {
    if (only_lock_if_needed == OnlyLockIfNeeded::Yes &&
        sead::ThreadMgr::instance()->getCurrentThread()->getPriority() <=
            sead::Thread::cDefaultPriority + 1) {
        return;
    }
    mCS.unlock();
}

void World::sub_71012B3FB0() {
    _74.increment();
}

void World::sub_71012B3FC8() {
    _74.decrement();
}

}  // namespace ksys::phys

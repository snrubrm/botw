#pragma once

#include <heap/seadDisposer.h>

namespace ksys {
class OverlayArenaSystemS1;
}

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class Event;
class Metadata;

// TODO
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void init(sead::Heap* heap);

    Event* getActiveEvent() const;
    bool hasActiveEvent() const;

    sead::Heap* getEventHeap() const { return mEventHeap; }

    bool callEvent(const Metadata& metadata, act::Actor* actor = nullptr, void* x = nullptr);

private:
    friend class ksys::OverlayArenaSystemS1;

    u8 pad_20[0x1d178 - 0x20];
    sead::Heap* mEventHeap;
    u8 pad_1d188[0x1d2b8 - 0x1d188];
    void* _1d2b8;
    u8 pad_1d2c0[0x1d2f4 - 0x1d2c0];
    u32 _1d2f4;
};

}  // namespace ksys::evt

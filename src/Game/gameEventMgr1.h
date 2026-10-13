#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "Game/gameEventCounter.h"

// Name from the CSV EventMgr1::createInstance (0x7100e48658).
// Source namespace remains unknown; global spelling follows the scene placeholders.
class EventMgr1 {
    SEAD_SINGLETON_DISPOSER(EventMgr1)
    EventMgr1() = default;

public:
    virtual ~EventMgr1();

    bool init(s32 capacity, sead::Heap* heap);
    void calc();
    void initBeforeStageGenB();

    // 0x7100e48a90 / 0x7100e48ed8: counter registration operations.
    bool sub_7100E48A90(const sead::SafeString& actor_name,
                      const sead::SafeString& game_data_name, bool initialize);
    bool sub_7100E48ED8(const sead::SafeString& actor_name,
                      const sead::SafeString& game_data_name, bool initialize);

    // 0x7100e48c44 / 0x7100e4908c: counter unregister operations.
    void sub_7100E48C44(const sead::SafeString& name);
    void sub_7100E4908C(const sead::SafeString& name);

    // 0x7100e48d8c: operation on records for this actor name.
    void sub_7100E48D8C(const sead::SafeString& name);
    void sub_7100E491D4(const sead::SafeString& name);

private:
    // Full singleton producer E48658 and lifetime E486FC establish these composed members.
    /* 0x28 */ sead::CriticalSection mCS;
    /* 0x68 */ sead::PtrArray<Unk_7102518b60> mDeathCounters;
    /* 0x78 */ sead::PtrArray<Unk_7102518b60> mGetCounters;
    /* 0x88 */ sead::Heap* mHeap = nullptr;
};
static_assert(sizeof(EventMgr1) == 0x90);

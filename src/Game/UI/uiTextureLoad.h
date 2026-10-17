#pragma once

#include <container/seadObjArray.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/Thread/TaskData.h"
#include "KingSystem/Utils/Thread/Task.h"

namespace ksys {
class ManagedTaskHandle;
}

// vtable 0x710247e960 (4 slots); placeholder generated from the vtable (genskel.py).
class Unk_710247e960 : public ksys::res::Context {
    SEAD_RTTI_OVERRIDE(Unk_710247e960, ksys::res::Context)
public:
    // 0x71009caef4: two empty fixed strings, an empty name, size 8 and limit 100
    Unk_710247e960();
    ~Unk_710247e960() override;

    // Inline-only in the original; name is a guess. The reset sequence repeats in
    // the context destructor 9CAFD4 and loader destructor 9CC7C4.
    void reset() {
        _8.clear();
        _60.clear();
        _b8 = sead::SafeString();
        _c8 = 8;
        _cc = 0;
        _d0 = 100;
    }

    sead::FixedSafeString<64> _8;
    sead::FixedSafeString<64> _60;
    sead::SafeString _b8;
    s32 _c8;
    u16 _cc;
    s32 _d0;
};

static_assert(sizeof(Unk_710247e960) == 0xd8);

// Loader embedded in the UI texture controller. Constructor 9CC648 and request
// worker 9CBFC4 establish the queue, two contexts and task handle.
class Unk_710247e990 : public ksys::TaskData {
    SEAD_RTTI_OVERRIDE(Unk_710247e990, ksys::TaskData)
public:
    struct Command {
        s32 type = 0;
    };

    Unk_710247e990();
    ~Unk_710247e990() override;

    /* 0x008 */ sead::FixedObjArray<Command, 2> mCommands;
    /* 0x048 */ s32 mQueueState = 13;
    /* 0x050 */ Unk_710247e960 mPendingRequest;
    /* 0x128 */ Unk_710247e960 mCurrentRequest;
    /* 0x200 */ ksys::ManagedTaskHandle* mTaskHandle = nullptr;
};
static_assert(sizeof(Unk_710247e990) == 0x208);

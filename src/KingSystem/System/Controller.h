#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/System/ControllerSnapshot.h"
#include "KingSystem/Utils/Unk_7102517d58.h"

namespace ksys {
class SeadController;
}

namespace sead {
class Thread;
}

// Complete root lifetime interface at 0x71024dd5a8. Controller::init allocates
// eight bytes for this object; SeadController also embeds one at +0x1d8.
class Unk_71024dd5a8 {
public:
    virtual ~Unk_71024dd5a8();
};
KSYS_CHECK_SIZE_NX150(Unk_71024dd5a8, 0x8);

// Independent root lifetime interface at 0x71024dd640. Controller's producer
// stores the vptr at +0xa0 and a zero word at +0xa8, before the list at +0xb0.
class Unk_71024dd640 {
public:
    virtual ~Unk_71024dd640();

private:
    u32 _8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024dd640, 0x10);

// CSV owner name. Complete vtable 0x71024dd618: Node::getNodeClassType, D1/D0.
// The Node base is inferred from that interface and its empty release layout.
// Producer 0x7100d9e964 allocates 0x140 bytes and constructs the members below.
class Controller : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Controller)

public:
    Controller() = default;
    virtual ~Controller();

    s32 sub_7100D9F0C8() const;
    bool sub_7100D9F7D4() const;
    Unk_71024dd5c8* sub_7100D9F7DC();
    void sub_7100D9F7E4(ksys::SeadController* controller);
    void sub_7100D9F838(ksys::SeadController* controller);

private:
    Unk_71024dd5a8* _28 = nullptr;
    u32 _30 = 0;
    u8 _34[4];
    Unk_71024dd5c8 mSnapshot;
    Unk_7102517d58 mFlags;
    Unk_71024dd640 _a0;
    // Controller::init sets this list's node offset to SeadController +0x178.
    sead::OffsetList<ksys::SeadController> mControllers;
    sead::CriticalSection mCS;
    sead::Thread* _108 = nullptr;
    u64 _110 = 0;
    f32 _118 = 150.0f;
    f32 _11c = 15.0f;
    f32 _120 = 270.0f;
    u32 _124 = 0;
    f32 _128 = 31.0f;
    s32 _12c = 2;
    u16 _130 = 0;
    bool _132 = false;
    bool _133 = true;
    bool _134 = true;
    bool _135 = true;
    u32 _138 = 0;
};
KSYS_CHECK_SIZE_NX150(Controller, 0x140);

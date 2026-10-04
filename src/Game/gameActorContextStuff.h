#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {
class RigidBody;
}

// The context entries derive from ActorBind (ctor 0x7100660550). Partial declaration;
// the entry's virtual overrides and the rest of its layout remain to be recovered.
// Address placeholder for the vtable header at 0x710243be90.
class Unk_710243be90 : public ksys::act::ActorBind {
public:
    // 0x7100661058 / 0x7100661a58: carried actor detach/update (declarations only).
    void sub_7100661058(ksys::act::Actor* actor);
    void sub_7100661A58(ksys::act::Actor* actor);
    // 0x7100661988 / 0x71006619dc: sleeps/wakes the entry's carried actor.
    void sub_7100661988();
    void sub_71006619DC();
    // 0x71006618ac: resets the entry's temporary rigid body.
    void sub_71006618AC();
    bool sub_7100661538(ksys::act::BaseProc* proc) const;
    u32 _28;
    u32 _2c;
    ksys::act::BaseProcLink _30;
    void* _40;
    ksys::phys::RigidBody* _48;
    u8 _50[0x70 - 0x50];
    f32 _70;
    f32 _74;
    u8 _78[0x128 - 0x78];
};
static_assert(sizeof(Unk_710243be90) == 0x128);

// Name from the CSV. Carried-item context embedded in GameSceneSubsys12; layout incomplete.
class ActorContextStuff {
public:
    // 0x710065d8e4
    void sub_710065D8E4(sead::Heap* heap, bool a2);
    // 0x710065f044: number of entries in the carried-item array at +0x638.
    s32 sub_710065F044();
    // 0x710065f07c: number of active entries.
    s32 sub_710065F07C();
    // 0x710065f80c: the link of the carried actor at index, or null.
    ksys::act::BaseProcLink* sub_710065F80C(s32 index);
    // 0x710065f9ac
    void sub_710065F9AC();

    u8 _0[0x28];
    sead::CriticalSection _28;
    u8 _68[0x638 - 0x68];
    sead::PtrArray<Unk_710243be90> _638;
    u8 _648[0x760 - 0x648];
};
KSYS_CHECK_SIZE_NX150(ActorContextStuff, 0x760);

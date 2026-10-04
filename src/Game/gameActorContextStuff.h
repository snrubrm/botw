#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <container/seadTList.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {
class RigidBody;
class ContactPointInfo;
}

class ActorContextStuff;

// The context entries derive from ActorBind (ctor 0x7100660550). Partial declaration;
// the entry's virtual overrides and the rest of its layout remain to be recovered.
// Address placeholder for the vtable header at 0x710243be90.
class Unk_710243be90 : public ksys::act::ActorBind {
public:
    // Vtable slot 4 is 0x7100661e64, not the abstract ActorBind slot.
    bool m4(ksys::act::BaseProc* proc) override;
    bool sub_71006606E8();
    void sub_710066136C();
    void sub_71006613B0(bool delete_actor);
    void sub_7100661494(bool immediately);
    bool sub_7100661540(const ksys::act::BaseProcLink& link) const;
    void sub_71006620CC(sead::Vector3f* position, sead::Quatf* rotation) const;
    void sub_71006620F8(sead::Matrix34f* matrix) const;
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
    // init66074c allocates a TListNode with the temporary RigidBody* as its data.
    sead::TListNode<ksys::phys::RigidBody*>* _40;
    ksys::phys::RigidBody* _48;
    ksys::phys::ContactPointInfo* _50;
    ksys::phys::RigidBody* _58;
    u8 _60[8];
    s32 _68;
    s32 _6c;
    f32 _70;
    f32 _74;
    u8 _78[0x118 - 0x78];
    ActorContextStuff* _118;
    u8 _120[8];
};
static_assert(sizeof(Unk_710243be90) == 0x128);

// Name from the CSV. Carried-item context embedded in GameSceneSubsys12; layout incomplete.
class ActorContextStuff {
public:
    // 0x710065d8e4
    void sub_710065D8E4(sead::Heap* heap, bool a2);
    // 0x710065e2b0: binds a matching entry to proc, or returns null.
    Unk_710243be90* sub_710065E2B0(ksys::act::BaseProc* proc);
    // 0x710065e3c0 / 0x710065e400: sleep/wake all five embedded entries.
    void x_0();
    void x();
    // 0x710065f044: number of entries in the carried-item array at +0x638.
    s32 sub_710065F044();
    // 0x710065f07c: number of active entries.
    s32 sub_710065F07C();
    // 0x710065f12c / 0x710065f16c: random and arranged placement offsets.
    void sub_710065F12C(sead::Vector3f* out, s32 index);
    void sub_710065F16C(sead::Vector3f* out, s32 index);
    // 0x710065f1f0 / 0x710065f954: active scene-context scale and carry flag.
    f32 sub_710065F1F0(f32 scale);
    bool sub_710065F954() const;
    // 0x710065f80c: the link of the carried actor at index, or null.
    ksys::act::BaseProcLink* sub_710065F80C(s32 index);
    // 0x710065f9ac
    void sub_710065F9AC();
    // 0x710065fa28: fade progress for the entry bound to proc.
    f32 sub_710065FA28(ksys::act::BaseProc* proc, f32 time);

    u8 _0[0x28];
    sead::CriticalSection _28;
    u32 _68;
    s32 _6c;
    // Constructor65d6e8 constructs five entries at70/198/2c0/3e8/510.
    sead::SafeArray<Unk_710243be90, 5> _70;
    sead::PtrArray<Unk_710243be90> _638;
    u8 _648[0x760 - 0x648];
};
KSYS_CHECK_SIZE_NX150(ActorContextStuff, 0x760);

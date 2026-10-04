#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelAccessKey.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <container/seadTList.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {
class RigidBody;
class ContactPointInfo;
class SystemGroupHandler;
}

class ActorContextStuff;

// The context entries derive from ActorBind (ctor 0x7100660550). Partial declaration;
// the entry's virtual overrides and the rest of its layout remain to be recovered.
// Address placeholder for the vtable header at 0x710243be90.
class Unk_710243be90 : public ksys::act::ActorBind {
public:
    Unk_710243be90();
    ~Unk_710243be90() override;
    // Vtable slot 4 is 0x7100661e64, not the abstract ActorBind slot.
    bool m4(ksys::act::BaseProc* proc) override;
    bool m5(ksys::act::BaseProc* proc) override { return false; }
    bool sub_71006606E8();
    void sub_710066136C();
    void sub_71006613B0(bool delete_actor);
    void sub_7100661494(bool immediately);
    // 0x7100660ad8: binds the actor's placement/physics to this entry.
    void sub_7100660AD8(ksys::act::Actor* actor);
    // 0x710066074c: creates the temporary carried-item physics objects.
    void sub_710066074C(ActorContextStuff* context, s32 index, bool for_menu,
                      ksys::phys::SystemGroupHandler* handler, sead::Heap* heap);
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
    u32 _28 = 0;
    u32 _2c;
    ksys::act::BaseProcLink _30;
    // init66074c allocates a TListNode with the temporary RigidBody* as its data.
    sead::TListNode<ksys::phys::RigidBody*>* _40 = nullptr;
    ksys::phys::RigidBody* _48 = nullptr;
    ksys::phys::ContactPointInfo* _50 = nullptr;
    ksys::phys::RigidBody* _58 = nullptr;
    ksys::phys::ContactPointInfo* _60 = nullptr;
    s32 _68 = -1;
    s32 _6c = -1;
    f32 _70 = 10.0f;
    f32 _74 = 1.0f;
    sead::Quatf _78 = sead::Quatf::unit;
    sead::Vector3f _88{0.0f, 0.0f, 0.0f};
    f32 _94 = 1.0f;
    sead::Vector3f _98{0.0f, 0.0f, 0.0f};
    u8 _a4[4];
    sead::Vector3f _a8{0.0f, 0.0f, 0.0f};
    u8 _b4[4];
    f32 _b8 = 1.0f;
    f32 _bc = 0.0f;
    f32 _c0 = 1.0f;
    f32 _c4 = 1.0f;
    sead::Vector3f _c8 = sead::Vector3f::zero;
    ksys::act::BaseProcLink _d8;
    sead::Matrix34f _e8 = sead::Matrix34f::ident;
    ActorContextStuff* _118 = nullptr;
    u32 _120 = 0;
};
static_assert(sizeof(Unk_710243be90) == 0x128);

// Name from the CSV. The constructor65d6e8 has a TListNode<ActorContextStuff*> base at+8,
// a virtual destructor (vtable header243be70), five entries and two backed pointer arrays.
class ActorContextStuff : public sead::TListNode<ActorContextStuff*> {
public:
    explicit ActorContextStuff(ksys::act::BaseProc* proc);
    virtual ~ActorContextStuff();
    // 0x710065d8e4
    void sub_710065D8E4(sead::Heap* heap, bool a2);
    // 0x710065e2b0: binds a matching entry to proc, or returns null.
    Unk_710243be90* sub_710065E2B0(ksys::act::BaseProc* proc);
    // 0x710065e3c0 / 0x710065e400: sleep/wake all five embedded entries.
    void x_0();
    void x();
    // 0x710065e4bc: releases the active entries into the free pool.
    void sub_710065E4BC(bool delete_actor);
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

    sead::CriticalSection _28;
    u32 _68 = 0;
    s32 _6c = 0;
    // Constructor65d6e8 constructs five entries at70/198/2c0/3e8/510.
    sead::SafeArray<Unk_710243be90, 5> _70;
    sead::PtrArray<Unk_710243be90> _638;
    sead::SafeArray<Unk_710243be90*, 5> _648;
    sead::PtrArray<Unk_710243be90> _670;
    sead::SafeArray<Unk_710243be90*, 5> _680;
    ksys::phys::SystemGroupHandler* _6a8;
    ksys::phys::SystemGroupHandler* _6b0;
    sead::SafeArray<ksys::act::BaseProcHandle, 5> _6b8;
    ksys::act::BaseProcLink _708;
    sead::Vector3f _718 = sead::Vector3f::zero;
    gsys::BoneAccessKeyEx _728;
};
KSYS_CHECK_SIZE_NX150(ActorContextStuff, 0x760);

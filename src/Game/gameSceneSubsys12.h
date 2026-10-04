#pragma once

#include <basis/seadTypes.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/gameActorContextStuff.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

// Placeholder declaration (lane3 s23; name from the CSV: createInstance 0x71006623f0, ctor 0x7100662478, ~70 unnamed
// users, e.g. Carried::calc_, CarryBox, DemoCookPotCook, Player::m76): the scene subsystem that handles carried
// items. A sead singleton (disposer at +0x18, size 0xc00); only the instance pointer and the flag word that the
// carry actions read are declared. Layout incomplete.
class GameSceneSubsys12 {
public:
    static GameSceneSubsys12* instance() { return sInstance; }

    // 0x7100662aec / 0x7100662b4c
    void init(sead::Heap* heap);
    bool x() const;
    // 0x7100662c4c / 0x7100662ef0: creates the carrier and sends its setup messages.
    ksys::act::Actor* sub_7100662C4C();
    void sub_7100662EF0(ksys::act::Actor* actor);
    // 0x7100663278: assigns a carried entry for proc.
    Unk_710243be90* sub_7100663278(ksys::act::BaseProc* proc);
    // 0x7100663364: copies the carrier's actor matrix if it exists.
    bool sub_7100663364(sead::Matrix34f* out);
    // 0x710066358c / 0x71006652c8
    s32 sub_710066358C();
    bool sub_71006652C8() const;
    // 0x7100664bc8 / 0x7100664dbc: carried actor links of active/embedded contexts.
    ksys::act::BaseProcLink* sub_7100664BC8(s32 index);
    ksys::act::BaseProcLink* sub_7100664DBC(s32 index);
    // 0x7100664d24 / 0x7100664d64
    s32 sub_7100664D24();
    s32 sub_7100664D64();
    // 0x7100664f00 / 0x7100664f30 / 0x7100664f3c / 0x7100664f64
    void sub_7100664F00(const sead::Matrix34f& matrix);
    bool sub_7100664F30() const;
    void sub_7100664F3C(const sead::Matrix34f& matrix);
    void sub_7100664F64(const sead::Matrix34f& matrix);
    // 0x7100664f8c: records the indexed cooking transform.
    void sub_7100664F8C(s32 index, const sead::Matrix34f& matrix);
    // 0x7100665304
    void sub_7100665304();
    // 0x7100664484: handles the carried-context state transition (declaration only).
    void sub_7100664484(s32 state, ActorContextStuff* context);
    // 0x7100664acc: returns the carried actor's fade progress.
    f32 sub_7100664ACC(ksys::act::BaseProc* proc);
    // 0x7100664b3c / 0x7100664c30: carried-context scale and placement offset.
    f32 sub_7100664B3C(ActorContextStuff* context, f32 scale);
    void sub_7100664C30(sead::Vector3f* out, s32 count, s32 index);
    // 0x7100664cc0: unscaled carried-item placement offset.
    void sub_7100664CC0(sead::Vector3f* out, s32 count, s32 index);
    // 0x7100665360: releases the carried actor and resets carry flags (declaration only).
    void sub_7100665360();

    u8 _0[0x38];
    sead::CriticalSection _38;
    u8 _78[0xd0 - 0x78];
    f32 _d0;
    s32 _d4;
    sead::Matrix34f _d8;
    sead::Matrix34f _108;
    sead::Matrix34f _138;
    // ctor62478 initializes five matrices; cooking664f8c writes index stride0x30.
    sead::SafeArray<sead::Matrix34f, 5> _168;
    u8 _258[0x270 - 0x258];
    f32 _270;
    u8 _274[0x300 - 0x274];
    ksys::act::BaseProcLink _300;
    ActorContextStuff* _310;
    ActorContextStuff _318;
    /* 0xa78 */ sead::Atomic<u32> _a78;
    u8 _a7c[0xa98 - 0xa7c];
    // 664c30/664cc0 read five sets of five Vector3f offsets, stride0x3c.
    sead::SafeArray<sead::SafeArray<sead::Vector3f, 5>, 5> _a98;
    sead::SafeArray<sead::Vector3f, 5> _bc4;

    // 0x71025c5a00
    static GameSceneSubsys12* sInstance;
};
static_assert(sizeof(GameSceneSubsys12) == 0xc00);

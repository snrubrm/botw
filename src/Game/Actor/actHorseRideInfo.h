#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class BaseProc;
struct Unk117;
}  // namespace ksys::act

namespace uking::act {

// Name from the CSV (HorseRideInfo::*, functions 0x7100e7be78-0x7100e7c684). vtable
// 0x71024ec068 (10 slots), size 0x38. Returned by Actor vtable slot 130 (getPlayerRideInfo).
// Derived: Unk_71023cee88 (NPC::_f28), an intermediate class (vtable 0x710244eaa0) and
// Player::RideInfo (vtable 0x710246ad80, Player::_26b0).
// TODO: incomplete. Members are public: AI code reads them directly.
class HorseRideInfo {
    SEAD_RTTI_BASE(HorseRideInfo)
public:
    explicit HorseRideInfo(ksys::act::Actor* actor) : mActor(actor) {}
    virtual ~HorseRideInfo();

    /* 4 */ virtual void m4() {}
    /* 5 */ virtual bool m5(const ksys::act::ActorConstDataAccess& accessor) { return true; }
    /* 6 */ virtual void m6() {}
    /* 7 */ virtual bool m7() { return true; }
    /* 8 */ virtual void m8() {}
    /* 9 */ virtual void m9() {}

    bool init();
    void sub_7100E7C350();
    bool sub_7100E7BEC0(ksys::act::BaseProc* proc);
    bool sub_7100E7BF5C(ksys::act::ActorConstDataAccess& accessor, bool a2);
    bool sub_7100E7C054(ksys::act::BaseProcLink* link);
    void sub_7100E7C0EC();
    void sub_7100E7C380();
    // 0x7100e7c4f8 (CSV Player::RideInfo::x_1): forwards the request to the ridden actor.
    void sub_7100E7C4F8(ksys::act::Unk117* arg);

    /* 0x08 */ ksys::act::Actor* mActor;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ ksys::act::BaseProcLink _18;
    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ u16 _30 = 0;  // flags
};
KSYS_CHECK_SIZE_NX150(HorseRideInfo, 0x38);

// 0x7100e81140 (CSV act::getRideActor; lane2 s21): the actor linked in the ride info of `actor` (null without
// ride info or when it is no actor).
ksys::act::Actor* getRideActor(ksys::act::Actor* actor);

// Placeholder name (vtable 0x71023cee88). The HorseRideInfo embedded in NPC at 0xf28; its
// functions sit at 0x71002c9ffc-0x71002ca1d8.
class Unk_710244eaa0;

class Unk_71023cee88 : public HorseRideInfo {
    SEAD_RTTI_OVERRIDE(Unk_71023cee88, HorseRideInfo)
public:
    explicit Unk_71023cee88(ksys::act::Actor* actor) : HorseRideInfo(actor) {}
    ~Unk_71023cee88() override;

    bool m5(const ksys::act::ActorConstDataAccess& accessor) override;
    void m6() override {}
    bool m7() override { return true; }
    void m8() override {}
    void m9() override {}

    /* 0x38 */ ksys::act::BaseProcLink _38;
};
KSYS_CHECK_SIZE_NX150(Unk_71023cee88, 0x48);

// Placeholder name (vtable 0x710244eaa0; D1 / D0 0x7100 6e1614 / 6e1684, RTTI functions 0x6e1b98 / 0x6e1c64). The base
// of Player::RideInfo (vtable 0x710246ad80): two bone-bound seats (bone handles `_40` / `_118`) that are
// configured from the actor's GParam lists. Size 0x1f0.
// TODO: incomplete (m5 / m7 / m9 are not decompiled).
class Unk_710244eaa0 : public HorseRideInfo {
    SEAD_RTTI_OVERRIDE(Unk_710244eaa0, HorseRideInfo)
public:
    explicit Unk_710244eaa0(ksys::act::Actor* actor) : HorseRideInfo(actor) {}
    ~Unk_710244eaa0() override;

    // 0x6e16fc (CSV Player::RideInfo::x): removes the bone handles from their actors.
    void m4() override;
    bool m5(const ksys::act::ActorConstDataAccess& accessor) override;
    void m6() override;
    bool m7() override;
    void m8() override;
    void m9() override;

    /* 0x038 */ ksys::act::Actor* _38 = nullptr;
    /* 0x040 */ ksys::act::BoneHandle _40;
    /* 0x0e8 */ const sead::SafeString* _e8 = nullptr;
    /* 0x0f0 */ f32 _f0 = 0.0f;
    /* 0x0f8 */ const void* _f8 = nullptr;
    /* 0x100 */ u32 _100 = 0;
    /* 0x104 */ f32 _104 = 1.0f;
    /* 0x108 */ s32 _108 = 0;
    /* 0x10c */ u32 _10c = 1;
    /* 0x110 */ ksys::act::Actor* _110 = nullptr;
    /* 0x118 */ ksys::act::BoneHandle _118;
    /* 0x1c0 */ const sead::SafeString* _1c0 = nullptr;
    /* 0x1c8 */ f32 _1c8 = 0.0f;
    /* 0x1d0 */ const void* _1d0 = nullptr;
    /* 0x1d8 */ u32 _1d8 = 0;
    /* 0x1dc */ f32 _1dc = 1.0f;
    /* 0x1e0 */ s32 _1e0 = 0;
    /* 0x1e4 */ u32 _1e4 = 1;
    /* 0x1e8 */ bool _1e8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710244eaa0, 0x1f0);

}  // namespace uking::act

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

namespace ksys::phys {
class NavMeshCharacter;
}  // namespace ksys::phys

namespace ksys::as {
class ASList;
}

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
    /* 0x28 */ ksys::phys::NavMeshCharacter* _28 = nullptr;
    /* 0x30 */ u16 _30 = 0;  // flags
};
KSYS_CHECK_SIZE_NX150(HorseRideInfo, 0x38);

// 0x7100e81140 (CSV act::getRideActor; lane2 s21): the actor linked in the ride info of `actor` (null without
// ride info or when it is no actor).
ksys::act::Actor* getRideActor(ksys::act::Actor* actor);

// Original ride animation-name and relative-angle helpers; declarations only.
sead::SafeString sub_7100E81260(ksys::act::Actor* actor, ksys::act::Actor* ride_actor);
f32 sub_7100E8134C(ksys::act::Actor* actor, ksys::act::Actor* ride_actor);
bool sub_7100E813B0(ksys::as::ASList* list);

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
// of Player::RideInfo (vtable 0x710246ad80): two foot rotation controllers (the left / right foot node of the rider,
// see the HorseRider GParam object) that are configured from the actor's GParam lists. Size 0x1f0.
// TODO: incomplete.
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

    // Placeholder name (size 0xd8; the functions at 0x7100 6e1984 (update, 532 B) work on it).
    struct Foot {
        // 0x6e1984 (declaration only)
        void sub_71006E1984();

        /* 0x00 */ ksys::act::Actor* actor = nullptr;
        /* 0x08 */ ksys::act::BoneHandle bone;
        /* 0xb0 */ const sead::SafeString* name = nullptr;
        /* 0xb8 */ f32 _b8 = 0.0f;
        /* 0xc0 */ const void* axis = nullptr;
        /* 0xc8 */ u32 _c8 = 0;
        /* 0xcc */ f32 ratio = 1.0f;
        /* 0xd0 */ f32 retRatio = 0.0f;
        /* 0xd4 */ u32 _d4 = 1;
    };
    KSYS_CHECK_SIZE_NX150(Foot, 0xd8);

    /* 0x038 */ Foot mLeft;
    /* 0x110 */ Foot mRight;
    /* 0x1e8 */ bool _1e8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710244eaa0, 0x1f0);

}  // namespace uking::act

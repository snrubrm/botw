#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class BaseProc;
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

}  // namespace uking::act

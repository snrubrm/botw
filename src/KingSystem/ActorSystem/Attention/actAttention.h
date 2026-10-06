#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>

namespace ksys::act {

enum class AttType {
    Action = 0,
    Lock = 1,
    SwordSearch = 2,
    Attack = 3,
    Appeal = 4,
    JumpRide = 5,
    NameBalloon = 6,
    LookOnly = 7,
    Invalid = 8,
};

// Make sure to update AttActionType if this is changed
enum class AttActionCode {
    None = 0x1800000,
    Talk,
    Listen,
    Awake,
    Grab,
    Open,
    Pick,
    Catch,
    CheckCatch,
    CatchWeapon,
    Skin,
    Sleep,
    Sit,
    Lumber,
    Pushpull,
    Read,
    Check,
    Boot,
    BootPStop,
    Leave,
    Remind,
    Buy,
    Ride,
    Wakeboard,
    WakeboardRide,
    RideRito,
    RideZora,
    Cook,
    KillTime,
    Display,
    DisplayBow,
    DisplayShield,
    PickUp,
    Pray,
    PullOut,
    Waterfall,
    CommandWait,
    CommandCome,
    Thrust,
    Put,
    PickToEvent,
    Dummy,
};

// Placeholder (name is a guess; a one-value SEAD_ENUM that holds raw AttActionCode values): the original passes and returns
// the action code as a SEAD_ENUM-like 4-byte class by value, which AArch64 coerces to a 64-bit register (the
// `and x0, x0, #0xffffffff` / `and x2, x1, #0xffffffff` zero-extensions) and whose `operator int() const volatile` spills it
// to the stack (Attention::sub_7100D74880 / sub_7100D748B8 / sub_7100D748FC / PlayerSkin::calc_).
SEAD_ENUM(AttActionCodeValue, None)

// clang-format off
SEAD_ENUM(AttActionType, None,Talk,Listen,Awake,Grab,Open,Pick,Catch,CheckCatch,CatchWeapon,Skin,Sleep,Sit,Lumber,Pushpull,Read,Check,Boot,BootPStop,Leave,Remind,Buy,Ride,Wakeboard,WakeboardRide,RideRito,RideZora,Cook,KillTime,Display,DisplayBow,DisplayShield,PickUp,Pray,PullOut,Waterfall,CommandWait,CommandCome,Thrust,Put,PickToEvent,Dummy)
SEAD_ENUM(AttPriorityType, Default,Enemy,Npc,Obj,ObjLow,ObjMiddle,ObjHigh,Bullet)
// clang-format on

}  // namespace ksys::act

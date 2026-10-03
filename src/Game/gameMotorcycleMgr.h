#pragma once

#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::act {
class Actor;
class BaseProc;
struct Unk117;
}

namespace ksys::phys {
class CapsuleRigidBody;
class Unk_7102372790;
}

namespace uking {

// Name from the CSV (MotorcycleMgr::*; instance pointer 0x71025c5fa8, TU 0x71006783f4 - 0x710067b8f0).
// The singleton that spawns the motorcycle (Master Cycle Zero) next to the player: it tracks the
// actor of the spawned motorcycle (mProcLink / mProcHandle), the "Motorcycle_Energy" game data flag
// and the nav mesh / Havok queries used to find a place for it. Size 0x190. Layout from createInstance;
// the members after the slot are placeholders until the functions that use them are decompiled.
class MotorcycleMgr {
    SEAD_SINGLETON_DISPOSER(MotorcycleMgr)
    MotorcycleMgr();
    virtual ~MotorcycleMgr();

public:
    // 0x7100678954
    void init(sead::Heap* heap);

    // 0x71006785dc: reloads the "Motorcycle_Energy" flag handle (called when the game data is reinitialised).
    void setMotorcycleEnergyIter(ksys::gdt::Manager::ReinitEvent*);

    // 0x7100678b28: clamps the energy to [0, 1000] (or resets it to 1000 without the flag).
    void clampMotorcycleEnergy();

    // 0x7100679ad0: whether `actor` is the actor riding the motorcycle.
    bool checkIsActorRidingMotorcycle(ksys::act::Actor* actor);
    // 0x710067b728 (CSV MotorcycleMgr::x): whether the tracked motorcycle actor is `actor`.
    bool x(ksys::act::BaseProc* actor);
    // (the BaseProc forward declaration)
    // 0x7100679ac8 (CSV MotorcycleMgr::x_0): whether there is a tracked motorcycle actor.
    bool x_0();
    // 0x71006796f8
    bool hasHavokQueryStarted() const;
    // 0x710067b63c: the position of the motorcycle actor.
    bool sub_710067B63C(sead::Vector3f* pos);
    // 0x710067b6bc: the physics transform of the motorcycle actor.
    bool sub_710067B6BC(sead::Matrix34f* mtx);
    // 0x710067afb0: sets actor flag 0x1c of the motorcycle actor.
    void sub_710067AFB0();
    // 0x710067af08: Player::m117 forwards the Actor::x_17 request to the tracked motorcycle actor
    // (declared only).
    void sub_710067AF08(ksys::act::Unk117* arg);
    // 0x7100679a90: fades the xlink events of the motorcycle (the pair at +0x148).
    void effectFadeXLink();

    /* 0x28 */ ksys::act::BaseProcLink mProcLink;
    /* 0x38 */ f32 mEnergy = 1000.0f;
    /* 0x3c */ ksys::gdt::FlagHandle mEnergyHandle = ksys::gdt::InvalidHandle;
    /* 0x40 */ ksys::gdt::Manager::ReinitSignal::Slot mSlot{this, &MotorcycleMgr::setMotorcycleEnergyIter};
    /* 0xb0 */ u64 _b0 = 0;
    /* 0xb8 */ u64 _b8 = 0;
    /* 0xc0 */ u64 _c0 = 0;
    /* 0xc8 */ f32 _c8 = 0;
    /* 0xd0 */ ksys::phys::CapsuleRigidBody* _d0 = nullptr;  // "MotorcycleShapeCast" (init)
    /* 0xd8 */ ksys::phys::Unk_7102372790* _d8 = nullptr;  // the nav mesh query (HavokAI)
    /* 0xe0 */ ksys::act::BaseProcHandle mProcHandle;
    /* 0xf0 */ sead::Matrix34f _f0 = sead::Matrix34f::ident;
    /* 0x120 */ sead::Vector3f _120 = sead::Vector3f::zero;
    /* 0x12c */ sead::Vector3f _12c{0, 0, 0};
    /* 0x138 */ sead::Vector3f _138{0, 0, 0};
    /* 0x148 */ Unk_71012419b4 _148{};
    /* 0x168 */ xlink2::HandleSLink _168;
    /* 0x178 */ u8 _178 = 0;
    /* 0x179 */ u8 _179 = 0;
    /* 0x17a */ u8 _17a = 1;
    /* 0x17b */ u8 _17b = 0;
    /* 0x17c */ u8 _17c = 0;
    /* 0x17d */ u8 _17d = 0;
    /* 0x17e */ u8 _17e = 0;
    /* 0x17f */ u8 _17f = 0xff;
    /* 0x180 */ u8 _180 = 0;
    /* 0x184 */ sead::Vector3f _184{-1, -1, -1};
};
KSYS_CHECK_SIZE_NX150(MotorcycleMgr, 0x190);

}  // namespace uking

#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class QueryContactPointInfo;
class RigidBody;
}

namespace uking {

// Name from the CSV (IceBlockMgr::createInstance 0x710066e984 = new(0x190) + inlined ctor, init,
// x, x_0, x_1, x_2 = handleMessage returning 1; instance 0x71025c5d88). Not decompiled yet: the
// layout follows the inlined constructor and the destructor 0x710066eac4.
// TODO: incomplete (member types and meanings unknown).
class IceBlockMgr : public ksys::ActorMessageTransceiver::IHandler, public Unk_710243c330 {
    SEAD_SINGLETON_DISPOSER(IceBlockMgr)
    IceBlockMgr();
    ~IceBlockMgr() override;

public:
    // 0x7100671634 (CSV IceBlockMgr::x_2).
    int handleMessage(const ksys::Message* message) override { return 1; }

    // 0x710066f004 / 0x710066f038 (CSV IceBlockMgr::__auto2; placeholder names): _140 / 50 clamped to [0, 1],
    // and whether _140 is positive.
    f32 sub_710066F004() const;
    bool sub_710066F038() const;

    // 0x710066f8c4: declaration only; removes all linked ice blocks.
    void sub_710066F8C4();
    // 0x710066f538: fades the current effect handle (_100[_14c]), resets the effect position to
    // (0, 0, 1) and tells the linked actor (message 0x80000b7) to release the ice block.
    void fadeEffectAndReleaseActorMaybe();

    // Element type unknown (the ctor sets up a three-pointer buffer at 0x48; the dtor clears it first).
    /* 0x038 */ sead::FixedPtrArray<u8, 3> _38;
    /* 0x060 */ ksys::act::BaseProcLink _60;
    /* 0x070 */ ksys::act::BaseProcLink _70;
    /* 0x080 */ ksys::act::BaseProcLink _80;
    /* 0x090 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    /* 0x0e8 */ u8 _e8 = 0;
    /* 0x0e9 */ u8 _e9 = 0;
    /* 0x0ea */ u8 _ea[2] = {};
    // Zeroed by the inlined ctor in createInstance 0x710066e984 (types unknown). 0x710066f538 fades an effect
    // handle at 0x100 + _14c * 0x20, so 0x100-0x140 are probably two 0x20-byte effect handles, not the
    // placeholder fields below.
    /* 0x0ec */ sead::Vector3f _ec = {};
    /* 0x0f8 */ u8 _f8 = 0;
    /* 0x0fc */ u32 _fc = 0;
    // Two xlink effect handles; fadeEffectAndReleaseActorMaybe fades the one at _14c.
    /* 0x100 */ Unk_71012419b4 _100[2];
    /* 0x140 */ f32 _140 = 0;  // a level: sub_710066F004 returns it / 50 clamped to [0, 1]
    /* 0x144 */ u32 _144 = 0;
    /* 0x148 */ f32 _148 = -1.0;
    /* 0x14c */ u8 _14c = 0;
    /* 0x14d */ u8 _14d = 0;
    /* 0x14e */ bool _14e = false;  // set by RemainsWaterBattleRoot::handleMessage_ (message 0x8000069)
    // Deleted through its virtual destructor in ~IceBlockMgr (AmiiboMgr keeps a CylinderRigidBody here).
    /* 0x150 */ ksys::phys::RigidBody* _150 = nullptr;
    /* 0x158 */ ksys::phys::QueryContactPointInfo* _158 = nullptr;
    /* 0x160 */ s64 _160 = -1;
    /* 0x168 */ s32 _168 = -1;
    /* 0x170 */ ksys::act::BaseProcHandle _170;
    /* 0x180 */ ksys::act::BaseProcLink _180;
};
KSYS_CHECK_SIZE_NX150(IceBlockMgr, 0x190);

}  // namespace uking

#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
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

    // Element type unknown (the ctor sets up a three-pointer buffer at 0x48; the dtor clears it first).
    /* 0x038 */ sead::FixedPtrArray<u8, 3> _38;
    /* 0x060 */ ksys::act::BaseProcLink _60;
    /* 0x070 */ ksys::act::BaseProcLink _70;
    /* 0x080 */ ksys::act::BaseProcLink _80;
    /* 0x090 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    /* 0x0e8 */ u16 _e8 = 0;
    // Zeroed by the inlined ctor in createInstance 0x710066e984 (types unknown).
    /* 0x0ec */ u32 _ec = 0;
    /* 0x0f0 */ u32 _f0 = 0;
    /* 0x0f4 */ u32 _f4 = 0;
    /* 0x0f8 */ u8 _f8 = 0;
    /* 0x0fc */ u32 _fc = 0;
    /* 0x100 */ u32 _100 = 0;
    /* 0x104 */ u32 _104 = 0;
    /* 0x108 */ u32 _108 = 0;
    struct Entry {
        void* _0 = nullptr;
        u32 _8 = 0;
    };
    /* 0x110 */ sead::SafeArray<Entry, 3> _110;
    /* 0x140 */ f32 _140 = 0;  // a level: sub_710066F004 returns it / 50 clamped to [0, 1]
    /* 0x144 */ u32 _144 = 0;
    /* 0x148 */ f32 _148 = -1.0;
    /* 0x14c */ u16 _14c = 0;
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

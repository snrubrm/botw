#pragma once

#include <heap/seadDisposer.h>
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class QueryContactPointInfo;
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
    /* 0x038 */ u8 _38[0x60 - 0x38];  // a sead::FixedPtrArray<?, 3>
    /* 0x060 */ ksys::act::BaseProcLink _60;
    /* 0x070 */ ksys::act::BaseProcLink _70;
    /* 0x080 */ ksys::act::BaseProcLink _80;
    /* 0x090 */ ksys::ActorMessageTransceiver mTransceiver;
    /* 0x0e8 */ u16 _e8 = 0;
    /* 0x0ea */ u8 _ea[0x148 - 0xea];
    /* 0x148 */ f32 _148 = -1.0;
    /* 0x14c */ u16 _14c = 0;
    /* 0x14e */ bool _14e = false;  // set by RemainsWaterBattleRoot::handleMessage_ (message 0x8000069)
    /* 0x150 */ void* _150 = nullptr;  // polymorphic, deleted in the destructor
    /* 0x158 */ ksys::phys::QueryContactPointInfo* _158 = nullptr;
    /* 0x160 */ s64 _160 = -1;
    /* 0x168 */ s32 _168 = -1;
    /* 0x170 */ ksys::act::BaseProcHandle _170;
    /* 0x180 */ ksys::act::BaseProcLink _180;
};
KSYS_CHECK_SIZE_NX150(IceBlockMgr, 0x190);

}  // namespace uking

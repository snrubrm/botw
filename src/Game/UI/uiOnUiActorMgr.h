#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverRxOnly.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class PlayerArmors;
}

namespace uking::act {
class PauseMenuPlayer;
}

namespace uking::ai {
class PauseMenuPlayerRoot;
}

namespace uking::ui {

// Original vtable 0x2473660: Node at 0, receive handler at 8, acknowledgement handler at 0x10.
class OnUiActorMgr : public sead::hostio::Node,
                     public ksys::MessageTransceiverRxOnly::IHandler,
                     public ksys::MessageTransceiverTxOnly::IHandler {
    SEAD_SINGLETON_DISPOSER(OnUiActorMgr)
    OnUiActorMgr();

public:
    ~OnUiActorMgr() override;
    int handleMessage(const ksys::Message& message) override;

    // 0x710090ab60
    ksys::act::Actor* getActor() const;
    ksys::act::PlayerArmors* getArmors() const { return mArmors; }
    void sub_7100906F08(ksys::act::Actor* actor);
    bool sub_710090AB4C() const;
    void sub_7100907A30();
    // 0x7100906e70 (CSV OnUiActorMgr::__auto3; placeholder name): releases the armors/actor/link actors
    void sub_7100906E70();

private:
    friend class uking::act::PauseMenuPlayer;
    friend class uking::ai::PauseMenuPlayerRoot;

    /* 0x38 */ ksys::act::BaseProcLink mActorLink;
    /* 0x48 */ ksys::act::Actor* mActor;
    /* 0x50 */ ksys::act::BaseProcLink _50;
    u8 _60[0x90 - 0x60];
    /* 0x90 */ ksys::act::PlayerArmors* mArmors;
    u8 _98[0xb0 - 0x98];
    /* 0xb0 */ sead::FixedSafeString<64> _b0;
    u8 _108[0x1f4 - 0x108];
    /* 0x1f4 */ sead::BitFlag8 _1f4;
    u8 _1f5[3];
};
KSYS_CHECK_SIZE_NX150(OnUiActorMgr, 0x1f8);

}  // namespace uking::ui

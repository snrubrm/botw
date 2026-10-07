#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
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

private:
    friend class uking::act::PauseMenuPlayer;

    /* 0x38 */ ksys::act::BaseProcLink mActorLink;
    /* 0x48 */ ksys::act::Actor* mActor;
    u8 _50[0x90 - 0x50];
    /* 0x90 */ ksys::act::PlayerArmors* mArmors;
    u8 _98[0xb0 - 0x98];
    /* 0xb0 */ sead::FixedSafeString<64> _b0;
    u8 _108[0x1f8 - 0x108];
};
KSYS_CHECK_SIZE_NX150(OnUiActorMgr, 0x1f8);

}  // namespace uking::ui

#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverRxOnly.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/Utils/Types.h"

namespace gsys {
class ModelScene;
}

namespace ksys::act {
class Actor;
class PlayerArmors;
}

namespace uking::act {
class Weapon;
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
    int handleMessage(const ksys::Message* message) override;

    // 0x710090ab60
    ksys::act::Actor* getActor() const;
    ksys::act::PlayerArmors* getArmors() const { return mArmors; }
    void sub_7100906F08(ksys::act::Actor* actor);
    bool sub_710090AB4C() const;
    // 0x710090aa30 (placeholder name): releases the ready weapon proc of slot `idx` (handles at
    // 0x60, 0x10 apart) and returns it as a Weapon (PauseMenuPlayer::sub_71006EA160)
    uking::act::Weapon* sub_710090AA30(s32 idx);
    // 0x710090941c (CSV OnUiActorMgr::__auto1; declaration only, placeholder name): called in the wait loop of
    // SystemPauseMgr::waitForOnUiActorMgrAndBlockSaveMaybe / waitForOnUiActorMgr until
    // sub_710090AB4C() holds.
    void sub_710090941C();
    // 0x71009079ec (placeholder name): turns the pause menu player's _c34 mode on / off (off also clears _c38) and
    // mirrors it in bit 0x8 of _1f4
    void sub_71009079EC(bool on);
    void sub_7100907A30();
    // 0x7100906f18 (CSV OnUiActorMgr::x_0, declared only): pushes the pause menu player's resist levels, stores the
    // model matrix scale at 0x1e8 / 0x1f0, sets bit 4 of _1f4 and either applies a rotation to the actor's pose or
    // resets the 0x110 - 0x128 block
    void sub_7100906F18();
    // inline-only in the original; name is a guess (ScreenPauseMenu::m180 flips bit 0 of _1f4)
    void toggleFlag1f4Bit0() { _1f4.toggleBit(0); }
    // 0x7100906e70 (CSV OnUiActorMgr::__auto3; placeholder name): releases the armors/actor/link actors
    void sub_7100906E70();
    // 0x71009070d0 (CSV OnUiActorMgr::x_4): applies the heat/cold/burn resist levels to the player
    void x_4();

private:
    friend class uking::act::PauseMenuPlayer;
    friend class uking::ai::PauseMenuPlayerRoot;

    /* 0x38 */ ksys::act::BaseProcLink mActorLink;
    /* 0x48 */ ksys::act::Actor* mActor;
    /* 0x50 */ ksys::act::BaseProcLink _50;
    // the weapons being created for the pause menu player (sub_710090AA30 hands them over)
    /* 0x60 */ sead::SafeArray<ksys::act::BaseProcHandle, 3> _60;
    /* 0x90 */ ksys::act::PlayerArmors* mArmors;
    /* 0x98 */ gsys::ModelScene* _98;  // the scene the handed-over weapons' models are bound to
    u8 _a0[0xb0 - 0xa0];
    /* 0xb0 */ sead::FixedSafeString<64> _b0;
    u8 _108[0x1f4 - 0x108];
    /* 0x1f4 */ sead::BitFlag8 _1f4;
    u8 _1f5[3];
};
KSYS_CHECK_SIZE_NX150(OnUiActorMgr, 0x1f8);

}  // namespace uking::ui

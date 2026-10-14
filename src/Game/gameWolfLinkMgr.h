#pragma once

#include <basis/seadTypes.h>
#include <limits>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys::act {
class Actor;
}

namespace uking {

namespace act {
class WolfLink;
}

// Placeholder declaration (names from the CSV: WolfLinkMgr::createInstance 0x71006828a8, init_ 0x7100682b94,
// postCalc 0x71006836d0; instance pointer at 0x71025c6ff8; namespace is a guess, like HorseMgr's). The manager of
// the Wolf Link (amiibo) actor; only what the AI actions use is declared.
// TODO: incomplete.
// 0x7100683548 (308 B, declared only; placeholder name): checks the event manager (an active event that keeps the
// Wolf Link in state 5).
bool sub_7100683548();

class WolfLinkMgr {
    SEAD_SINGLETON_DISPOSER(WolfLinkMgr)
    WolfLinkMgr() = default;
    // 0x7100682a1c (D1) / 0x7100682b40 (D0)
    virtual ~WolfLinkMgr();

public:
    // 0x7100682b64 (CSV WolfLinkMgr::init)
    void init();
    // 0x7100682b94 (CSV WolfLinkMgr::init_): looks up the WolfLink_* flag handles.
    void init_();
    // 0x7100682a18 (CSV j_WolfLinkMgr::init_; placeholder name): the gdt reinit callback.
    void onGdtReinit(ksys::gdt::Manager::ReinitEvent*) { init_(); }

    // 0x71006836D0: updates the registered Wolf Link state.
    void postCalc();

    // 0x7100683410 / 0x7100683790 / 0x710068386c (312 / 220 / 260 B, declared only; placeholder names): the
    // postCalc handlers of the states 7 (and 6), 1 and 2. sub_7100683410 respawns the Wolf Link at the saved position.
    bool sub_7100683410();
    // 0x7100683214 (placeholder name): in state 2, sends message 0 from `actor` (with itself as user data) to the
    // Wolf Link; false when there is none.
    bool sub_7100683214(ksys::act::Actor* actor);
    // 0x71006832c0 (CSV WolfLinkMgr::__auto0; placeholder name): in state 2 or 5, saves the Wolf Link state and
    // releases it (state 6 unless its life ran out).
    void sub_71006832C0();
    // 0x71006833c8 (CSV WolfLinkMgr::__auto1; placeholder name): in state 6, moves to state 7 while an event is
    // active, else runs sub_7100683410.
    void sub_71006833C8();
    void sub_7100683790();
    // 0x7100683970 (428 B, declared only; placeholder name): registers the created Wolf Link (stores it in _80).
    void sub_7100683970(act::WolfLink* wolf_link);
    void sub_710068386C();

    // 0x7100682cb4: registered state 2 and the linked actor flag at 0x1699 bit 6.
    bool sub_7100682CB4() const;
    // 0x7100683120 / 0x7100683174 (placeholder names): the Wolf Link's life (1 without a life value) / max life;
    // -1 without a Wolf Link.
    s32 sub_7100683120();
    s32 sub_7100683174();
    sead::Vector3f sub_71006831BC() const;
    // 2026-10-07: original WolfLink pre-delete call passes this actor and true.
    bool sub_7100682F80(ksys::act::Actor* actor, bool deleting);
    // 0x7100682ce8 (declared only; WolfLinkAmiiboRegister::enter_): registers the amiibo Wolf Link at `pos`.
    bool sub_7100682CE8(const sead::Vector3f* pos, sead::BitFlag8 flags);
    // 0x7100683088 (declared only; WolfLinkEvent::enter_ with 1).
    bool sub_7100683088(bool a1);
    // 0x710068367c / 0x7100683698 (declared only; WolfLinkAmiiboRegister::calc_).
    bool sub_710068367C();
    bool sub_7100683698();

    /* 0x28 */ ksys::act::BaseProcLink _28;  // the Wolf Link actor (sub_710068367C / sub_7100683698)
    /* 0x38 */ ksys::act::BaseProcHandle _38;
    /* 0x48 */ sead::Vector3f _48{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                                  std::numeric_limits<f32>::quiet_NaN()};
    /* 0x54 */ sead::Vector3f _54{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                                  std::numeric_limits<f32>::quiet_NaN()};  // warp destination (WolfLinkAmiiboWarp::enter_)
    /* 0x60 */ s32 _60 = 0;  // 1: a Wolf Link is registered / spawned
    /* 0x64 */ u8 _64 = 0;
    /* 0x68 */ ksys::MesTransceiverId _68;
    // Registration 683970 stores the WolfLink cast from 683790; release 682F80 clears it.
    /* 0x80 */ act::WolfLink* _80 = nullptr;
    /* 0x88 */ ksys::gdt::Manager::ReinitSignal::Slot mSlot{this, &WolfLinkMgr::onGdtReinit};
    /* 0xf8 */ ksys::gdt::FlagHandle mCurrentLifeHandle = ksys::gdt::InvalidHandle;
    /* 0xfc */ ksys::gdt::FlagHandle mCurrentPosHandle = ksys::gdt::InvalidHandle;
    /* 0x100 */ ksys::gdt::FlagHandle mMaxLifeHandle = ksys::gdt::InvalidHandle;
    /* 0x104 */ ksys::gdt::FlagHandle mDiedTodayHandle = ksys::gdt::InvalidHandle;
};
KSYS_CHECK_SIZE_NX150(WolfLinkMgr, 0x108);

}  // namespace uking

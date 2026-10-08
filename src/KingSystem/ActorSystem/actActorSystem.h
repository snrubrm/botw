#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace uking {
class Unk_710243c7c8;
}

namespace ksys {
namespace act {
class PlayerLink;
}
void setPlayerLink(act::PlayerLink* link);
}  // namespace ksys

namespace ksys::act {

class Actor;
class ActorConstDataAccess;
class PlayerBase;
class PlayerLink;

// TODO: incomplete
class ActorSystem {
    SEAD_SINGLETON_DISPOSER(ActorSystem)
    ActorSystem();

public:
    void onBaseProcMgrCalc();

    bool getPlayer(ActorConstDataAccess* accessor);
    // 0x7100d5d4c0: the player actor (null without a player link). New virtual-slot-free
    // overload; the bool one above takes an accessor.
    PlayerBase* getPlayer();

    // 0x7100d5d954: sets _138 and tail-calls ResourceMgrTask::sub_7101208400
    // (return type uncertain; no in-tree callers).
    void handleActorCreateFailure();
    bool getPlayerPosition(sead::Vector3f* out);

    bool getAutoPlacementActorPos(const sead::SafeString& name, sead::Vector3f* pos) const;

    sead::Heap* getEmergencyHeap() const { return mEmergencyHeap; }
    const sead::Vector3f& getPlayerPos() const { return mPlayerPos; }
    // The player (read inline by MotorcycleMgr::isProhibited).
    PlayerLink* getPlayerLink() const { return _c0; }
    // inline-only in the original; name is a guess (Swarm::m81, Guardian::m81).
    uking::Unk_710243c7c8* getStasisMessageSender() const { return _c8; }

    // inline-only in the original; name is a guess (GameScene::sub_71007B4B50 clears it).
    void set104(bool value) { _104 = value; }

    bool callAutoPlacementMgrPreCalcFn(void* userdata);
    void allocEmergencyHeap(sead::Heap* heap);

    void insertActiveActor(Actor* actor);
    void eraseFromActiveActorList(Actor* actor);
    void registerActorThatLostPlacementObj(Actor* actor);
    void eraseActorThatLostPlacementObj(Actor* actor);
    Actor* getActorThatLostPlacementObj(const u32& hash_id);

    void invokeRadarMgrInvoker();
    void invokeAutoPlacementMgrInvoker3();
    bool a();
    bool auto1();
    void callRadarMgrInvoker();
    void callAutoPlacementInvoker3();
    void auto4(void* a1, void* a2);

    bool isPlacementMgrDynamicHeapOom() const;
    void submitReqCallAutoPlacementMgrFn();
    // Used by AutoPlacementMgr::stopThread (stores in this order).
    void clearAutoPlacementMgrDelegates() {
        _280 = nullptr;
        _298 = nullptr;
        _290 = nullptr;
    }

private:
    DebugMessage mDebugMessage{"アクタ"};
    void* _b0 = nullptr;
    void* _b8 = nullptr;
    friend void ksys::setPlayerLink(PlayerLink* link);
    PlayerLink* _c0 = nullptr;  // the player (set by setPlayerLink)
    uking::Unk_710243c7c8* _c8 = nullptr;
    sead::Heap* mEmergencyHeap = nullptr;
    sead::Vector3f mPlayerPos = sead::Vector3f::zero;
    u32 _e4 = 0;
    u32 _e8 = 0;
    sead::Vector3f _ec = sead::Vector3f::zero;
    sead::Vector3f _f8 = sead::Vector3f::zero;
    bool _104 = false;
    sead::OffsetList<Actor> mActiveActors;
    sead::OffsetList<Actor> mActorsThatLostPlacementObj;
    bool _138 = false;
    bool _139 = true;
    bool _13a = true;
    bool _13b = false;
    // 3 ActorMessageTransceiver::IHandler implementations (0x10 each)
    u8 _140[0x170 - 0x140];
    ActorMessageTransceiver _170;
    ActorMessageTransceiver _1c8;
    ActorMessageTransceiver _220;
    sead::IDelegate1R<int, bool>* _278 = nullptr;
    sead::IDelegate1R<int, bool>* _280 = nullptr;
    sead::IDelegate2<void*, void*>* _288 = nullptr;
    sead::IDelegate2R<const sead::SafeString&, sead::Vector3f*, bool>* _290 = nullptr;
    sead::IDelegate* _298 = nullptr;
    sead::Delegate1R<ActorSystem, void*, bool> _2a0{this, &ActorSystem::callAutoPlacementMgrPreCalcFn};
};
KSYS_CHECK_SIZE_NX150(ActorSystem, 0x2c0);

}  // namespace ksys::act

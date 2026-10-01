#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
class ActorConstDataAccess;

// TODO: incomplete
class ActorSystem {
    SEAD_SINGLETON_DISPOSER(ActorSystem)
    ActorSystem();

public:
    void onBaseProcMgrCalc();

    bool getPlayer(ActorConstDataAccess* accessor);

    bool getAutoPlacementActorPos(const sead::SafeString& name, sead::Vector3f* pos) const;

    sead::Heap* getEmergencyHeap() const { return mEmergencyHeap; }
    const sead::Vector3f& getPlayerPos() const { return mPlayerPos; }

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

private:
    DebugMessage mDebugMessage{"アクタ"};
    void* _b0 = nullptr;
    void* _b8 = nullptr;
    void* _c0 = nullptr;
    void* _c8 = nullptr;
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

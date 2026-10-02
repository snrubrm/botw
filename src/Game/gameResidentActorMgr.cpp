#include "Game/gameResidentActorMgr.h"
#include <heap/seadExpHeap.h>
#include <resource/seadResource.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Framework/GameConfig.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(ResidentActorMgr)

// NON_MATCHING: regalloc (x8/x9 swapped in the first FreeList initialisation loop)
ResidentActorMgr::ResidentActorMgr() = default;

void ResidentActorMgr::init(sead::Heap* heap) {
    mHeap = sead::ExpHeap::create(0xa00000, "MemoryResidentActor", heap, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, true);
    ksys::act::ActorHeapUtil::instance()->setMemoryResidentActorHeap(mHeap);
}

void ResidentActorMgr::loadByml() {
    ksys::res::LoadRequest req;
    req.mRequester = "ResidentActorMgr";
    req._22 = true;
    req.mLoadCompressed = false;
    mResHandle.requestLoad("Actor/ResidentActors.byml", &req);
}

bool ResidentActorMgr::resIsReady() const {
    return mResHandle.isReadyOrNeedsParse();
}

bool ResidentActorMgr::parseResource() {
    return mResHandle.parseResource(nullptr);
}

void ResidentActorMgr::generateResidentActors(sead::Heap* heap) {
    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.getResource());
    al::ByamlIter root{res->getRawData()};
    const s32 num = root.getSize();
    for (s32 i = 0; i < num; ++i) {
        al::ByamlIter entry;
        al::ByamlIter scale_iter;
        if (!root.tryGetIterByIndex(&entry, i))
            continue;

        const char* name = "";
        entry.tryGetStringByKey(&name, "name");
        bool only_res = false;
        entry.tryGetBoolByKey(&only_res, "only_res");

        ksys::act::InstParamPack params;
        if (entry.tryGetIterByKey(&scale_iter, "scale")) {
            sead::Vector3f scale;
            if (scale_iter.tryGetFloatByKey(&scale.x, "x") &&
                scale_iter.tryGetFloatByKey(&scale.y, "y") &&
                scale_iter.tryGetFloatByKey(&scale.z, "z")) {
                params->addScale(scale);
            }
        }

        sead::Heap* actor_heap;
        ksys::act::BaseProcHandle* handle;
        if (only_res) {
            actor_heap = heap;
            handle = mOnlyResHandles.emplaceBack();
        } else {
            actor_heap = mHeap;
            handle = mHandles.emplaceBack();
            params->addSystemBits();
        }

        params->addPosition({-1060.0, 250.0, 1830.0});

        if (sead::SafeString("GameROMPlayer") == name) {
            params->addMA(4);
        } else if (sead::SafeString("WakeBoardRope") == name) {
            params->addScale({1.0, 3.0, 1.0});
            params->addModelUser("WakeBoardPlayer");
        }

        ksys::act::ActorCreator::instance()->requestCreateActor(name, actor_heap, handle, &params,
                                                                nullptr, 1);
    }
}

void ResidentActorMgr::finishLoadingResidentActors() {
    if (GameConfig::getInstance()->_419) {
        ksys::act::BaseProcMgr::instance()->writeResidentActorsCsv(
            "%PROJECT_ROOT%/Log/BootupPatrol/resident_actors.csv");
    }

    for (auto& handle : mOnlyResHandles)
        handle.deleteProc();
    mOnlyResHandles.clear();

    for (auto it = mHandles.begin(), end = mHandles.end(); it != end; ++it) {
        auto* proc = it->getProc();
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            it->releaseProc();
            mActors.pushBack(actor);
        }
    }

    if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer())
        static_cast<ksys::act::Player*>(player)->initResidentActors();
}

bool ResidentActorMgr::allActorsLoaded() const {
    for (s32 i = 0, n = mOnlyResHandles.size(); i < n; ++i) {
        if (!mOnlyResHandles[i]->isProcReady())
            return false;
    }
    for (s32 i = 0, n = mHandles.size(); i < n; ++i) {
        if (!mHandles[i]->isProcReady())
            return false;
    }
    return true;
}

void ResidentActorMgr::sub_710090EB34() {
    for (auto& actor : mActors)
        actor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void ResidentActorMgr::sub_710090EB70() {
    for (auto it = mActors.begin(), end = mActors.end(); it != end; ++it) {
        const auto& name = it->getName();
        if (!name.isEmpty() && sead::SafeString("GameROMPlayer") == name)
            it->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

bool ResidentActorMgr::hasLoadedResidentActors() const {
    return mActors.size() != 0;
}

ksys::act::Actor* ResidentActorMgr::getActorByName(const sead::SafeString& name) const {
    for (auto it = mActors.begin(), end = mActors.end(); it != end; ++it) {
        if (name == it->getName())
            return &*it;
    }
    return nullptr;
}

}  // namespace uking

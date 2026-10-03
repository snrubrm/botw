#include "Game/AI/Action/actionCreateObjectsOfOwnedHorse.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

CreateObjectsOfOwnedHorse::CreateObjectsOfOwnedHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateObjectsOfOwnedHorse::~CreateObjectsOfOwnedHorse() = default;

bool CreateObjectsOfOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateObjectsOfOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = HorseMgr::instance();
    if (!mgr || !mgr->mOwnedHorse.hasProc()) {
        setFailed();
        return;
    }
    bool created = false;
    if (!mHorseManeActorName_d.isEmpty()) {
        mgr->sub_7100E87340(mHorseManeActorName_d,
                            ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
        created = true;
    }
    if (!mHorseReinsActorName_d.isEmpty()) {
        mgr->sub_7100E87424(mHorseReinsActorName_d,
                            ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
        created = true;
    }
    if (!mHorseSaddleActorName_d.isEmpty()) {
        mgr->sub_7100E87508(mHorseSaddleActorName_d,
                            ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
        return;
    }
    if (!created)
        setFailed();
}

void CreateObjectsOfOwnedHorse::leave_() {
    if (auto* mgr = HorseMgr::instance())
        mgr->sub_7100E875EC();
}

void CreateObjectsOfOwnedHorse::loadParams_() {
    getDynamicParam(&mHorseReinsActorName_d, "HorseReinsActorName");
    getDynamicParam(&mHorseSaddleActorName_d, "HorseSaddleActorName");
    getDynamicParam(&mHorseManeActorName_d, "HorseManeActorName");
}

void CreateObjectsOfOwnedHorse::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* mgr = HorseMgr::instance();
    if (!mgr) {
        setFailed();
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor))
        setFailed();
    else if (!act::sub_7100E6EAAC(accessor))
        setFinished();
}

}  // namespace uking::action

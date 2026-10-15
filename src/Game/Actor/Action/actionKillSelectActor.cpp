#include "Game/Actor/Action/actionKillSelectActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapLinkTag.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

KillSelectActor::KillSelectActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillSelectActor::~KillSelectActor() = default;

bool KillSelectActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillSelectActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KillSelectActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void KillSelectActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

// NON_MATCHING: guard scheduling and string-comparison register allocation.
void KillSelectActor::calc_() {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (mActorName_d.isEmpty() || !placement || !placement->mPlacementActors) {
        setFailed();
        return;
    }
    {
        ksys::act::BaseProcMgr::ProcIteratorContext context(
            *ksys::act::BaseProcMgr::instance(),
            ksys::act::BaseProcMgr::ProcFilter::Sleeping |
                ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        while (auto* proc = context.next()) {
            if (sead::DynamicCast<ksys::map::LinkTag>(proc))
                continue;
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (!actor || actor->getName() != mActorName_d)
                continue;
            if (!mUniqueName_d.isEmpty() &&
                mUniqueName_d != sead::SafeString(actor->getUniqueName()))
                continue;
            ksys::evt::Manager::instance()->setActorBeingDeletedOnContexts(actor);
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            if (auto* xlink = actor->getXLink())
                xlink->resetELinkEvents();
        }
    }
    setFinished();
}

}  // namespace uking::action

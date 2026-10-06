#include "Game/AI/Action/actionDemoPlayerZoraRide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

DemoPlayerZoraRide::DemoPlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {}

DemoPlayerZoraRide::~DemoPlayerZoraRide() = default;

bool DemoPlayerZoraRide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void DemoPlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    _1d = false;
    if (!ksys::gdt::Manager::instance()) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    ksys::act::BaseProcMgr::ProcIteratorContext context(
        *ksys::act::BaseProcMgr::instance(),
        ksys::act::BaseProcMgr::ProcFilter::Sleeping | ksys::act::BaseProcMgr::ProcFilter::Initializing |
            ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
    while (auto* proc = context.next()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (proc->getName() == "Npc_Zora030") {
                ksys::act::BaseProcLink link;
                link.acquire(proc, false);
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                accessor.setThisActorAsParent(mActor, false);
                _20.x(proc);
                break;
            }
        }
    }
}

void DemoPlayerZoraRide::leave_() {
    static_cast<ksys::act::PlayerBase*>(mActor)->_c48.resetBit(8);
    mActor->sub_71011DA834(&_20);
}

void DemoPlayerZoraRide::loadParams_() {}

void DemoPlayerZoraRide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action

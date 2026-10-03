#include "Game/AI/AI/aiStopTimerObserver.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

StopTimerObserver::StopTimerObserver(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StopTimerObserver::~StopTimerObserver() = default;

bool StopTimerObserver::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StopTimerObserver::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* physics = mActor->getPhysics()) {
        if (auto* info = physics->getContactPointInfo(0))
            info->setAllLayerMask2();
    }
    changeChild("ビタロックオブジェクトなし");
}

// NON_MATCHING: the original builds the begin iterator twice (an emptiness test, then the loop; same as
// FixableLiftable::calc_) and evaluates both isCurrentChild calls without short-circuiting
void StopTimerObserver::calc_() {
    bool touching_stasis_object = false;
    if (auto* physics = mActor->getPhysics()) {
        if (auto* info = physics->getContactPointInfo(0)) {
            if (info->getNumContactPoints() != 0) {
                for (auto it = info->begin(); it != info->end(); ++it) {
                    {
                        ksys::act::ActorConstDataAccess accessor;
                        ksys::act::getCollidedActorMaybe(&accessor, (*it)->body_b);
                        if (!accessor.hasProc() || !accessor.sub_7100D10FB8())
                            continue;
                    }
                    touching_stasis_object = true;
                    break;
                }
            }
        }
    }

    if (touching_stasis_object && isCurrentChild("ビタロックオブジェクトなし"))
        changeChild("ビタロックオブジェクトあり");
    else if (!touching_stasis_object && isCurrentChild("ビタロックオブジェクトあり"))
        changeChild("ビタロックオブジェクトなし");
}

void StopTimerObserver::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StopTimerObserver::loadParams_() {}

}  // namespace uking::ai

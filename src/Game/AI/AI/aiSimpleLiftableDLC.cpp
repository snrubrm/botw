#include "Game/AI/AI/aiSimpleLiftableDLC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SimpleLiftableDLC::SimpleLiftableDLC(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftableDLC::~SimpleLiftableDLC() = default;

bool SimpleLiftableDLC::init_(sead::Heap* heap) {
    _40.x();
    _80.x();
    return true;
}

void SimpleLiftableDLC::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::disableAttClient(mActor, "Grab");
    _d0 = false;
    _80.x();
    sub_710056EA38();
}

void SimpleLiftableDLC::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLiftableDLC::loadParams_() {
    getStaticParam(&mScaleToLiftUp_s, "ScaleToLiftUp");
}

inline void SimpleLiftableDLC::x() {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
    ksys::act::disableAllAttClients(actor);
    _40.x();
    changeChild("所持");
}

void SimpleLiftableDLC::calc_() {
    sub_710056EC90();

    if (_d0) {
        auto* actor = mActor;
        if (isCurrentChild("通常") &&
            (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _40._30)) {
            x();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("通常");
}

}  // namespace uking::ai

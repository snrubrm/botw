#include "Game/AI/Action/actionFlyingBalloonObserverTag.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

FlyingBalloonObserverTag::FlyingBalloonObserverTag(const InitArg& arg)
    : AreaObserveActorAction(arg) {}

FlyingBalloonObserverTag::~FlyingBalloonObserverTag() = default;

bool FlyingBalloonObserverTag::init_(sead::Heap* heap) {
    return AreaObserveActorAction::init_(heap);
}

void FlyingBalloonObserverTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaObserveActorAction::enter_(params);
}

void FlyingBalloonObserverTag::leave_() {
    AreaObserveActorAction::leave_();
}

void FlyingBalloonObserverTag::calc_() {
    AreaObserveActorAction::calc_();
}

bool FlyingBalloonObserverTag::m37(const ksys::act::ActorConstDataAccess& accessor) {
    if (!AreaObserveActorAction::m37(accessor))
        return false;
    return accessor.isFlyingBalloon();
}

}  // namespace uking::action

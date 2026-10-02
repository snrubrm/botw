#include "Game/AI/Action/actionCallOvserveActorTag.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

CallOvserveActorTag::CallOvserveActorTag(const InitArg& arg) : AreaObserveActorAction(arg) {}

CallOvserveActorTag::~CallOvserveActorTag() = default;

bool CallOvserveActorTag::init_(sead::Heap* heap) {
    return AreaObserveActorAction::init_(heap);
}

void CallOvserveActorTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaObserveActorAction::enter_(params);
}

void CallOvserveActorTag::leave_() {
    AreaObserveActorAction::leave_();
}

void CallOvserveActorTag::calc_() {
    AreaObserveActorAction::calc_();
}

bool CallOvserveActorTag::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!accessor.hasProc())
        return false;

    if (m37(accessor)) {
        _98._18.x(mActor);
        _98.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
    return AreaActorObserve::m15(accessor);
}

}  // namespace uking::action

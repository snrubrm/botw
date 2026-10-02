#include "Game/AI/Action/actionBindParentAction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BindParentAction::BindParentAction(const InitArg& arg) : BindAction(arg) {}

BindParentAction::~BindParentAction() = default;

void BindParentAction::loadParams_() {
    BindAction::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BindParentAction::calc_() {
    if (!m33())
        setFailed();
}

void BindParentAction::m32() {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

ksys::act::Actor* BindParentAction::m33() {
    return sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
}

}  // namespace uking::action

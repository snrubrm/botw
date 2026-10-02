#include "Game/AI/Action/actionRegistedActorDeadCheck.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

RegistedActorDeadCheck::RegistedActorDeadCheck(const InitArg& arg)
    : RegistedActorDeadCheckBase(arg) {}

RegistedActorDeadCheck::~RegistedActorDeadCheck() = default;

bool RegistedActorDeadCheck::init_(sead::Heap* heap) {
    return RegistedActorDeadCheckBase::init_(heap);
}

void RegistedActorDeadCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorDeadCheckBase::enter_(params);
}

void RegistedActorDeadCheck::leave_() {
    RegistedActorDeadCheckBase::leave_();
}

void RegistedActorDeadCheck::loadParams_() {
    RegistedActorDeadCheckBase::loadParams_();
}

void RegistedActorDeadCheck::calc_() {
    RegistedActorDeadCheckBase::calc_();
}

bool RegistedActorDeadCheck::m32(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.getLife() > 0;
}

}  // namespace uking::action

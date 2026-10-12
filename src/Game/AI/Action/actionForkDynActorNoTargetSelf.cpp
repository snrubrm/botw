#include "Game/AI/Action/actionForkDynActorNoTargetSelf.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

// Source namespace is unknown; constness follows the read-only accessor use.
bool sub_710001A9A4(const ksys::act::ActorConstDataAccess& accessor, ksys::act::BaseProc* proc);

namespace uking::action {

ForkDynActorNoTargetSelf::ForkDynActorNoTargetSelf(const InitArg& arg)
    : ForkEndByConditionBase(arg) {}

ForkDynActorNoTargetSelf::~ForkDynActorNoTargetSelf() = default;

bool ForkDynActorNoTargetSelf::init_(sead::Heap* heap) {
    return ForkEndByConditionBase::init_(heap);
}

void ForkDynActorNoTargetSelf::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEndByConditionBase::enter_(params);
}

void ForkDynActorNoTargetSelf::leave_() {
    ForkEndByConditionBase::leave_();
}

void ForkDynActorNoTargetSelf::loadParams_() {
    ForkEndByConditionBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ForkDynActorNoTargetSelf::calc_() {
    ForkEndByConditionBase::calc_();
}

bool ForkDynActorNoTargetSelf::m32() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    return sub_710001A9A4(accessor, mActor);
}

}  // namespace uking::action

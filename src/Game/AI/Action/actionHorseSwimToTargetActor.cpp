#include "Game/AI/Action/actionHorseSwimToTargetActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseSwimToTargetActor::HorseSwimToTargetActor(const InitArg& arg) : HorseSwim(arg) {}

HorseSwimToTargetActor::~HorseSwimToTargetActor() = default;

bool HorseSwimToTargetActor::init_(sead::Heap* heap) {
    return HorseSwim::init_(heap);
}

// NON_MATCHING: regalloc (the original rematerialises the accessor address for the destructor)
void HorseSwimToTargetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseSwim::enter_(params);
    auto* nav = mActor->m45();
    if (!nav) {
        setFailed();
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(mTargetActor_d, &accessor)) {
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        nav->sub_7100F75F8C(pos);
    } else {
        setFailed();
    }
}

void HorseSwimToTargetActor::leave_() {
    HorseSwim::leave_();
}

void HorseSwimToTargetActor::loadParams_() {
    HorseSwim::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseSwimToTargetActor::calc_() {
    HorseSwim::calc_();
}

}  // namespace uking::action

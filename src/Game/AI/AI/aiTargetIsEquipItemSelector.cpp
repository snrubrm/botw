#include "Game/AI/AI/aiTargetIsEquipItemSelector.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetIsEquipItemSelector::TargetIsEquipItemSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetIsEquipItemSelector::~TargetIsEquipItemSelector() = default;

bool TargetIsEquipItemSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetIsEquipItemSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    pack.addVec3(pos, "TargetPos", -1);
    if (ksys::act::isWeaponProfile(accessor))
        changeChild("武器族", &pack);
    else
        changeChild("非武器族", &pack);
}

void TargetIsEquipItemSelector::calc_() {
    auto* child = getCurrentChild();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    child->setDynamicParam(pos, "TargetPos");
    child->setDynamicParam(*mTargetActor_d, "TargetActor");
}

void TargetIsEquipItemSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetIsEquipItemSelector::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool TargetIsEquipItemSelector::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetIsEquipItemSelector::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai

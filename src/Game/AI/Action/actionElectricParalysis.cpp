#include "Game/AI/Action/actionElectricParalysis.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

ElectricParalysis::ElectricParalysis(const InitArg& arg) : StopBase(arg) {}

bool ElectricParalysis::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void ElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void ElectricParalysis::leave_() {
    StopBase::leave_();
}

void ElectricParalysis::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ElectricParalysis::calc_() {
    StopBase::calc_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(4))
        setFinished();
}

}  // namespace uking::action

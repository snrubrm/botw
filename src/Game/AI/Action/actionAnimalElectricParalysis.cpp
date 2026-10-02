#include "Game/AI/Action/actionAnimalElectricParalysis.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

AnimalElectricParalysis::AnimalElectricParalysis(const InitArg& arg)
    : HorseElectricParalysis(arg) {}

AnimalElectricParalysis::~AnimalElectricParalysis() = default;

bool AnimalElectricParalysis::init_(sead::Heap* heap) {
    return HorseElectricParalysis::init_(heap);
}

void AnimalElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseElectricParalysis::enter_(params);
    if (mASName_s.isEmpty())
        return;
    if (mActor->m132())
        mActor->m132()->_18.sub_7100E786F0(mASName_s);
    else
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void AnimalElectricParalysis::leave_() {
    HorseElectricParalysis::leave_();
    sub_71005DB434(mActor);
}

void AnimalElectricParalysis::loadParams_() {
    HorseElectricParalysis::loadParams_();
}

void AnimalElectricParalysis::calc_() {
    HorseElectricParalysis::calc_();
    if (_68 >= *mPauseDelayFrames_s)
        sub_71005DB41C(mActor);
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(4))
        setFinished();
}

}  // namespace uking::action

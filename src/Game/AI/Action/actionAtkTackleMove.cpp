#include "Game/AI/Action/actionAtkTackleMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AtkTackleMove::AtkTackleMove(const InitArg& arg) : TackleMove(arg) {}

AtkTackleMove::~AtkTackleMove() = default;

bool AtkTackleMove::init_(sead::Heap* heap) {
    return TackleMove::init_(heap);
}

void AtkTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleMove::enter_(params);
    mFlags.reset(Flag::Changeable);
    setDamageCallbackTiming(mActor, 4, &_98);
    m36();
}

void AtkTackleMove::leave_() {
    m37();
    sub_71005DA114(mActor, &_98);
    TackleMove::leave_();
}

void AtkTackleMove::loadParams_() {
    TackleMove::loadParams_();
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
}

void AtkTackleMove::calc_() {
    TackleMove::calc_();
}

}  // namespace uking::action

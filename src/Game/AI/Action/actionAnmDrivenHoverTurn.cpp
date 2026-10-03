#include "Game/AI/Action/actionAnmDrivenHoverTurn.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnmDrivenHoverTurn::AnmDrivenHoverTurn(const InitArg& arg) : AnmDrivenHoverBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmDrivenHoverTurn::~AnmDrivenHoverTurn() {
    ;
}

bool AnmDrivenHoverTurn::init_(sead::Heap* heap) {
    return AnmDrivenHoverBase::init_(heap);
}

void AnmDrivenHoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmDrivenHoverBase::enter_(params);
    sub_710073FA90(&_78, mActor);
    _9c = mActor->getAngVelocity().y;
}

void AnmDrivenHoverTurn::leave_() {
    AnmDrivenHoverBase::leave_();
}

void AnmDrivenHoverTurn::loadParams_() {
    AnmDrivenHoverBase::loadParams_();
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mParams.mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void AnmDrivenHoverTurn::calc_() {
    AnmDrivenHoverBase::calc_();
}

}  // namespace uking::action

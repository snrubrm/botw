#include "Game/AI/Action/actionAnmBlownOffBackward.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

AnmBlownOffBackward::AnmBlownOffBackward(const InitArg& arg) : AnmBlownOff(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmBlownOffBackward::~AnmBlownOffBackward() {
    ;
}

bool AnmBlownOffBackward::init_(sead::Heap* heap) {
    return AnmBlownOff::init_(heap);
}

void AnmBlownOffBackward::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmBlownOff::enter_(params);
    sub_710073FA90(&_a4, mActor);
}

void AnmBlownOffBackward::leave_() {
    AnmBlownOff::leave_();
}

void AnmBlownOffBackward::loadParams_() {
    AnmBlownOff::loadParams_();
}

void AnmBlownOffBackward::calc_() {
    AnmBlownOff::calc_();
}

}  // namespace uking::action

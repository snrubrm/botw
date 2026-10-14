#include "Game/Actor/Action/actionAnmKnockBackShock.h"

namespace uking::action {

AnmKnockBackShock::AnmKnockBackShock(const InitArg& arg) : SimpleKnockBackShock(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmKnockBackShock::~AnmKnockBackShock() {
    ;
}

bool AnmKnockBackShock::init_(sead::Heap* heap) {
    return SimpleKnockBackShock::init_(heap);
}

void AnmKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleKnockBackShock::enter_(params);
    mFlags.set(Flag::Changeable);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void AnmKnockBackShock::leave_() {
    SimpleKnockBackShock::leave_();
}

void AnmKnockBackShock::loadParams_() {
    SimpleKnockBackShock::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void AnmKnockBackShock::calc_() {
    SimpleKnockBackShock::calc_();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action

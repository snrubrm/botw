#include "Game/AI/Action/actionSubAnmKnockBackShock.h"

namespace uking::action {

SubAnmKnockBackShock::SubAnmKnockBackShock(const InitArg& arg) : AnmKnockBackShock(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SubAnmKnockBackShock::~SubAnmKnockBackShock() {
    ;
}

bool SubAnmKnockBackShock::init_(sead::Heap* heap) {
    return AnmKnockBackShock::init_(heap);
}

void SubAnmKnockBackShock::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmKnockBackShock::enter_(params);
    playAS(mSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
}

void SubAnmKnockBackShock::leave_() {
    if (!mLeaveSubAS_s.isEmpty())
        playAS(mLeaveSubAS_s.cstr(), false, 0, *mSubASSlot_s, -1.0f);
    AnmKnockBackShock::leave_();
}

void SubAnmKnockBackShock::loadParams_() {
    AnmKnockBackShock::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

void SubAnmKnockBackShock::calc_() {
    AnmKnockBackShock::calc_();
}

}  // namespace uking::action

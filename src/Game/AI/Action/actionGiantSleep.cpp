#include "Game/AI/Action/actionGiantSleep.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GiantSleep::GiantSleep(const InitArg& arg) : Sleep(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantSleep::~GiantSleep() {
    ;
}

bool GiantSleep::init_(sead::Heap* heap) {
    return Sleep::init_(heap);
}

void GiantSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    Sleep::enter_(params);
}

void GiantSleep::leave_() {
    Sleep::leave_();
}

void GiantSleep::loadParams_() {
    Sleep::loadParams_();
    getStaticParam(&mRidableRigidBodyName_s, "RidableRigidBodyName");
    getStaticParam(&mASName_s, "ASName");
}

void GiantSleep::calc_() {
    Sleep::calc_();
}

// NON_MATCHING: the original computes &rideable->_18 after the cstr() call; regalloc
void GiantSleep::m32() {
    if (mASName_s.isEmpty())
        return;
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0(mASName_s.cstr());
    else
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action

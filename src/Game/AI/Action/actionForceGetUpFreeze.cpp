#include "Game/AI/Action/actionForceGetUpFreeze.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ForceGetUpFreeze::ForceGetUpFreeze(const InitArg& arg) : Freeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForceGetUpFreeze::~ForceGetUpFreeze() {
    ;
}

bool ForceGetUpFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void ForceGetUpFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void ForceGetUpFreeze::leave_() {
    Freeze::leave_();
}

void ForceGetUpFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpFreeze::calc_() {
    if (_88 == 2) {
        Freeze::calc_();
        return;
    }
    if (_88 == 1) {
        ksys::act::sub_7100EE5980(mActor, sead::Vector3f::zero);
        ksys::act::sub_7100EE5A14(mActor, sead::Vector3f::zero);
        ++_88;
    } else {
        _88 = 1;
    }
}

}  // namespace uking::action

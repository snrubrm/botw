#include "Game/AI/Action/actionSimpleGrabWithAS.h"

namespace uking::action {

SimpleGrabWithAS::SimpleGrabWithAS(const InitArg& arg) : SimpleGrabWithASBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SimpleGrabWithAS::~SimpleGrabWithAS() {
    ;
}

void SimpleGrabWithAS::loadParams_() {
    SimpleGrabWithASBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SimpleGrabWithAS::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action

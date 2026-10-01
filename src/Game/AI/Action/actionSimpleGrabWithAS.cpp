#include "Game/AI/Action/actionSimpleGrabWithAS.h"

namespace uking::action {

SimpleGrabWithAS::SimpleGrabWithAS(const InitArg& arg) : SimpleGrabWithASBase(arg) {}

SimpleGrabWithAS::~SimpleGrabWithAS() = default;

void SimpleGrabWithAS::loadParams_() {
    SimpleGrabWithASBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SimpleGrabWithAS::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action

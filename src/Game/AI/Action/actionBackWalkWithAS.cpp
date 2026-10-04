#include "Game/AI/Action/actionBackWalkWithAS.h"

namespace uking::action {

BackWalkWithAS::BackWalkWithAS(const InitArg& arg) : BackWalkEx(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BackWalkWithAS::~BackWalkWithAS() {
    ;
}

void BackWalkWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void BackWalkWithAS::loadParams_() {
    BackWalkEx::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BackWalkWithAS::calc_() {
    BackWalkEx::calc_();
    if (isFinishedAS(0, 0) && !mASName_s.isEmpty())
        setFinished();
}

void BackWalkWithAS::sub_71000B6D2C() {
    if (isFinishedAS(0, 0) && !mASName_s.isEmpty())
        setFinished();
}

}  // namespace uking::action

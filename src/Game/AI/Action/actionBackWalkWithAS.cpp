#include "Game/AI/Action/actionBackWalkWithAS.h"

namespace uking::action {

BackWalkWithAS::BackWalkWithAS(const InitArg& arg) : BackWalkEx(arg) {}

BackWalkWithAS::~BackWalkWithAS() = default;

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
}

}  // namespace uking::action

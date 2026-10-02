#include "Game/AI/AI/aiWeaponSubTypeSelect.h"

namespace uking::ai {

WeaponSubTypeSelect::WeaponSubTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponSubTypeSelect::~WeaponSubTypeSelect() = default;

void WeaponSubTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005F18C0(params);
}

void WeaponSubTypeSelect::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void WeaponSubTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponSubTypeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai

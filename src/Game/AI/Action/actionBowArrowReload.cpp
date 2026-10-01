#include "Game/AI/Action/actionBowArrowReload.h"

namespace uking::action {

BowArrowReload::BowArrowReload(const InitArg& arg) : BindAction(arg) {}

void BowArrowReload::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    mFlags.set(Flag::Changeable);
}

void BowArrowReload::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action

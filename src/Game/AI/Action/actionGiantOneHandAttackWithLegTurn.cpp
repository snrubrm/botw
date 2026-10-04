#include "Game/AI/Action/actionGiantOneHandAttackWithLegTurn.h"

namespace uking::action {

GiantOneHandAttackWithLegTurn::GiantOneHandAttackWithLegTurn(const InitArg& arg)
    : GiantOneHandActionWithLegTurn(arg) {}

GiantOneHandAttackWithLegTurn::~GiantOneHandAttackWithLegTurn() = default;

bool GiantOneHandAttackWithLegTurn::init_(sead::Heap* heap) {
    return GiantOneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandAttackWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantOneHandActionWithLegTurn::enter_(params);
}

void GiantOneHandAttackWithLegTurn::leave_() {
    GiantOneHandActionWithLegTurn::leave_();
}

void GiantOneHandAttackWithLegTurn::loadParams_() {
    GiantOneHandActionWithLegTurn::loadParams_();
    _280.sub_71007050F0(this);
}

void GiantOneHandAttackWithLegTurn::calc_() {
    GiantOneHandActionWithLegTurn::calc_();
}

void GiantOneHandAttackWithLegTurn::m32(const sead::SafeString* name) {
    _280.sub_7100705138(name);
}

void GiantOneHandAttackWithLegTurn::m33() {
    _280.sub_7100705188();
}

}  // namespace uking::action

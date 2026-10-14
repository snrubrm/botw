#include "Game/Actor/Action/actionGiantOneHandPunchWithLegTurn.h"

namespace uking::action {

GiantOneHandPunchWithLegTurn::GiantOneHandPunchWithLegTurn(const InitArg& arg)
    : OneHandActionWithLegTurn(arg) {}

GiantOneHandPunchWithLegTurn::~GiantOneHandPunchWithLegTurn() = default;

bool GiantOneHandPunchWithLegTurn::init_(sead::Heap* heap) {
    return OneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandPunchWithLegTurn::leave_() {
    OneHandActionWithLegTurn::leave_();
}

void GiantOneHandPunchWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    OneHandActionWithLegTurn::enter_(params);
    _280.sub_7100704944();
}

void GiantOneHandPunchWithLegTurn::loadParams_() {
    OneHandActionWithLegTurn::loadParams_();
    _280.sub_7100704D84(this);
}

void GiantOneHandPunchWithLegTurn::calc_() {
    OneHandActionWithLegTurn::calc_();
    _280.sub_710070494C();
}

void GiantOneHandPunchWithLegTurn::m32(const sead::SafeString* name) {
    _280.sub_7100704F1C(name);
}

void GiantOneHandPunchWithLegTurn::m33() {
    _280.sub_710070507C();
}

}  // namespace uking::action

#include "Game/AI/Action/actionFall.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

Fall::Fall(const InitArg& arg) : ActionEx(arg) {}

Fall::~Fall() = default;

void Fall::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Fall::leave_() {
    ActionEx::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x40000);
}

void Fall::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mASName_s, "ASName");
}

void Fall::calc_() {
    ActionEx::calc_();
}

bool Fall::isChangeable() const {
    return false;
}

}  // namespace uking::action

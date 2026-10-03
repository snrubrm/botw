#include "Game/AI/Action/actionPlayerGuardSlip.h"
#include <cstring>

namespace uking::action {

PlayerGuardSlip::PlayerGuardSlip(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mBaseInitSpeedNSword_s, 0, 0x80);
}

void PlayerGuardSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardSlip::leave_() {}

void PlayerGuardSlip::loadParams_() {
    getStaticParam(&mBaseInitSpeedNSword_s, "BaseInitSpeedNSword");
    getStaticParam(&mBaseInitSpeedLSword_s, "BaseInitSpeedLSword");
    getStaticParam(&mBaseInitSpeedSpear_s, "BaseInitSpeedSpear");
    getStaticParam(&mBaseInitSpeedOther_s, "BaseInitSpeedOther");
    getStaticParam(&mAddSpeedNSword_s, "AddSpeedNSword");
    getStaticParam(&mAddSpeedLSword_s, "AddSpeedLSword");
    getStaticParam(&mAddSpeedSpear_s, "AddSpeedSpear");
    getStaticParam(&mAddSpeedOther_s, "AddSpeedOther");
    getStaticParam(&mMaxSpeedNSword_s, "MaxSpeedNSword");
    getStaticParam(&mMaxSpeedLSword_s, "MaxSpeedLSword");
    getStaticParam(&mMaxSpeedSpear_s, "MaxSpeedSpear");
    getStaticParam(&mMaxSpeedOther_s, "MaxSpeedOther");
    getStaticParam(&mDecSpeedNSword_s, "DecSpeedNSword");
    getStaticParam(&mDecSpeedLSword_s, "DecSpeedLSword");
    getStaticParam(&mDecSpeedSpear_s, "DecSpeedSpear");
    getStaticParam(&mDecSpeedOther_s, "DecSpeedOther");
}

void PlayerGuardSlip::calc_() {
    PlayerAction::calc_();
}

bool PlayerGuardSlip::isChangeable() const {
    return _1c;
}

}  // namespace uking::action

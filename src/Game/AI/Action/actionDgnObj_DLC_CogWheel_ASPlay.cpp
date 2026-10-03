#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_ASPlay.h"
#include "Game/gameGearMgr.h"

namespace uking::action {

DgnObj_DLC_CogWheel_ASPlay::DgnObj_DLC_CogWheel_ASPlay(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_ASPlay::~DgnObj_DLC_CogWheel_ASPlay() = default;

bool DgnObj_DLC_CogWheel_ASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CogWheel_ASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = true;
}

void DgnObj_DLC_CogWheel_ASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CogWheel_ASPlay::loadParams_() {}

void DgnObj_DLC_CogWheel_ASPlay::calc_() {
    if (auto* mgr = GearMgr::instance()) {
        if (mgr->sub_7100669B48()) {
            m32();
            _1c = false;
        }
    }
}

void DgnObj_DLC_CogWheel_ASPlay::m32() {
    auto* mgr = GearMgr::instance();
    if (!mgr)
        return;
    if (!(mgr->_10a4 & 1) && !_1c)
        return;
    if (mgr->_10b0[mgr->_2c ^ 1] & 1)
        playAS("Left", false, 0, 0, -1.0f);
    else
        playAS("Right", false, 0, 0, -1.0f);
}

}  // namespace uking::action

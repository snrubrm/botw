#include "Game/AI/AI/aiDgnObj_DLC_CWRotDirSwitch.h"
#include "Game/gameGearMgr.h"

namespace uking::ai {

DgnObj_DLC_CWRotDirSwitch::DgnObj_DLC_CWRotDirSwitch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CWRotDirSwitch::~DgnObj_DLC_CWRotDirSwitch() = default;

bool DgnObj_DLC_CWRotDirSwitch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_CWRotDirSwitch::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("Off");
}

void DgnObj_DLC_CWRotDirSwitch::calc_() {
    auto* gear_mgr = GearMgr::instance();
    if (!gear_mgr || !mActor || !(gear_mgr->_10a4 & 8))
        return;

    if (gear_mgr->_10a8[gear_mgr->_28 ^ 1] & 1) {
        if (isCurrentChild("Off"))
            changeChild("On");
    } else {
        if (isCurrentChild("On"))
            changeChild("Off");
    }
}

void DgnObj_DLC_CWRotDirSwitch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_CWRotDirSwitch::loadParams_() {}

}  // namespace uking::ai

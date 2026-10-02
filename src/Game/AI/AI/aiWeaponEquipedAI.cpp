#include "Game/AI/AI/aiWeaponEquipedAI.h"
#include "Game/AI/aiXlinkHandle.h"

namespace uking::ai {

WeaponEquipedAI::WeaponEquipedAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipedAI::~WeaponEquipedAI() {
    sub_7100E1DC50();
}

void WeaponEquipedAI::sub_7100E1DC50() {
    if (_40.getEvent() && _40.getEvent()->getCreateId() == u32(_40.getCreateId()) &&
        !_40.getEvent()->getBitFlag().isOnBit(4)) {
        xlink::fade(_40, -1);
    }
}

void WeaponEquipedAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponEquipedAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai

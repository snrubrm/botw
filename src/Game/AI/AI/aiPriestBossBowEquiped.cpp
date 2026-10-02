#include "Game/AI/AI/aiPriestBossBowEquiped.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

PriestBossBowEquiped::PriestBossBowEquiped(const InitArg& arg) : BowEquiped(arg) {}

PriestBossBowEquiped::~PriestBossBowEquiped() = default;

bool PriestBossBowEquiped::init_(sead::Heap* heap) {
    return BowEquiped::init_(heap);
}

void PriestBossBowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    BowEquiped::enter_(params);
}

void PriestBossBowEquiped::calc_() {
    if (sub_710033788C() && isCurrentChild("装備")) {
        sead::FixedSafeString<32> arrow_name;
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (weapon)
            weapon->bowGetArrowName(&arrow_name);
        if (_38.isAllocatedOrFailed() && _60 != arrow_name) {
            _38.deleteProc();
            weapon->_e50 &= ~0x80;
            _60 = arrow_name;
        }
    } else if (!_60.isEmpty() && isCurrentChild("射撃")) {
        _60.clear();
    }
    BowEquiped::calc_();
}

void PriestBossBowEquiped::leave_() {
    BowEquiped::leave_();
}

void PriestBossBowEquiped::loadParams_() {}

}  // namespace uking::ai

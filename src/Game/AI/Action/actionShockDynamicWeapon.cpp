#include "Game/AI/Action/actionShockDynamicWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

ShockDynamicWeapon::ShockDynamicWeapon(const InitArg& arg) : Shock(arg) {}

ShockDynamicWeapon::~ShockDynamicWeapon() = default;

void ShockDynamicWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    Shock::enter_(params);
    _88 = false;
}

void ShockDynamicWeapon::leave_() {
    if (!_88)
        sub_710024DA0C();
    Shock::leave_();
}

void ShockDynamicWeapon::loadParams_() {
    Shock::loadParams_();
    getDynamicParam(&mDropWeapon_d, "DropWeapon");
    getDynamicParam(&mDropDir_d, "DropDir");
}

void ShockDynamicWeapon::calc_() {
    Shock::calc_();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, *mASSlot_s, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_710024DA0C();
    }
}

void ShockDynamicWeapon::m33(const sead::Vector3f* velocity) {}

bool ShockDynamicWeapon::m32() {
    return mDropWeapon_d->hasProc();
}

}  // namespace uking::action

#include "Game/AI/Action/actionForkASTrgDeleteEquip.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgDeleteEquip::ForkASTrgDeleteEquip(const InitArg& arg) : ForkASTrgDelete(arg) {}

ForkASTrgDeleteEquip::~ForkASTrgDeleteEquip() = default;

void ForkASTrgDeleteEquip::loadParams_() {
    ForkASTrgDelete::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkASTrgDeleteEquip::m32() {
    if (auto* weapon = sub_71005DA374(mActor, *mWeaponIdx_s))
        weapon->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

}  // namespace uking::action

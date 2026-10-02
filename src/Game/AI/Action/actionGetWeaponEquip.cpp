#include "Game/AI/Action/actionGetWeaponEquip.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

GetWeaponEquip::GetWeaponEquip(const InitArg& arg) : GetItem(arg) {}

void GetWeaponEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItem::enter_(params);
    if (auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(mActor)) {
        weapon->m182();
        weapon->emitDeadUpLifeZeroAndSetRevival();
        weapon->unlinkPlacementObj();
        weapon->resetMubinBymlIter();
    }
    ksys::act::disableAllAttClients(mActor);
}

void GetWeaponEquip::calc_() {}

}  // namespace uking::action

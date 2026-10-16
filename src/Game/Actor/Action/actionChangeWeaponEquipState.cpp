#include "Game/Actor/Action/actionChangeWeaponEquipState.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"

namespace uking::action {

ChangeWeaponEquipState::ChangeWeaponEquipState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeWeaponEquipState::~ChangeWeaponEquipState() = default;

bool ChangeWeaponEquipState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ChangeWeaponEquipState::oneShot_() {
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    if (!npc)
        return false;

    if (mEquipState_d == "Hold") {
        npc->_1060 = 0;
        auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(
            npc->getWeapons()->mWeapons[0].link.getProc(nullptr, nullptr));
        if (sead::IsDerivedFrom<act::Weapon>(weapon)) {
            const sead::SafeString type = weapon->getParam()
                                              ->getRes()
                                              .mGParamList->getWeaponCommon()
                                              ->mNPCWeaponType.ref();
            if (type.isEmpty())
                mActor->getASList()->goLimpFromHeadShotMaybe(44, weapon->getProfile(), 0);
            else
                mActor->getASList()->goLimpFromHeadShotMaybe(44, type, 0);
            return true;
        }
        mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
        return true;
    }
    if (mEquipState_d == "Equip") {
        npc->_1060 = 1;
        mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
        return true;
    }
    if (mEquipState_d == "Invisible") {
        npc->_1060 = 2;
        mActor->getASList()->goLimpFromHeadShotMaybe(44, "", 0);
        return true;
    }
    return false;
}

void ChangeWeaponEquipState::loadParams_() {
    getDynamicParam(&mEquipState_d, "EquipState");
}

}  // namespace uking::action

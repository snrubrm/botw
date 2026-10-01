#include "Game/AI/Action/actionUnk_71023c8378.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

Unk_71023c8378::Unk_71023c8378(ksys::act::ai::ActionBase* owner) : Unk_71023c8418(owner) {}

// NON_MATCHING: the original loads *mWeaponIdx_s before calling getWeapons()
void Unk_71023c8378::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mOwner->getActor())) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(
            actor->getWeapons()->getEquippedWeapon(*mWeaponIdx_s));
        if (weapon) {
            mOwner->getActor()->getASList()->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(),
                                                                      0);
            sub_71005D787C(mOwner->getActor(), *mWeaponIdx_s, uking::act::Unk_71002eda38(1));
        }
    }
    Unk_71023c8418::enter_(params);
}

void Unk_71023c8378::m13() {
    getDynamicParam(const_cast<int**>(&mWeaponIdx_s), "DynWeaponIdx");
}

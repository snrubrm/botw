#include "Game/Actor/aiEquipDisplayUtil.h"
#include <gsys/gsysModel.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

bool sub_7100701774(ksys::act::Actor* weapon, s32 slot) {
    if (slot != 0)
        return true;
    auto* typed_weapon = sead::DynamicCast<uking::act::Weapon>(weapon);
    return typed_weapon && typed_weapon->isMasterSword();
}

bool sub_710070181C(ksys::act::Actor* actor, const sead::SafeString& bone_name) {
    auto* model = actor->getModel();
    return model && model->searchBone(bone_name).isValid();
}

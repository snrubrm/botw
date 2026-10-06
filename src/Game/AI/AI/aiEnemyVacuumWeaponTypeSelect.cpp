#include "Game/AI/AI/aiEnemyVacuumWeaponTypeSelect.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"

namespace uking::ai {

EnemyVacuumWeaponTypeSelect::EnemyVacuumWeaponTypeSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
EnemyVacuumWeaponTypeSelect::~EnemyVacuumWeaponTypeSelect() {
    ;
}

bool EnemyVacuumWeaponTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyVacuumWeaponTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* parts = mActor->m101()) {
        auto& weapon = parts->getActorPartsActor(mPartsKey_s);
        if (weapon.hasProc() && ksys::act::isWeaponProfile(&weapon)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&weapon, &accessor);
            if (auto* list = accessor.getGParamList()) {
                if (list->getWeaponCommon()->mIsBoomerang.ref()) {
                    changeChild("ブーメラン", params);
                    return;
                }
            }
            switch (sub_71002F0258(accessor)) {
            case 0:
                changeChild("小剣", params);
                return;
            case 1:
                changeChild("大剣", params);
                return;
            case 2:
                changeChild("槍", params);
                return;
            case 3:
                changeChild("弓", params);
                return;
            case 4:
                changeChild("盾", params);
                return;
            }
        }
    }
    changeChild("その他", params);
}

void EnemyVacuumWeaponTypeSelect::calc_() {}

void EnemyVacuumWeaponTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyVacuumWeaponTypeSelect::loadParams_() {
    getStaticParam(&mPartsKey_s, "PartsKey");
}

}  // namespace uking::ai

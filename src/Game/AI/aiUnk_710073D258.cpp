#include "Game/AI/aiUnk_710073D258.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/Vibration.h"

bool sub_710073BCB4(const sead::SafeString& weapon_type) {
    return !uking::ui::PauseMenuDataMgr::instance()->isWeaponSectionFull(weapon_type);
}

void sub_710073D258() {
    const bool value = ksys::gdt::getBoolByKey("Fire_Relic_PlayerWhistle");
    ksys::gdt::setBoolByKey(!value, "Fire_Relic_PlayerWhistle");
}

void sub_710073D2B4(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6,
                    const sead::Vector3f& a7, u8 a8) {
    const ksys::Vibration::Unk2 request(a1, a2, a3, a4, a5, a6, a7, a8);
    ksys::Vibration::instance()->sub_71010BB428(request);
}

s32 getEnemyRank(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.getEnemyRank();
}

void* sub_710073D4D4(ksys::act::Actor* actor, const sead::SafeString& name) {
    if (auto* root = actor->getRootAi()) {
        void* value = nullptr;
        if (root->getAITreeVariable(&value, name))
            return *static_cast<void**>(value);
    }
    return nullptr;
}

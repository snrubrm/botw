#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/actWeapon.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

using ksys::act::Unk_71024dc858;
using ksys::act::Unk_71024dc978;

bool Unk_7102451358::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.sub_7100D10FB8();
}

bool Unk_71024513d0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::isDoor(&target->mLink);
}

bool Unk_7102451448::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isEnemyProfile(&target->mLink))
        return true;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::AwarenessEnemySearchTarget);
}

bool Unk_7102451538::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::ExplosivesEnemyAI);
}

bool Unk_7102451588::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.getProfile() == "Horse";
}

bool Unk_7102451628::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isPlayerProfile(&target->mLink))
        return true;
    return ksys::act::isNPCProfile(&target->mLink);
}

bool Unk_7102451678::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::isPlayerProfile(&target->mLink);
}

bool Unk_71024516a0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return ksys::act::hasTag(&target->mLink, ksys::act::tags::IsPressBreakByEnNPC);
}

bool Unk_7102451768::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    return target->mLink.getId() == _28;
}

bool Unk_7102451830::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (!target->mLink.hasProc() || !ksys::act::isAlive(&target->mLink))
        return false;
    if (ksys::act::isEnemyProfile(&target->mLink))
        return true;
    return ksys::act::isWolfOrBear(&target->mLink);
}

bool Unk_7102451600::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    if (!accessor.isDerivedFrom<uking::act::NPC>())
        return false;
    if (_28 && !accessor.sub_7100022ED8())
        return false;
    if (_29 && accessor.sub_7100022FD0())
        return false;

    return true;




}

bool Unk_71024513f8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return sub_710073697C(&target->mLink, "IsPlayerPut") ||
           ksys::act::isWeaponProfile(&target->mLink) ||
           accessor.getName().findIndex("RemoteBomb") != -1;

}

bool Unk_7102451498::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    if (_30 && accessor.getProfile() == "Player")
        return true;
    if (_31 && accessor.getProfile() == "WolfLink")
        return true;
    return false;
}

bool Unk_7102451560::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (!ksys::act::isEnemyProfile(&target->mLink))
        return false;
    if (_28 && _28->sub_71002DC9E8(target->mLink, 0x20, false))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.sub_7100D10E6C(25) && !accessor.sub_7100D10FB8();
}

bool Unk_71024514c0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (_28->getParam()->getRes().mGParamList->getEnemyRace()->mTargetActorType.ref().isEmpty())
        return false;

    auto* link = &target->mLink;
    if (sub_71005D777C(link))
        return false;
    if (ksys::act::hasTag(link, ksys::act::tags::EnemyNotTarget))
        return false;

    if (ksys::act::isPlayerProfile(link)) {
        if (_30 & 1)
            return false;
        if ((_30 & 4) && enemyTeamStuff(_28, link))
            return false;
    } else if (_30 & 2) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.getProfile() != "WolfLink")
            return false;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (sub_71007399B4(_28, accessor))
        return true;
    return sub_7100739A10(_28, accessor.getProfile());
}

bool Unk_7102451470::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isNotLivingCreature(&target->mLink))
        return true;
    return Unk_71024514c0::m2(entry);
}

bool Unk_7102451510::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    if (accessor.getSpAttackTarget().hasProcById(_28))
        return false;
    return Unk_71024514c0::m2(entry);
}

bool Unk_71024517e0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (!ksys::act::isWeaponProfile(&target->mLink))
        return false;
    ksys::act::acc::Weapon accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    if (accessor.sub_71002EF980())
        return false;
    if (accessor.hasTag(ksys::act::tags::CanPullOutGiantObject))
        return false;
    return !accessor.sub_71002F1228();
}

bool Unk_7102451808::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::hasTag(&target->mLink, ksys::act::tags::EnemyNotPick))
        return false;
    return Unk_71024517e0::m2(entry);
}

// NON_MATCHING: the original keeps a cleanup flag for the failed-acquire path instead of
// duplicating the accessor destructor call; loads of the translation z/x swapped
bool Unk_71024516f0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::isStalfosParts(&target->mLink)) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&target->mLink, &accessor)) {
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            if (sead::Mathf::abs(_34.y - pos.y) <= _30) {
                if (sead::Mathf::square(_34.x - pos.x) + sead::Mathf::square(_34.z - pos.z) <= _28)
                    return sead::Mathf::square(_40.x - pos.x) + sead::Mathf::square(_40.z - pos.z) <= _2c;
            }
            return false;
        }
    }
    return false;



}

bool Unk_71024515b0::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    return accessor.sub_7100D11F10();
}

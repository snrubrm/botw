#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/actWeapon.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"

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

bool Unk_7102451740::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return target->mLink == _28;
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

Unk_7102451498::Unk_7102451498(ksys::act::Actor* actor) : _28(actor) {
    const auto* race = actor->getParam()->getRes().mGParamList->getEnemyRace();
    const sead::SafeString& types = race->mTargetActorType.ref();
    if (types.isEmpty())
        return;
    sead::FixedSafeString<32> type;
    for (auto it = types.tokenBegin(","); types.tokenEnd(",") != it; ++it) {
        it.get(&type);
        if (type == "Player")
            _30 = true;
        else if (type == "WolfLink")
            _31 = true;
    }
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

bool Unk_71024514e8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    auto* link = &target->mLink;
    if (ksys::act::hasTag(link, ksys::act::tags::EnemyNotTarget))
        return false;
    if (target->m5(1))
        return true;

    const bool not_living = ksys::act::isNotLivingCreature(link);
    if (!not_living) {
        ksys::act::acc::PlayerBase accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.getSpAttackTarget().hasProcById(_28))
            return false;
    }

    if (_30 & 0x28) {
        if (target->m5(8)) {
            if (target->m5(8) && (_30 & 0x20))
                return false;
        } else {
            ksys::act::acc::Bullet accessor;
            ksys::act::acquireActor(link, &accessor);
            if (accessor.isDerivedFrom<ksys::act::Bullet>()) {
                if (target->m5(8) || ksys::act::isPlayerProfile(&accessor.sub_71000056E4())) {
                    if (_30 & 0x20)
                        return false;
                } else if (_30 & 8) {
                    return false;
                }
            }
        }
    }

    if ((_30 & 4) && enemyTeamStuff(_28, link))
        return false;
    if ((_30 & 0x10) && ksys::act::isPreyOrSwarm(link))
        return false;

    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (uking::act::Unk_7100e8b2b8* rideable = accessor.getHorseOptions()) {
            const uking::act::Unk_7100e8b2b8::Unk8 type = rideable->_8 & 0xff;
            switch (type) {
            case uking::act::Unk_7100e8b2b8::Unk8::_3:
                if (sub_7100739A10(_28, "NPC") || sub_7100739A10(_28, "ClerkNPC"))
                    return true;
                // fallthrough
            case uking::act::Unk_7100e8b2b8::Unk8::_1:
                if (sub_7100739A10(_28, "Player")) {
                    if ((_30 & 4) && enemyTeamStuff(_28, &ksys::act::PlayerInfo::getSomeProcLink()))
                        return false;
                    return true;
                }
                break;
            case uking::act::Unk_7100e8b2b8::Unk8::_2:
                if (sub_7100739A10(_28, "Enemy"))
                    return true;
                break;
            default:
                break;
            }
        }
    }

    if (_38 && *_38 == *link) {
        if (not_living)
            return true;
    } else if (auto* unk = sub_71005D9E64(_28)) {
        const bool result = unk->sub_71002DC9E8(*link, 4, false);
        if (not_living || result)
            return !result;
    } else if (not_living) {
        return true;
    }
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

// NON_MATCHING: same stores and loads; the translation copy is not interleaved with the multiplications and is
// merged into an stp.
void Unk_71024516f0::sub_71007470B8(ksys::act::Actor* actor, f32 a, f32 b, f32 height) {
    actor->getHomePos(&_40);
    _34 = actor->getMtx().getTranslation();
    _28 = a * a;
    _2c = b * b;
    _30 = height;
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

bool Unk_7102451380::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target->mLink, &accessor);
    if (!sub_7100739E24(_28, &target->mLink, -1))
        return false;
    return sub_710073697C(&target->mLink, "IsPlayerPut") ||
           sub_71007369D0(&target->mLink, "IsDrop") ||
           ksys::act::isWeaponProfile(&target->mLink) || accessor.sub_7100D10E6C(26);
}

bool Unk_7102451420::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return sub_7100739E24(_28, &target->mLink, -1) &&
           sub_71007369D0(&target->mLink, "IsDrop");
}

bool Unk_71024515d8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    return sub_71005DA304(&target->mLink);
}

bool Unk_71024517b8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    auto* link = &target->mLink;

    if (ksys::act::isWeaponProfile(link)) {
        ksys::act::acc::Weapon accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.sub_71002EF980())
            return false;
        return !accessor.hasTag(ksys::act::tags::CanPullOutGiantObject);
    }

    if (ksys::act::isGrabAttClientEnabled(_28, link)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        ksys::res::AttCheck_Unk1 arg;
        arg._35 = true;
        arg._34 = _30;
        arg._36 = true;
        if (!accessor.sub_7100D13AE4("Grab", _28, &arg, false))
            return false;
        return !accessor.sub_7100D10E6C(30);
    }

    if (!_31)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_7100D10E6C(30);
}

bool Unk_71024516c8::m2(Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<Unk_71024dc858>(entry);
    if (!target)
        return false;
    auto* link = &target->mLink;

    if (!ksys::act::isGrabAttClientEnabled(_28, link))
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.sub_7100D10FB8())
        return false;
    if (accessor.getProfile() == "Prey")
        return false;
    if (ksys::act::isEnemyProfile(_28) && !accessor.sub_71006E3E00())
        return false;
    if (accessor.sub_7100D131D0(-1) == 1 && accessor.isDisableFreezeLift())
        return false;
    if (accessor.sub_7100D131D0(-1) == 2 && accessor.isDisableBurnLift())
        return false;

    ksys::act::acc::Bullet bullet;
    ksys::act::acquireActor(link, &bullet);
    const auto& owner = bullet.sub_71000056E4();
    if (owner.hasProc() && owner.hasProcById(_28))
        return false;

    ksys::res::AttCheck_Unk1 arg;
    arg._35 = true;
    arg._34 = _30;
    arg._36 = true;
    if (!accessor.sub_7100D13AE4("Grab", _28, &arg, false))
        return false;
    return !accessor.sub_7100D10E6C(30);
}

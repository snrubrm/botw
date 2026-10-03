#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace ksys::act {

ActorWeapons::ActorWeapons(Actor* actor) : mActor(actor) {}

ActorWeapons::~ActorWeapons() = default;

WeaponBase* ActorWeapons::getEquippedWeapon(int idx) const {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (!weapon)
        return nullptr;
    return weapon->isCalc() ? weapon : nullptr;
}

void ActorWeapons::resetBaseProcLinkForActor(BaseProc* proc) {
    if (!proc)
        return;
    if (!BaseProcMgr::instance()->isAccessingProcSafe(mActor, nullptr))
        return;
    s32 idx = -1;
    for (s32 i = 0; i < mWeapons.size(); ++i) {
        if (mWeapons[i].link.hasProcById(proc)) {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        return;
    mWeapons[idx].link.reset();
}

// NON_MATCHING: the original recomputes the address of mWeapons[idx].link after the call (register
// allocation: x26 holds the clamped index); ours keeps the address
bool ActorWeapons::dropWeapon(int idx, const sead::Vector3f& pos, bool a2, bool a3, void* a4,
                              bool a5) {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (weapon && weapon->isCalc()) {
        weapon->m175(pos, a2, a3, a4, a5);
        mWeapons[idx].link.reset();
    }
    return true;
}

void ActorWeapons::sleep(BaseProc::SleepWakeReason reason) {
    for (auto& weapon : mWeapons) {
        ActorConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        accessor.sleep(reason);
    }
}

void ActorWeapons::wakeUp(BaseProc::SleepWakeReason reason) {
    for (auto& weapon : mWeapons) {
        ActorConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        accessor.wakeUp(reason);
    }
}

// NON_MATCHING: the original keeps the first cast as a branch to a shared `x19 = null` block; ours
// if-converts it to a csel
void sub_7100EFA810(ActorConstDataAccess* accessor) {
    BaseProc* proc = accessor->getProc();
    Actor* actor = nullptr;
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        actor = static_cast<Actor*>(proc);
    if (auto* weapon = sead::DynamicCast<WeaponBase>(actor))
        weapon->m215();
}

void ActorWeapons::x() {
    for (auto& weapon : mWeapons) {
        ActorConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        sub_7100EFA810(&accessor);
    }
}

bool ActorWeapons::dropAllWeapons(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) {
    for (int i = 0; i < 6; ++i) {
        auto* actor = sead::DynamicCast<WeaponBase>(mWeapons[i].link.getProc(nullptr, nullptr));
        if (actor && actor->isCalc()) {
            actor->m175(pos, a2, a3, a4, a5);
            mWeapons[i].link.reset();
        }
    }
    return true;
}

bool ActorWeapons::dropAllWeaponsToTarget(const sead::Vector3f& target, const sead::Vector3f& pos,
                                          bool a3, bool a4, void* a5, bool a6) {
    for (int i = 0; i < 6; ++i) {
        auto* actor = sead::DynamicCast<WeaponBase>(mWeapons[i].link.getProc(nullptr, nullptr));
        if (actor && actor->isCalc()) {
            actor->m176(target, pos, a3, a4, a5, a6);
            mWeapons[i].link.reset();
        }
    }
    return true;
}

// NON_MATCHING: the original recomputes the address of mWeapons[idx].link after the call (as in dropWeapon)
bool ActorWeapons::dropWeaponM177(int idx, const sead::Vector3f& target, void* a2) {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (weapon && weapon->isCalc()) {
        weapon->m177(target, a2);
        mWeapons[idx].link.reset();
    }
    return true;
}

// NON_MATCHING: the original recomputes the address of mWeapons[idx].link after the call (as in dropWeapon)
bool ActorWeapons::dropWeaponM179(int idx) {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (weapon && weapon->isCalc()) {
        weapon->m179();
        mWeapons[idx].link.reset();
    }
    return true;
}

bool ActorWeapons::sub_7100EFD1F8() {
    for (auto& weapon : mWeapons) {
        ActorConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        if (accessor.sub_7100D0FEAC())
            return true;
    }
    return false;
}

bool sub_7100EFD700(Actor* actor) {
    if (!actor)
        return false;
    const auto& profile = actor->getProfile();
    if (profile == "Player" || profile == "PauseMenuPlayer")
        return true;
    if (profile == "NPC" || profile == "ClerkNPC")
        return !isNPCOffPodFromWeapon(actor);
    return false;
}

bool sub_7100EFD8E4(Actor* actor) {
    return actor && actor->getProfile() == "PauseMenuPlayer";
}

void ActorWeapons::sub_7100EFD458(Unk117* arg) {
    for (auto& weapon : mWeapons) {
        if (auto* actor = sead::DynamicCast<WeaponBase>(weapon.link.getProc(nullptr, nullptr)))
            actor->x_17(arg);
    }
}

}  // namespace ksys::act

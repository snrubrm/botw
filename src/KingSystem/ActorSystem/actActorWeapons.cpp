#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "Game/Actor/aiUnk_7100EDD26C.h"
#include "Game/gameGraphics.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace ksys::act {

ActorWeapons::ActorWeapons(Actor* actor) : mActor(actor) {}

ActorWeapons::~ActorWeapons() = default;

// NON_MATCHING: the inlined reset keeps the link address instead of recomputing it after m174.
bool ActorWeapons::equipWeapon(s32 idx, Actor* weapon, bool a3, bool a4) {
    if (!weapon)
        return false;
    if (!static_cast<WeaponBase*>(weapon)->m173(idx, mActor,
                                              ::sub_7100EDD258(mActor, idx).cstr(),
                                              ::sub_7100EDD26C(mActor, idx)->cstr(), a3, a4))
        return false;
    if (getEquippedWeapon(idx))
        resetWeaponBaseProcLink(idx);
    mWeapons[idx].link.acquire(weapon, false);
    ActorLinkConstDataAccess accessor(weapon);
    accessor.sub_7100D150E8(mActor);
    return true;
}

// NON_MATCHING: the inlined reset keeps the link address instead of recomputing it after m174.
bool ActorWeapons::m2(s32 idx, Actor* weapon) {
    if (!weapon)
        return false;
    static_cast<WeaponBase*>(weapon)->m180(idx, mActor, ::sub_7100EDD258(mActor, idx).cstr(),
                                         ::sub_7100EDD26C(mActor, idx)->cstr());
    if (getEquippedWeapon(idx))
        resetWeaponBaseProcLink(idx);
    mWeapons[idx].link.acquire(weapon, false);
    ActorLinkConstDataAccess accessor(weapon);
    accessor.sub_7100D150E8(mActor);
    return true;
}

// NON_MATCHING: the SafeArray iterator keeps an index; the original advances the link address.
void ActorWeapons::m3() {
    for (auto& entry : mWeapons) {
        auto* weapon = sead::DynamicCast<WeaponBase>(entry.link.getProc(nullptr, nullptr));
        if (weapon && weapon->isCalc() && weapon->get920() == 0xff) {
            Actor* owner = mActor;
            if (owner && !weapon->get921() && weapon->getParentLink().hasProcById(owner)) {
                weapon->m229(owner);
                weapon->_9f4.set(8);
            }
        }
    }
}

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

// NON_MATCHING: same as dropWeapon: the original recomputes the address of mWeapons[idx].link after the call
bool ActorWeapons::resetWeaponBaseProcLink(s32 idx) {
    auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[idx].link.getProc(nullptr, nullptr));
    if (weapon && weapon->isCalc()) {
        weapon->m174();
        mWeapons[idx].link.reset();
    }
    return true;
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
        ActorLinkConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        accessor.sleep(reason);
    }
}

void ActorWeapons::wakeUp(BaseProc::SleepWakeReason reason) {
    for (auto& weapon : mWeapons) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        accessor.wakeUp(reason);
    }
}

// NON_MATCHING: the original keeps the first cast as a branch to a shared `x19 = null` block; ours
// if-converts it to a csel
void sub_7100EFA810(ActorLinkConstDataAccess* accessor) {
    BaseProc* proc = accessor->getProc();
    Actor* actor = nullptr;
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        actor = static_cast<Actor*>(proc);
    if (auto* weapon = sead::DynamicCast<WeaponBase>(actor))
        weapon->m215();
}

void ActorWeapons::sub_7100EFCC20(BaseProc::DeleteReason reason) {
    for (auto& weapon : mWeapons) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&weapon.link, &accessor);
        if (!accessor.sub_7100D14250())
            accessor.deleteLater(reason);
    }
}

// NON_MATCHING: the original keeps the loop index and recomputes the link address each iteration (smaddl); ours
// strength-reduces the address
void ActorWeapons::sub_7100EFCF10(bool on) {
    for (int i = 0; i < 6; ++i) {
        if (auto* weapon = sead::DynamicCast<WeaponBase>(mWeapons[i].link.getProc(nullptr, nullptr)))
            weapon->m51(on);
    }
}

void ActorWeapons::sub_7100EFCD98(Actor* owner) {
    for (auto& weapon : mWeapons) {
        acc::WeaponBase accessor;
        acquireActor(&weapon.link, &accessor);
        if (!accessor.sub_7100D14250())
            accessor.m228(owner);
    }
}

void ActorWeapons::x() {
    for (auto& weapon : mWeapons) {
        ActorLinkConstDataAccess accessor;
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
        ActorLinkConstDataAccess accessor;
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

// Source owner unknown: the OptionalWeapon caller passes an Actor.
void sub_7100EFD980(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (auto* model = actor->getModel()) {
        if (auto* scene = Graphics::instance()->mModelScenes[1])
            model->bind(scene);
    }
}

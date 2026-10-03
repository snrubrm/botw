#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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

void ActorWeapons::sub_7100EFD458(Unk117* arg) {
    for (auto& weapon : mWeapons) {
        if (auto* actor = sead::DynamicCast<WeaponBase>(weapon.link.getProc(nullptr, nullptr)))
            actor->x_17(arg);
    }
}

}  // namespace ksys::act

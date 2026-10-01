#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
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

}  // namespace ksys::act

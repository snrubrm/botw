#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace ksys::act {

// NON_MATCHING: ActorWeapons member at 0xb90 is still a placeholder
PlayerOrEnemy::~PlayerOrEnemy() = default;

}  // namespace ksys::act

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

bool ActorConstDataAccess::isPlayerOrEnemy() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::IsDerivedFrom<PlayerOrEnemy>(actor);
}

namespace acc {

inline act::PlayerOrEnemy* PlayerOrEnemy::getPlayerOrEnemy() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<act::PlayerOrEnemy>(actor);
}

f32 PlayerOrEnemy::getGuardableAngle() const {
    if (auto* poe = getPlayerOrEnemy())
        return poe->getGuardableAngle();
    return sead::Mathf::deg2rad(100.0f);
}

bool PlayerOrEnemy::isGuard() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    debugLog(0, "isGuard");
    return poe->isGuard();
}

bool PlayerOrEnemy::isGuardJust() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    debugLog(0, "isGuardJust");
    return poe->isGuardJust();
}

}  // namespace acc

}  // namespace ksys::act

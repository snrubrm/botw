#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/actWeapon.h"

namespace ksys::act {

PlayerOrEnemy::PlayerOrEnemy(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 2;
}

PlayerOrEnemy::~PlayerOrEnemy() = default;

bool PlayerOrEnemy::startPreparingForPreDelete_() {
    return DynamicActor::startPreparingForPreDelete_();
}

void PlayerOrEnemy::sub_7100007CA8(int idx, const uking::act::Unk_71002eda38& arg) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDA38(arg);
}

void PlayerOrEnemy::sub_7100007D58(int idx, const uking::act::Unk_71002edaec& arg) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDAEC(arg);
}

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

bool PlayerOrEnemy::getWeapon(ActorConstDataAccess* accessor, int idx) const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    auto& link = poe->getWeapons()->mWeapons[idx].link;
    if (!link.hasProc())
        return false;
    act::acquireActor(&link, accessor);
    return true;
}

}  // namespace acc

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::m81(const Message& message) {
    if (DynamicActor::m81(message))
        return true;
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->m8(message);
}

bool PlayerOrEnemy::m151(u16 bit) {
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->_8.isOnBit(bit);
}

bool PlayerOrEnemy::m152(u16 mask) {
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->_8.isOn(mask);
}

}  // namespace ksys::act

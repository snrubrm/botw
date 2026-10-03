#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

UnarmedEnemySearch::UnarmedEnemySearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

UnarmedEnemySearch::~UnarmedEnemySearch() = default;

bool UnarmedEnemySearch::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void UnarmedEnemySearch::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = sub_71005E2BCC(mActor);
    mActor->m45();
    if (m34())
        m37();
    else
        changeChild("見まわす");
}

void UnarmedEnemySearch::leave_() {
    if (_50 && _50->_0)
        _50->_0->inlineReset();
}

void UnarmedEnemySearch::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
}

void UnarmedEnemySearch::sub_71004B5FB8() {
    changeChild("見まわす");
}

int UnarmedEnemySearch::sub_71004B62E4() const {
    if (!_50)
        return -1;
    return _50->_8;
}

bool UnarmedEnemySearch::sub_71004B62FC(sead::Vector3f* out) const {
    if (_50 && _50->_0 && (_50->_8 | 2) == 3) {
        auto* nav = _50->_0;
        auto lock = sead::makeScopedLock(nav->_1e0);
        out->set(nav->_1a0);
        return true;
    }
    return false;
}

bool UnarmedEnemySearch::sub_71004B6370(sead::Vector3f* out) const {
    if (_50 && _50->_0 && _50->_8 != -1) {
        auto* nav = _50->_0;
        auto lock = sead::makeScopedLock(nav->_1e0);
        out->set(nav->_194);
        return true;
    }
    return false;
}

void UnarmedEnemySearch::sub_71004B63E4() {
    if (_50)
        _50->_8 = -1;
}

f32 UnarmedEnemySearch::sub_71004B6BC0() const {
    return *mReachTargetArea_s + sub_71007320F0(mActor, *mWeaponIdx_s);
}

bool UnarmedEnemySearch::m34() {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    if (!nav->_18)
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    if (!_50)
        return false;
    if (auto* character = _50->_0)
        character->sub_7100F7604C(0.5f);
    return true;
}

void UnarmedEnemySearch::m39() {
    setFinished();
}

bool UnarmedEnemySearch::m40(const sead::ObjList<sead::Vector3f>& points, sead::Vector3f* out) {
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (sub_710072E154(mActor, *it, nullptr, -1)) {
            *out = *it;
            return true;
        }
    }
    return false;
}

void UnarmedEnemySearch::m42() {
    setFailed();
}

}  // namespace uking::ai

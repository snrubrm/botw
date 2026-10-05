#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

void UnarmedEnemySearch::changeToLookAround() {
    changeChild("見まわす");
}

int UnarmedEnemySearch::getStateMaybe() const {
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

void UnarmedEnemySearch::resetStateMaybe() {
    if (_50)
        _50->_8 = -1;
}

f32 UnarmedEnemySearch::getReachDistanceMaybe() const {
    return *mReachTargetArea_s + sub_71007320F0(mActor, *mWeaponIdx_s);
}

// NON_MATCHING: stack layout only (the original keeps `pos` / `dir` / the key temporary above the
// 0xa10-byte param pack; ours puts the pack above them)
void UnarmedEnemySearch::startMoveToTargetMaybe(const sead::Vector3f& target) {
    if (_50)
        _50->_8 = -1;
    if (_50 && _50->_0)
        _50->_0->inlineReset();
    _58 = target;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_58, "TargetPos", -1);
    if (!isCurrentChild("移動") && mActor) {
        const auto& mtx = mActor->getMtx();
        const sead::Vector3f dir = mtx.getBase(2);
        const sead::Vector3f pos = mtx.getTranslation();
        if (!sub_710072DCFC(_58, pos, dir, *mTurnStartAng_s)) {
            changeChild("回転", &params);
            return;
        }
    }
    changeChild("直進", &params);
}

bool UnarmedEnemySearch::isMove() const {
    return isCurrentChild("移動");
}

bool UnarmedEnemySearch::isGoStraight() const {
    return isCurrentChild("直進");
}

bool UnarmedEnemySearch::isGoStraightOrMove() const {
    if (isCurrentChild("直進"))
        return true;
    return isCurrentChild("移動");
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

// NON_MATCHING: iterator argument setup is scheduled in a different order.
void UnarmedEnemySearch::m41(const sead::ObjList<sead::Vector3f>& points) {
    if (!mActor->m45())
        return;
    auto* state = _50;
    if (state && state->_0) {
        state->_0->sub_7100394884(points.begin(), points.end());
        state->_8 = 0;
    }
}

void UnarmedEnemySearch::m42() {
    setFailed();
}

void UnarmedEnemySearch::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ジャンプ")) {
            m37();
            return;
        }
        if (isCurrentChild("見まわす")) {
            m42();
            return;
        }
        if (isCurrentChild("回転")) {
            m37();
            return;
        }
        if (isCurrentChild("直進") || isCurrentChild("移動")) {
            if (!_50 || _50->_8 == -1) {
                m39();
                return;
            }
        }
    }

    if (isCurrentChild("直進") || isCurrentChild("移動")) {
        if (!getCurrentChild()->isChangeable()) {
            m38();
            return;
        }
        if (isCurrentChild("移動") && _50 && _50->_8 == 3) {
            m39();
            return;
        }
        sead::Vector3f target;
        if (m43(&target)) {
            m35(target);
            return;
        }
        if (_50 && _50->_8 == 2) {
            changeChild("見まわす");
            return;
        }
        m38();
    } else if (isCurrentChild("見まわす")) {
        sead::Vector3f target;
        if (m43(&target))
            m35(target);
    }
}

void UnarmedEnemySearch::m35(const sead::Vector3f& target) {
    if (_50)
        _50->_8 = -1;
    _58 = target;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_58, "TargetPos", -1);
    changeChild("移動", &params);
}

bool UnarmedEnemySearch::m43(sead::Vector3f* out) {
    if (!_50 || _50->_8 != 1)
        return false;
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    const sead::Vector3f pos = nav->_194;
    if (pos.isNan())
        return false;
    if (out)
        *out = pos;
    return true;
}

}  // namespace uking::ai

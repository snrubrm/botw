#include "Game/Actor/AI/aiLynelNavMoveNoStop.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LynelNavMoveNoStop::LynelNavMoveNoStop(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelNavMoveNoStop::~LynelNavMoveNoStop() = default;

bool LynelNavMoveNoStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelNavMoveNoStop::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* as_list = mActor->getASList())
        as_list->x_6(9, 0, 0.0f);
    if (auto* nav = mActor->m45())
        nav->sub_7100F7604C(nav->getRadiusMaybe());
    m34();
}

void LynelNavMoveNoStop::calc_() {
    // Whether the actor is within ReachTargetArea (plus the weapon reach) of the target.
    const auto hasReachedTarget = [this] {
        const f32 dist = (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
        return dist <= *mReachTargetArea_s + sub_71007320F0(mActor, *mWeaponIdx_s);
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (hasReachedTarget()) {
            sub_71004923C0();
            setFinished();
            return;
        }
        // sub_710072FEC4 along the actor's front axis over 5 units.
        const auto checkFront = [this] {
            sead::Vector3f front;
            mActor->getMtx().getBase(front, 2);
            return sub_710072FEC4(mActor, front, 5.0f, nullptr, true, nullptr);
        };
        if (m35() || !checkFront()) {
            if (isCurrentChild("直進")) {
                if (sub_7100492CB8()) {
                    changeToMove();
                    return;
                }
            } else if (sub_710072E154(mActor, *mTargetPos_d, nullptr, -1)) {
                changeToGoStraight();
                return;
            }
        }
        sub_71004923C0();
        setFailed();
        return;
    }

    if (child->isChangeable()) {
        if (hasReachedTarget()) {
            sub_71004923C0();
            setFinished();
            return;
        }
        const bool straight = isCurrentChild("直進");
        const bool reachable = sub_710072E154(mActor, *mTargetPos_d, nullptr, -1);
        bool check_nav = false;
        if (!straight) {
            if (reachable) {
                if (sub_7100492E34()) {
                    changeToGoStraight();
                    return;
                }
            } else {
                check_nav = true;
            }
        } else if (!reachable) {
            if (sub_7100492CB8()) {
                changeToMove();
                return;
            }
            check_nav = true;
        }
        if (check_nav && sub_7100492DDC()) {
            setFailed();
            return;
        }
    }

    sub_7100493058();
    sub_71004930D0();
}

void LynelNavMoveNoStop::leave_() {
    ksys::act::ai::Ai::leave_();
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor)) {
        if (auto* holder = static_cast<act::Enemy*>(actor)->_12d0)
            holder->_8 = -1;
    }
}

void LynelNavMoveNoStop::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelNavMoveNoStop::sub_71004923C0() {
    auto* actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor)) {
        if (auto* holder = static_cast<act::Enemy*>(actor)->_12d0) {
            if (holder->_0)
                holder->_0->inlineReset();
            holder->_8 = -1;
            return;
        }
    }

    if (auto* nav = mActor->m45())
        nav->inlineReset();
}

void LynelNavMoveNoStop::m34() {
    sub_71004923C0();
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F75F8C(*mTargetPos_d);
        _60 = ksys::Timer(*mRepathTime_s, *mRepathTime_s);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("直進", &pack);
}

bool LynelNavMoveNoStop::m35() {
    return false;
}

void LynelNavMoveNoStop::sub_7100492574() {
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F75F8C(*mTargetPos_d);
        _60 = ksys::Timer(*mRepathTime_s, *mRepathTime_s);
    }
}

bool LynelNavMoveNoStop::sub_7100492CB8() {
    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        return state == 1;
    }
    return false;
}

bool LynelNavMoveNoStop::sub_7100492DDC() {
    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        return state == 3;
    }
    return true;
}

bool LynelNavMoveNoStop::sub_7100492E34() {
    const sead::Vector3f up = getUpDir(mActor);
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();
    sead::Vector3f to_target = *mTargetPos_d - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();
    return forward.dot(to_target) >= std::cos(sead::Mathf::pi() / 4);
}

void LynelNavMoveNoStop::sub_7100493058() {
    if (*mRepathTime_s > 0) {
        _60.update();
        if (_60.value <= sead::Mathf::epsilon()) {
            if (auto* nav = mActor->m45()) {
                nav->sub_7100F75F8C(*mTargetPos_d);
                _60 = ksys::Timer(*mRepathTime_s, *mRepathTime_s);
            }
        }
    }
}

void LynelNavMoveNoStop::sub_71004930D0() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void LynelNavMoveNoStop::changeToGoStraight() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("直進", &pack);
}

void LynelNavMoveNoStop::changeToMove() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai

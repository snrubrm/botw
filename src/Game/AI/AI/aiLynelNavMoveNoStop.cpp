#include "Game/AI/AI/aiLynelNavMoveNoStop.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
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

}  // namespace uking::ai

#include "Game/AI/AI/aiLynelNavMoveNoStop.h"
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
        nav->sub_7100F7604C(nav->_2a8 * nav->_2ac);
    m34();
}

void LynelNavMoveNoStop::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelNavMoveNoStop::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
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

#include "Game/AI/Action/actionChallengeChainRing.h"
#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ChallengeChainRing::ChallengeChainRing(const InitArg& arg) : FollowChallenge(arg) {}

ChallengeChainRing::~ChallengeChainRing() = default;

bool ChallengeChainRing::init_(sead::Heap* heap) {
    if (!FollowChallenge::init_(heap))
        return false;

    _b70 = *mIsFirstNode_m;
    _b78 = new (heap) Unk_71024f15c0;
    ksys::gdt::resetFlag_BalladOfHeroes_ChainRing_Running(false);
    return true;
}

void ChallengeChainRing::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowChallenge::enter_(params);
}

void ChallengeChainRing::leave_() {
    FollowChallenge::leave_();
}

void ChallengeChainRing::loadParams_() {
    FollowChallenge::loadParams_();
    getMapUnitParam(&mChainRingOrbitSpeed_m, "ChainRingOrbitSpeed");
    getMapUnitParam(&mIsFirstNode_m, "IsFirstNode");
}

void ChallengeChainRing::calc_() {
    FollowChallenge::calc_();
}

void ChallengeChainRing::m34(const sead::Vector3f& pos, const sead::Vector3f& dir) {
    const sead::Vector3f up_axis = sead::Vector3f::ey;
    sead::Vector3f front = dir;
    front.normalize();
    sead::Vector3f side;
    side.setCross(up_axis, front);
    side.normalize();
    sead::Vector3f up;
    up.setCross(front, side);
    up.normalize();

    sead::Matrix34f mtx;
    mtx.setBase(0, side);
    mtx.setBase(1, up);
    mtx.setBase(2, front);
    mtx.setBase(3, pos);
    if (auto* body = mActor->getMainBody())
        body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
    mActor->actorPhysicsSetFlag2();
}

void ChallengeChainRing::m35(sead::Vector3f* pos) {
    if (pos)
        pos->set(_b78->_30.sub_7100EEB370());
}

}  // namespace uking::action

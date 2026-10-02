#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

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
    ksys::act::ai::Ai::leave_();
}

void UnarmedEnemySearch::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
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

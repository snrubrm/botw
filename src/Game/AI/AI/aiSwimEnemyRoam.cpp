#include "Game/AI/AI/aiSwimEnemyRoam.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007368A4.h"

namespace uking::ai {

SwimEnemyRoam::SwimEnemyRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwimEnemyRoam::~SwimEnemyRoam() = default;

void SwimEnemyRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    if (sub_7100736D98(mActor) || testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sub_71005B51E8();
    } else {
        sub_71005B52EC();
    }
}

void SwimEnemyRoam::leave_() {
    sub_71005DB3EC(mActor);
}

void SwimEnemyRoam::loadParams_() {
    getStaticParam(&mRoamRadius_s, "RoamRadius");
    getStaticParam(&mRoamRatio_s, "RoamRatio");
    getStaticParam(&mRoamXRadius_s, "RoamXRadius");
    getStaticParam(&mRoamZRadius_s, "RoamZRadius");
}

void SwimEnemyRoam::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("徘徊準備")) {
        sub_71005B51E8();
        return;
    }

    if (!isCurrentChild("徘徊"))
        return;

    sead::Vector3f pos;
    sub_71005B5628(&pos);
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
    sead::Vector3f target = _64;
    target.y = mActor->getMtx().m[1][3];
    sub_71005DB068(mActor, target);
}

// NON_MATCHING: register allocation only (home.x lands in s1 instead of s2 in the distance check)
void SwimEnemyRoam::sub_71005B52EC() {
    mActor->getMtx().getTranslation(_58);
    _64 = _58;

    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 2);
    dir.y = 0;
    dir.normalize();
    _58 += dir * *mRoamZRadius_s;

    sead::Vector3f home;
    mActor->getHomePos(&home);
    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(_58, home)) > *mRoamZRadius_s) {
        _58 = home + dir * *mRoamZRadius_s;
        _64 = home;
    }

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_58, "TargetPos", -1);
    changeChild("徘徊準備", &params);
}

void SwimEnemyRoam::sub_71005B51E8() {
    _70 = 0;
    _74 = mActor->getMtx();
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target;
    sub_71005B5628(&target);
    params.addVec3(target, "TargetPos", -1);
    changeChild("徘徊", &params);
}

}  // namespace uking::ai

#include "Game/AI/AI/aiSwimEnemyRoam.h"
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
    ksys::act::ai::Ai::leave_();
}

void SwimEnemyRoam::loadParams_() {
    getStaticParam(&mRoamRadius_s, "RoamRadius");
    getStaticParam(&mRoamRatio_s, "RoamRatio");
    getStaticParam(&mRoamXRadius_s, "RoamXRadius");
    getStaticParam(&mRoamZRadius_s, "RoamZRadius");
}

}  // namespace uking::ai

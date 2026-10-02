#include "Game/AI/AI/aiSiteBossThrowIceRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SiteBossThrowIceRoot::SiteBossThrowIceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossThrowIceRoot::~SiteBossThrowIceRoot() {
    ;
}

bool SiteBossThrowIceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossThrowIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack child_params;
    child_params.addInt(*mIgnitionNum_s, "IgnitionNum", -1);
    changeChild("弾生成", &child_params);
}

void SiteBossThrowIceRoot::leave_() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        for (int i = 0; i < 9; ++i)
            boss->_1560.sub_710066CBD4(i);
    }
}

void SiteBossThrowIceRoot::loadParams_() {
    getStaticParam(&mIgnitionNum_s, "IgnitionNum");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

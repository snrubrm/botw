#include "Game/AI/AI/aiGolfBallRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

GolfBallRoot::GolfBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolfBallRoot::~GolfBallRoot() = default;

bool GolfBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolfBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = sead::Vector3f::zero;
    _64 = false;
    _65 = false;
    _68 = 0;
    _6c = false;
    _70 = 0;
    _e0 = false;
    if (!mActor)
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (auto* obj = ksys::act::findLinkReferenceObj(mActor, "FldObj_FlagChallengeGoal_A", "",
                                                    nullptr)) {
        const sead::Vector3f pos = obj->getTranslate();
        _74 = pos;
    }
    _80.sub_7100EEBAE0(sub_7100EEF264(mActor, 0), 0.0f);
    _80.sub_7100EEBE9C(1);
}

void GolfBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolfBallRoot::loadParams_() {
    getStaticParam(&mIntSmashJudgeFrame_s, "IntSmashJudgeFrame");
    getStaticParam(&mIntSmashContinueFrame_s, "IntSmashContinueFrame");
    getStaticParam(&mFloatJudgeSmash_s, "FloatJudgeSmash");
    getStaticParam(&mFloatJudgeStop_s, "FloatJudgeStop");
}

void GolfBallRoot::m34() {}

}  // namespace uking::ai

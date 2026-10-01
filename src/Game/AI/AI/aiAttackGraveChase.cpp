#include "Game/AI/AI/aiAttackGraveChase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

AttackGraveChase::AttackGraveChase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackGraveChase::~AttackGraveChase() = default;

bool AttackGraveChase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack slot assignment of the accessor/position locals
void AttackGraveChase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(mTargetActor_d, &acc);
        acc.getActorMtx().getTranslation(pos);
    }
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
    _60 = 0.0f;
    _64 = false;
}

void AttackGraveChase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackGraveChase::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
    getStaticParam(&mNearTime_s, "NearTime");
    getStaticParam(&mEndHeight_s, "EndHeight");
    getStaticParam(&mEndNear_s, "EndNear");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiAnimalPreAttack.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalPreAttack::AnimalPreAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalPreAttack::~AnimalPreAttack() = default;

bool AnimalPreAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 minimum = *mForceEndTime_s;
    _5c = minimum;
    _60 = minimum + 15;
    _58 = f32(sead::GlobalRandom::instance()->getS32Range(minimum, minimum + 15));
    if (!((mActor->getMtx().getTranslation() - *mTargetPos_d).length() >
          *mKeepDistCheckLength_s) || sub_7100307B44()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("距離を取る", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("対象を向く", &pack);
    }
}

void AnimalPreAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalPreAttack::loadParams_() {
    getStaticParam(&mForceEndTime_s, "ForceEndTime");
    getStaticParam(&mKeepDistCheckLength_s, "KeepDistCheckLength");
    getStaticParam(&mBackCliffCheckLength_s, "BackCliffCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

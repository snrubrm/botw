#include "Game/AI/AI/aiHorseWanderAI.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseWanderAI::HorseWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseWanderAI::~HorseWanderAI() = default;

// NON_MATCHING: stack slot order (the original puts the key SafeString temporaries above the
// InlineParamPack, ours below)
void HorseWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    auto* actor = mActor;
    auto* horse = sead::DynamicCast<act::HorseBase>(actor);
    auto* rideable = actor->getHorseOptionsMaybe();
    if ((rideable && rideable->Unk_7100e8b2b8::_c == 1) || !horse) {
        changeChild("移動", &pack);
    } else if (horse->_b30.hasProc()) {
        pack.addActor(horse->_b30, "TargetActor", -1);
        pack.addFloat(0.0f, "DistanceKept", -1);
        changeChild("移動(リーダーあり)", &pack);
    } else if (horse->_b40) {
        changeChild("移動(パスあり)", &pack);
    } else {
        changeChild("移動", &pack);
    }
}

void HorseWanderAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseWanderAI::loadParams_() {}

void HorseWanderAI::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished())
        setFinished();
    else if (child->isFailed())
        setFailed();
}

}  // namespace uking::ai

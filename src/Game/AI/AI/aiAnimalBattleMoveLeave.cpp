#include "Game/AI/AI/aiAnimalBattleMoveLeave.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalBattleMoveLeave::AnimalBattleMoveLeave(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalBattleMoveLeave::~AnimalBattleMoveLeave() = default;

bool AnimalBattleMoveLeave::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: store scheduling of the first three members only (the original stores _50 right after the `this`
// move and builds the _48 / _4c pair afterwards)
void AnimalBattleMoveLeave::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 0.0f;
    _4c = -1.0f;
    _50 = 0;
    _48 = 0.0f;
    _4c = -1.0f;
    _54 = *mTargetPos_d;
    _60 = {-1.0f, -1.0f, 0.0f};
    _6c = 0;
    if (sub_710072FEC4(mActor, mActor->getMtx().getBase(2), *mCheckForwardDist_s, nullptr, true,
                       nullptr)) {
        sub_7100303A90();
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_54, "TargetPos", -1);
        changeChild("移動", &pack);
    }
}

void AnimalBattleMoveLeave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalBattleMoveLeave::loadParams_() {
    getStaticParam(&mCheckForwardDist_s, "CheckForwardDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

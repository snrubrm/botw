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
    _48 = ksys::Timer(0.0f, -1.0f, 0.0f);
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

// NON_MATCHING: the original loads all vector components and the distance parameter before the sqrt and
// scales the direction in a different register order
void AnimalBattleMoveLeave::sub_7100303A90() {
    sead::Vector3f dir = -mActor->getMtx().getBase(2);
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= *mCheckForwardDist_s * 3.0f / length;
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    _48 = ksys::Timer(70.0f, 70.0f);
    _54 = position + dir;
    _60 = {-1.0f, -1.0f, 0.0f};
    ++_6c;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_54, "TargetPos", -1);
    changeChild("旋回", &pack);
}

void AnimalBattleMoveLeave::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalBattleMoveLeave::loadParams_() {
    getStaticParam(&mCheckForwardDist_s, "CheckForwardDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

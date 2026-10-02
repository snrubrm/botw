#include "Game/AI/AI/aiSeqPredictOctarockAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SeqPredictOctarockAttack::SeqPredictOctarockAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqPredictOctarockAttack::~SeqPredictOctarockAttack() = default;

bool SeqPredictOctarockAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqPredictOctarockAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c = *mTargetPos_d;
    _58 = *mTargetVel_d;
    _48 = true;
    sub_7100564154();
}

void SeqPredictOctarockAttack::sub_7100564154() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("先行動", &params);
}

void SeqPredictOctarockAttack::calc_() {
    sub_710056439C();
    sub_71005DB3EC(mActor);
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動")) {
            sub_710056464C();
            return;
        }
        if (isCurrentChild("中行動")) {
            sub_7100564738();
            return;
        }
        setFinished();
    } else {
        child->isChangeable();
    }
    child->setDynamicParam(_4c, "TargetPos");
    child->setDynamicParam(_58, "TargetVel");
}

void SeqPredictOctarockAttack::sub_710056464C() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("中行動", &params);
}

void SeqPredictOctarockAttack::sub_7100564738() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_4c, "TargetPos", -1);
    params.addVec3(_58, "TargetVel", -1);
    changeChild("後行動", &params);
}

void SeqPredictOctarockAttack::leave_() {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void SeqPredictOctarockAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai

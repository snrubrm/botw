#include "Game/AI/AI/aiLinkageEnemyNormal.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LinkageEnemyNormal::LinkageEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

LinkageEnemyNormal::~LinkageEnemyNormal() = default;

bool LinkageEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void LinkageEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void LinkageEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void LinkageEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

void LinkageEnemyNormal::calc_() {
    getCurrentChild();
    if (!isCurrentChild("連携") && _3d0._30) {
        sub_71004839A4(_3d0._38.mLink);
        _3d0.x();
        return;
    }
    EnemyNormal::calc_();
}

bool LinkageEnemyNormal::handleMessage_(const ksys::Message* message) {
    if (isChangeable() && _3d0.m2(*message))
        return true;
    return EnemyNormal::handleMessage_(message);
}

void LinkageEnemyNormal::sub_71004839A4(const ksys::act::BaseProcLink& link) {
    _3ac.reset(8);
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);
    ksys::act::ai::InlineParamPack params;
    params.addActor(link, "TargetActor", -1);
    changeChild("連携", &params);
}

void LinkageEnemyNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("連携")) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m49(out, idx);
}

void LinkageEnemyNormal::m50(Unk1* out, s32 idx) {
    if (!isCurrentChild("連携")) {
        EnemyNormal::m50(out, idx);
        return;
    }
    const s32 type = m52(idx);
    switch (type) {
    case 0:
    case 1:
    case 4:
        out->_8 |= 6;
        out->_0 = type;
        out->_4 = 2;
        break;
    default:
        out->_0 = -1;
        break;
    }
}

}  // namespace uking::ai

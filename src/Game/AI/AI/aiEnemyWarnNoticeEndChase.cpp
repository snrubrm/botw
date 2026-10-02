#include "Game/AI/AI/aiEnemyWarnNoticeEndChase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyWarnNoticeEndChase::EnemyWarnNoticeEndChase(const InitArg& arg) : EnemyWarnNoticeSelect(arg) {}

EnemyWarnNoticeEndChase::~EnemyWarnNoticeEndChase() = default;

bool EnemyWarnNoticeEndChase::init_(sead::Heap* heap) {
    return EnemyWarnNoticeSelect::init_(heap);
}

void EnemyWarnNoticeEndChase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyWarnNoticeSelect::enter_(params);
    _14c = false;
}

void EnemyWarnNoticeEndChase::leave_() {
    EnemyWarnNoticeSelect::leave_();
}

void EnemyWarnNoticeEndChase::loadParams_() {
    EnemyWarnNoticeSelect::loadParams_();
}

void EnemyWarnNoticeEndChase::m34() {
    _148 = 30.0f;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_13c, "TargetPos", -1);
    changeChild("追跡", &params);
}

}  // namespace uking::ai

#include "Game/AI/AI/aiTargetLastAttackerPos.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetLastAttackerPos::TargetLastAttackerPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetLastAttackerPos::~TargetLastAttackerPos() = default;

bool TargetLastAttackerPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetLastAttackerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetLastAttackerPos::calc_() {
    TargetPosAI::calc_();
}

void TargetLastAttackerPos::leave_() {
    TargetPosAI::leave_();
}

void TargetLastAttackerPos::loadParams_() {
    TargetPosAI::loadParams_();
}

// NON_MATCHING: the original addresses the matrix relative to &enemy->_e08 (kept in x20 after the
// hasProc call), as if through an inline Unk_71006e4478 member; ours rebases on enemy
void TargetLastAttackerPos::m35(sead::Vector3f* pos) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& attacker = enemy->_e08;
        if (attacker._0.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&attacker._0, &accessor);
            accessor.getActorMtx().getTranslation(*pos);
        } else {
            attacker._10.getTranslation(*pos);
        }
    } else {
        pos->set(0, 0, 0);
    }
}

}  // namespace uking::ai

#include "Game/AI/AI/aiAssassinBossAttackSeq.h"

// Declaration only; the original global source namespace is unknown.
bool sub_7100314FE8(ksys::act::Actor* actor, const sead::SafeString& part_name, s32 count);

namespace uking::ai {

AssassinBossAttackSeq::AssassinBossAttackSeq(const InitArg& arg) : SeqTwoAction(arg) {}

AssassinBossAttackSeq::~AssassinBossAttackSeq() = default;

bool AssassinBossAttackSeq::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AssassinBossAttackSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (sub_7100314FE8(actor, "IronBall", 2) || sub_7100314FE8(actor, "SpareBall", 1))
        changeChild("後行動", params);
    else
        SeqTwoAction::enter_(params);
}

void AssassinBossAttackSeq::calc_() {
    SeqTwoAction::calc_();
}

void AssassinBossAttackSeq::leave_() {
    SeqTwoAction::leave_();
}

void AssassinBossAttackSeq::loadParams_() {
    SeqTwoAction::loadParams_();
}

}  // namespace uking::ai

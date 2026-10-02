#include "Game/AI/AI/aiLynelFindPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

LynelFindPlayer::LynelFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LynelFindPlayer::~LynelFindPlayer() = default;

bool LynelFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void LynelFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LynelFindPlayer::calc_() {
    EnemyBaseFindPlayer::calc_();
}

void LynelFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LynelFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

void LynelFindPlayer::m40() {
    *mLynelAIFlags_a &= ~0x20;
    EnemyBaseFindPlayer::m40();
}

void LynelFindPlayer::m47() {
    const auto& pos = sub_71005D93CC(mActor);
    sub_71005DB068(mActor, pos);
}

}  // namespace uking::ai

#include "Game/AI/AI/aiRemainsFireBattleMove.h"

namespace uking::ai {

RemainsFireBattleMove::RemainsFireBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsFireBattleMove::~RemainsFireBattleMove() = default;

bool RemainsFireBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsFireBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsFireBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsFireBattleMove::handlePendingChildChange_() {
    const sead::SafeString name = mChildren[mPendingChildIdx]->getName();
    if (name == "攻撃") {
        sub_7100540FE4();
        return;
    }
    if (name == "移動")
        changeChild("移動");
    else
        changeChild("待機");
}

void RemainsFireBattleMove::loadParams_() {}

bool RemainsFireBattleMove::handleAck_(const ksys::MessageAck& ack) {
    if (!_50.sub_710070E070(ack))
        return false;
    if (_50._14)
        _80 = true;
    return true;
}

}  // namespace uking::ai

#include "Game/AI/Action/actionForkTurnASHold.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ForkTurnASHold::ForkTurnASHold(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkTurnASHold::~ForkTurnASHold() = default;

void ForkTurnASHold::calc_() {
    ForkAlwaysTurn::calc_();
    if (!m32())
        sub_7100738AA8(mActor, 0.0f);
}

}  // namespace uking::action

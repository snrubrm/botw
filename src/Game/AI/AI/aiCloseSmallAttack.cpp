#include "Game/AI/AI/aiCloseSmallAttack.h"

namespace uking::ai {

CloseSmallAttack::CloseSmallAttack(const InitArg& arg) : CloseSmallAttackBase(arg) {}

CloseSmallAttack::~CloseSmallAttack() = default;

// NON_MATCHING: the original keeps the SafeString vtable GOT address and re-adds 0x10; ours CSEs the sum
bool CloseSmallAttack::isFinished() const {
    if (CloseSmallAttackBase::isFinished())
        return true;
    if (isCurrentChild(m35()))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiCloseSmallAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CloseSmallAttack : public CloseSmallAttackBase {
    SEAD_RTTI_OVERRIDE(CloseSmallAttack, CloseSmallAttackBase)
public:
    explicit CloseSmallAttack(const InitArg& arg);
    ~CloseSmallAttack() override;
    bool isFinished() const override;

    const char* m34() const override { return "ステップ"; }
    const char* m35() const override { return "小攻撃"; }

protected:
};

}  // namespace uking::ai

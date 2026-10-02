#pragma once

#include "Game/AI/AI/aiRememberMesOneActorEnemyRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinShooterJuniorAzitoRoot : public RememberMesOneActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinShooterJuniorAzitoRoot, RememberMesOneActorEnemyRoot)
public:
    explicit AssassinShooterJuniorAzitoRoot(const InitArg& arg);
    ~AssassinShooterJuniorAzitoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_710235aba0 _238{mActor, 0x8000040};
    Unk_710235abc8 _268{mActor, 0x8000006};
};
KSYS_CHECK_SIZE_NX150(AssassinShooterJuniorAzitoRoot, 0x2c0);

}  // namespace uking::ai

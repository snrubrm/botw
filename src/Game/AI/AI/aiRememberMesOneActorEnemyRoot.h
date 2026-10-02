#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RememberMesOneActorEnemyRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(RememberMesOneActorEnemyRoot, EnemyRoot)
public:
    explicit RememberMesOneActorEnemyRoot(const InitArg& arg);
    ~RememberMesOneActorEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    sead::SafeString mRememberKey_s{};
    Unk_7102450ac8 _1e8;
};
KSYS_CHECK_SIZE_NX150(RememberMesOneActorEnemyRoot, 0x238);

}  // namespace uking::ai

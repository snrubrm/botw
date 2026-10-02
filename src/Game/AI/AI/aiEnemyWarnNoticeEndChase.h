#pragma once

#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWarnNoticeEndChase : public EnemyWarnNoticeSelect {
    SEAD_RTTI_OVERRIDE(EnemyWarnNoticeEndChase, EnemyWarnNoticeSelect)
public:
    explicit EnemyWarnNoticeEndChase(const InitArg& arg);
    ~EnemyWarnNoticeEndChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;

protected:
    // In EnemyWarnNoticeSelect's tail padding.
    sead::Vector3f _13c;
    f32 _148 = 0;
    bool _14c = false;
};
KSYS_CHECK_SIZE_NX150(EnemyWarnNoticeEndChase, 0x150);

}  // namespace uking::ai

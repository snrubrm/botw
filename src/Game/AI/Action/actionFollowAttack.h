#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "Game/AI/Action/actionUnk_71023c8418.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowAttack : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowAttack, RotateTurnToTarget)
public:
    explicit FollowAttack(const InitArg& arg);
    ~FollowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m35();

    Unk_71023c8418 _78{this};
    // static_param at offset 0x108
    const bool* mForceKillMode_s{};
    // static_param at offset 0x110
    const bool* mIsRodDirHosei_s{};
};
KSYS_CHECK_SIZE_NX150(FollowAttack, 0x118);

}  // namespace uking::action

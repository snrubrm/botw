#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionAssassinBossIronBallAttack.h"
#include "Game/AI/Action/actionUnk_71023c84b8.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AssassinBossIronBallAtkWithRot : public AssassinBossIronBallAttack {
    SEAD_RTTI_OVERRIDE(AssassinBossIronBallAtkWithRot, AssassinBossIronBallAttack)
public:
    explicit AssassinBossIronBallAtkWithRot(const InitArg& arg);
    ~AssassinBossIronBallAtkWithRot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(sead::Vector3f* angle);
    virtual void m33(sead::Vector3f* pos);

    u64 _68 = 0;
    u64 _70 = 0;
    // static_param at offset 0x78
    sead::SafeString mCentralAnchorName_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mAddAngle_s{};
    Unk_71023c84b8 _90{this};
    /// Rotation direction (1 or -1), chosen randomly on enter.
    s8 _f8 = 1;
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class SandwormBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormBattle, ksys::act::ai::Ai)
public:
    explicit SandwormBattle(const InitArg& arg);
    ~SandwormBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_7100557504();
    void sub_710055762C();
    void sub_7100557744();
    bool sub_710055785C();
    // inline-only in the original; name is a guess. Evidence: the same accessor + link-or-dummy +
    // getActorMtx().getTranslation() sequence is inlined in sub_710055762C / sub_7100557744 / calc_ /
    // sub_710055785C of this class (callee allocas end up above the caller's).
    void getTargetPos(sead::Vector3f* out);

protected:
    // static_param at offset 0x38
    const float* mAttackAngle_s{};
    // static_param at offset 0x40
    const float* mAttackInterval_s{};
    // static_param at offset 0x48
    const float* mAttackIntervalRand_s{};
    // static_param at offset 0x50
    const float* mBattleFailTimer_s{};
    ksys::act::Unk_7100d3bce4 _58{mActor};  // attack interval
    ksys::act::Unk_7100d3bce4 _70{mActor};  // BattleFailTimer
};
KSYS_CHECK_SIZE_NX150(SandwormBattle, 0x88);

}  // namespace uking::ai

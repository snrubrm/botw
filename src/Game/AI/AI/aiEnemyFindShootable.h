#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class EnemyFindShootable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFindShootable, ksys::act::ai::Ai)
public:
    explicit EnemyFindShootable(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x710038db48 (placeholder name)
    void changeToAction();

protected:
    // Inline-only in the original (name guess; evidence: enter_'s ActorConstDataAccess sits below the param pack).
    void changeToApproach() {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_68, "TargetPos", -1);
        changeChild("接近", &pack);
    }

    struct Params {
        // static_param at offset 0x38
        const float* mGrabCheckRadius_s{};
        // static_param at offset 0x40
        const bool* mCanGrabHeavy_s{};
        // static_param at offset 0x48
        const sead::Vector3f* mAttOffset_s{};
        // dynamic_param at offset 0x50
        ksys::act::BaseProcLink* mTargetActor_d{};
        // static_param at offset 0x58
        const float* mChaseItemDist_s{};
        // static_param at offset 0x60
        const float* mChaseItemSpeed_s{};
    };
    Params mParams;
    sead::Vector3f _68;
    bool _74{};
};

}  // namespace uking::ai

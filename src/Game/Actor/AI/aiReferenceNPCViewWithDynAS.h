#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class ReferenceNPCViewWithDynAS : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReferenceNPCViewWithDynAS, ksys::act::ai::Ai)
public:
    explicit ReferenceNPCViewWithDynAS(const InitArg& arg);
    ~ReferenceNPCViewWithDynAS() override;

    bool isFinished() const override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // inline-only in the original; name is a guess (enter_ inlines it twice, calc_ once; its param pack sits
    // above the callers' locals): changes to the "待機" child with the dynamic AS key
    void changeToWait() {
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mParams.mDynASKey_d, "DynASKey", -1);
        changeChild("待機", &pack);
    }
    // 0x710053b7b4 (placeholder name): the position of the linked NPC (_58, or the first NPC among the
    // map object's linked objects, which then becomes _58)
    bool sub_710053B7B4(sead::Vector3f* pos);
    // 0x710053b8f4 (placeholder name): whether `pos` is within TurnStartAngle of the actor's front
    bool sub_710053B8F4(const sead::Vector3f& pos);
    // 0x710053bb30: changes to the "回転" child with the dynamic AS key
    void sub_710053BB30(const sead::Vector3f& pos);
    struct Params {
        // static_param at offset 0x38
        const float* mTurnStartAngle_s{};
        // static_param at offset 0x40
        const bool* mCheckOnce_s{};
        // dynamic_param at offset 0x48
        sead::SafeString mDynASKey_d{};
    };
    Params mParams;
    ksys::act::BaseProcLink _58;
};
KSYS_CHECK_SIZE_NX150(ReferenceNPCViewWithDynAS, 0x68);

}  // namespace uking::ai

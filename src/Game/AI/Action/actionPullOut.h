#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PullOut : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(PullOut, ActionWithAS)
public:
    explicit PullOut(const InitArg& arg);
    ~PullOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x30
        const sead::Vector3f* mAnimGrabPos_s{};
        // dynamic_param at offset 0x38
        ksys::act::BaseProcLink* mTargetActor_d{};
    };
    Params mParams;
    Unk_71023b1608 _40{mActor};
    Unk_71024505b8 _70;

    // 0x7100223964 / 0x7100223b90 (declared only).
    void sub_7100223964();
    void sub_7100223B90();
};
KSYS_CHECK_SIZE_NX150(PullOut, 0xc0);

}  // namespace uking::action

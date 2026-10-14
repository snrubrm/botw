#pragma once

#include <math/seadMatrix.h>

#include "Game/Actor/Action/actionUnk_7102451320.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnGiantAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TurnGiantAttack, ksys::act::ai::Action)
public:
    explicit TurnGiantAttack(const InitArg& arg);
    ~TurnGiantAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71002a182c (declared only): the body of calc_ is out of line in the original.
    void sub_71002A182C();
    void sub_71002A1A08();
    void sub_71002A1C38();
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mRotBaseBoneName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _50;
    sead::Vector3f _5c;
    sead::Matrix33f _68;
    f32 _8c = 0.0f;
    Unk_7102451320 _90;
};
KSYS_CHECK_SIZE_NX150(TurnGiantAttack, 0x128);

}  // namespace uking::action

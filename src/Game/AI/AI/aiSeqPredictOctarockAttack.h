#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqPredictOctarockAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqPredictOctarockAttack, ksys::act::ai::Ai)
public:
    explicit SeqPredictOctarockAttack(const InitArg& arg);
    ~SeqPredictOctarockAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_7100564154();

    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetVel_d{};
    bool _48 = true;
    sead::Vector3f _4c;
    sead::Vector3f _58;
};
KSYS_CHECK_SIZE_NX150(SeqPredictOctarockAttack, 0x68);

}  // namespace uking::ai

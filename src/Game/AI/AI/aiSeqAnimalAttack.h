#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqAnimalAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqAnimalAttack, ksys::act::ai::Ai)
public:
    explicit SeqAnimalAttack(const InitArg& arg);
    ~SeqAnimalAttack() override;

    bool isFinished() const override;

    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsUseAfterAttackState_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _48;
    bool _54 = false;
};
KSYS_CHECK_SIZE_NX150(SeqAnimalAttack, 0x58);

}  // namespace uking::ai

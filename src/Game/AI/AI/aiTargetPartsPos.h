#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPartsPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPartsPos, TargetPosAI)
public:
    explicit TargetPartsPos(const InitArg& arg);
    ~TargetPartsPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(sead::Vector3f* pos) override;

protected:
    // static_param at offset 0x40
    sead::SafeString mPartsName_s{};
};

}  // namespace uking::ai

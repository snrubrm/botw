#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCMoveToRailPoint : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCMoveToRailPoint, ksys::act::ai::Ai)
public:
    explicit NPCMoveToRailPoint(const InitArg& arg);
    ~NPCMoveToRailPoint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    int* mRailPointIndex_d{};
    // dynamic_param at offset 0x40
    bool* mIsTurnToRailPointDir_d{};
    // dynamic_param at offset 0x48
    bool* mIsAlignmentAnchor_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mRailUniqueName_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mASName_d{};
    sead::Vector3f _70;
    sead::Vector3f _7c;
};
KSYS_CHECK_SIZE_NX150(NPCMoveToRailPoint, 0x88);

}  // namespace uking::ai

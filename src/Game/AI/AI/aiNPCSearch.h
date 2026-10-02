#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCSearch : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCSearch, ksys::act::ai::Ai)
public:
    explicit NPCSearch(const InitArg& arg);
    ~NPCSearch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsHearing_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTarget_d{};
    bool _50 = false;
};
KSYS_CHECK_SIZE_NX150(NPCSearch, 0x58);

}  // namespace uking::ai

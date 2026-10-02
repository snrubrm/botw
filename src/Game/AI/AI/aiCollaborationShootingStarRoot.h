#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CollaborationShootingStarRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CollaborationShootingStarRoot, ksys::act::ai::Ai)
public:
    explicit CollaborationShootingStarRoot(const InitArg& arg);
    ~CollaborationShootingStarRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    sead::SafeString* mCollaboShootingStarId_a{};
    u32 _40{};
    sead::SafeString _48;
    void* _58{};
    u32 _60{};
    void* _68{};
    u32 _70{};
};

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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
    Unk_71012419b4 _58;
};

}  // namespace uking::ai

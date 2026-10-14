#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

class Unk_7102450fa8;
class Unk_71025afb58;

namespace uking::ai {

class PriestBoss : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBoss, ksys::act::ai::Ai)
public:
    explicit PriestBoss(const InitArg& arg);
    ~PriestBoss() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();

protected:
    Unk_7102450fa8* sub_7100505BE4();
    // 0x7100505c74: the "Grave" part actor of the enemy exists
    bool sub_7100505C74();
    // 0x7100505bd8: stores the unit into the PriestBossMetaAIUnit variable
    void sub_7100505BD8(Unk_71025afb58* unit);

    // aitree_variable at offset 0x38
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai

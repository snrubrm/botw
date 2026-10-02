#pragma once

#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class ActorConstDataAccess;
class BaseProcLink;
}  // namespace ksys::act

namespace uking::ai {

class PriestBossMeta : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossMeta, ksys::act::ai::Ai)
public:
    explicit PriestBossMeta(const InitArg& arg);
    ~PriestBossMeta() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // The PriestBossMetaAIUnit object (Unk_7102450fa8) shared through the AI tree variable.
    Unk_7102450fa8* sub_7100525A88();
    bool sub_7100525B18(int idx, ksys::act::ActorConstDataAccess* accessor);
    bool sub_7100525BC0(int idx, ksys::act::BaseProcLink* link);

    // aitree_variable at offset 0x38
    int* mMetaAILife_a{};
    // aitree_variable at offset 0x40
    int* mMetaAIMaxLife_a{};
    // aitree_variable at offset 0x48
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai

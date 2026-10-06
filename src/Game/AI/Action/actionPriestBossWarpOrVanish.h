#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class ActorConstDataAccess;
}

namespace uking::action {

class PriestBossWarpOrVanish : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossWarpOrVanish, ksys::act::ai::Action)
public:
    explicit PriestBossWarpOrVanish(const InitArg& arg);
    ~PriestBossWarpOrVanish() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710022134c (placeholder name): Unk_7102450fa8::sub_71007194D4 on the meta AI unit.
    bool sub_710022134C(int idx, ksys::act::ActorConstDataAccess* accessor);

    // aitree_variable at offset 0x20
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::action

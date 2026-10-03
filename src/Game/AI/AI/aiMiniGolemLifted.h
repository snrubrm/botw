#pragma once

#include "Game/AI/AI/aiEnemyLifted.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemLifted : public EnemyLifted {
    SEAD_RTTI_OVERRIDE(MiniGolemLifted, EnemyLifted)
public:
    explicit MiniGolemLifted(const InitArg& arg);
    ~MiniGolemLifted() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m34() override;

protected:
    // aitree_variable at offset 0x70
    void* mGolemChemicalController_a{};
    Unk_7102451a18 _78{mActor};
};

}  // namespace uking::ai

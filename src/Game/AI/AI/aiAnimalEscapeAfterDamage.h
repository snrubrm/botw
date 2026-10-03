#pragma once

#include "Game/AI/AI/aiAnimalEscapeAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalEscapeAfterDamage : public AnimalEscapeAI {
    SEAD_RTTI_OVERRIDE(AnimalEscapeAfterDamage, AnimalEscapeAI)
public:
    explicit AnimalEscapeAfterDamage(const InitArg& arg);
    ~AnimalEscapeAfterDamage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m36() override;
    bool m37() override;

    void sub_7100304854();

protected:
};

}  // namespace uking::ai

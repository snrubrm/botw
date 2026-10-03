#pragma once

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemSleepNormal : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(GolemSleepNormal, SpecialEnemySleep)
public:
    explicit GolemSleepNormal(const InitArg& arg);
    ~GolemSleepNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleAck_(const ksys::MessageAck* ack) override;
    void m34() override;

protected:
    // aitree_variable at offset 0x60
    void* mGolemChemicalController_a{};
    Unk_7102451c98 _68;
    Unk_7102396b48 _90{mActor, 0x800002e};
    Unk_7102396b20 _a8{mActor, 0x800002d};
};

}  // namespace uking::ai

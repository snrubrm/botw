#pragma once

#include <math/seadVector.h>

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class GiantSleepNormal : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(GiantSleepNormal, SpecialEnemySleep)
public:
    explicit GiantSleepNormal(const InitArg& arg);
    ~GiantSleepNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m34() override;
    void m35() override;

protected:
    // static_param at offset 0x60
    const float* mForceAwakeDist_s{};
    // static_param at offset 0x68
    sead::SafeString mAwakeRbName_s{};
    ksys::phys::RigidBody* _78{};
    sead::Vector3f _80;
    sead::Vector3f _8c;
    u32 _98 = 0;
};

}  // namespace uking::ai

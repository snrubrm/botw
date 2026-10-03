#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AmbushableWeaponShoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AmbushableWeaponShoot, ksys::act::ai::Ai)
public:
    explicit AmbushableWeaponShoot(const InitArg& arg);
    ~AmbushableWeaponShoot() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100300908 (placeholder name)
    void sub_7100300908();

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai

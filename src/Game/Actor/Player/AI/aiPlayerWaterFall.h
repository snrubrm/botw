#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::map {
class Rail;
}

namespace uking::ai {

class PlayerWaterFall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerWaterFall, ksys::act::ai::Ai)
public:
    explicit PlayerWaterFall(const InitArg& arg);
    ~PlayerWaterFall() override;
    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool isFinished() const override;
    bool isFailed() const override;

protected:
    sead::FixedSafeString<32> _38{""};
    sead::Vector3f _70{0.0f, 0.0f, 0.0f};
    sead::Vector3f _7c{0.0f, 0.0f, 0.0f};
    ksys::map::Rail* _88 = nullptr;
    f32 _90 = 0;  // the controller's water flow rate, saved while the action runs
};
KSYS_CHECK_SIZE_NX150(PlayerWaterFall, 0x98);

}  // namespace uking::ai

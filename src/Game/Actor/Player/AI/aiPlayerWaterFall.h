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
    void leave_() override;
    void loadParams_() override;

    bool isFinished() const override;
    bool isFailed() const override;

protected:
    sead::FixedSafeString<32> _38;
    sead::Vector3f _70{};
    sead::Vector3f _7c{};
    ksys::map::Rail* _88 = nullptr;
    s32 _90 = 0;
};
KSYS_CHECK_SIZE_NX150(PlayerWaterFall, 0x98);

}  // namespace uking::ai

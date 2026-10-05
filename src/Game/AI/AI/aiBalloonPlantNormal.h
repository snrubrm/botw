#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

class BalloonPlantNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BalloonPlantNormal, ksys::act::ai::Ai)
public:
    explicit BalloonPlantNormal(const InitArg& arg);
    ~BalloonPlantNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710032782C();

protected:
    bool sub_7100327B54();
    void sub_7100327C24();
    void sub_7100327D48();

    // static_param at offset 0x38
    const float* mRopeLength_s{};
    // static_param at offset 0x40
    sead::SafeString mRopeActorName_s{};
    ksys::act::BaseProcHandle _50;
    sead::FixedSafeString<64> _60;
    sead::Vector3f _b8;
    bool _c4 = false;
    u32 _c8 = 0;
};
KSYS_CHECK_SIZE_NX150(BalloonPlantNormal, 0xd0);

}  // namespace uking::ai

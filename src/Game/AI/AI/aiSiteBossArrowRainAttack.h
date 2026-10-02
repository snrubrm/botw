#pragma once

#include "KingSystem/System/Timer.h"

#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossArrowRainAttack : public SiteBossReflectArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossArrowRainAttack, SiteBossReflectArrowRoot)
public:
    explicit SiteBossArrowRainAttack(const InitArg& arg);
    ~SiteBossArrowRainAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35() override;
    void m37() override;
    void m42() override;
    s32 m43() override;
    void m45(sead::Vector3f* out) override;
    bool m48() override;

protected:
    // in SiteBossReflectArrowRoot's tail padding
    bool _50c = false;
    bool _50d = false;
    ksys::Timer _510;
};
KSYS_CHECK_SIZE_NX150(SiteBossArrowRainAttack, 0x520);

}  // namespace uking::ai

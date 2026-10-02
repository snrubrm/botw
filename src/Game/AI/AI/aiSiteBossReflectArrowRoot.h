#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

#include "Game/AI/AI/aiSiteBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossReflectArrowRoot : public SiteBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossReflectArrowRoot, SiteBossShootNormalArrowRoot)
public:
    explicit SiteBossReflectArrowRoot(const InitArg& arg);
    ~SiteBossReflectArrowRoot() override;
    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_7100582688();

    bool m34() override;
    void m37() override;
    void m41() override;
    s32 m43() override;
    void m45(sead::Vector3f* out) override;
    void m46(sead::Vector3f* out) override;
    bool m48() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool sub_7100582C20(sead::Vector3f* out);

protected:
    // dynamic_param at offset 0x338
    bool* mIsReflectAmongChild_d{};
    // dynamic_param at offset 0x340
    ksys::act::BaseProcLink* mTargetActor_d{};
    sead::SafeArray<ksys::act::BaseProcLink, 20> _348;
    sead::SafeArray<bool, 20> _488;
    sead::SafeArray<bool, 20> _49c;
    sead::SafeArray<f32, 20> _4b0;
    s32 _500 = 0;
    s32 _504 = -1;
    s32 _508 = -1;
};
KSYS_CHECK_SIZE_NX150(SiteBossReflectArrowRoot, 0x510);

}  // namespace uking::ai

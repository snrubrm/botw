#pragma once

#include "Game/AI/AI/aiSandwormNormalBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNormal : public SandwormNormalBase {
    SEAD_RTTI_OVERRIDE(SandwormNormal, SandwormNormalBase)
public:
    explicit SandwormNormal(const InitArg& arg);
    ~SandwormNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m43() override;
    bool m44(const sead::Vector3f& pos) override;
    bool m72(Unk2* out, Unk1* info) override;

protected:
};

}  // namespace uking::ai

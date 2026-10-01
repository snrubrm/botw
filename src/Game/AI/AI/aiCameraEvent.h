#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEvent : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraEvent, CameraAI)
public:
    explicit CameraEvent(const InitArg& arg);

    bool m34(sead::Heap* heap) override;
    void m35(ksys::act::ai::InlineParamPack* params) override;
    void m36() override;
    void m37() override;
    void m38() override;

    virtual bool m39(sead::Heap* heap) { return true; }
    virtual void m40(ksys::act::ai::InlineParamPack* params) {}
    virtual void m41() {}
    virtual void m42() {}
    virtual void m43() {}

protected:
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEvent : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraEvent, CameraAction)
public:
    explicit CameraEvent(const InitArg& arg);

protected:
    bool m32(sead::Heap* heap) override;
    void m33() override;
    void m34() override;
    void m35() override;
    void m36() override;
    // inline: emitted in the CameraEventAnim translation unit in the original.
    int m38() override { return 1; }
    void m41() override;

    virtual bool m42(sead::Heap* heap) { return true; }
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
};

}  // namespace uking::action

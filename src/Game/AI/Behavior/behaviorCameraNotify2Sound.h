#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CameraNotify2Sound : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CameraNotify2Sound, ksys::act::ai::Behavior)
public:
    explicit CameraNotify2Sound(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mCameraStateNotify2Sound_s{};
    /* 0x30 */ bool _30 = false;
};
KSYS_CHECK_SIZE_NX150(CameraNotify2Sound, 0x38);

}  // namespace uking::behavior

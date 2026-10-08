#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMagneCatch : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraMagneCatch, CameraLockOnBase)
public:
    explicit CameraMagneCatch(const InitArg& arg);
    ~CameraMagneCatch() override;

protected:
    void m43() override;
    float m44() override;
    float m45() override;
    bool m51() override;
    bool m55(f32* out0, f32* out1) override;
    bool m60(int idx) override { return u32(idx) < 3; }

    void sub_7100775B78(act::Unk_71009214b8* out);
    void sub_7100775B80(act::Unk_71009214b8* out);
    void sub_7100775B88(act::Unk_71009214b8* out);
    void sub_7100775F84(act::Unk_71009214b8* out, f32 rate);

    // Members not recovered yet (class size from the factory).
    u8 _1c0[0x454 - 0x1c0];
    f32 _454 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(CameraMagneCatch, 0x458);

}  // namespace uking::action

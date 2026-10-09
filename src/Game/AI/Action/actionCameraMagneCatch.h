#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include <container/seadSafeArray.h>
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMagneCatch : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraMagneCatch, CameraLockOnBase)
public:
    explicit CameraMagneCatch(const InitArg& arg);
    ~CameraMagneCatch() override;

protected:
    bool m42(sead::Heap* heap) override;
    void m43() override;
    void m46(act::Unk_7100922700* polar, bool reset) override;
    sead::PtrArray<Unk_7102457a80>* m47() override;
    const sead::PtrArray<Unk_7102457a80>* m48() override;
    sead::PtrArray<Unk_7102457b00>* m49() override;
    const sead::PtrArray<Unk_7102457b00>* m50() override;
    float m44() override;
    float m45() override;
    bool m51() override;
    void m52() override;
    bool m55(f32* out0, f32* out1) override;
    bool m60(int idx) override { return u32(idx) < 3; }

    void sub_7100775B78(act::Unk_71009214b8* out);
    void sub_7100775B80(act::Unk_71009214b8* out);
    void sub_7100775B88(act::Unk_71009214b8* out);
    void sub_7100775F84(act::Unk_71009214b8* out, f32 rate);

    // Native ctor 0x71007758c4 and m42 prove the delegates, camera states and pointer arrays.
    sead::Delegate1<CameraMagneCatch, act::Unk_71009214b8*> _1c0;
    sead::Delegate1<CameraMagneCatch, act::Unk_71009214b8*> _1e0;
    sead::Delegate1<CameraMagneCatch, act::Unk_71009214b8*> _200;
    sead::SafeArray<Unk_7102457ac0, 3> _220{};
    sead::FixedPtrArray<Unk_7102457a80, 3> _310;
    Unk_7102457b50 _338;
    Unk_7102457b50 _388;
    Unk_7102457b28 _3d8;
    sead::FixedPtrArray<Unk_7102457b00, 3> _428;
    f32 _450 = angleStuff(0);
    f32 _454 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(CameraMagneCatch, 0x458);

}  // namespace uking::action

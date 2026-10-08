#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraClimbObj : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraClimbObj, CameraAction)
public:
    explicit CameraClimbObj(const InitArg& arg);
    ~CameraClimbObj() override;

protected:
    void m33() override;
    void m35() override;
    bool m32(sead::Heap* heap) override;
    void m36() override;

    // 0x7100755c80 (placeholder name; called by m34): stores the polar angle of the camera's offset to its
    // target in _c8 (from the offset to the camera actor's _2b8 when it is not vertical), once (_124 bit 0).
    void sub_7100755C80();
    // 0x7100755d60 (placeholder name; called by m34): the m33 setup of _68 / _74 / _80, eased by the camera's frame
    // rate instead of set directly.
    void sub_7100755D60();

    sead::Vector3f _4c = sead::Vector3f::zero;
    sead::Vector3f _58 = sead::Vector3f::zero;
    f32 _64 = 0;
    sead::Vector3f _68 = sead::Vector3f::zero;
    sead::Vector3f _74 = sead::Vector3f::zero;
    f32 _80 = 0;
    f32 _84 = angleStuff(0);
    f32 _88 = angleStuff(0);
    f32 _8c = angleStuff(0);
    f32 _90 = angleStuff(0);
    f32 _94 = 0;
    f32 _98 = 0;
    f32 _9c = 0;
    f32 _a0 = 0;
    u8 _a4[0xa8 - 0xa4];
    act::Unk_7102459dd8 _a8;
    f32 _c8 = angleStuff(0);
    u8 _cc[0xd0 - 0xcc];
    // static_param at offset 0xd0
    const float* mLat_s{};
    // static_param at offset 0xd8
    const float* mLatMin_s{};
    // static_param at offset 0xe0
    const float* mLatMax_s{};
    // static_param at offset 0xe8
    const float* mLatStickScale_s{};
    // static_param at offset 0xf0
    const float* mLngStickScale_s{};
    // static_param at offset 0xf8
    const float* mRadius_s{};
    // static_param at offset 0x100
    const float* mOffsetY_s{};
    // static_param at offset 0x108
    const float* mFovy_s{};
    f32 _110 = 0;
    f32 _114 = 0;
    f32 _118 = 0;
    f32 _11c = 0;
    f32 _120 = 0;
    u8 _124 = 0;
    u8 _125 = 3;
    u8 _126[0x128 - 0x126];
};
KSYS_CHECK_SIZE_NX150(CameraClimbObj, 0x128);

}  // namespace uking::action

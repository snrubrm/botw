#pragma once

#include <gfx/seadColor.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/StringBoard.h"

namespace uking::behavior {

// The members after the parameters (0x98-0x130) hold the values of the (stubbed in release builds)
// string board; their names are unknown.
class ShowConstStringBoard : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ShowConstStringBoard, ksys::act::ai::Behavior)
public:
    explicit ShowConstStringBoard(const InitArg& arg);
    ~ShowConstStringBoard() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;

    /* 0x28 */ const float* mTextScale_s{};
    /* 0x30 */ const float* mBGRotateRadian_s{};
    /* 0x38 */ const float* mBGAlpha_s{};
    /* 0x40 */ const float* mLineAlpha_s{};
    /* 0x48 */ sead::SafeString mText_s{};
    /* 0x58 */ const sead::Vector3f* mTextColor_s{};
    /* 0x60 */ const sead::Vector3f* mTextShadowOffset_s{};
    /* 0x68 */ const sead::Vector3f* mTextShadowColor_s{};
    /* 0x70 */ const sead::Vector3f* mBGScale_s{};
    /* 0x78 */ const sead::Vector3f* mBGCenterOffset_s{};
    /* 0x80 */ const sead::Vector3f* mBGColor_s{};
    /* 0x88 */ const sead::Vector3f* mLineColor_s{};
    /* 0x90 */ void* _90 = nullptr;
    /* 0x98 */ s32 _98 = 3;
    /* 0xa0 */ sead::SafeString _a0{};
    /* 0xb0 */ f32 _b0 = 1.0f;
    /* 0xb4 */ u32 _b4 = 0;
    /* 0xb8 */ sead::Color4f _b8 = sead::Color4f::cBlack;
    /* 0xc8 */ sead::Color4f _c8 = sead::Color4f::cBlack;
    /* 0xd8 */ sead::Vector2f _d8{0, 0};
    /* 0xe0 */ sead::Vector2f _e0{1, 1};
    /* 0xe8 */ sead::Color4f _e8 = sead::Color4f::cBlue;
    /* 0xf8 */ sead::Vector3f _f8{0, 0, 0};
    /* 0x104 */ f32 _104 = 0;
    /* 0x108 */ f32 _108 = 0;
    /* 0x10c */ f32 _10c = 0;
    /* 0x110 */ sead::Vector3f _110{0, 0, 0};
    /* 0x11c */ sead::Color4f _11c = sead::Color4f::cBlack;
    /* 0x130 */ ksys::StringBoard _130;
};
KSYS_CHECK_SIZE_NX150(ShowConstStringBoard, 0x138);

}  // namespace uking::behavior

#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// TODO: the members after the parameters (0x98-0x138: colours, a SafeString, a vtable pointer) are not declared yet.
class ShowConstStringBoard : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ShowConstStringBoard, ksys::act::ai::Behavior)
public:
    explicit ShowConstStringBoard(const InitArg& arg);
    ~ShowConstStringBoard() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100d670b8)

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
    /* 0x98 */ u8 _98[0x138 - 0x98];
};
KSYS_CHECK_SIZE_NX150(ShowConstStringBoard, 0x138);

}  // namespace uking::behavior

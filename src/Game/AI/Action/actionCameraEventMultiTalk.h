#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

using Unk_CameraEventMultiTalkElem = act::Unk_71009241ac;

class CameraEventMultiTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMultiTalk, CameraEvent)
public:
    explicit CameraEventMultiTalk(const InitArg& arg);
    ~CameraEventMultiTalk() override;

protected:
    void m43() override;
    void m44() override;
    void m45() override;
    void m46() override;
    void sub_7100765C78();
    void sub_7100765D60();
    void sub_7100765E84();
    void sub_7100765FA8();

    sead::Vector3f _4c = sead::Vector3f::zero;
    f32 _58 = 0.0f;
    f32 _5c = 0.0f;
    sead::Vector3f _60 = sead::Vector3f::zero;
    sead::Vector3f _6c = sead::Vector3f::zero;
    f32 _78 = 0.0f;
    f32 _7c = 0.0f;
    f32 _80 = 0.0f;
    f32 _84 = 0.0f;
    f32 _88 = 0.0f;
    uking::act::Unk_7102459dd8 _90;
    Unk_CameraEventMultiTalkElem _b0[3];
    s32 _260 = 0;
    const f32* mLatMin_s = nullptr;
    const f32* mLatMax_s = nullptr;
    const f32* mLatStickScale_s = nullptr;
    const f32* mLngStickScale_s = nullptr;
    const f32* mRadiusOffset_s = nullptr;
    const f32* mConnect_s = nullptr;
    f32* mFovy_d = nullptr;
    act::Unk_71009241ac::Params mTargets_d[3];
    f32 _318 = 0.0f;
    f32 _31c = 0.0f;
    f32 _320 = 0.0f;
    f32 _324 = 0.0f;
    f32 _328 = 0.0f;
    sead::BitFlag8 _32c;
};

KSYS_CHECK_SIZE_NX150(CameraEventMultiTalk, 0x330);

}  // namespace uking::action

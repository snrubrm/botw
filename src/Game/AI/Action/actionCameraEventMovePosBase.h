#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys {
class Message;
}

namespace ksys::act {
class ActorConstDataAccess;
}

namespace ksys::map {
class Object;
}

namespace uking::action {

// Moves the camera to a position / look-at point given relative to up to two target actors
// (TargetActor1 / TargetActor2: -1 = none, 0-3 = kind). The parameters are loaded by the
// subclasses (static for CameraEventMovePos, mostly dynamic for CameraEventMovePosFlow).
class CameraEventMovePosBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMovePosBase, CameraEvent)
public:
    // "Pattern1" parameters.
    struct Pattern {
        const f32* at_x;
        const f32* at_y;
        const f32* at_z;
        const f32* pos_x;
        const f32* pos_y;
        const f32* pos_z;
        const f32* fovy;
        const bool* use;
    };

    explicit CameraEventMovePosBase(const InitArg& arg);
    // inline: the CameraEventMovePos / CameraEventMovePosFlow destructors inline it.
    ~CameraEventMovePosBase() override = default;

    bool handleMessage_(const ksys::Message& message) override;

protected:
    void m43() override;
    void m44() override;
    void m46() override;

    // Fovy of `pattern`.
    virtual float m47(const Pattern& pattern);
    // Accept1FrameDelay.
    virtual bool m48();

    void sub_7100760DF8();
    void sub_7100761338();
    bool sub_7100761F84(const act::Unk_71009214b8& prev, act::Unk_71009214b8* state);
    void sub_710076203C();
    void sub_7100762144();
    bool sub_71007624A8(s16 target, ksys::act::BaseProcLink* link, sead::Matrix34f* mtx,
                        sead::Vector3f* pos, u8* state, u8 link_flag, u8 mtx_flag);
    // Delegate callbacks for target 1 / 2.
    void sub_710076264C(ksys::act::ActorConstDataAccess* accessor);
    void sub_7100762698(ksys::map::Object* object);
    void sub_71007626AC(s16 target, const sead::SafeString& actor_name,
                        const sead::SafeString& unique_name, ksys::act::BaseProcLink* link,
                        u8* state, u8 link_flag,
                        sead::IDelegate1<ksys::act::ActorConstDataAccess*>* on_actor,
                        sead::IDelegate1<ksys::map::Object*>* on_object);
    void sub_710076294C(ksys::act::ActorConstDataAccess* accessor);
    void sub_7100762998(ksys::map::Object* object);
    // Appends "<flow><entry>" of the active event to `message`.
    void sub_71007629AC(sead::BufferedSafeString* message);
    void sub_7100762AB8(ksys::map::Object* object, sead::Matrix34f* mtx, u8* state, u8 flag1,
                        u8 flag2);
    void sub_7100762C2C(ksys::act::BaseProcLink* link, sead::Matrix34f* mtx, sead::Vector3f* pos,
                        u8 flag);
    void sub_7100762D14(act::Unk_71009214b8* from, act::Unk_71009214b8* to);
    void sub_71007630E8(act::Unk_71009214b8* from, act::Unk_71009214b8* to);
    void sub_71007633A4(act::Unk_71009214b8* state);
    void sub_710076353C(act::Unk_71009214b8* state);

    act::Unk_71009214b8 _4c;
    act::Unk_71009214b8 _84;
    act::Unk_71009214b8 _bc;
    act::Unk_71009214b8 _f4;
    act::Unk_71009214b8 _12c;
    // TargetActor1 / TargetActor2 (-1 = none).
    s16 _164 = -1;
    s16 _166 = -1;
    ksys::act::BaseProcLink _168;
    ksys::act::BaseProcLink _178;
    sead::Matrix34f _188 = sead::Matrix34f::ident;
    sead::Matrix34f _1b8 = sead::Matrix34f::ident;
    sead::Vector3f _1e8 = sead::Vector3f::zero;
    sead::Vector3f _1f4 = sead::Vector3f::zero;
    f32 _200 = 0;
    act::Unk_7102459dd8 _208;
    f32 _228{};
    f32 _22c{};
    Pattern mPattern{};
    const s32* mTargetActor1{};
    const s32* mTargetActor2{};
    const s32* mAtAppendMode{};
    const s32* mPosAppendMode{};
    const s32* mFovyAppendMode{};
    const s32* mMotionMode{};
    const s32* mBaseMode{};
    // dynamic2_param at offset 0x2a8
    int* mReviseModeEnd_d{};
    // dynamic2_param at offset 0x2b0
    float* mLatShiftRange_d{};
    // dynamic2_param at offset 0x2b8
    float* mLngShiftRange_d{};
    // dynamic2_param at offset 0x2c0
    int* mActorIgnoringCollision_d{};
    float* mCount{};
    float* mCushion{};
    bool* mStartCalcOnly{};
    bool* mCollisionInterpolateSkip{};
    sead::SafeString mActorName1;
    sead::SafeString mActorName2;
    sead::SafeString mUniqueName1;
    sead::SafeString mUniqueName2;
    sead::SafeString mGameDataVec3fCameraPos;
    sead::SafeString mGameDataVec3fCameraAt;
    f32 _348 = 0;
    f32 _34c = 0;
    s32 _350 = -1;
    s16 _354 = 0;
    u8 _356 = 0;
    u8 _357 = 2;
    u8 _358 = 2;
    u8 _359 = 4;
    u8 _35a = 4;
    u8 _35b = 2;
    u8 _35c = 2;
    u8 _35d = 2;
    u8 _35e = 3;
    u8 _35f = 3;
};
KSYS_CHECK_SIZE_NX150(CameraEventMovePosBase, 0x360);

}  // namespace uking::action

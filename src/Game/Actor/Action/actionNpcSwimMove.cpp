#include "Game/Actor/Action/actionNpcSwimMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

void sub_71006F54EC(ksys::phys::CharacterController* controller);
void sub_71006F5538(ksys::phys::CharacterController* controller);

// Name and signature are inferred from the call sites (also used by SwimGetUp and others).
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

extern const f32 sUnk_7101EC1934;
extern const f32 sUnk_7101EC1938;
extern const f32 sUnk_7101EC193C;

static const f32 sUnk_7101E79B54 = 0.6f;
static const f32 sUnk_7101E79B58 = 0.15f;
static const f32 sUnk_7101E79B5C = 0.002f;
static const f32 sUnk_7101E79B60 = 0.4f;

namespace uking::action {

void NpcSwimMove::m32() {
    if (m33().isEmpty())
        return;
    playAS(m33().cstr(), true, 0, 0, -1.0f);
}

NpcSwimMove::NpcSwimMove(const InitArg& arg)
    : ksys::act::ai::Action(arg),
      _a0{&sUnk_7101E79B54, &sUnk_7101E79B58, &sUnk_7101E79B5C,
            &sUnk_7101EC1934, &sUnk_7101EC1938, &sUnk_7101EC193C, 0.0f, 0.0f, 0.0f},
      _e0{&sUnk_7101E79B60, 0.0f}, _f0(0.0f, 0.0f, 0.0f),
      _108(1.309f), _10c(1.0f), _110(0.0f), _114(true) {}

NpcSwimMove::~NpcSwimMove() = default;

bool NpcSwimMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: position loads, normalization stores and the finished epilogue are reordered.
void NpcSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    _10c = 1.0f;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _98.sub_710072AD1C(controller);
    if (controller->_210 > *mInWaterDepth_s) {
        _114 = true;
        sub_71006F54EC(controller);
    } else {
        _114 = false;
        sub_71006F5538(controller);
    }
    auto* npc = sead::DynamicCast<act::NPC>(actor);
    if (npc)
        npc->_fe8 |= 0x10000000;

    _110 = mActor->getVelocity().y * 30.0f;
    const auto target = *mTargetPos_d;
    const auto position = mActor->getMtx().getTranslation();
    const f32 fin_height = *mFinHeight_s;
    if (!(fin_height >= 0.0f && sead::Mathf::abs(target.y - position.y) > fin_height)) {
        const sead::Vector2f diff(target.x - position.x, target.z - position.z);
        if (!(diff.length() > *mFinRadius_s)) {
            setFinished();
            return;
        }
    }
    if (npc) {
        _108 = npc->sub_7100022B9C(m33());
        if (_108 <= 0.0f)
            _108 = 1.309f;
    } else {
        _108 = 1.309f;
    }
    _a0._30 = 0.0f;
    _a0._34 = 0.0f;
    _a0._38 = 0.0f;
    _e0._8 = 0.0f;
    if (auto* as_list = actor->getASList()) {
        sead::Vector3f front;
        actor->getMtx().getBase(front, 2);
        front.y = 0.0f;
        front.normalize();
        sead::Vector3f to_target(mTargetPos_d->x - actor->getMtx().m[0][3], 0.0f,
                                  mTargetPos_d->z - actor->getMtx().m[2][3]);
        to_target.normalize();
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
        as_list->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    }
    m32();
    _10c = 1.0f;
}

void NpcSwimMove::leave_() {
    auto* actor = mActor;
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 &= ~0x10000000;
    _98.resetMotionType(_98.sub_710072ACF8(actor));
}

void NpcSwimMove::loadParams_() {
    getStaticParam(&mRotRadPerSec_s, "RotRadPerSec");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinHeight_s, "FinHeight");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NpcSwimMove::sub_71002001A4() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        _110 = 0.0f;
        return;
    }
    f32 speed;
    {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        speed = velocity.y / 30.0f;
    }
    f32 out = speed;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    sub_71005DF820(&out, speed, depth, *mFloatDepth_s, *mInWaterDepth_s,
                   *mFloatRadius_s, *mFloatCycleTime_s, *mChangeDepthSpeed_s);
    _110 = out * 30.0f;
}

void NpcSwimMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

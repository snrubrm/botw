#include "Game/Actor/Action/actionNpcSwimNavMove.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// Name and signature are inferred from the call sites (also used by SwimGetUp and others).
void sub_71006F54EC(ksys::phys::CharacterController* controller);
void sub_71006F5538(ksys::phys::CharacterController* controller);

void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

extern const f32 sUnk_7101EC1934;
extern const f32 sUnk_7101EC1938;
extern const f32 sUnk_7101EC193C;

static const f32 sUnk_7101E79B64 = 0.6f;
static const f32 sUnk_7101E79B68 = 0.15f;
static const f32 sUnk_7101E79B6C = 0.002f;
static const f32 sUnk_7101E79B70 = 0.4f;

namespace uking::action {

void NpcSwimNavMove::sub_7100201974() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        _128 = 0.0f;
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
    sub_71005DF820(&out, speed, depth, *mFloatDepth_s, *mInWaterDepth_s, *mFloatRadius_s,
                   *mFloatCycleTime_s, *mChangeDepthSpeed_s);
    _128 = out * 30.0f;
}

void NpcSwimNavMove::m34() {
    if (m35().isEmpty())
        return;
    playAS(m35().cstr(), true, 0, 0, -1.0f);
}

NpcSwimNavMove::NpcSwimNavMove(const InitArg& arg)
    : RandomMoveAction(arg),
      _b8{&sUnk_7101E79B64, &sUnk_7101E79B68, &sUnk_7101E79B6C,
            &sUnk_7101EC1934, &sUnk_7101EC1938, &sUnk_7101EC193C, 0.0f, 0.0f, 0.0f},
      _f8{&sUnk_7101E79B70, 0.0f}, _108(0.0f, 0.0f, 0.0f),
      _120(1.309f), _124(1.0f), _128(0.0f), _12c(true) {}

NpcSwimNavMove::~NpcSwimNavMove() = default;

bool NpcSwimNavMove::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

// NON_MATCHING: same scheduling differences as NpcSwimMove::enter_ (finished epilogue placement, store order).
void NpcSwimNavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    _124 = 1.0f;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _130.sub_710072AD1C(controller);
    if (controller->_210 > *mInWaterDepth_s) {
        _12c = true;
        sub_71006F54EC(controller);
    } else {
        _12c = false;
        sub_71006F5538(controller);
    }
    auto* npc = sead::DynamicCast<act::NPC>(actor);
    if (npc)
        npc->_fe8 |= 0x10000000;

    _128 = mActor->getVelocity().y * 30.0f;
    const auto position = mActor->getMtx().getTranslation();
    const auto target = *mTargetPos_d;
    const f32 fin_height = *mFinHeight_s;
    if (!(fin_height >= 0.0f && sead::Mathf::abs(target.y - position.y) > fin_height)) {
        const sead::Vector2f diff(target.x - position.x, target.z - position.z);
        if (!(diff.length() > *mFinRadius_s)) {
            setFinished();
            return;
        }
    }
    if (npc) {
        _120 = npc->sub_7100022B9C(m35());
        if (_120 <= 0.0f)
            _120 = 1.309f;
    } else {
        _120 = 1.309f;
    }
    _b8._30 = 0.0f;
    _b8._34 = 0.0f;
    _b8._38 = 0.0f;
    _f8._8 = 0.0f;
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
    m34();
    RandomMoveAction::enter_(params);

    auto* nav = actor->m45();
    if (!ksys::phys::HavokAI::instance()) {
        setFailed();
        return;
    }
    if (!nav)
        return;
    nav->inlineSetField2C0(12.0f);
    nav->sub_7100F76694(actor->getMtx().getBase(2));
    nav->sub_7100F7604C(*mFinRadius_s);
    nav->_2d0 = std::numeric_limits<f32>::infinity();
    nav->_2d4 = 8.0f;
}

void NpcSwimNavMove::leave_() {
    auto* actor = mActor;
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 &= ~0x10000000;
    _130.resetMotionType(_130.sub_710072ACF8(actor));
    RandomMoveAction::leave_();
}

void NpcSwimNavMove::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
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

void NpcSwimNavMove::calc_() {
    RandomMoveAction::calc_();
}

s32 NpcSwimNavMove::m32(RandomMovePoints* points) {
    points->add(*mTargetPos_d);
    return *mUpdateTargetPosInterval_s;
}

}  // namespace uking::action

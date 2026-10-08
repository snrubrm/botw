#include "Game/AI/Action/actionForkAITreeVariableMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

// Original separate two-entry table at 0x7101e78df4, indexed by *mIsArrivedAtDestination_a.
static const f32 sUnk_7101e78df4[2] = {0.8f, 1.2f};

ForkAITreeVariableMove::ForkAITreeVariableMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAITreeVariableMove::~ForkAITreeVariableMove() = default;

bool ForkAITreeVariableMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads the main body (actor + 0x190) before testing the character controller; with
// `auto* body = actor->getMainBody();` declared before the branch it matches (borderline, not applied)
void ForkAITreeVariableMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    *mDestinationPos_a = actor->getMtx().getTranslation();
    sub_710005BE70();
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    if (actor->getCharacterController())
        _ac = 1;
    else if (actor->getMainBody())
        _ac = 2;
    _88.set(*mDestinationPos_a);
    *mIsArrivedAtDestination_a = false;
    _b0 = false;
    _b1 = false;
}

void ForkAITreeVariableMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAITreeVariableMove::loadParams_() {
    getStaticParam(&mArrivedRadius_s, "ArrivedRadius");
    getStaticParam(&mTargetSpeed_s, "TargetSpeed");
    getStaticParam(&mRotSlerpRate_s, "RotSlerpRate");
    getStaticParam(&mKeepDistFromGround_s, "KeepDistFromGround");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsSuccessEndOnArrive_s, "IsSuccessEndOnArrive");
    getStaticParam(&mIsKeepDistFromGround_s, "IsKeepDistFromGround");
    getAITreeVariable(&mTargetSpeed_a, "TargetSpeed");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

void ForkAITreeVariableMove::sub_710005BE70() {
    if (!*mIsKeepDistFromGround_s)
        return;
    const f32 dist = *(*mKeepDistFromGround_a > 0.0f ? mKeepDistFromGround_a : mKeepDistFromGround_s);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    start.x = mDestinationPos_a->x + 0.0f;
    start.y = dist + mDestinationPos_a->y;
    start.z = mDestinationPos_a->z + 0.0f;
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setStartAndDisplacementScaled(start, sead::Vector3f::ey, dist * -5.0f);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&start);
        mDestinationPos_a->y = dist + start.y;
    }
}

// NON_MATCHING: regalloc/scheduling only — the original holds &_94 in a register across the
// face-select copy (two `add x9, x19, #0x94`, one hoisted above the last b.ne) where ours folds it
// into immediates, with downstream register renaming; the original also lays the shared
// `*mIsArrivedAtDestination_a = false` store inline (ours out of line) and sinks the arrival
// range fmul pair below the actor loads. Calls, branch structure, constants identical.
void ForkAITreeVariableMove::calc_() {
    if (!*mIsActive_a)
        return;
    _b1 = _b0;
    _b0 = false;
    const sead::Vector3f* face = mFacePos_a;
    if (face->x == 0.0f && face->y == 0.0f && face->z == 0.0f)
        face = mDestinationPos_a;
    _94.set(*face);
    sub_710005BE70();
    const sead::Vector3f* dest = mDestinationPos_a;
    const f32 dx = _88.x - dest->x;
    const f32 dy = _88.y - dest->y;
    const f32 dz = _88.z - dest->z;
    if (!(dx * dx + dy * dy + dz * dz > 1.0f)) {
        if (_b0) {
            *mIsArrivedAtDestination_a = false;
        } else {
            const f32 range = sUnk_7101e78df4[*mIsArrivedAtDestination_a] * *mArrivedRadius_s;
            const f32 ax = mActor->getMtx().m[0][3] - dest->x;
            const f32 ay = mActor->getMtx().m[1][3] - dest->y;
            const f32 az = mActor->getMtx().m[2][3] - dest->z;
            if (ax * ax + ay * ay + az * az < range * range) {
                *mIsArrivedAtDestination_a = true;
                if (*mIsSuccessEndOnArrive_s)
                    setFinished();
            } else {
                *mIsArrivedAtDestination_a = false;
            }
        }
    } else {
        _b0 = true;
        _88.set(*mDestinationPos_a);
        *mIsArrivedAtDestination_a = false;
    }
    sub_710005BF68();
    if (_ac != 1)
        return;
    sub_710005C14C();
}

}  // namespace uking::action

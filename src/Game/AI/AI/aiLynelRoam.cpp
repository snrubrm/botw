#include "Game/AI/AI/aiLynelRoam.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

LynelRoam::LynelRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRoam::~LynelRoam() = default;

bool LynelRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool LynelRoam::sub_7100498398(sead::Vector3f* out) {
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    sead::Vector3f direction;
    sub_71000891C8(&direction, mActor);
    const f32 angle = sead::GlobalRandom::instance()->getF32() * (2.0f * sead::Mathf::pi() / 3);
    sead::Vector3f ray = direction;
    ksys::util::sub_71011EF010(&ray, angle);
    sead::Vector3f hit;
    for (int i = 0; i < 3; ++i) {
        if (sub_710072FD28(mActor, ray, &hit, -1, *mTargetDistMax_s, -1.0f, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
        if (sead::Vector2f(hit.x - x, hit.z - z).squaredLength() >=
            *mTargetDistMin_s * *mTargetDistMin_s) {
            *out = hit;
            return true;
        }
        ksys::util::sub_71011EF010(&ray, 2.0f * sead::Mathf::pi() / 3);
    }
    return false;
}

// NON_MATCHING: scheduling of the random-number conversions and constants (the original converts the first
// draw before the third getU32 call) and stack slots of the ray / hit.
bool LynelRoam::sub_710049951C(sead::Vector3f* out, const sead::Vector3f& direction) {
    auto* random = sead::GlobalRandom::instance();
    const f32 randoms[3] = {random->getF32(), random->getF32(), random->getF32()};
    const f32 offsets[3] = {0.0f, 0.7853982f, -0.7853982f};
    sead::Vector3f hit;
    for (int i = 0; i < 3; ++i) {
        sead::Vector3f ray = direction;
        ksys::util::sub_71011EF010(&ray, randoms[i] * 0.34906584f - 0.17453292f + offsets[i]);
        if (sub_710072FD28(mActor, ray, &hit, -1, *mTargetDistMax_s,
                           *mTargetDistMax_s - *mTargetDistMin_s, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
    }
    return false;
}

bool LynelRoam::sub_7100498C00() {
    ksys::act::ActorConstDataAccess player;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &player);
    const auto& mtx = player.getActorMtx();
    const sead::Vector3f player_pos(mtx.m[0][3], 0.0f, mtx.m[2][3]);
    const sead::Vector3f actor_pos(mActor->getMtx().m[0][3], 0.0f, mActor->getMtx().m[2][3]);
    sead::Vector3f direction = player_pos - actor_pos;
    const f32 distance = direction.normalize();
    bool result;
    if (distance > *mSpAttackServiceDist_s) {
        result = false;
    } else {
        sead::Vector3f forward;
        mActor->getMtx().getBase(forward, 2);
        result = (-direction).dot(forward) >= std::cos(*mSpAttackServiceAngle_s);
    }
    return result;
}

// NON_MATCHING: stack layout only (the original puts `position` below the shared direction / parameter pack slot).
// NON_MATCHING: stack layout (the original keeps `target` at sp+8 and `direction` at sp+0x18 below the pack; ours puts
// `direction` above it) and the operand order of the squared XZ length.
void LynelRoam::sub_7100498EF8() {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction(mCentralPos_d->x - position.x, 0.0f, mCentralPos_d->z - position.z);
    if (direction.x * direction.x + direction.z * direction.z < 1.0f)
        direction.normalize();
    ksys::util::sub_71011EF010(
        &direction, sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f) * (sead::Mathf::pi() / 6));
    const sead::Vector3f target = position + direction;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("回転", &pack);
}

void LynelRoam::sub_7100498D14() {
    sead::Vector3f position;
    if (!sub_7100498398(&position)) {
        sead::Vector3f direction;
        sub_71000891C8(&direction, mActor);
        const f32 sign = f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
        ksys::util::sub_71011EF010(&direction, sign * sead::Mathf::deg2rad(40));
        position = mActor->getMtx().getTranslation() + direction;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("回転", &pack);
}

bool LynelRoam::sub_7100498E54() {
    sead::Vector3f direction;
    sead::Vector3f opposite;
    sead::Vector3f position;
    if (!sub_7100498398(&position)) {
        sub_71000891C8(&direction, mActor);
        if (!sub_710049951C(&position, direction)) {
            sub_71000891C8(&direction, mActor);
            opposite = -direction;
            if (!sub_710049951C(&position, opposite))
                return false;
        }
    }
    changeToMove(position);
    return true;
}

// NON_MATCHING: same control flow and calls; the spin-attack-service flag, the timer updates and several
// stack / register choices are scheduled differently.
void LynelRoam::calc_() {
    const bool service = sub_7100498C00();
    if (service)
        _b0.update();
    else
        _b0.reset();
    const bool in_service = service && !(_b0.value <= 0.0f);
    if (!(_bc.value <= sead::Mathf::epsilon()))
        _bc.update();
    if (!(_c8.value <= sead::Mathf::epsilon()))
        _c8.update();

    bool moved = false;
    bool turned = false;
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable()) {
            if (isCurrentChild("移動")) {
                moved = !(_e0.value > sead::Mathf::epsilon());
            } else if (!isCurrentChild("回転") && !isCurrentChild("暇つぶし") &&
                       isCurrentChild("待機")) {
                if (_bc.value <= sead::Mathf::epsilon() && _d4.value <= sead::Mathf::epsilon()) {
                    sead::Vector3f pos;
                    sub_7100498398(&pos);
                    changeToMove(pos);
                    return;
                }
                if (_c8.value <= sead::Mathf::epsilon()) {
                    sead::Vector3f front;
                    sub_71000891C8(&front, mActor);
                    sead::Vector3f dir(mCentralPos_d->x - mActor->getMtx()(0, 3), 0.0f,
                                       mCentralPos_d->z - mActor->getMtx()(2, 3));
                    dir.normalize();
                    if ((-front).dot(dir) < 0.8660254f) {
                        if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mFreePer_s)
                            changeChild("暇つぶし");
                        else
                            changeChild("索敵");
                        return;
                    }
                    sub_7100498EF8();
                    return;
                }
            }
        }
    } else if (isCurrentChild("移動")) {
        moved = true;
    } else if (isCurrentChild("回転")) {
        turned = true;
    } else if (!isCurrentChild("暇つぶし") && isCurrentChild("待機")) {
        if (!(_bc.value <= sead::Mathf::epsilon() && sub_7100498E54()))
            sub_7100498D14();
    } else {
        const s32 time =
            sead::GlobalRandom::instance()->getS32Range(*mFreeIntervalMin_s, *mFreeIntervalMax_s);
        _c8 = ksys::Timer(time, time);
        if (!(_bc.value <= sead::Mathf::epsilon() && sub_7100498E54()))
            changeChild("待機");
    }

    if (moved) {
        _bc.reset(*mNoMoveTime_s);
        sead::Vector3f front;
        sub_71000891C8(&front, mActor);
        if (sub_710072FEC4(mActor, front, *mTargetDistMin_s, nullptr, true, nullptr) &&
            !in_service)
            sub_7100498D14();
        else
            turned = true;
    }
    if (turned) {
        if (!(_c8.value <= sead::Mathf::epsilon()))
            changeChild("待機");
        else if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mFreePer_s)
            changeChild("暇つぶし");
        else
            changeChild("索敵");
    }

    if (isCurrentChild("移動")) {
        _e0.update();
        sub_71004990C8();
    }
}

// NON_MATCHING: register allocation and load scheduling of the distance tests.
// Repaths while moving (RepathTime): a new position in front of the actor while inside the territory (or behind
// it when it faces away from the central position), else a position back inside the territory.
void LynelRoam::sub_71004990C8() {
    if (!(_d4.value <= sead::Mathf::epsilon())) {
        _d4.update();
        return;
    }

    const f32 dx = mActor->getMtx()(0, 3) - mCentralPos_d->x;
    const f32 dz = mActor->getMtx()(2, 3) - mCentralPos_d->z;
    if (dx * dx + dz * dz > *mTerritory_s * *mTerritory_s) {
        sead::Vector3f pos;
        if (!sub_7100499704(&pos))
            return;
        _d4.reset(*mRepathTime_s);
        changeToMove(pos);
        return;
    }

    sead::Vector3f front;
    sub_71000891C8(&front, mActor);
    sead::Vector3f dir(mCentralPos_d->x - mActor->getMtx()(0, 3), 0.0f,
                       mCentralPos_d->z - mActor->getMtx()(2, 3));
    dir.normalize();
    const f32 half = *mTerritory_s * 0.5f;
    const f32 dx2 = mActor->getMtx()(0, 3) - mCentralPos_d->x;
    const f32 dz2 = mActor->getMtx()(2, 3) - mCentralPos_d->z;
    sead::Vector3f pos;
    if ((-front).dot(dir) < 0.8660254f || dx2 * dx2 + dz2 * dz2 <= half * half) {
        sub_71000891C8(&front, mActor);
        if (!sub_710049951C(&pos, front))
            return;
    } else {
        sub_71000891C8(&front, mActor);
        if (!sub_710049951C(&pos, -front))
            return;
    }
    _d4.reset(*mRepathTime_s);
    changeToMove(pos);
}

// NON_MATCHING: store order of the direction and the scheduling of the Territory * 2 load.
// A position back towards the central position (mixed with the actor's front direction near the territory).
bool LynelRoam::sub_7100499704(sead::Vector3f* out) {
    const f32 x = mActor->getMtx()(0, 3);
    const f32 z = mActor->getMtx()(2, 3);
    sead::Vector3f to_center(mCentralPos_d->x - x, 0.0f, mCentralPos_d->z - z);
    to_center.normalize();
    const f32 dx = x - mCentralPos_d->x;
    const f32 dz = z - mCentralPos_d->z;
    const f32 limit = *mTerritory_s + *mTerritory_s;
    if (dx * dx + dz * dz > limit * limit)
        return sub_710049951C(out, to_center);

    sead::Vector3f front;
    sub_71000891C8(&front, mActor);
    sead::Vector3f dir = front * 0.5f + to_center * 0.5f;
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) {
        dir = front;
        const s32 sign = s32(sead::GlobalRandom::instance()->getU32() & 2) - 1;
        ksys::util::sub_71011EF010(&dir, static_cast<f32>(sign) * sead::Mathf::piHalf());
    }
    return sub_710049951C(out, dir);
}

// NON_MATCHING: timer load scheduling differs.
void LynelRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mNoSpAttackMoveTime_s;
    _b0.value = time;
    _b0.min = _b0.max = time;
    _c8.reset(sead::GlobalRandom::instance()->getS32Range(*mFreeIntervalMin_s,
                                                      *mFreeIntervalMax_s));
    _bc.reset(*mNoMoveTime_s);
    sead::Vector3f direction;
    sead::Vector3f position;
    if (!sub_7100498398(&position)) {
        sub_71000891C8(&direction, mActor);
        if (!sub_710049951C(&position, direction)) {
            changeChild("待機");
            return;
        }
    }
    changeToMove(position);
}

void LynelRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRoam::loadParams_() {
    getStaticParam(&mFreeIntervalMin_s, "FreeIntervalMin");
    getStaticParam(&mFreeIntervalMax_s, "FreeIntervalMax");
    getStaticParam(&mFreePer_s, "FreePer");
    getStaticParam(&mMoveIntervalMin_s, "MoveIntervalMin");
    getStaticParam(&mMoveIntervalMax_s, "MoveIntervalMax");
    getStaticParam(&mNoMoveTime_s, "NoMoveTime");
    getStaticParam(&mNoSpAttackMoveTime_s, "NoSpAttackMoveTime");
    getStaticParam(&mSpAttackServiceTime_s, "SpAttackServiceTime");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTerritory_s, "Territory");
    getStaticParam(&mTargetDistMin_s, "TargetDistMin");
    getStaticParam(&mTargetDistMax_s, "TargetDistMax");
    getStaticParam(&mSpAttackServiceDist_s, "SpAttackServiceDist");
    getStaticParam(&mSpAttackServiceAngle_s, "SpAttackServiceAngle");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void LynelRoam::changeToMove(const sead::Vector3f& pos) {
    if (!isCurrentChild("移動")) {
        const s32 min = *mMoveIntervalMin_s;
        const s32 max = *mMoveIntervalMax_s;
        const s32 time = sead::GlobalRandom::instance()->getS32Range(min, max);
        _e0 = ksys::Timer(time, time);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai

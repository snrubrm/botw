#include "Game/Actor/Action/actionBowChildArrowRain.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

namespace {
struct Unk_8000054_Payload {
    u8 _0[0x20];
    s32 _20;
};
}  // namespace

// NON_MATCHING: the original emits the zero stores of _d4/_100/_108/_110 before both memsets (0x20..0xd3 and
// the 0x408-byte block at 0x12c); here they end up between / after the memsets.
BowChildArrowRain::BowChildArrowRain(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildArrowRain::~BowChildArrowRain() = default;

bool BowChildArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = 0;
    _bc = 0;
    const s32 id = *mID_d;
    _110 = 0;
    _100 = 0;
    _108 = 0;
    _c0 = f32(id) * (sead::Mathf::pi() / 2);
    for (auto& state : _12c._3d8)
        state = {false, false};
    _12c._3cc.set(*mToTargetTime_s, *mToTargetTime_s, -1);
    _d0 = false;
    _d1 = false;
    _d2 = false;
    _d8 = *mID_d;
    _c8 = sead::GlobalRandom::instance()->getF32();
    _cc = sead::GlobalRandom::instance()->getF32Range(-5, 5);
}

void BowChildArrowRain::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildArrowRain::loadParams_() {
    getStaticParam(&mRainMax_s, "RainMax");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveHeight_s, "MoveHeight");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mMoveCountNum_s, "MoveCountNum");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mMoveOffsetBase_s, "MoveOffsetBase");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mRotateStepMax_s, "RotateStepMax");
    getStaticParam(&mAngleToTarget_s, "AngleToTarget");
    getStaticParam(&mTargetOffsetBase_s, "TargetOffsetBase");
    getStaticParam(&mRainScale_s, "RainScale");
    getStaticParam(&mToTargetTime_s, "ToTargetTime");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsIgnoreHightOffset_d, "IsIgnoreHightOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

bool BowChildArrowRain::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;
    if (message->getType() != 0x8000054)
        return false;
    if (!message->getUserData())
        return true;

    const auto* data = static_cast<const Unk_8000054_Payload*>(message->getUserData());
    if (!data)
        return true;

    if (data->_20 == 1) {
        _d1 = true;
        return true;
    }

    _b8 = 1;
    _12c._3c0.set(45.0f, 45.0f, -1.0f);
    playAS("Open", false, 0, 0, -1.0f);
    return true;
}

bool BowChildArrowRain::isChangeable() const {
    return _b8 != 1 && _b8 != 2;
}

void BowChildArrowRain::calc_() {
    ksys::act::ai::Action::calc_();
}

void BowChildArrowRain::sub_71000CDEEC(const sead::Vector3f& pos, bool use_pos) {
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    sead::Matrix33f rotation_mtx = _dc;
    sead::Matrix33f rotation;
    rotation.makeR({*mXRotateAngle_d, 0, 0});
    rotation_mtx.setMul(rotation_mtx, rotation);
    sead::Matrix34f mtx(rotation_mtx, pos);
    if (!use_pos)
        mtx.setTranslation(_120);
    body->changePositionAndRotation(mtx);
}

// NON_MATCHING: the original repeats the speed sqrt (dead) after the store; register allocation.
void BowChildArrowRain::sub_71000CD040() {
    if (!mParentActor_d)
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return;

    for (s32 i = 0; i < 24; ++i) {
        auto& state = _12c._3d8[i];
        if (state.entered)
            state.entered = false;
        auto* link = boss->_1560.sub_710066DE24(i);
        if (!link->hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f velocity = accessor.getVelocity();
        const f32 speed = velocity.length();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - (pos + velocity);
        const bool inside = diff.squaredLength() < speed * speed;
        if (inside && !state.inside)
            state.entered = true;
        state.inside = inside;
    }
}

// NON_MATCHING: the original keeps &_1560 in a register and adds 0x1e0 after the index (we fold the offsets).
bool BowChildArrowRain::sub_71000CD2A8(sead::Vector3f* pos) {
    if (!mParentActor_d)
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return false;

    auto& bound = boss->_1560;
    _d8 = bound.sub_710066DF44(_d8, (*mID_d & 1) ? -1 : 1, *mID_d);
    auto& link = bound._1e0[_d8];
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateCalc()) {
            accessor.getActorMtx().getTranslation(*pos);
            return true;
        }
    }
    return false;
}

bool BowChildArrowRain::sub_71000CE328() {
    if (mParentActor_d) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(actor)) {
            for (u32 i = 0; i < 24; ++i) {
                if (boss->_1560.sub_710066DE24(i)->hasProcInCalcState())
                    return false;
            }
        }
    }
    return true;
}

}  // namespace uking::action

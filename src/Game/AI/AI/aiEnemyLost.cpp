#include "Game/AI/AI/aiEnemyLost.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/Timer.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100D8C538.h"

bool sub_71005E2128(ksys::act::Actor* actor);
bool sub_710072C7A0(sead::Vector3f* out, ksys::act::Actor* actor);

namespace uking::ai {

EnemyLost::EnemyLost(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLost::~EnemyLost() = default;

bool EnemyLost::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLost::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    m34();
}

void EnemyLost::calc_() {
    if (!*mParams.mSealForceReturn_s && !isCurrentChild("強制帰還") &&
        sub_71005E2128(mActor)) {
        sead::Vector3f target;
        if (sub_71005D9F04(mActor)) {
            auto* object = mActor->getMapObject();
            if (!object || !object->getRails_0() || sub_710072C7A0(&target, mActor)) {
                setFinished();
                return;
            }
        } else {
            target = *mParams.mTargetPos_d;
        }
        if (!visibilityCheckMaybe(target, *mParams.mForceReturnNoCameraRad_s)) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(target, "TargetPos", -1);
            changeChild("強制帰還", &params);
        }
    }
    if (sub_71005D9F04(mActor)) {
        ksys::Timer::update(&_58, -1.0f);
        if (_58 <= 0.0f) {
            sead::Vector3f target;
            auto* object = mActor->getMapObject();
            if (!object || !object->getRails_0() || sub_710072C7A0(&target, mActor))
                setFinished();
            getCurrentChild()->setDynamicParam(target, "TargetPos");
            _58 = *mParams.mRailCheckInterval_s;
        }
    }
}

bool EnemyLost::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyLost::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyLost::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyLost::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLost::loadParams_() {
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mRailCheckInterval_s, "RailCheckInterval");
    getStaticParam(&mParams.mSealForceReturn_s, "SealForceReturn");
    getStaticParam(&mParams.mForceReturnNoCameraRad_s, "ForceReturnNoCameraRad");
}

}  // namespace uking::ai

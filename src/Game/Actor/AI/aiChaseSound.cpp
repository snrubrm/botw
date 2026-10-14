#include "Game/Actor/AI/aiChaseSound.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

bool sub_71005E2068(ksys::act::Actor* actor);

namespace uking::ai {

ChaseSound::ChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChaseSound::~ChaseSound() = default;

void ChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005E21E8(mActor);
    if (_78) {
        _78->release();
        _78 = nullptr;
    }
    auto* actor = mActor;
    _80 = actor->getMtx().getTranslation();
    _74 = 30.0f;
    sead::Vector3f direction = *mParams.mTargetPos_d;
    direction -= actor->getMtx().getTranslation();
    direction.y = 0.0f;
    direction.normalize();
    const sead::Vector3f front = mActor->getMtx().getBase(2);
    if (front.dot(direction) >= sead::Mathf::cos(*mParams.mTurnDir_s)) {
        if (!sub_7100345C2C())
            setFailed();
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
        changeChild("回転", &pack);
    }
}

void ChaseSound::leave_() {
    if (_78) {
        _78->release();
        _78 = nullptr;
    }
}

// NON_MATCHING: Temporary string storage uses a larger stack frame.
void ChaseSound::calc_() {
    if (isCurrentChild("見まわし")) {
        sub_71005DB3EC(mActor);
    } else {
        const sead::Vector3f target = _80;
        if (*mParams.mUseViewPointSimpleOffset_s)
            sub_71005DB1D8(mActor, target);
        else
            sub_71005DB068(mActor, target);
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転")) {
            if (!sub_7100345C2C())
                setFailed();
        } else if (isCurrentChild("見まわし")) {
            sub_7100345C2C();
        } else if (getCurrentChild()->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    }
    if (getCurrentChild()->isChangeable() && !isCurrentChild("回転") &&
        !isCurrentChild("見まわし") && sub_71005E2068(mActor)) {
        setFailed();
    }
    sub_7100346114();
    getCurrentChild()->setDynamicParam(_80, "TargetPos");
}

void ChaseSound::loadParams_() {
    getStaticParam(&mParams.mTargetUpdateIntervalMin_s, "TargetUpdateIntervalMin");
    getStaticParam(&mParams.mTargetUpdateIntervalMax_s, "TargetUpdateIntervalMax");
    getStaticParam(&mParams.mNearDist_s, "NearDist");
    getStaticParam(&mParams.mTurnDir_s, "TurnDir");
    getStaticParam(&mParams.mUseViewPointSimpleOffset_s, "UseViewPointSimpleOffset");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: distance-load scheduling and the hit-position copy base register
bool ChaseSound::sub_7100345C2C() {
    if (sub_710072E154(mActor, *mParams.mTargetPos_d, nullptr, -1)) {
        if (isCurrentChild("直線追跡"))
            return false;
        _80 = *mParams.mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_80, "TargetPos", -1);
        changeChild("直線追跡", &pack);
        return true;
    }

    const sead::Vector3f target = *mParams.mTargetPos_d;
    const f32 distance = (target - mActor->getMtx().getTranslation()).length();
    if (distance < *mParams.mNearDist_s) {
        if (isCurrentChild("近場追跡"))
            return false;
        _80 = *mParams.mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_80, "TargetPos", -1);
        changeChild("近場追跡", &pack);
    } else {
        if (isCurrentChild("遠方追跡"))
            return false;
        sub_71003463B0();
    }
    return true;
}

// NON_MATCHING: the start position's stack slot (shared with the param pack in the original) and the _80 update
// scheduling.
void ChaseSound::sub_71003463B0() {
    const sead::Vector3f start = mActor->getMtx().getTranslation();
    bool found = false;
    if (sub_710072EA18(start, *mParams.mTargetPos_d, 1, &_80, nullptr, nullptr, 1.6f)) {
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        sead::Vector3f dir(_80.x - pos.x, 0.0f, _80.z - pos.z);
        dir.normalize();
        _80 += dir * 2.0f;
        sead::Vector3f to = _80;
        to.y += -2.0f;
        found = sub_710072EA18(_80, to, 1, &_80, nullptr, nullptr, 0.0f);
    }
    if (!found)
        _80 = *mParams.mTargetPos_d;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_80, "TargetPos", -1);
    changeChild("遠方追跡", &pack);
}

void ChaseSound::sub_7100346114() {
    if (!isCurrentChild("回転")) {
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        if (!((*mParams.mTargetPos_d - pos).length() < *mParams.mNearDist_s) &&
            !sub_710072E154(mActor, *mParams.mTargetPos_d, nullptr, -1)) {
            if (!_78) {
                _78 = ksys::phys::RayCastForRequest::allocRequest(nullptr, ksys::phys::GroundHit(0xf));
                if (!_78)
                    return;
            }
            if (_78->isRequestQueued())
                return;
            auto* cast = _78;
            if (_68.value <= sead::Mathf::epsilon()) {
                sead::Vector3f start = mActor->getMtx().getTranslation();
                sub_710072EC24(cast, start, *mParams.mTargetPos_d,
                               ksys::phys::RayCast::NormalCheckingMode(1), 1.6f);
            } else if (cast->get70() == 1) {
                bool ok = false;
                if (cast->hasHit()) {
                    cast->getHitPosition(&_80);
                    sead::Vector3f to = _80;
                    to.y += -2.0f;
                    ok = sub_710072EA18(_80, to, 1, &_80, nullptr, nullptr, 0.0f);
                }
                if (!ok)
                    _80 = *mParams.mTargetPos_d;
                const f32 dist = (_80 - *mParams.mTargetPos_d).length();
                const int min = *mParams.mTargetUpdateIntervalMin_s;
                const int max = *mParams.mTargetUpdateIntervalMax_s;
                const f32 near = *mParams.mNearDist_s;
                const f32 t = min + (max - min) * (dist - near) / near;
                _68.reset(t > max ? f32(max) : t);
            }
            _68.update();
            return;
        }
    }
    _80 = *mParams.mTargetPos_d;
    _68.reset(0.0f);
}

}  // namespace uking::ai

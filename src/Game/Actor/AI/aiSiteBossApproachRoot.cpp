#include "Game/Actor/AI/aiSiteBossApproachRoot.h"
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

// Source namespace and reference spelling are inferred from the known caller interfaces.
bool sub_71002D2B5C(bool* side, ksys::act::Actor* actor, const gsys::BoneAccessKeyEx& key,
                  f32 angle, f32 scale);

// Existing declaration also used by GanonBattleOnFloorRoot.
bool sub_71002D2A80();

namespace uking::ai {

// Original five-element ray fan table at 0x7101e7ab70.
static const f32 sUnk_7101e7ab70[5] = {
    0.0f, -0.5235987901687622f, 0.5235987901687622f, -2.094395160675049f, 2.094395160675049f,
};

SiteBossApproachRoot::SiteBossApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    for (auto& ray_cast : mRayCasts)
        ray_cast = nullptr;
    for (auto& pos : _c8)
        pos.set(0, 0, 0);
}

SiteBossApproachRoot::~SiteBossApproachRoot() = default;

bool SiteBossApproachRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _1f8.search(model, "Head");
    else
        _1f8.getKey().reset();
    return true;
}

// NON_MATCHING: ray pointer clearing and vector-array zero-store scheduling.
void SiteBossApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = false;
    _94 = 0;
    _98 = 0;
    const f32 approach_time = *mApproachTime_s;
    _7c = ksys::Timer(approach_time, approach_time);
    _88 = ksys::Timer(30.0f, 30.0f);
    for (auto*& ray_cast : mRayCasts) {
        if (ray_cast && !ray_cast->isRequestFinished())
            ray_cast->release();
        ray_cast = nullptr;
    }
    for (auto& pos : _104)
        pos = sead::Vector3f::zero;
    for (auto& distance : _1b8)
        distance = -1.0f;
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    if (_79) {
        for (auto& pos : _c8)
            pos = position;
        _79 = false;
    }
    sead::Vector3f destination = *mTargetPos_d;
    sead::Vector3f direction = destination - position;
    const f32 distance = direction.normalize();
    if (distance <= *mEndDist_s) {
        destination = position + direction * ((distance - *mEndDist_s) * 0.75f);
        if (sub_71002D2A80() && !*mIsMoveSide_d &&
            !act::SiteBoss::sub_71002D3804(mActor, "WearFlame") &&
            !sub_710072EB10(position, destination, ksys::phys::RayCast::NormalCheckingMode(0),
                            mActor, nullptr, nullptr, nullptr, 0.5f)) {
            setFinished();
        }
    }
    sub_71005702D4(destination);
    _230 = destination;
}

// NON_MATCHING: result/weight loops, branch layout and saved vector scheduling.
void SiteBossApproachRoot::calc_() {
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (isCurrentChild("移動") && *mDoAttack_s) {
        if (m34())
            sub_7100570CA4();
    } else if (isCurrentChild("遠距離攻撃移動") && getCurrentChild()->isFailed()) {
        setFailed();
        return;
    }
    bool pending = false;
    for (auto* ray_cast : mRayCasts) {
        if (ray_cast)
            pending = true;
    }
    if (pending) {
        _78 = true;
        for (s32 i = 0; i < 5; ++i) {
            if (mRayCasts[i] && mRayCasts[i]->get70() == 1) {
                if (mRayCasts[i]->hasHit())
                    mRayCasts[i]->getHitPosition(&_104[_94 * 5 + i]);
                _1b8[_94 * 5 + i] = (_104[_94 * 5 + i] - _c8[_94]).length();
                mRayCasts[i]->release();
                mRayCasts[i] = nullptr;
            }
        }
    } else {
        if (_78) {
            _78 = false;
            const f32 threshold = *mCheckWallDist_s * 0.8f;
            sead::SafeArray<f32, 5> weights;
            sead::Vector3f destination = sead::Vector3f::zero;
            s32 first_valid = -1;
            for (s32 i = 0; i < 5; ++i) {
                const f32 distance = _1b8[_94 * 5 + i];
                if (distance >= threshold) {
                    if (first_valid == -1)
                        first_valid = i;
                    weights[i] = distance;
                    if (i == 1 || i == 2) {
                        if (sub_71002D2A80() && !*mIsMoveSide_d) {
                            weights[i] = distance * 0.15f;
                            if (u32(i) == _98)
                                weights[i] *= 4.0f;
                        } else if (u32(i) != _98) {
                            weights[i] = distance * 0.5f;
                        }
                    } else if (i == 0) {
                        weights[i] = (sub_71002D2A80() && !*mIsMoveSide_d ? 1.0f : 0.5f) * distance;
                    } else {
                        weights[i] = distance * (sub_71002D2A80() ? 0.05f : 0.5f);
                    }
                } else {
                    weights[i] = 0.0f;
                }
            }
            if (first_valid == -1) {
                destination = _c8[_94 == 0 ? 4 : _94 - 1];
            } else {
                const f32 choice = threshold * sead::GlobalRandom::instance()->getF32();
                f32 total = 0.0f;
                s32 selected = first_valid;
                for (s32 i = 4; i >= 0; --i) {
                    total += weights[i];
                    if (total > choice) {
                        selected = i;
                        break;
                    }
                }
                destination = _104[_94 * 5 + selected];
                _98 = selected;
            }
            if (!sub_71002D2A80() &&
                sead::Mathf::square(destination.x - position.x) +
                    sead::Mathf::square(destination.z - position.z) <=
                    sead::Mathf::square(*mEndDist_s)) {
                destination = position;
            }
            destination.y += -1.2f;
            if (sead::Mathf::abs(mTargetPos_d->y - destination.y) > 1.0f)
                sead::Mathf::chase(&destination.y, mTargetPos_d->y, 0.05f);
            getCurrentChild()->setDynamicParam(destination, "MoveDstPos");
            _230 = destination;
        }
        _88.update();
        if (_88.value <= sead::Mathf::epsilon()) {
            for (auto*& ray_cast : mRayCasts) {
                ray_cast = ksys::phys::RayCastForRequest::allocRequest(
                    sub_710072E804(mActor, 0), ksys::phys::GroundHit(15));
            }
            if (mRayCasts[0] && mRayCasts[1] && mRayCasts[2] && mRayCasts[3] && mRayCasts[4]) {
                _94 = u32(_94 + 1) < 3 ? _94 + 1 : 0;
                sead::Vector3f direction = *mTargetPos_d - position;
                direction.normalize();
                sub_7100570D90(direction);
                _88 = ksys::Timer(30.0f, 30.0f);
            }
        }
    }
    const sead::Vector2f diff(mTargetPos_d->x - position.x, mTargetPos_d->z - position.z);
    const f32 distance = diff.length();
    if (distance <= *mEndDist_s) {
        if (act::SiteBoss::sub_71002D3804(mActor, "WearFlame")) {
            if (distance > 6.0f) {
                setFinished();
                return;
            }
        } else if (_1b8[_94 * 5] >= distance) {
            setFinished();
            return;
        }
    } else {
        if (distance > *mEndFarDist_s) {
            setFailed();
            return;
        }
        if (distance > *mAttackStartDist_s && isCurrentChild("移動") && *mDoAttack_s)
            sub_7100570CA4();
    }
    _7c.update();
    if (_7c.value <= sead::Mathf::epsilon())
        setFailed();
}

void SiteBossApproachRoot::leave_() {
    for (auto*& ray_cast : mRayCasts) {
        if (ray_cast && !ray_cast->isRequestFinished()) {
            ray_cast->release();
            ray_cast = nullptr;
        }
    }
}

void SiteBossApproachRoot::loadParams_() {
    getStaticParam(&mCheckWallDist_s, "CheckWallDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mEndFarDist_s, "EndFarDist");
    getStaticParam(&mAttackStartDist_s, "AttackStartDist");
    getStaticParam(&mDoAttack_s, "DoAttack");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SiteBossApproachRoot::m34() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || !boss->sub_71002D33D0(90.0f))
        return false;
    bool side = false;
    return sub_71002D2B5C(&side, mActor, _1f8, 0.34906584f, 1.2f);
}

// NON_MATCHING: position and quaternion-matrix register scheduling.
void SiteBossApproachRoot::sub_7100570D90(const sead::Vector3f& direction) {
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    position.y += 1.2f;
    _c8[_94] = position;
    for (s32 i = 0; i < 5; ++i) {
        sead::Quatf quaternion;
        quaternion.setAxisRadian(sead::Vector3f::ey, sUnk_7101e7ab70[i]);
        sead::Matrix34f rotation;
        rotation.makeQT(quaternion, sead::Vector3f::zero);
        sead::Vector3f destination = direction;
        destination.rotate(rotation);
        destination *= *mCheckWallDist_s;
        destination += position;
        sub_710072EC24(mRayCasts[i], position, destination,
                        ksys::phys::RayCast::NormalCheckingMode(0), 2.0f);
        _104[_94 * 5 + i] = destination;
    }
}

// 0x71005702d4
void SiteBossApproachRoot::sub_71005702D4(const sead::Vector3f& dst) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(dst, "MoveDstPos", -1);
    changeChild("移動", &pack);
}

// 0x7100570ca4
void SiteBossApproachRoot::sub_7100570CA4() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(_230, "MoveDstPos", -1);
    changeChild("遠距離攻撃移動", &pack);
}

}  // namespace uking::ai

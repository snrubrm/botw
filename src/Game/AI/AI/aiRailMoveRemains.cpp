#include "Game/AI/AI/aiRailMoveRemains.h"
#include "Game/Actor/actRemains.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

RailMoveRemains::RailMoveRemains(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveRemains::~RailMoveRemains() = default;

bool RailMoveRemains::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveRemains::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RailMoveRemains::calc_() {
    if (!_60->_8.rail)
        return;
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (isCurrentChild("移動")) {
        m44();
        sead::Vector3f target_pos;
        m47(&target_pos);
        child->setDynamicParam(target_pos, "TargetPos");
        child->setDynamicParam(_68, "TargetFrontDir");
    }

    if (isCurrentChild("移動") && m39()) {
        m35();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            const s32 next = _60->_30.progress;
            if (next != s32(_60->_8.progress) && sub_7100EEF078(_60->_8.rail, next) > 0)
                m36();
            else
                m37();
        } else if (isCurrentChild("停止")) {
            m37();
        } else if (isCurrentChild("再稼働")) {
            m37();
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (isCurrentChild("停止"))
        m37();
    else if (isCurrentChild("一時停止") && m40())
        m38();
}

void RailMoveRemains::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveRemains::loadParams_() {
    getStaticParam(&mReactivateTime_s, "ReactivateTime");
    getStaticParam(&mFrontCheckMinDist_s, "FrontCheckMinDist");
    getStaticParam(&mFrontDirUpdateInterval_s, "FrontDirUpdateInterval");
    getStaticParam(&mSpeedScale_s, "SpeedScale");
    getStaticParam(&mInitPosByRailRatio_s, "InitPosByRailRatio");
}

void RailMoveRemains::m9() {}

bool RailMoveRemains::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;

    auto* other_ = sead::DynamicCast<RailMoveRemains>(other);
    if (!other_)
        return false;

    _60 = m45();
    _60->sub_7100EEBDB8(other_->_60);
    _68 = other_->_68;
    _74.reset(-1.0f);
    return true;
}

ksys::map::Rail* RailMoveRemains::m34() {
    return sub_7100EEF264(mActor, 0);
}

void RailMoveRemains::m35() {
    sead::Vector3f pos;
    if (_60->sub_7100EEBB74())
        pos = _60->_30.sub_7100EEB370();
    else
        mActor->getMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack params;
    params.addFloat(*mReactivateTime_s, "DynStopTime", -1);
    params.addVec3(pos, "DynStopPos", -1);
    changeChild("一時停止", &params);
}

void RailMoveRemains::m36() {
    ksys::act::ai::InlineParamPack params;
    const auto* rail = _60->_8.rail;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 time;
    if (rail)
        time = sub_7100EEF078(rail, _60->_8.progress);
    else
        time = 999999.0f;
    params.addFloat(time, "DynStopTime", -1);
    params.addVec3(pos, "DynStopPos", -1);
    changeChild("停止", &params);
}

void RailMoveRemains::m37() {
    _74.reset(-1.0f);
    mActor->getMtx().getBase(_68, 2);
    _68.normalize();
    m44();

    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target_pos;
    m47(&target_pos);
    const f32 speed = m43();
    params.addVec3(target_pos, "TargetPos", -1);
    params.addVec3(_68, "TargetFrontDir", -1);
    params.addFloat(speed, "TargetSpeed", -1);
    changeChild("移動", &params);
}

void RailMoveRemains::m38() {
    changeChild("再稼働");
}

bool RailMoveRemains::m39() {
    return false;
}

bool RailMoveRemains::m40() {
    return true;
}

f32 RailMoveRemains::m41() {
    return *mSpeedScale_s;
}

f32 RailMoveRemains::m42() {
    return *mInitPosByRailRatio_s;
}

f32 RailMoveRemains::m43() {
    if (const auto* rail = _60->_8.rail)
        return sub_7100EEF60C(rail, _60->_8.progress) * m41();
    return 0.0f;
}

// NON_MATCHING: regalloc (the original keeps two phis for the progress sum)
void RailMoveRemains::m44() {
    if (!_60->_8.rail)
        return;

    const f32 dist = m43() * ksys::VFR::instance()->getDeltaTime();
    if (dist < 0.01f)
        return;

    _60->x(dist);

    if (!(_74.value <= sead::Mathf::epsilon())) {
        _74.update();
        return;
    }

    sead::Vector3f pos;
    if (dist < *mFrontCheckMinDist_s) {
        f32 progress;
        if (dist > 0.01f) {
            progress = _60->_8.progress +
                       *mFrontCheckMinDist_s * (_60->_30.progress - _60->_8.progress) / dist;
        } else {
            progress = _60->_8.progress + 0.1f;
        }

        const auto* rail = _60->_8.rail;
        f32 p = 0.0f;
        if (rail && rail->getNumPoints() > 0) {
            p = progress;
            const bool closed = rail->isClosed();
            const f32 num_points = rail->getNumPoints();
            if (closed) {
                const f32 max = std::max(num_points - sead::Mathf::epsilon(), 0.0f);
                if (p < 0.0f) {
                    while (p < 0.0f)
                        p += max;
                } else if (max < p) {
                    while (p > max)
                        p -= max;
                }
            } else {
                const f32 max = std::max(num_points - 1.0f, 0.0f);
                if (p < 0.0f)
                    p = 0.0f;
                else if (max < p)
                    p = max;
            }
        }
        _60->_8.rail->calcTranslate(&pos, p);
    } else {
        pos = _60->_30.sub_7100EEB370();
    }

    pos -= _60->_8.sub_7100EEB370();
    pos.normalize();
    _68 = pos;
    _74.reset(*mFrontDirUpdateInterval_s);
}

Unk_71024f15c0* RailMoveRemains::m45() {
    auto* remains = static_cast<act::Remains*>(mActor);
    if (!remains)
        return nullptr;
    return remains->_b90;
}

void RailMoveRemains::m46(const sead::Vector3f& pos, const sead::Vector3f& dir) {
    const sead::Vector3f up_axis = sead::Vector3f::ey;
    sead::Vector3f front = dir;
    front.normalize();
    sead::Vector3f side;
    side.setCross(up_axis, front);
    side.normalize();
    sead::Vector3f up;
    up.setCross(front, side);
    up.normalize();

    sead::Matrix34f mtx;
    mtx.setBase(0, side);
    mtx.setBase(1, up);
    mtx.setBase(2, front);
    mtx.setTranslation(pos);

    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60500(mtx);
    else if (auto* body = mActor->getMainBody())
        body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
    mActor->actorPhysicsSetFlag2();
}

void RailMoveRemains::m47(sead::Vector3f* out) {
    if (out)
        out->set(_60->_30.sub_7100EEB370());
}

}  // namespace uking::ai

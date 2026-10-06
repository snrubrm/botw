#include "Game/AI/AI/aiSimpleEscapeFromTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

// Declaration only; original source namespace is unknown.
bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from,
                    const sead::Vector3f& to, sead::Vector3f* out_pos, s32 kind,
                    f32 tolerance, f32 unused);

namespace uking::ai {

SimpleEscapeFromTarget::SimpleEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleEscapeFromTarget::~SimpleEscapeFromTarget() = default;

bool SimpleEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = _60 = *mKeepTime_s;
    sub_710056CF84();
}

// NON_MATCHING: load order only (the original reads the target position's x / z before the actor's
// translation; getTranslation() returns a by-value copy that is loaded first)
void SimpleEscapeFromTarget::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    f32& timer = _58;
    if (ksys::util::sqXZDistance(*mTargetPos_d, mActor->getMtx().getTranslation()) >
        sead::Mathf::square(*mSpaceDist_s)) {
        ksys::Timer::update(&timer, -1.0f);
    } else {
        s32 time = _5c;
        if (_60 != _5c)
            time = sead::GlobalRandom::instance()->getS32Range(_5c, _60);
        timer = time;
    }

    if (child->isFinished() || child->isFailed()) {
        if (!(ksys::util::sqXZDistance(*mTargetPos_d, mActor->getMtx().getTranslation()) >
              sead::Mathf::square(*mSpaceDist_s))) {
            setFailed();
            return;
        }
        m35(child->isFinished());
    } else if (child->isChangeable() && timer <= 0.0f) {
        m35(true);
        return;
    }
    m37();
}

void SimpleEscapeFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleEscapeFromTarget::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SimpleEscapeFromTarget::m34() {
    setFailed();
    return false;
}

void SimpleEscapeFromTarget::m35(bool finished) {
    if (finished)
        setFinished();
    else
        setFailed();
}

void SimpleEscapeFromTarget::m36(sead::Vector3f* dir) {
    dir->set(*mTargetPos_d);
    *dir -= mActor->getMtx().getTranslation();
    dir->y = 0.0f;
    dir->normalize();
}

void SimpleEscapeFromTarget::m37() {
    sead::Vector3f pos;
    if (sub_710056D354(&pos)) {
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        return;
    }
    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17)
        m34();
}

void SimpleEscapeFromTarget::m38(sead::Vector3f* dir, s32 idx) {
    const s32 sign = (idx & 1) ? 1 : -1;
    const f32 angle = sead::Mathf::deg2rad(f32(sign * (idx + 1)) * 0.5f);
    sead::Matrix34f rot;
    rot.makeR({0, angle, 0});
    dir->rotate(rot);
}

// NON_MATCHING: the position copy and query arguments are scheduled differently.
bool SimpleEscapeFromTarget::m39(const sead::Vector3f& dir) {
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    sead::Vector3f target = dir;
    target *= *mSpaceDist_s;
    target += position;
    return sub_710072F99C(actor, position, target, nullptr, -1, -1.0f, -1.0f);
}

bool SimpleEscapeFromTarget::sub_710056D24C() {
    const sead::Vector2f target(mTargetPos_d->x, mTargetPos_d->z);
    const auto& mtx = mActor->getMtx();
    const sead::Vector2f pos(mtx.m[0][3], mtx.m[2][3]);
    return (target - pos).squaredLength() > *mSpaceDist_s * *mSpaceDist_s;
}

bool SimpleEscapeFromTarget::sub_710056D354(sead::Vector3f* out) {
    sead::Vector3f dir;
    m36(&dir);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f d;
    d = dir;
    if (!m39(d)) {
        m38(&d, 1);
        if (!m39(d)) {
            m38(&d, 2);
            if (!m39(d)) {
                m38(&d, 3);
                if (!m39(d))
                    return false;
            }
        }
    }
    d *= *mSpaceDist_s;
    d += pos;
    *out = d;
    return true;
}

void SimpleEscapeFromTarget::sub_710056CF84() {
    auto* nav = mActor->m45();
    sead::Vector3f pos;
    if ((nav && (nav->_2a4 & 0xffff) == 0x17) || !sub_710056D354(&pos)) {
        m34();
        return;
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("後退移動", &params);
}

}  // namespace uking::ai

#include "Game/AI/AI/aiGiantNavMoveTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GiantNavMoveTarget::GiantNavMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantNavMoveTarget::~GiantNavMoveTarget() = default;

bool GiantNavMoveTarget::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

// NON_MATCHING: the original tests `(state | 1) == 5` on the byte (not `state == 4 || state == 5`)
void GiantNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = sub_71005E2BCC(mActor);
    if (!_78) {
        changeChild("見まわす", nullptr);
        setFailed();
        return;
    }

    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 4 || state == 5)
            nav->sub_7100F76790();
    }

    if (auto* nav = _78->_0)
        nav->sub_7100F7604C(nav->getRadiusMaybe());
    m34();
}

void GiantNavMoveTarget::changeToLookAround() {
    changeChild("見まわす", nullptr);
}

void GiantNavMoveTarget::changeToGoStraight() {
    if (_78->_8 != -1) {
        _78->_8 = -1;
        if (auto* nav = _78->_0)
            nav->inlineReset();
    }

    const f32 time = *mRepathTime_s;
    _80.value = time;
    _80.previous_value = time;
    _80.rate = -1.0f;

    const sead::Vector3f& target = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("直進", &pack);
}

inline bool GiantNavMoveTarget::findNavPoint(ksys::phys::NavMeshCharacter* nav, sead::Vector3f* point) {
    return nav->sub_7100F76078(point, *mTargetPos_d,
                               sead::Mathf::clampMin(sub_71007320F0(mActor, *mWeaponIdx_s), 0.0f) +
                                   *mReachTargetArea_s)
        .sub_7100F7EB40();
}

void GiantNavMoveTarget::sub_71003F7DA8() {
    _80.reset(*mRepathTime_s);

    if (auto* nav = mActor->m45()) {
        sead::Vector3f point;
        const bool found = findNavPoint(nav, &point);
        auto* data = _78;
        if (found) {
            if (data->_0) {
                data->_0->sub_7100F75F8C(point);
                data->_8 = 0;
            }
            return;
        }
    }

    auto* data = _78;
    if (data->_0) {
        data->_0->sub_7100F75F8C(*mTargetPos_d);
        data->_8 = 0;
    }
}

void GiantNavMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantNavMoveTarget::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTooFarDist_s, "TooFarDist");
    getStaticParam(&mTargetVMax_s, "TargetVMax");
    getStaticParam(&mTargetVMin_s, "TargetVMin");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

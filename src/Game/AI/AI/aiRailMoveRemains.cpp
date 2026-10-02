#include "Game/AI/AI/aiRailMoveRemains.h"

namespace uking::ai {

RailMoveRemains::RailMoveRemains(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveRemains::~RailMoveRemains() = default;

bool RailMoveRemains::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveRemains::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
    _74.set(-1.0f, -1.0f, -1.0f);
    return true;
}

ksys::map::Rail* RailMoveRemains::m34() {
    return sub_7100EEF264(mActor, 0);
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

void RailMoveRemains::m47(sead::Vector3f* out) {
    if (out)
        out->set(_60->_30.sub_7100EEB370());
}

}  // namespace uking::ai

#include "Game/AI/Action/actionSiteBossShootArrowRain.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

SiteBossShootArrowRain::SiteBossShootArrowRain(const InitArg& arg)
    : SiteBossShootNormalArrow(arg) {}

SiteBossShootArrowRain::~SiteBossShootArrowRain() = default;

bool SiteBossShootArrowRain::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrow::init_(heap);
}

void SiteBossShootArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrow::enter_(params);
}

void SiteBossShootArrowRain::leave_() {
    SiteBossShootNormalArrow::leave_();
}

void SiteBossShootArrowRain::loadParams_() {
    SiteBossShootNormalArrow::loadParams_();
    getStaticParam(&mArrowType_s, "ArrowType");
}

void SiteBossShootArrowRain::calc_() {
    SiteBossShootNormalArrow::calc_();
}

// NON_MATCHING: branch order, receiver setup and tail calls.
ksys::act::BaseProcLink* SiteBossShootArrowRain::sub_7100262BCC() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (*mArrowType_s == 1)
            return boss->_1560.sub_710066DE0C(*mIndex_d);
        if (*mArrowType_s == 0)
            return boss->_1560.sub_710066DE24(*mIndex_d);
    }
    return &ksys::act::getDummyBaseProcLink();
}

// NON_MATCHING: matrix expression scheduling and registers.
void SiteBossShootArrowRain::m33(const sead::Vector3f& pos, const sead::Matrix33f& rotation,
                                const sead::Vector3f& velocity) {
    auto* link = sub_7100262BCC();
    if (link->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (!accessor.isStateCalc()) {
            sead::Matrix33f ignite_rotation;
            ignite_rotation.makeR(*mIgniteRotate_s);
            sead::Matrix33f final_rotation;
            final_rotation.setMul(rotation, ignite_rotation);
            sead::Matrix34f mtx(final_rotation, pos);
            accessor.setProperties(mtx, &velocity, nullptr, nullptr, false, 2, -1);
            if (*mIsConnectChild_s)
                accessor.setThisActorAsChild(mActor, false);
        }
    }
}

}  // namespace uking::action

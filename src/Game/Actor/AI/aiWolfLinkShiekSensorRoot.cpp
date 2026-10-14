#include "Game/Actor/AI/aiWolfLinkShiekSensorRoot.h"
#include "Game/UI/uiUtils.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/gameRadarMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

WolfLinkShiekSensorRoot::WolfLinkShiekSensorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkShiekSensorRoot::~WolfLinkShiekSensorRoot() = default;

bool WolfLinkShiekSensorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkShiekSensorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::showRuntimeTip(14);
    changeChild("誘導", params);
}

void WolfLinkShiekSensorRoot::calc_() {
    auto* subsys = ui::UiSubsys1::instance();
    auto* radar = RadarMgr::instance();
    if (!subsys->get38d8() || !subsys->sub_71009674E8() || radar->_52) {
        setFailed();
        return;
    }

    if (*mUpdateTarget_d) {
        auto* nav = mActor->m45();
        nav->_1e0.lock();
        const sead::Vector3f current = nav->_194;
        nav->_1e0.unlock();
        if (!current.isNan()) {
            const sead::Vector3f target = radar->_6c;
            const f32 dx = current.x - target.x;
            const f32 dz = current.z - target.z;
            if (sead::Mathf::sqrt(dx * dx + dz * dz) > _48) {
                auto* child = getCurrentChild();
                ksys::act::ai::InlineParamPack pack;
                pack.addActor(act::PlayerInfo::getSomeProcLink(), "LeaderActor", -1);
                pack.addVec3(target, "TargetPos", -1);
                child->setFailed();
                changeChild("誘導", &pack);
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!child->isFinished())
            setFailed();
        else if (!subsys->sub_71009674E8())
            setFinished();
    }
}

void WolfLinkShiekSensorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkShiekSensorRoot::loadParams_() {
    if (getStaticParam(&mDistanceUntilUpdateTarget_s, "DistanceUntilUpdateTarget"))
        _48 = *mDistanceUntilUpdateTarget_s * *mDistanceUntilUpdateTarget_s;
    getDynamicParam(&mUpdateTarget_d, "UpdateTarget");
}

}  // namespace uking::ai

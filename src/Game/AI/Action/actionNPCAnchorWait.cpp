#include "Game/AI/Action/actionNPCAnchorWait.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

NPCAnchorWait::NPCAnchorWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCAnchorWait::~NPCAnchorWait() = default;

bool NPCAnchorWait::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<uking::act::NPC>(mActor);
    return true;
}

void NPCAnchorWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_40 && *mIsRainAnchor_d)
        _40->_8b9 = true;
    _48 = false;
    bool start_same_as = *mIsStartSameAS_d;
    if (auto* schedule = mActor->getSchedule()) {
        const sead::SafeString current_as(mActor->getASList()->sub_710115ECF4(0x37, 1));
        if (!current_as.isEmpty() &&
            current_as != sead::SafeString((*mIsRainAnchor_d ? schedule->_258 : schedule->_248)
                                               .getStringTop()))
            start_same_as = true;
    }
    playAS(m32(), !start_same_as, 0, 0, -1.0f);
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76778();
}

void NPCAnchorWait::leave_() {
    _48 = false;
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76790();
}

void NPCAnchorWait::loadParams_() {
    getDynamicParam(&mIsRainAnchor_d, "IsRainAnchor");
    getDynamicParam(&mIsStartSameAS_d, "IsStartSameAS");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCAnchorWait::calc_() {
    ksys::act::ai::Action::calc_();
}

bool NPCAnchorWait::handleMessage_(const ksys::Message* message) {
    return false;
}


}  // namespace uking::action

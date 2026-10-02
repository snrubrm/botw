#include "Game/AI/AI/aiSiteBossLswordTornadoRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

SiteBossLswordTornadoRoot::SiteBossLswordTornadoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossLswordTornadoRoot::~SiteBossLswordTornadoRoot() = default;

bool SiteBossLswordTornadoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossLswordTornadoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x40000);
    sub_710057DD54();
}

// NON_MATCHING: register allocation and the block order around isStateSleep()
void SiteBossLswordTornadoRoot::leave_() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    if (!enemy->_1128.getActorPartsActor("SiteBossBigFlameBall0").hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_1128.getActorPartsActor("SiteBossBigFlameBall0"), &accessor);
    if (!accessor.isStateSleep())
        mActor->sendMessage(*accessor.getMessageTransceiverId(), 0x8000004, nullptr, true);
}

void SiteBossLswordTornadoRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mDestPos_d, "DestPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai

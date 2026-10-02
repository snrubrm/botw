#include "Game/AI/AI/aiSiteBossLswordTornadoRoot.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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

void SiteBossLswordTornadoRoot::sub_710057DD54() {
    _88 = ksys::Timer(90, 90);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addVec3(*mDestPos_d, "MoveDstPos", -1);
    params.addInt(0, "RailIndex", -1);
    params.addBool(false, "IsReturnHome", -1);
    params.addBool(false, "IsForceWarp", -1);
    params.addBool(false, "IsPartsActorTgOn", -1);
    params.addBool(false, "IsPartsWarpEffectSync", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai

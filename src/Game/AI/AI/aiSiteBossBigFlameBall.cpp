#include "Game/AI/AI/aiSiteBossBigFlameBall.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SiteBossBigFlameBall::SiteBossBigFlameBall(const InitArg& arg) : SiteBossFlameBall(arg) {}

SiteBossBigFlameBall::~SiteBossBigFlameBall() = default;

bool SiteBossBigFlameBall::init_(sead::Heap* heap) {
    return SiteBossFlameBall::init_(heap);
}

void SiteBossBigFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossFlameBall::enter_(params);
    _1f4 = m35();
    _200 = *mDestOffset_s;
    _20c = *mRotOffset_m;
    _1f0 = *mSpeed_m;
}

void SiteBossBigFlameBall::calc_() {
    SiteBossFlameBall::calc_();
}

void SiteBossBigFlameBall::leave_() {
    SiteBossFlameBall::leave_();
}

bool SiteBossBigFlameBall::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1) || message->getType() != 0x8000058 ||
        !message->getUserData()) {
        return SiteBossFlameBall::handleMessage_(message);
    }
    auto* payload = static_cast<SiteBossProjectilePayload*>(message->getUserData());
    if (!getCurrentChild())
        return SiteBossFlameBall::handleMessage_(message);

    _200 = *mDestOffset1_s;
    ksys::act::ai::InlineParamPack params;
    params.addString(payload->mNodeName.cstr(), "NodeName", -1);
    _20c = payload->_c;
    _1f0 = 0.1f;
    params.addVec3(payload->_c, "RotOffset", -1);
    params.addVec3(_1f4, "TransOffset", -1);
    params.addBool(true, "IsKeepParentActor", -1);
    params.acquireActor(nullptr, "ParentActor", -1);
    changeChild("所持", &params);
    return true;
}

void SiteBossBigFlameBall::loadParams_() {
    SiteBossFlameBall::loadParams_();
    getStaticParam(&mDestOffset_s, "DestOffset");
    getStaticParam(&mDestOffset1_s, "DestOffset1");
    getMapUnitParam(&mSpeed_m, "Speed");
    getMapUnitParam(&mRotOffset_m, "RotOffset");
}

void SiteBossBigFlameBall::m37() {}

u32 SiteBossBigFlameBall::m50() {
    return 8;
}

sead::Vector3f SiteBossBigFlameBall::m58() {
    return _20c;
}

}  // namespace uking::ai

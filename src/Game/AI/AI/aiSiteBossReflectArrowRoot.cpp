#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossReflectArrowRoot::SiteBossReflectArrowRoot(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossReflectArrowRoot::~SiteBossReflectArrowRoot() = default;

bool SiteBossReflectArrowRoot::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossReflectArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
}

void SiteBossReflectArrowRoot::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1560.sub_710066C540(sub_71005D9050(mActor), 20);
}

void SiteBossReflectArrowRoot::loadParams_() {
    SiteBossShootNormalArrowRoot::loadParams_();
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool SiteBossReflectArrowRoot::m34() {
    return sub_7100588164(false);
}

void SiteBossReflectArrowRoot::m41() {}

s32 SiteBossReflectArrowRoot::m43() {
    return 1;
}

void SiteBossReflectArrowRoot::calc_() {
    sub_7100582688();
    SiteBossShootNormalArrowRoot::calc_();
}

void SiteBossReflectArrowRoot::m45(sead::Vector3f* out) {
    if (sub_7100582C20(out))
        return;
    SiteBossShootNormalArrowRoot::m45(out);
}

void SiteBossReflectArrowRoot::m46(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
}

bool SiteBossReflectArrowRoot::m48() {
    return SiteBossShootNormalArrowRoot::m48() | (_144 >= u32(_500));
}

// NON_MATCHING: the original null-checks the message reference
bool SiteBossReflectArrowRoot::handleMessage_(const ksys::Message& message) {
    if (message.getBrokerId() != u32(-1) || message.getType() != 0x8000057)
        return false;

    if (!message.getUserData())
        return false;
    const s32 idx = *static_cast<s32*>(message.getUserData());
    if (idx >= 0 && idx <= 20)
        _488[idx] = true;
    return true;
}

}  // namespace uking::ai

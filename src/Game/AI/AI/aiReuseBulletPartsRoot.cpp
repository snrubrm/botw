#include "Game/AI/AI/aiReuseBulletPartsRoot.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ReuseBulletPartsRoot::ReuseBulletPartsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReuseBulletPartsRoot::~ReuseBulletPartsRoot() = default;

bool ReuseBulletPartsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReuseBulletPartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _88 = false;
    if (mActor->getRootAi()->getI() == 2) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
        if (auto* lod_state = mActor->getLodState())
            lod_state->mFlags10.set(0x40);
        changeChild("投擲生成");
    } else {
        changeChild("通常");
    }
}

void ReuseBulletPartsRoot::calc_() {
    if (_88) {
        sub_7100551DAC();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        sub_7100551DAC();
        if (isCurrentChild("投擲生成"))
            m34();
    } else if (child->isChangeable()) {
        auto* life = mActor->getLife();
        if (life && *life <= 0)
            sub_7100551DAC();
    }
}

void ReuseBulletPartsRoot::leave_() {
    if (isActorDeletedOrDeleting())
        return;
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D8EEE0();
}

void ReuseBulletPartsRoot::loadParams_() {}

bool ReuseBulletPartsRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000007) {
        sub_7100551DAC();
        return true;
    }
    if (_38.m2(message)) {
        _88 = true;
        return true;
    }
    return false;
}

void ReuseBulletPartsRoot::sub_7100551DAC() {
    if (auto* info = mActor->m135())
        info->_4 = 1;
    mActor->emitDisappearEffect();

    ksys::act::BaseProcLink* link;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor);
    if (bullet && bullet->_bd0._0.hasProc()) {
        link = &bullet->_bd0._0;
    } else {
        auto& create_link = mActor->getCreateArgBaseProcLink();
        link = create_link.hasProc() ? &create_link : &ksys::act::sUnk_71026505e0;
    }

    if (!link->hasProc()) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.isDeletedOrDeleting())
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    else
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

bool ReuseBulletPartsRoot::m34() {
    return true;
}

}  // namespace uking::ai

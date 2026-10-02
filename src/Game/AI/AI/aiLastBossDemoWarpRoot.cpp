#include "Game/AI/AI/aiLastBossDemoWarpRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossDemoWarpRoot::LastBossDemoWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossDemoWarpRoot::~LastBossDemoWarpRoot() = default;

bool LastBossDemoWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossDemoWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    sub_71005DB3EC(mActor);
}

void LastBossDemoWarpRoot::leave_() {
    m37();
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void LastBossDemoWarpRoot::loadParams_() {
    getStaticParam(&mIsPartsActorTgOn_s, "IsPartsActorTgOn");
}

void LastBossDemoWarpRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child || (!child->isFinished() && !child->isFailed()))
        return;

    if (isCurrentChild("ワープ前")) {
        m35();
    } else if (isCurrentChild("ワープ")) {
        m36();
    } else if (isCurrentChild("ワープ後")) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void LastBossDemoWarpRoot::m34() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(true, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ前", &pack);
}

void LastBossDemoWarpRoot::m35() {
    changeChild("ワープ");
}

void LastBossDemoWarpRoot::m36() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sead::Vector3f::zero, "TargetPos", -1);
    pack.addBool(false, "IsKeepDisableDraw", -1);
    pack.addBool(*mIsPartsActorTgOn_s, "IsPartsActorTgOn", -1);
    pack.addBool(true, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ後", &pack);
}

// NON_MATCHING: the MessageType temporary is at sp+0x2c in the original (sp+0x28 here)
void LastBossDemoWarpRoot::m37() {
    sub_71007A3540(mActor);
    if (!*mIsPartsActorTgOn_s)
        return;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    for (auto* part : enemy->_1128.mList) {
        if (!part->mLink.hasProc())
            continue;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&part->mLink, &accessor);
        if (accessor.isStateCalc())
            mActor->sendMessage(*accessor.getMessageTransceiverId(), 0x8000030, nullptr, true);
    }
}

}  // namespace uking::ai

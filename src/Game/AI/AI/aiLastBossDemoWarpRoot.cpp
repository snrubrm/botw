#include "Game/AI/AI/aiLastBossDemoWarpRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace uking::ai

#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

StalEnemyRoot::StalEnemyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyRoot::~StalEnemyRoot() {
    auto* actor = mActor;
    sub_71007253C0(actor);
    sub_71007254A4(actor);
    if (mStalEnemyUnit_a && *static_cast<Unk_71024241a8**>(mStalEnemyUnit_a) == &_2e8)
        *static_cast<Unk_71024241a8**>(mStalEnemyUnit_a) = nullptr;
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
}

bool StalEnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyRoot::leave_() {
    sub_71005DA114(mActor, &_38);
}

bool StalEnemyRoot::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("所持") && _100.m2(*message))
        return true;

    auto* actor = mActor;
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) && !_150._30 &&
        ksys::act::isAttClientEnabled(actor, "Grab")) {
        if (!isCurrentChild("所持") && !isCurrentChild("拾い合体") && _150.m2(*message)) {
            _150.sub_710070B5A0(actor);
            return true;
        }
    }

    if (message->getType() == 0x3000007) {
        _2e0 = true;
        return true;
    }
    return false;
}

void StalEnemyRoot::loadParams_() {
    getStaticParam(&mDeadCount_s, "DeadCount");
    getStaticParam(&mSearchFrame_s, "SearchFrame");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutOfWaterOffset_s, "OutOfWaterOffset");
    getStaticParam(&mDeadCheckFrame_s, "DeadCheckFrame");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSmallSpreadDist_s, "SmallSpreadDist");
    getStaticParam(&mSearchDistXZ_s, "SearchDistXZ");
    getStaticParam(&mSearchDistY_s, "SearchDistY");
    getStaticParam(&mFallHeight_s, "FallHeight");
    getMapUnitParam(&mIsCreateStalPart_m, "IsCreateStalPart");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
    getAITreeVariable(&mStalEnemyUnit_a, "StalEnemyUnit");
}

bool StalEnemyRoot::m34() {
    if (_2e8._8.isOnBit(0))
        return false;
    return sub_71005D6E28(mActor);
}

void StalEnemyRoot::m35(ksys::act::ai::InlineParamPack* params) {}

bool StalEnemyRoot::m36() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return true;
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai

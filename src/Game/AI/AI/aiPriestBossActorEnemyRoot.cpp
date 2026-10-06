#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBossActorEnemyRoot::PriestBossActorEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

PriestBossActorEnemyRoot::~PriestBossActorEnemyRoot() = default;

bool PriestBossActorEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void PriestBossActorEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void PriestBossActorEnemyRoot::calc_() {
    if (sub_710071E208())
        return;

    m48();
    m49();
    m50();
    if (m51() || m53())
        return;

    EnemyRoot::calc_();
}

bool PriestBossActorEnemyRoot::m51() {
    if (isCurrentChild("フェイズ開始")) {
        auto* child = getCurrentChild();
        if (!m45() && !child->isFinished() && !child->isFailed() && !child->isChangeable())
            return true;
        child->setFinished();
    }
    return false;
}

bool PriestBossActorEnemyRoot::m52() {
    if (!sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a)))
        return false;
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    return unit->_248[unit->_3c]._0;
}

void PriestBossActorEnemyRoot::leave_() {
    EnemyRoot::leave_();
    sub_7100507440(false);
    sub_710071EDD0(mActor, _22c);
}

void PriestBossActorEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mIsReactionOnDead_s, "IsReactionOnDead");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossActorEnemyRoot::handleMessage_(const ksys::Message* message) {
    EnemyRoot::handleMessage_(message);
    return false;
}

Unk_7102450fa8* PriestBossActorEnemyRoot::sub_7100506A40() {
    return sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
}

bool PriestBossActorEnemyRoot::m45() {
    return false;
}

bool PriestBossActorEnemyRoot::m46() {
    return false;
}

bool PriestBossActorEnemyRoot::m47() {
    return true;
}

void PriestBossActorEnemyRoot::m48() {
    if (!m47())
        return;
    if (auto* lod = mActor->getLodState())
        sub_710071EDD0(mActor, lod->mFlags8.isOn(2));
}

void PriestBossActorEnemyRoot::m49() {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20)) {
        ksys::act::disableAttClient(mActor, "LockOn");
    } else if (!sub_7100506A40() ||
               !sub_7100506A40()->isFlagOn(Unk_7102450fa8::Flag::_12) ||
               ksys::act::attentionStuff(mActor)) {
        ksys::act::enableAttClient(mActor, "LockOn");
    } else {
        ksys::act::disableAttClient(mActor, "LockOn");
    }
}

void PriestBossActorEnemyRoot::sub_7100506DB0() {
    if (!sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a)))
        return;
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    _1e8 = unit->_3c;
    _228.resetBit(Flag(Flag::_1));
}

// NON_MATCHING: the three SEAD_ENUM bit-index round trips use separate stack slots here; the original shares one slot
// (frame 0x30 instead of 0x40)
void PriestBossActorEnemyRoot::m50() {
    auto* as_list = mActor->getASList();
    if (!as_list->x_1(0, 0).isEmpty() &&
        as_list->sub_710115AD68(as_list->x_1(0, 0))) {
        _228.setBit(Flag(Flag::_3));
        as_list->sub_710115F4A0(false, 1, 0, &ksys::as::ASList::Unk2::sub_7100507A64);
    } else if (_228.isOnBit(Flag(Flag::_3))) {
        _228.resetBit(Flag(Flag::_3));
        as_list->sub_710115F4A0(true, 1, 0, &ksys::as::ASList::Unk2::sub_7100507A64);
        as_list->startAnimationMaybe(-1.0f, -1.0f, "VeilMatAnime", 1, 0, true);
    }
}

}  // namespace uking::ai

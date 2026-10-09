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

// NON_MATCHING: enum bit-index temporaries occupy separate stack slots
// (frame 0x70 instead of 0x50), with different flag reload scheduling.
// 0x710050719c
bool PriestBossActorEnemyRoot::m53() {
    if (!m52())
        return false;
    const bool phase_finished = m46();
    if (!phase_finished &&
        (!isCurrentChild("フェイズ終了") || _228.isOnBit(Flag(Flag::_2)))) {
        changeChild("フェイズ終了", nullptr);
        sub_7100507440(true);
        _228.resetBit(Flag(Flag::_2));
        return true;
    }
    if (!_228.isOnBit(Flag(Flag::_1))) {
        auto* child = getCurrentChild();
        if (phase_finished || child->isFinished() || child->isFailed() || child->isChangeable()) {
            sub_7100507440(false);
            _228.setBit(Flag(Flag::_1));
        }
    }
    if (!_228.isOnBit(Flag(Flag::_1)))
        return true;
    const u32 old_phase = _1e8;
    const u32 new_phase =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))->_3c;
    const bool phase_finished_now = m46();
    if (old_phase == new_phase && !phase_finished_now)
        return true;
    sub_7100506DB0();
    _228.resetBit(Flag(Flag::_2));
    _228.resetBit(Flag(Flag::_1));
    if (old_phase != new_phase) {
        _228.setBit(Flag(Flag::_2));
        return true;
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

// NON_MATCHING: function-argument evaluation caches the actor before the unit RTTI check.
// 0x7100506ed8
bool PriestBossActorEnemyRoot::m35() {
    if (*mIsReactionOnDead_s) {
        if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive))
            return true;
        if (auto* life = mActor->getLife(); life && *life < 1)
            return true;
    }
    return sub_710071E64C(
        mActor,
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a)));
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

void PriestBossActorEnemyRoot::m34(ksys::act::ai::InlineParamPack* params) {
    _228.resetBit(Flag(Flag::_2));
    if (sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a)) &&
        !m45() &&
        _1e8 != sead::DynamicCast<Unk_7102450fa8>(
                    *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a))
                    ->_3c) {
        sub_7100506DB0();
        changeChild("フェイズ開始", nullptr);
        return;
    }
    EnemyRoot::m34(params);
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

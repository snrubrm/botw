#include "Game/AI/AI/aiZoraHeroRelicBattleRidePlayer.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_7102433970.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::ai {

ZoraHeroRelicBattleRidePlayer::ZoraHeroRelicBattleRidePlayer(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRidePlayer::~ZoraHeroRelicBattleRidePlayer() = default;

bool ZoraHeroRelicBattleRidePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroRelicBattleRidePlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _c0 = false;
    _50.reset();
    _60.reset();
    _40.reset();
    sub_71006138CC();
}

void ZoraHeroRelicBattleRidePlayer::sub_71006138CC() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    pos.setMul(mActor->getMtx(), sead::Vector3f{0.0f, 0.0f, 15.0f});
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void ZoraHeroRelicBattleRidePlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleRidePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

bool ZoraHeroRelicBattleRidePlayer::handleMessage_(const ksys::Message* message) {
    if (!_70._30 && _70.m2(*message)) {
        sub_7100614194(_70._38.mLink);
        _70.x();
        return true;
    }
    if (message->getType() == 0x800006a) {
        _c0 = true;
        return true;
    }
    return false;
}

// NON_MATCHING: the original copies the link position component-wise (separate stores, `fcmp; b.gt` on the squared
// distances, the actor height read after the access destructor); ours merges the copy and schedules the loads differently.
// 0x7100614194
void ZoraHeroRelicBattleRidePlayer::sub_7100614194(const ksys::act::BaseProcLink& link) {
    if (!link.hasProc())
        return;
    if (_50 == link || _60 == link || _40 == link)
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    sead::Vector3f target = accessor.getActorMtx().getTranslation();
    if (!_40.hasProc()) {
        target.y = mActor->getMtx().getTranslation().y;
    } else {
        const f32 actor_x = mActor->getMtx().getTranslation().x;
        const f32 actor_z = mActor->getMtx().getTranslation().z;
        ksys::act::ActorConstDataAccess current;
        ksys::act::acquireActor(&_40, &current);
        const sead::Vector3f current_pos = current.getActorMtx().getTranslation();
        const f32 current_dx = actor_x - current_pos.x;
        const f32 current_dz = actor_z - current_pos.z;
        const f32 link_dx = actor_x - target.x;
        const f32 link_dz = actor_z - target.z;
        target.y = mActor->getMtx().getTranslation().y;
        if (current_dx * current_dx + current_dz * current_dz <= link_dx * link_dx + link_dz * link_dz)
            return;
    }
    if (sub_710061430C(target))
        _40 = link;
}

// 0x7100613d60: takes over the candidate link _60 as _50 if the ray to it is free; clears both otherwise
void ZoraHeroRelicBattleRidePlayer::sub_7100613D60() {
    if (_60.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_60, &accessor)) {
            const auto& mtx = accessor.getActorMtx();
            sead::Vector3f target;
            target.x = mtx.m[0][3];
            target.z = mtx.m[2][3];
            target.y = mActor->getMtx().m[1][3];
            if (sub_710061430C(target)) {
                _50 = _60;
                _60.reset();
                return;
            }
        }
    }
    _50.reset();
    _60.reset();
}

// 0x7100613ff0
void ZoraHeroRelicBattleRidePlayer::sub_7100613FF0() {
    if (!ksys::gdt::getFlag_Water_Relic_ChanceTime(false)) {
        if (auto** unit = static_cast<Unk_71025afb58**>(mZoraHeroShowMsgUnit_a)) {
            if (auto* msg_unit = sead::DynamicCast<Unk_7102433970>(*unit))
                msg_unit->_8.sub_7100744200(1, false);
        }
    }
    changeChild("周回", nullptr);
}

// 0x710061430c
bool ZoraHeroRelicBattleRidePlayer::sub_710061430C(const sead::Vector3f& target) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.setGroundHit(ksys::phys::GroundHit::HitAll);
    query.setStartAndEnd(mActor->getMtx().getTranslation(), target);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

}  // namespace uking::ai

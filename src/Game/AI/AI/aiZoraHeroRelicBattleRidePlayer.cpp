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

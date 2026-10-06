#include "Game/AI/AI/aiZoraHeroRelicBattleNormal.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

static const sead::SafeString sUnk_7102433600 = "DestinationAnchor";

ZoraHeroRelicBattleNormal::ZoraHeroRelicBattleNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleNormal::~ZoraHeroRelicBattleNormal() = default;

bool ZoraHeroRelicBattleNormal::init_(sead::Heap* heap) {
    _9c = -1;
    sub_710061223C();
    return true;
}

void ZoraHeroRelicBattleNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
           std::numeric_limits<f32>::quiet_NaN()};
    if (ksys::gdt::getFlag_Water_Relic_firstPrinceRide()) {
        _98 = false;
        sub_7100612434();
    } else {
        _98 = true;
        sub_710061288C();
    }
}

void ZoraHeroRelicBattleNormal::calc_() {
    if (_98)
        return;
    sub_7100612434();
}

void ZoraHeroRelicBattleNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleNormal::loadParams_() {
    getStaticParam(&mWarpDistanceXZ_s, "WarpDistanceXZ");
    getStaticParam(&mNearPlayerDistanceXZ_s, "NearPlayerDistanceXZ");
}

void ZoraHeroRelicBattleNormal::sub_710061223C() {
    for (auto& anchor : _38)
        anchor._c = false;

    auto* map_object = mActor->getMapObject();
    if (!map_object)
        return;

    auto* link_data = map_object->getLinkData();
    if (!link_data)
        return;

    if (link_data->mObjects.size() < 1)
        return;

    int count = 0;
    for (auto& object : link_data->mObjects) {
        if (sUnk_7102433600 != object->getUnitConfigName())
            continue;

        auto& anchor = _38[count];
        anchor._c = true;
        const sead::Vector3f pos = object->getTranslate();
        anchor.pos = pos;
        if (++count >= 5)
            return;
    }
}

void ZoraHeroRelicBattleNormal::sub_710061288C() {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("待機", &params);
}

// 0x71006129e8
void ZoraHeroRelicBattleNormal::sub_71006129E8(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤ水中", &pack);
}

// 0x7100612ad4
void ZoraHeroRelicBattleNormal::sub_7100612AD4(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤ上空", &pack);
}

// 0x7100612bc0
void ZoraHeroRelicBattleNormal::sub_7100612BC0(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("エリア外移動", &pack);
}

// 0x7100612cac
void ZoraHeroRelicBattleNormal::sub_7100612CAC(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("エリア外待機", &pack);
}

// 0x7100612d98
void ZoraHeroRelicBattleNormal::sub_7100612D98(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("水中ワープ", &pack);
}

}  // namespace uking::ai

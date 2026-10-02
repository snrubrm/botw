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

// NON_MATCHING: the original copies the translation as 8 + 4 bytes (memcpy order)
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
        anchor.pos = object->getTranslate();
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

}  // namespace uking::ai

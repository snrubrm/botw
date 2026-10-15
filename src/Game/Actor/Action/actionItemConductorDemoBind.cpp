#include "Game/Actor/Action/actionItemConductorDemoBind.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actArmorBase.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

ItemConductorDemoBind::ItemConductorDemoBind(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ItemConductorDemoBind::~ItemConductorDemoBind() = default;

// NON_MATCHING: transform calculation and parameter load scheduling.
void ItemConductorDemoBind::sub_71001C256C() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor || !ksys::evt::Manager::instance())
        return;
    auto* link = ksys::evt::Manager::instance()->getBaseProcLinkFromActiveEvent(
        mActorName_d, mUniqueName_d);
    if (!link)
        return;
    armor->_8f8.x(*link);
    armor->_8f8._28 = mNodeName_d.cstr();
    armor->_8f8._30.getKey().reset();
    armor->_8f8._68.makeRT(
        sead::Vector3f(*mRotOffsetX_d, *mRotOffsetY_d, *mRotOffsetZ_d) * sead::Mathf::deg2rad(1),
        {*mTransOffsetX_d, *mTransOffsetY_d, *mTransOffsetZ_d});
    if (!armor->getModelBindInfo())
        armor->sub_71011DA824(&armor->_8f8);
}

void ItemConductorDemoBind::sub_71001C27A8() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return;
    auto* owner = armor->getOwner();
    if (!owner)
        return;
    auto* player = sead::DynamicCast<act::PlayerBase>(owner);
    if (!player)
        return;
    armor->_8f8.x(player);
    armor->_8f8._28 = armor->sub_7100E2AEF4().cstr();
    armor->_8f8._30.getKey().reset();
    sead::Vector3f translation, rotation;
    armor->sub_7100E2B094(&translation);
    armor->sub_7100E2B3D0(&rotation);
    armor->_8f8._68.makeRT(rotation, translation);
    if (!armor->getModelBindInfo())
        armor->sub_71011DA824(&armor->_8f8);
}

void ItemConductorDemoBind::sub_71001C2A08() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return;
    auto* owner = armor->getOwner();
    if (!owner)
        return;
    auto* player = sead::DynamicCast<act::PlayerBase>(owner);
    if (!player)
        return;
    armor->_8f8.x(player);
    armor->_8f8._28 = armor->sub_7100E2AFC4().cstr();
    armor->_8f8._30.getKey().reset();
    sead::Vector3f translation, rotation;
    armor->sub_7100E2B718(&translation);
    armor->sub_7100E2B820(&rotation);
    armor->_8f8._68.makeRT(rotation, translation);
    if (!armor->getModelBindInfo())
        armor->sub_71011DA824(&armor->_8f8);
}

bool ItemConductorDemoBind::sub_71001C20C0() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return false;
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(armor->getOwner());
    return player && player->_c44.isOnBit(16);
}

bool ItemConductorDemoBind::sub_71001C21C0() {
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (!armor)
        return false;
    auto* player = sead::DynamicCast<uking::act::PlayerBase>(armor->getOwner());
    if (!player)
        return false;
    return sub_71001C2C68(player);
}

void ItemConductorDemoBind::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71001C20C0()) {
        sub_71001C256C();
        _80 = 0;
    } else if (sub_71001C21C0()) {
        sub_71001C2A08();
        _80 = 2;
    } else {
        sub_71001C27A8();
        _80 = 1;
    }
    setFinished();
}

void ItemConductorDemoBind::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemConductorDemoBind::loadParams_() {
    getDynamicParam(&mRotOffsetX_d, "RotOffsetX");
    getDynamicParam(&mRotOffsetY_d, "RotOffsetY");
    getDynamicParam(&mRotOffsetZ_d, "RotOffsetZ");
    getDynamicParam(&mTransOffsetX_d, "TransOffsetX");
    getDynamicParam(&mTransOffsetY_d, "TransOffsetY");
    getDynamicParam(&mTransOffsetZ_d, "TransOffsetZ");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mNodeName_d, "NodeName");
}

void ItemConductorDemoBind::calc_() {
    switch (_80) {
    case 0:
        if (sub_71001C20C0())
            break;
        // Fall through.
    case 1:
        if (sub_71001C21C0()) {
            sub_71001C2A08();
            _80 = 2;
        }
        break;
    case 2:
        if (sub_71001C20C0()) {
            sub_71001C256C();
            _80 = 0;
        } else if (!sub_71001C21C0()) {
            sub_71001C27A8();
            _80 = 1;
        }
        break;
    }
}

}  // namespace uking::action

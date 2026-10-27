#include "Game/Actor/AI/aiWolfLinkAmiibo.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameAmiiboMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

WolfLinkAmiibo::WolfLinkAmiibo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkAmiibo::~WolfLinkAmiibo() {
    if (_60)
        ksys::phys::HavokAI::instance()->destroyQuery(_60);
}

bool WolfLinkAmiibo::havokQueryFinished() {
    auto* query = _60;
    if (!query || query->_8 != 2)
        return false;

    if (query->_38 >= query->_3c) {
        const sead::Vector3f pos = query->_40;
        ksys::phys::RayCastBodyQuery ray(nullptr, ksys::phys::GroundHit::HitAll);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGround);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        ray.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);

        {
            const sead::Vector3f start(pos.x, pos.y + 2.0f, pos.z);
            ray.setStart(start);
        }
        {
            const sead::Vector3f end(pos.x, pos.y - 2.0f, pos.z);
            ray.setEnd(end);
        }

        if (ray.worldRayCast(ksys::phys::ContactLayerType::Entity))
            ray.getHitPosition(&_50);
        else
            setFlag(Flag::_5);
    } else {
        setFlag(Flag::_5);
    }

    ksys::phys::HavokAI::instance()->destroyQuery(_60);
    _60 = nullptr;
    return true;
}

bool WolfLinkAmiibo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkAmiibo::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c.makeAllZero();
    if (cannotUseWolfLinkAmiibo()) {
        ui::showInfoOverlay(26);
        setFailed();
        return;
    }
    sub_7100600A6C();
}

void WolfLinkAmiibo::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the five flag tests differ only in the commutative `and` operand order (ours puts the
// mask first). The natural isOnBit form also loads _5c before the mask; a one-use mask local fixes that
// scheduling but not the operand order.
void WolfLinkAmiibo::sub_71006013D4() {
    if (!AmiiboMgr::instance() || !ksys::gdt::Manager::instance()) {
        ui::showInfoOverlay(15);
        setFailed();
        return;
    }

    if (isFlagOn(Flag::_5)) {
        ui::showInfoOverlay(26);
        setFailed();
        return;
    }

    if (isFlagOn(Flag::_0) && !isFlagOn(Flag::_2)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_50, "TargetPos", -1);
        changeChild("ワープ", &pack);
        return;
    }

    if (isFlagOn(Flag::_1)) {
        sub_7100601594();
        return;
    }

    if (isFlagOn(Flag::_3)) {
        ui::showInfoOverlay(25);
        setFailed();
        return;
    }

    sub_7100601594();
}

void WolfLinkAmiibo::sub_7100601594() {
    ksys::act::ai::InlineParamPack pack;
    pack.addInt(_5c.getDirect(), "SpawnFlags", -1);
    pack.addVec3(_50, "TargetPos", -1);
    changeChild("登録", &pack);
}

void WolfLinkAmiibo::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
}

}  // namespace uking::ai

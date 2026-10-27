#include "Game/Actor/AI/aiWolfLinkAmiibo.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"

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

void WolfLinkAmiibo::loadParams_() {
    getStaticParam(&mAreaSearchCharacterRadius_s, "AreaSearchCharacterRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mAreaSearchRadius_s, "AreaSearchRadius");
}

}  // namespace uking::ai

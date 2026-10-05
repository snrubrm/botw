#include "Game/AI/Action/actionWildHorseCreate.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::action {

WildHorseCreate::WildHorseCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WildHorseCreate::~WildHorseCreate() = default;

bool WildHorseCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WildHorseCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = ksys::map::PlacementMgr::instance();
    if (manager && manager->mPlacementActors) {
        const f32 distance = ksys::map::getActorTraverseDist("GameRomHorse01", 1.0f);
        _58 = distance * distance;
    }
}

void WildHorseCreate::leave_() {
    ksys::act::ai::Action::leave_();
}

void WildHorseCreate::loadParams_() {
    getStaticParam(&mMinCreateNum_s, "MinCreateNum");
    getStaticParam(&mMaxCreateNum_s, "MaxCreateNum");
    getMapUnitParam(&mWildHorseCreateNum_m, "WildHorseCreateNum");
}

void WildHorseCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

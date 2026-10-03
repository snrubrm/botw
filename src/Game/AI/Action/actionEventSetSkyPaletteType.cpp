#include "KingSystem/World/worldSkyMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventSetSkyPaletteType.h"

namespace uking::action {

EventSetSkyPaletteType::EventSetSkyPaletteType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetSkyPaletteType::~EventSetSkyPaletteType() = default;

bool EventSetSkyPaletteType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetSkyPaletteType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetSkyPaletteType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetSkyPaletteType::loadParams_() {
    getDynamicParam(&mSkyPalette_d, "SkyPalette");
}

void EventSetSkyPaletteType::calc_() {
    // NON_MATCHING: the original writes the SkyMgr fields without the PtrArray bounds check that
    // getXMgr() keeps (reads like an inline member function of the manager; not repeated elsewhere)
    auto* sky = ksys::world::Manager::instance()->getSkyMgr();
    sky->_3fa8 = 2;
    sky->_3fa4 = *mSkyPalette_d;
    setFinished();
}

}  // namespace uking::action

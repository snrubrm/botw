#include "Game/AI/AI/aiRemainElectricCannonRoot.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

RemainElectricCannonRoot::RemainElectricCannonRoot(const InitArg& arg)
    : RemainElectricCannonRootBase(arg) {}

RemainElectricCannonRoot::~RemainElectricCannonRoot() = default;

bool RemainElectricCannonRoot::init_(sead::Heap* heap) {
    return RemainElectricCannonRootBase::init_(heap);
}

void RemainElectricCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainElectricCannonRootBase::enter_(params);
}

void RemainElectricCannonRoot::calc_() {
    RemainElectricCannonRootBase::calc_();
}

void RemainElectricCannonRoot::leave_() {
    RemainElectricCannonRootBase::leave_();
}

void RemainElectricCannonRoot::loadParams_() {
    RemainElectricCannonRootBase::loadParams_();
    getStaticParam(&mSearchMaxDistLoiter_s, "SearchMaxDistLoiter");
}

f32 RemainElectricCannonRoot::m41() {
    bool is_battle = false;
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->getParam().get().getBool(&is_battle, "Electric_Relic_Battle");
    if (is_battle)
        return RemainElectricCannonRootBase::m41();
    return *mSearchMaxDistLoiter_s;
}

}  // namespace uking::ai

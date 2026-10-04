#include "Game/AI/Action/actionTerrainHideCenter.h"

namespace uking::action {

TerrainHideCenter::TerrainHideCenter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TerrainHideCenter::~TerrainHideCenter() = default;

bool TerrainHideCenter::init_(sead::Heap* heap) {
    _1c = false;
    return true;
}

void TerrainHideCenter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TerrainHideCenter::leave_() {
    if (_1c) {
        _1c = false;
        sub_7100E179A4(true, true, true, true);
    }
}

void TerrainHideCenter::loadParams_() {}

void TerrainHideCenter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

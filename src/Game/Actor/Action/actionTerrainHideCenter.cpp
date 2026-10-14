#include "Game/Actor/Action/actionTerrainHideCenter.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking::action {

static f32 sUnk_71024e1a40 = 0.01f;

TerrainHideCenter::TerrainHideCenter(const InitArg& arg) : ksys::act::ai::Action(arg) {
    if (sUnk_71024e1a40 > 0.0f)
        sUnk_71024e1a40 = ksys::tera::Terrain::instance()->_400;
}

// NON_MATCHING: same instructions; the original does not re-materialise `this` (`mov x0, x19`) for the call
// to sub_7100E179A4
TerrainHideCenter::~TerrainHideCenter() {
    leave_();
}

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

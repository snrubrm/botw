#include "Game/AI/Action/actionTerrainCalcCenter.h"
#include "KingSystem/Terrain/teraSystem.h"

void setInitBeforeStageGenDone(bool done);

namespace uking::action {

TerrainCalcCenter::TerrainCalcCenter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TerrainCalcCenter::~TerrainCalcCenter() = default;

bool TerrainCalcCenter::init_(sead::Heap* heap) {
    _40 &= ~2u;
    _40 |= 4u;
    return true;
}

void TerrainCalcCenter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TerrainCalcCenter::leave_() {
    if ((_40 & 3) != 1)
        return;
    ksys::tera::System::instance()->sub_710111F518(9, 9);
    ksys::tera::System::instance()->sub_7101112A74();
    setInitBeforeStageGenDone(true);
    _40 |= 2;
}

void TerrainCalcCenter::loadParams_() {
    getDynamicParam(&mlevel_d, "level");
    getDynamicParam(&mtype_d, "type");
    getDynamicParam(&mmeshReso_d, "meshReso");
    getDynamicParam(&mpos_d, "pos");
}

void TerrainCalcCenter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/AI/aiDungeonMoveTag.h"

namespace uking::ai {

DungeonMoveTag::DungeonMoveTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DungeonMoveTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonMoveTag::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = *mInitDgnMoveDis_m > 0.0f;
    changeChild("待機");
    _49 = false;
}

void DungeonMoveTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonMoveTag::loadParams_() {
    getMapUnitParam(&mInitDgnMoveDis_m, "InitDgnMoveDis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
}

}  // namespace uking::ai

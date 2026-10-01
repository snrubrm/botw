#include "Game/AI/AI/aiDungeonMoveTagCont.h"

namespace uking::ai {

DungeonMoveTagCont::DungeonMoveTagCont(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonMoveTagCont::~DungeonMoveTagCont() = default;

bool DungeonMoveTagCont::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonMoveTagCont::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = false;
    changeChild("待機");
    _51 = false;
}

void DungeonMoveTagCont::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonMoveTagCont::loadParams_() {
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mReturnDisFromCurrentPos_m, "ReturnDisFromCurrentPos");
    getMapUnitParam(&mReturnSpeedFromCurrentPos_m, "ReturnSpeedFromCurrentPos");
}

}  // namespace uking::ai

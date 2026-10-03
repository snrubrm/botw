#include "Game/AI/AI/aiDungeonMoveTagCont.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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

void DungeonMoveTagCont::sub_7100375380(f32 dis, f32 speed) {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(dis, "DynMoveDis", -1);
    pack.addFloat(speed, "DynMoveSpeed", -1);
    changeChild("戻る", &pack);
}

}  // namespace uking::ai

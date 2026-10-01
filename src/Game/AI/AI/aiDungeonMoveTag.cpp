#include "Game/AI/AI/aiDungeonMoveTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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

// NON_MATCHING: the original has a default case with target = -0.0f (unknown source form)
void DungeonMoveTag::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            switch (_48) {
            case 2:
                _48 = 1;
                break;
            case 3:
                _48 = 0;
                break;
            }
            changeChild("待機");
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (_49 == actor->checkBasicSig())
        return;
    _49 = actor->checkBasicSig();

    const f32 init_dis = *mInitDgnMoveDis_m;
    f32 target;
    switch (_48) {
    case 0:
    case 3:
        _48 = 2;
        target = *mMoveDis_m;
        break;
    case 1:
    case 2:
        target = 0.0f;
        _48 = 3;
        break;
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(target - init_dis, "DynMoveDis", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai

#include "Game/AI/AI/aiDungeonMoveTagCont.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DungeonMoveTagCont::DungeonMoveTagCont(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonMoveTagCont::~DungeonMoveTagCont() = default;

bool DungeonMoveTagCont::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonMoveTagCont::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0;
    changeChild("待機");
    _51 = false;
}

// NON_MATCHING: the original loads _50 with ldrsb (sign-extending) in the first and last dispatch, tests 3 before 2
// and lays the `_50 == 2` exit out of line; logic and calls are identical
void DungeonMoveTagCont::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            return;
        if (_50 == 3)
            _50 = 0;
        else if (_50 == 2)
            _50 = 1;
        changeChild("待機");
        return;
    }

    if (!child->isChangeable())
        return;
    if (_50 == 3)
        return;

    if (actor->checkGimmickSuccessSignal()) {
        _50 = 3;
        _51 = false;
        changeToGoBack(*mReturnDisFromCurrentPos_m, *mReturnSpeedFromCurrentPos_m);
        return;
    }

    if (_51 == actor->checkBasicSig())
        return;
    _51 = actor->checkBasicSig();

    if (_50 == 2) {
        _50 = 0;
        changeChild("待機");
        return;
    }
    if (_50 != 0)
        return;

    _50 = 2;
    const f32 dis = *mMoveDis_m;
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(dis + 0.0f, "DynMoveDis", -1);
    changeChild("移動", &pack);
}

void DungeonMoveTagCont::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonMoveTagCont::loadParams_() {
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mReturnDisFromCurrentPos_m, "ReturnDisFromCurrentPos");
    getMapUnitParam(&mReturnSpeedFromCurrentPos_m, "ReturnSpeedFromCurrentPos");
}

void DungeonMoveTagCont::changeToGoBack(f32 dis, f32 speed) {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(dis, "DynMoveDis", -1);
    pack.addFloat(speed, "DynMoveSpeed", -1);
    changeChild("戻る", &pack);
}

}  // namespace uking::ai

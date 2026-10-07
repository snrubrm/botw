#include "Game/Actor/actPauseMenuPlayer.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::act {

PauseMenuPlayer::PauseMenuPlayer(const CreateArg& arg) : PlayerOrEnemy(arg) {
    _c34 = false;
    _c35[0] = 1;
    _1c0 = 13;
}

// NON_MATCHING: separate stores of the inherited byte fields instead of a halfword store.
ksys::act::BaseProc* PauseMenuPlayer::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) PauseMenuPlayer(arg);
}

PauseMenuPlayer::~PauseMenuPlayer() = default;

void PauseMenuPlayer::calcMaybe() {}

void PauseMenuPlayer::finalizeInit_(InitContext* context) {
    if (_c35[0])
        mASList->x_2(66, 33, true, false);
    else
        mASList->x_2(66, 33, false, false);
    coldHotStatusEffectStuff();
    if (getLodState())
        getLodState()->mFlags10.set(2);
    Actor::finalizeInit_(context);
    _c34 = false;
    _c3c = 0;
    _c40 = 0;
    mActorFlags2.set(ActorFlag2::_200);
    _c44 = 0;
    if (getChemicalStuff())
        getChemicalStuff()->_c |= 0x1000000;
}

void PauseMenuPlayer::sub_71006E9E24() {
    _c3c = 0;
    _c40 = 0;
    _c44 = 0;
}

void PauseMenuPlayer::sub_71006EA6B8(s32 bit) {
    _c4c.setBit(bit);
}

}  // namespace uking::act

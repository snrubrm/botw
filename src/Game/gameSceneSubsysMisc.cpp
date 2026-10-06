#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys4)

void GameSceneSubsys5::init() {
    _9c = 1;
    _8c = 0.5f;
    _90 = 0.5f;
}

bool GameSceneSubsys5::sub_71009059D4() const {
    return _d8[_148];
}

void GameSceneSubsys5::sub_71009059EC(ksys::act::ActorConstDataAccess* accessor) {
    if (accessor)
        ksys::act::acquireActor(&_a8, accessor);
}

void GameSceneSubsys5::sub_7100905C70() {
    _fc[_144] = true;
}

void GameSceneSubsys5::sub_7100905D28(bool value) {
    _328 = value;
}

void GameSceneSubsys5::sub_7100905DE0(bool value) {
    _32f = value;
}


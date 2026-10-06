#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActor.h"
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

bool GameSceneSubsys5::sub_7100905B34() const {
    return _fc[_148];
}

bool GameSceneSubsys5::sub_7100905BEC() const {
    if (!_d8[_148])
        return true;
    if (!_32f)
        return true;
    return _138 > 3.5f;
}

bool GameSceneSubsys5::sub_7100905B4C(const sead::Vector3f& pos) const {
    if (!_331)
        return false;
    return (_dc[_148] - pos).length() <= _f4[_148];
}

bool GameSceneSubsys5::sub_7100905D44(ksys::act::Actor* actor) const {
    return actor->getId() == _140;
}

void GameSceneSubsys5::sub_7100905CA8(const sead::Vector3f& pos, f32 radius) {
    _dc[_144] = pos;
    _f4[_144] = radius;
}

void GameSceneSubsys5::sub_7100905C8C() {
    _fe[_144] = true;
}

void GameSceneSubsys5::sub_7100905C70() {
    _fc[_144] = true;
}

void GameSceneSubsys5::sub_7100905B1C() {
    _331 = true;
}

void GameSceneSubsys5::sub_7100905B28() {
    _331 = false;
    _58 = false;
}

bool GameSceneSubsys5::sub_7100905C30() const {
    return _32f;
}

const sead::Vector3f& GameSceneSubsys5::sub_7100905C38() const {
    return _dc[_148];
}

void GameSceneSubsys5::sub_7100905C54() {
    _d8[_144] = true;
}

void GameSceneSubsys5::sub_7100905CEC(s32* out) const {
    if (out) {
        out[0] = _124;
        out[1] = _128;
    }
}

void GameSceneSubsys5::sub_7100905D04(const s32* value) {
    _124 = value[0];
    _128 = value[1];
}

f32 GameSceneSubsys5::sub_7100905D18() const {
    return _130;
}

void GameSceneSubsys5::sub_7100905D20(f32 value) {
    _130 = value;
}

f32 GameSceneSubsys5::sub_7100905D34() const {
    return _134;
}

void GameSceneSubsys5::sub_7100905D3C(f32 value) {
    _134 = value;
}

sead::Vector3f GameSceneSubsys5::sub_7100905D58() const {
    return _100;
}

void GameSceneSubsys5::sub_7100905D68(const sead::Vector3f& value) {
    _100 = value;
}

void GameSceneSubsys5::sub_7100905D28(bool value) {
    _328 = value;
}

void GameSceneSubsys5::sub_7100905DE0(bool value) {
    _32f = value;
}


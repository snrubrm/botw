#include "KingSystem/System/ModelPicker.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(ModelPicker)

void ModelPicker::init(void* arg) {
    _20 = arg;
}

void ModelPicker::x(act::Actor* actor) {
    const s32 status = getSceneStatus();
    if (status == 2 || status == 4)
        return;
    sub_71010B9374(false);
    mTarget._10 = 0;
    mActor = actor;
    mObject = nullptr;
    mModel = nullptr;
    mState = 1;
}

void ModelPicker::x_0(map::Object* object) {
    const s32 status = getSceneStatus();
    if (status == 2 || status == 4)
        return;
    sub_71010B9374(false);
    mActor = nullptr;
    mObject = object;
    mModel = nullptr;
    mTarget._10 = 0;
    mState = 1;
}

void ModelPicker::x_1(const Target& target) {
    const s32 status = getSceneStatus();
    if (status == 2 || status == 4)
        return;
    sub_71010B9374(false);
    mActor = nullptr;
    mObject = nullptr;
    mModel = nullptr;
    mTarget.name = target.name;
    mTarget._10 = target._10;
    mTarget.mPosition = target.mPosition;
    mState = 1;
}

bool ModelPicker::Target::matches(const map::Unk_71012497f8Entry* entry) const {
    if (entry->_10 == _10 && entry->mPosition.x == mPosition.x &&
        entry->mPosition.y == mPosition.y && entry->mPosition.z == mPosition.z)
        return true;
    return false;
}

}  // namespace ksys

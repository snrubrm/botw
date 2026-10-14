#include "Game/Actor/AI/aiDungeonRotateTag3D.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/actSoundProxy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Sound/sndSound.h"

namespace uking::ai {

DungeonRotateTag3D::DungeonRotateTag3D(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag3D::~DungeonRotateTag3D() {
    if (_100) {
        delete _100;
        _100 = nullptr;
    }
}

bool DungeonRotateTag3D::init_(sead::Heap* heap) {
    _70 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_e4, "FieldBodyGroup"))
        _e4 = -1;
    _e8 = 0;
    _f0 = sead::Mathf::deg2rad(*mTiltAngularSpeed_m);
    _100 = new (heap) xlink2::HandleSLink;
    return true;
}

// NON_MATCHING: the original copies Vector3f::zero into _d8 as 8 + 4 bytes (our sead Vector3 has a memberwise
// operator=) and loads mActor for sub_71005DDE8C earlier.
void DungeonRotateTag3D::enter_(ksys::act::ai::InlineParamPack* params) {
    _68.fill(false);
    _a8 = sead::Matrix34f::ident;
    _f8 = *mTargetRad_s;
    _f4 = true;
    _f5 = false;
    sub_71005DDE8C(mActor, nullptr, *mRemainsPartType_m);
    _78 = sead::Matrix34f::ident;
    _d8 = sead::Vector3f::zero;
    _ec = 0;
    m36();
    changeChild("待機");
    _108 = 0;

    auto* manager = ksys::snd::SoundMgr::instance()->_a0;
    ksys::map::Object* proxy_object = nullptr;
    if (mActor) {
        auto* object = mActor->getMapObject();
        if (object && object->getLinkData()) {
            for (auto* linked : object->getLinkData()->mObjects) {
                if (linked && linked->getActorData().mActorName.findIndex("SoundProxy") != -1) {
                    proxy_object = linked;
                    break;
                }
            }
        }
    }
    if (auto* proxy = manager->sub_710105A830(proxy_object))
        proxy->_8b8 = true;
}

void DungeonRotateTag3D::leave_() {
    if (_100)
        xlink::fade(*_100, -1);
}

void DungeonRotateTag3D::loadParams_() {
    getStaticParam(&mTargetRad_s, "TargetRad");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

bool DungeonRotateTag3D::m34(s32* axis) {
    auto* actor = mActor;
    f32 rad;
    if (_68[0] != actor->checkAxisXSignal()) {
        *axis = 0;
        _68[*axis] = actor->checkAxisXSignal();
        rad = *mTargetRad_s;
    } else if (_68[1] != actor->checkAxisYSignal()) {
        *axis = 1;
        _68[*axis] = actor->checkAxisYSignal();
        rad = *mTargetRad_s;
    } else if (_68[2] != actor->checkAxisZSignal()) {
        *axis = 2;
        _68[*axis] = actor->checkAxisZSignal();
        rad = *mTargetRad_s;
    } else if (_68[3] != actor->checkNAxisXSignal()) {
        *axis = 3;
        _68[*axis] = actor->checkNAxisXSignal();
        rad = -*mTargetRad_s;
    } else if (_68[4] != actor->checkNAxisYSignal()) {
        *axis = 4;
        _68[*axis] = actor->checkNAxisYSignal();
        rad = -*mTargetRad_s;
    } else if (_68[5] != actor->checkNAxisZSignal()) {
        *axis = 5;
        _68[*axis] = actor->checkNAxisZSignal();
        rad = -*mTargetRad_s;
    } else {
        return false;
    }
    _f8 = rad;
    return true;
}

void DungeonRotateTag3D::m35() {
    auto* actor = mActor;
    if (_68[0] != actor->checkAxisXSignal())
        _68[0] = actor->checkAxisXSignal();
    else if (_68[1] != actor->checkAxisYSignal())
        _68[1] = actor->checkAxisYSignal();
    else if (_68[2] != actor->checkAxisZSignal())
        _68[2] = actor->checkAxisZSignal();
    else if (_68[3] != actor->checkNAxisXSignal())
        _68[3] = actor->checkNAxisXSignal();
    else if (_68[4] != actor->checkNAxisYSignal())
        _68[4] = actor->checkNAxisYSignal();
    else if (_68[5] != actor->checkNAxisZSignal())
        _68[5] = actor->checkNAxisZSignal();
}

void DungeonRotateTag3D::m36() {}

}  // namespace uking::ai

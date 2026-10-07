#include "Game/AI/AI/aiWindBoxPlace.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

WindBoxPlace::WindBoxPlace(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WindBoxPlace::~WindBoxPlace() = default;

bool WindBoxPlace::init_(sead::Heap* heap) {
    sead::Vector3f direction;
    sead::Vector3f pos;
    sead::Vector3f rot;
    sead::Vector3f size;
    sead::Matrix34f mtx;
    size = mActor->getScale() * 2;
    mActor->getHomePos(&pos);
    mActor->getHomeMtx(&mtx);
    rot.set(0, 0, 0);
    rot.y = std::atan2(mtx(0, 2), mtx(2, 2));
    pos.y += mActor->getScale().y;
    _58.sub_71010F13AC(&pos, &size, &rot, heap, nullptr);
    _58.sub_71010F1344(*mWindSpeed_m);

    switch (*mDirection_m) {
    case 0:
        direction.set(0, 0, 1);
        break;
    case 1:
        direction.set(-1, 0, 1);
        break;
    case 2:
        direction.set(-1, 0, 0);
        break;
    case 3:
        direction.set(-1, 0, -1);
        break;
    case 4:
        direction.set(0, 0, -1);
        break;
    case 5:
        direction.set(1, 0, -1);
        break;
    case 6:
        direction.set(1, 0, 0);
        break;
    case 7:
        direction.set(1, 0, 1);
        break;
    }
    _58.sub_71010F1364(&direction);
    return true;
}

void WindBoxPlace::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.sub_71010F16FC();
    mActor->m107();
}

void WindBoxPlace::calc_() {
    mActor->m107();
    if (ksys::world::Manager::instance()->getStageType() == ksys::StageType::OpenWorld)
        return;

    sead::Matrix34f offset;
    offset.makeT(0, mActor->getScale().y, 0);
    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    mtx.setMul(mtx, offset);
    _58.sub_71010F15C8(&mtx);
}

void WindBoxPlace::leave_() {
    _58.sub_71010F17FC(true);
}

void WindBoxPlace::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
}

bool WindBoxPlace::updateForPreDelete() {
    return _58.sub_71010F1314();
}

}  // namespace uking::ai

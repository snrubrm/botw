#include "Game/Actor/AI/aiKorokStoneLift.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

KorokStoneLift::KorokStoneLift(const InitArg& arg) : SimpleLiftable(arg) {}

KorokStoneLift::~KorokStoneLift() = default;

bool KorokStoneLift::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

// NON_MATCHING: scheduling of the ey / ez loads (a few instructions).
void KorokStoneLift::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
    _c8 = sead::Vector3f::zero;
    _d4 = sead::Vector3f::zero;
    _e0 = sead::Vector3f::zero;
    _ec = sead::Vector3f::zero;
    _f8 = sead::Vector3f::zero;
    _104 = sead::Vector3f::zero;
    _110 = sead::Vector3f::zero;
    _11c = sead::Vector3f::zero;
    _134 = 0.0f;
    _138 = false;
    _13c = -1.0f;
    _140 = false;
    _141 = false;
    _142 = false;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (auto* object =
            ksys::act::findLinkReferenceObj(mActor, "FldObj_KorokStone_A_01", "", nullptr)) {
        _c8 = object->getTranslate();
        sead::Matrix34f mtx;
        mtx.makeR(object->getRotate());
        _d4 = mtx * sead::Vector3f::ex;
        _e0 = mtx * sead::Vector3f::ey;
        _ec = mtx * sead::Vector3f::ez;
        _d4.normalize();
        _e0.normalize();
        _ec.normalize();
        _c8 += _e0 * 0.5f;
    }
}

void KorokStoneLift::leave_() {
    SimpleLiftable::leave_();
}

void KorokStoneLift::loadParams_() {}

}  // namespace uking::ai

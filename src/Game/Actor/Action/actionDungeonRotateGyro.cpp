#include "Game/Actor/Action/actionDungeonRotateGyro.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Framework/gameSystemStruct1.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DungeonRotateGyro::DungeonRotateGyro(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateGyro::~DungeonRotateGyro() {
    if (_108) {
        delete _108;
        _108 = nullptr;
    }
}

bool DungeonRotateGyro::init_(sead::Heap* heap) {
    _108 = new (heap) xlink2::HandleSLink;
    return true;
}

// NON_MATCHING: the original moves the player front / up components through integer registers and copies the
// transposed home rotation into _50 element by element from the stack matrix.
void DungeonRotateGyro::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = mActor->getFieldBodyGroup();
    _40 = *mInitDgnPriority_m;
    sead::Matrix34f home;
    mActor->getHomeMtx(&home);
    sead::Matrix33CalcCommon<f32>::copy(_74, home);
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.getActorMtx();
        sead::Vector3f front(mtx(0, 2), 0.0f, mtx(2, 2));
        front.normalize();
        sead::Vector3f side;
        side.setCross(sead::Vector3f::ey, front);
        side.normalize();
        _bc.setBase(0, side);
        _bc.setBase(1, sead::Vector3f::ey);
        _bc.setBase(2, front);
        _50.setTranspose(sead::Matrix33f(home));
        if (auto* system = frm::SystemStruct1::getInstance())
            _98 = system->_38;
    }
    _e0 = _74;
    _110 = {0, 0};
    _118 = {0, 0};
    _120 = {0, 0};
    _128 = 0;
}

void DungeonRotateGyro::leave_() {
    if (_108)
        xlink::fade(*_108, -1);
}

void DungeonRotateGyro::loadParams_() {
    getStaticParam(&mSlerpRatio_s, "SlerpRatio");
    getStaticParam(&mIsUseInstParamSlerpRatio_s, "IsUseInstParamSlerpRatio");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mGyroSlerpRatio_m, "GyroSlerpRatio");
}

void DungeonRotateGyro::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

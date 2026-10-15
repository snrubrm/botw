#include "Game/Actor/Action/actionDungeonMoveReset.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

DungeonMoveReset::DungeonMoveReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonMoveReset::~DungeonMoveReset() = default;

bool DungeonMoveReset::init_(sead::Heap* heap) {
    _68 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_70, "FieldBodyGroup"))
        _70 = -1;
    _60 = *mInitDgnPriority_m;
    return true;
}

// NON_MATCHING: home matrix values use stack storage rather than preserved SIMD registers.
void DungeonMoveReset::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = ksys::phys::System::instance()->getStaticCompoundMgr();
    _5c = *mDynMoveSpeed_d;
    const sead::Matrix34f home = mActor->getHomeMtxRaw();
    if (manager) {
        sead::Matrix34f transformed;
        transformed.setMul(manager->getExtraTransform(_68, _60), home);
        transformed.getTranslation(_40);
    }
    const f32 distance = (_40 - home.getTranslation()).length();
    _4c = _40 - home.getBase(1) * (distance > *mDynMoveDis_d ? *mDynMoveDis_d : distance);
    _74 = false;
    _58 = 0.0f;
    mFlags.set(Flag::Changeable);
}

void DungeonMoveReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonMoveReset::loadParams_() {
    getStaticParam(&mAccel_s, "Accel");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getDynamicParam(&mDynMoveSpeed_d, "DynMoveSpeed");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
}

// NON_MATCHING: vector chase and transform composition scheduling and register allocation.
void DungeonMoveReset::calc_() {
    auto* actor = mActor;
    const f32 acceleration = *mAccel_s;
    ksys::VFR::chase(&_58, _5c, acceleration);
    const bool finished = ksys::VFR::chaseVec(&_40, _4c, _58);
    if (_68 && !_74) {
        const sead::Vector3f home_position = actor->getHomeMtxRaw().getTranslation();
        sead::Matrix34f rotation;
        rotation.makeR(sead::Vector3f::zero);
        sead::Matrix34f inverse_home;
        inverse_home.makeT(-home_position);
        sead::Matrix34f transform;
        transform.setMul(rotation, inverse_home);
        sead::Matrix34f translation;
        translation.makeT(_40);
        transform.setMul(translation, transform);
        if (auto* manager = ksys::phys::System::instance()->getStaticCompoundMgr())
            manager->setExtraTransform(_68, transform, _60);
        if (auto* manager = ksys::phys::HavokAI::instance()->_48) {
            if (_70 >= 0)
                manager->sub_7100F8AA78(_70, transform);
        }
        if (!_74 && finished)
            setFinished();
    }
    _74 = finished;
}

}  // namespace uking::action

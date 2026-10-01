#include "Game/AI/AI/aiDominoRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DominoRoot::DominoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DominoRoot::~DominoRoot() = default;

bool DominoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DominoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        sead::BoundBox3f box;
        body->getAabbInLocal(&box);
        _78 = box.getHalfSizeY() * 2;
        body->setFrictionScale(*mFriction_s);
    }
    _78 *= *mCheckHeightRate_s;
    _80 = false;
    changeChild("待機");
}

void DominoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DominoRoot::loadParams_() {
    getStaticParam(&mPointVelTh_s, "PointVelTh");
    getStaticParam(&mLinearRate_s, "LinearRate");
    getStaticParam(&mAngRate_s, "AngRate");
    getStaticParam(&mCheckHeightRate_s, "CheckHeightRate");
    getStaticParam(&mFriction_s, "Friction");
    getStaticParam(&mIsIgnoreWater_s, "IsIgnoreWater");
    getMapUnitParam(&mIsBreakable_m, "IsBreakable");
    getMapUnitParam(&mEnableToEmitSpEffect_m, "EnableToEmitSpEffect");
}

}  // namespace uking::ai

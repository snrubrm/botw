#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCapsule.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCylinder.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyPolytope.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::act {

AreaActor::AreaActor(const CreateArg& arg) : Actor(arg) {}

AreaActor::PreDeletePrepareResult AreaActor::prepareForPreDelete_() {
    if (_840) {
        _840->removeFromWorldAndResetLinks();
        if (_840->isAddedToWorld())
            return PreDeletePrepareResult::NotDone;
    }
    if (auto* body = getColBody()) {
        body->setCollisionInfo(nullptr);
        body->setContactPointInfo(nullptr);
    }
    return Actor::prepareForPreDelete_();
}

bool AreaActor::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    _848 = phys::CollisionInfo::make(heap, sead::SafeString::cEmptyString);
    _850 = phys::ContactPointInfo::make(heap, 0x80, sead::SafeString::cEmptyString, 0, 0, 0);
    _850->set30(1);
    m151();
    initPhysics(heap);
    return true;
}

void AreaActor::preDelete2_(const PreDeleteArg& arg) {
    _878 = nullptr;
    if (_840) {
        if (_840->isAddedToWorld())
            _840->removeFromWorldImmediatelyAndResetLinks();
        if (_840) {
            delete _840;
            _840 = nullptr;
        }
    }
    if (_848) {
        phys::CollisionInfo::free(_848);
        _848 = nullptr;
    }
    if (_850) {
        phys::ContactPointInfo::free(_850);
        _850 = nullptr;
    }
}

void AreaActor::sub_7100E25D84() {
    if (_888 == 4) {
        _889 = 0;
    } else {
        {
            ActorLinkConstDataAccess accessor;
            sub_7100EE3A88(&accessor, this);
            _889 = accessor.hasProc() ? 1 : getFieldBodyGroupId() == -1 ? 3 : 2;
        }
        if (_889 == 3)
            bindCalc1ToJob1_2();
    }

    if (_888 == 4) {
        if (auto* body = getColBody()) {
            mMtx = body->getTransform();
            nullsub_4648();
        }
    } else {
        sead::Matrix34f mtx;
        getHomeMtx(&mtx);
        mMtx = mtx;
        nullsub_4648();
        if (_840 && !_840->isAddedToWorld())
            _840->setTransform(mMtx);
    }
}

// NON_MATCHING: stack slots (the original puts the overlay colour above the matrix / colour slot) and the
// _88d test (tbz bit 0, ours cbz).
void AreaActor::calcMaybe() {
    if (!mSpecialJobTypesMaskOverride.isOnBit(0))
        m148();

    if (auto* body = getColBody()) {
        if (_88a != 1) {
            m149(body);
            m150();
            _88a = 1;
        }
        if (!body->isAddedToWorld())
            body->addToWorld();
    }

    if (_840) {
        if (!_840->isSensor()) {
            sead::Matrix34f mtx;
            sub_7100E26084(&mtx);
            _840->changePositionAndRotation(mtx);
        }
        if (_840 && _840->isSensor() && _889 == 3)
            _840->changePositionAndRotation(mMtx);
    }

    auto* body = getColBody();
    if (body && _88d) {
        sead::Color4f color = sead::Color4f::cRed;
        sead::Color4f overlay(0, 0, 0, 0.1f);
        body->setColor(color, &overlay, true);
    }
}

void AreaActor::updatePositionMaybe() {
    sead::Matrix34f mtx;
    sub_7100E26084(&mtx);
    mMtx = mtx;
    nullsub_4648();
    if (_840 && _840->isSensor())
        _840->changePositionAndRotation(mMtx);
}

// Discarded call: the original calls the base shouldInit_ and drops its result.
bool AreaActor::shouldInit_() {
    Actor::shouldInit_();
    getJobHandler(JobType::Calc2) = nullptr;
    _888 = getShape();
    _868 = mScale;
    return true;
}

void AreaActor::m149(phys::RigidBody* body) {
    body->setCollisionInfo(_848);
    body->setContactPointInfo(_850);
    body->updateCollidableQualityType(true);
}

void AreaActor::m150() {
    phys::MaterialMask mask(0u);
    if (!(_878 == nullptr))
        (this->*_878)(&mask);
}

phys::ContactLayer AreaActor::m152() {
    return phys::ContactLayer(phys::ContactLayer::size());
}

void AreaActor::sub_7100E26784(phys::MaterialMask* mask) {
    if (!(_878 == nullptr))
        (this->*_878)(mask);
}

void AreaActor::sub_7100E267C8(phys::MaterialMask* mask) {
    if (auto* body = sead::DynamicCast<phys::SphereRigidBody>(_840))
        body->setMaterialMask(*mask);
}

void AreaActor::sub_7100E26860(phys::MaterialMask* mask) {
    if (auto* body = sead::DynamicCast<phys::CapsuleRigidBody>(_840))
        body->setMaterialMask(*mask);
}

void AreaActor::sub_7100E268F8(phys::MaterialMask* mask) {
    if (auto* body = sead::DynamicCast<phys::CylinderRigidBody>(_840))
        body->setMaterialMask(*mask);
}

void AreaActor::sub_7100E26990(phys::MaterialMask* mask) {
    if (auto* body = sead::DynamicCast<phys::PolytopeRigidBody>(_840))
        body->setMaterialMask(*mask);
}

u8 AreaActor::getShape() {
    static const char* sShapeNames[] = {"Sphere", "Box", "Capsule", "Cylinder", "Hull"};
    sead::SafeString shape;
    if (!mRootAi || !mRootAi->getMapUnitParam(&shape, "Shape"))
        shape = "Sphere";
    for (int i = 0; i < 5; ++i) {
        if (shape == sShapeNames[i])
            return i;
    }
    return 0;
}

void AreaActor::sub_7100E2677C() {
    _88a = 0;
}

bool AreaActor::sub_7100E26A80() {
    auto* body = getColBody();
    return body && !body->hasFlag(phys::RigidBody::Flag::NoCharStandingOn);
}

void AreaActor::sub_7100E26A28(bool enable) {
    if (auto* body = getColBody())
        body->changeNoCharStandingOnFlag(!enable);
}

}  // namespace ksys::act

namespace ksys::act::acc {

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline ksys::act::AreaActor* AreaActor::getAreaActor() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<ksys::act::AreaActor>(actor);
}

phys::CollisionInfo* AreaActor::getField848() const {
    auto* area = getAreaActor();
    return area ? area->_848 : nullptr;
}

phys::ContactPointInfo* AreaActor::getField850() const {
    auto* area = getAreaActor();
    return area ? area->_850 : nullptr;
}

bool AreaActor::sub_7100E26EEC() const {
    auto* mgr = BaseProcMgr::instance();
    if (!mgr || mgr->getStatus() != BaseProcMgr::Status::ProcessingActorJobs)
        return false;
    auto* area = getAreaActor();
    return area ? area->_88c != 0 : false;
}

}  // namespace ksys::act::acc

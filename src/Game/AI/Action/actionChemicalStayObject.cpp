#include "Game/AI/Action/actionChemicalStayObject.h"
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ChemicalStayObject::ChemicalStayObject(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChemicalStayObject::~ChemicalStayObject() {
    if (_1a8.isBufferReady()) {
        for (s32 i = 0; i < _1a8.size(); ++i) {
            if (_1a8[i].hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_1a8[i], &accessor);
                if (!accessor.isDeletedOrDeleting())
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
        _1a8.freeBuffer();
    }
}

bool ChemicalStayObject::init_(sead::Heap* heap) {
    if (*mCreateLimit_m > 1) {
        _bc = *mCreateLimit_m - 1;
        _1a8.tryAllocBuffer(_bc, heap);
        if (!sub_71005D6D10()) {
            ksys::act::InstParamPack params;
            params->add(*mAttackPower_m, "AttackPower");
            params->add(*mScaleTime_m, "ScaleTime");
            params->add(*mAtMinDamage_m, "AtMinDamage");
            params->add(1, "CreateLimit");
            for (s32 i = 0; i < _bc; ++i) {
                auto* creator = ksys::act::ActorCreator::instance();
                const auto& name = mActor->getName();
                name.cstr();
                auto* proc = creator->createActor(name.getStringTop(),
                    ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params, true, false);
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                    _1a8[i].acquire(actor, false);
            }
        }
    }
    return true;
}

// NON_MATCHING: one negative-epsilon branch uses mi instead of lt.
void ChemicalStayObject::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _a4 = actor->getScale().x;
    if (*mScaleTime_m > 1.0f) {
        _a0 = actor->getScale().x / *mScaleTime_m;
        actor->setScale(sead::Vector3f::ones * _a0);
    } else {
        _a0 = 0.0f;
    }

    u32 attributes = (1u << *mAtAttr_s) | 0x18;
    u32 attack_type = !*mIsChemicalAttack_s ? 0x10 : 0x800;
    if (auto* chemical = actor->getChemicalStuff()) {
        chemical->sub_7100D8EEE0();
        chemical->sub_7100D90C2C(false);
        chemical->sub_7100D91098(true);
        if ((chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1))
            chemical->sub_7100D90858(false, 2, false, true, false);
        if (*mAtAttr_s == 0) {
            if (chemical->_c0 == 2) {
                attributes = 0x218;
            } else {
                const u32 material_attributes = chemical->mMaterial->attribute.ref();
                if (material_attributes & 0x8000)
                    attributes = 0x418;
                else if (((material_attributes & 0x108) == 0x108 && !(chemical->_be & 4)) ||
                         chemical->_1b8 > 0.0f)
                    attributes = 0x818;
            }
        }
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        body->setTransform(actor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
        sub_71007A2B64(body, nullptr);
        sub_71007A2EB0(body, actor, nullptr);
        getActorAttackSensor(actor)->activateAttackSensor(attack_type, attributes, *mAttackPower_m,
            0, 0.0f, 0, 1, -1, false, *mAtMinDamage_m, -1);
    }
    _a8 = false;
    _d0.reset(*mDeleteTime_s);
    const f32 angle = sead::GlobalRandom::instance()->getF32() * sead::Mathf::piHalf();
    const f32 rate = sead::GlobalRandom::instance()->getF32() * 0.55f + 0.95f;
    _dc = ksys::Timer(angle, angle, rate * (sead::Mathf::pi() / 40.0f));
    if (*mIsBindToGeneratedActor_s)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    const f32 reduce_range = *mReduceVelRandomRange_s;
    const f32 reduce_rate = *mReduceVelRate_s;
    _ac = sead::Mathf::clamp(reduce_rate +
        ((reduce_range + reduce_range) * sead::GlobalRandom::instance()->getF32() - reduce_range),
        0.1f, 0.99f);
    const f32 curve_angle = *mCurveAng_s;
    if (!(curve_angle <= sead::Mathf::epsilon()) || curve_angle < -sead::Mathf::epsilon()) {
        const f32 curve_range = *mCurveAngRandomRange_s;
        _b0 = curve_angle +
            ((curve_range + curve_range) * sead::GlobalRandom::instance()->getF32() - curve_range);
    } else {
        _b0 = 0.0f;
    }
    _b8 = 0;
    _c0 = true;
    mActor->getMtx().getTranslation(_c4);
    _e8.reset(5.0f);
}

void ChemicalStayObject::leave_() {
    if (*mIsBindToGeneratedActor_s)
        mActor->sub_71011DA834(&_f8);

    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()))
        mActor->resetConnectedCalcParent(false);
}

void ChemicalStayObject::loadParams_() {
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mCurveAng_s, "CurveAng");
    getStaticParam(&mReduceVelRate_s, "ReduceVelRate");
    getStaticParam(&mCurveAngRandomRange_s, "CurveAngRandomRange");
    getStaticParam(&mReduceVelRandomRange_s, "ReduceVelRandomRange");
    getStaticParam(&mSideAmplitude_s, "SideAmplitude");
    getStaticParam(&mIsBindToGeneratedActor_s, "IsBindToGeneratedActor");
    getStaticParam(&mIsChemicalAttack_s, "IsChemicalAttack");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mBindOffset_s, "BindOffset");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mCreateLimit_m, "CreateLimit");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
}

void ChemicalStayObject::sub_71000DD774() {
    if (_bc <= _b8)
        return;

    _e8.update();
    if (!(_e8.value <= sead::Mathf::epsilon()))
        return;

    _e8 = ksys::Timer(20.0f, 20.0f);
    const sead::Vector3f pos = {mActor->getMtx()(0, 3), mActor->getMtx()(1, 3), mActor->getMtx()(2, 3)};
    if (_c0) {
        _c0 = false;
        _c4 = pos;
        return;
    }

    sead::Matrix34f mtx = mActor->getMtx();
    mtx.setTranslation(_c4);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_1a8[_b8], &accessor);
    accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
    _c4 = pos;
    ++_b8;
}

// NON_MATCHING: register allocation and side-wave scheduling differ; the original repeats the
// binding guard before acquiring its parent link.
void ChemicalStayObject::calc_() {
    if (!*mIsBindToGeneratedActor_s) {
        if (auto* body = mActor->getMainBody()) {
            sead::Vector3f velocity = body->getLinearVelocity();
            const f32 speed = velocity.normalize() * _ac;
            if (!(_b0 <= sead::Mathf::epsilon()) || _b0 < -sead::Mathf::epsilon()) {
                sead::Quatf rotation;
                rotation.setAxisRadian(sead::Vector3f::ey, _b0);
                sead::Matrix33f matrix;
                matrix.fromQuat(rotation);
                velocity.rotate(matrix);
            }
            velocity *= speed;
            if (!(*mSideAmplitude_s <= sead::Mathf::epsilon()) ||
                *mSideAmplitude_s < -sead::Mathf::epsilon()) {
                sead::Vector3f forward;
                mActor->getMtx().getBase(forward, 2);
                forward.normalize();
                sead::Vector3f side;
                side.setCross(forward, sead::Vector3f::ey);
                side.normalize();
                const f32 amount = sead::Mathf::sin(_dc.value);
                _dc.update();
                velocity += side * amount * *mSideAmplitude_s;
            }
            body->setLinearVelocity(velocity, sead::Mathf::epsilon());
        }
    } else if (!_a8) {
        if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
            if (!_198.hasProc())
                _198.acquire(parent, false);
            mActor->resetConnectedCalcParent(false);
        }
        if (_198.hasProc()) {
            _f8.x(_198);
            if (!mBindNodeName_s.isEmpty()) {
                _f8._28 = mBindNodeName_s.cstr();
                _f8._30.getKey().reset();
            }
            _f8._68 = sead::Matrix34f(sead::Matrix33f::ident, *mBindOffset_s);
            mActor->sub_71011DA824(&_f8);
            _a8 = true;
        }
    } else if (!_198.hasProc()) {
        setFinished();
    }
    sub_71000DD774();
    auto* actor = mActor;
    const f32 scale = actor->getScale().x + _a0 <= _a4 ? actor->getScale().x + _a0 : _a4;
    actor->setScale(sead::Vector3f::ones * scale);
    if (!(*mDeleteTime_s <= 0.0f)) {
        _d0.update();
        if (_d0.value <= sead::Mathf::epsilon()) {
            sub_71007A2D7C(mActor, "AtkBody");
            sub_71007A2D7C(mActor, "AtkChemical");
            if (auto* chemical = actor->getChemicalStuff()) {
                chemical->sub_7100D91098(false);
                if ((chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1))
                    chemical->sub_7100D90C2C(true);
            }
            setFinished();
        }
    }
}

}  // namespace uking::action

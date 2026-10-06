#include "Game/AI/Action/actionPlayASForDemo.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayASForDemo::PlayASForDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayASForDemo::~PlayASForDemo() = default;

bool PlayASForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// 0x7100e9cf30 (declared only): calls vtable slot 4 of `obj` (the object returned by Actor::m119()).
void sub_7100E9CF30(void* obj);

// NON_MATCHING: the original calls the out-of-line `sead::Buffer<ASList::Unk1>::size()` (0x7101 15f0b4) and keeps the bounds
// check (csel) of the following `mSlots(_a4)`; here size() is inlined and the check folds away.
void PlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FB9D24();
    actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    _70 = false;
    _71 = false;
    if (actor->get7d0())
        _70 = true;
    sub_710021AF3C();
    int anime_driven = *mIsEnabledAnimeDriven_d;
    if (anime_driven == -1)
        anime_driven = *mAnimeDrivenSettings_s;
    if (anime_driven == 1) {
        if (auto* list = mActor->getASList())
            list->sub_710115CE44("Root");
    }
    m36();
    if (s32(_a4) < as_list->mSlots.size())
        _a8 = as_list->mSlots(_a4).sub_71011653C4();
    else
        _a8 = false;
    anime_driven = *mIsEnabledAnimeDriven_d;
    if (anime_driven == -1)
        anime_driven = *mAnimeDrivenSettings_s;
    if (anime_driven == 1 && _70 && _a8) {
        auto* actor2 = mActor;
        if (auto* physics = actor2->getPhysics())
            physics->sub_7100FBA0F4();
        actor2->sub_71011DAC3C(ksys::phys::MotionType::Keyframed, true);
        actor2->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10);
    }
    if (auto* physics = mActor->getPhysics()) {
        physics->clothVisibleStuff();
        physics->clothVisibleStuff_0(*mClothWarpMode_d);
        physics->setInDemo();
    }
    if (auto* obj = actor->m119())
        sub_7100E9CF30(obj);
}

void PlayASForDemo::leave_() {
    auto* actor = mActor;
    if (*mTargetIndex_d == -1) {
        if (auto* as_list = actor->getASList()) {
            if (as_list->_163 & 2) {
                as_list->sub_710115C11C();
                as_list->sub_710115C278(_a4);
            }
        }
    }
    if (auto* physics = mActor->getPhysics())
        physics->resetInDemo();
    int anime_driven = *mIsEnabledAnimeDriven_d;
    if (anime_driven == -1)
        anime_driven = *mAnimeDrivenSettings_s;
    if (anime_driven == 1) {
        if (auto* as_list = mActor->getASList())
            as_list->sub_710115D0AC();
        if (_70 && _a8) {
            auto* actor2 = mActor;
            if (auto* physics = actor2->getPhysics())
                physics->sub_7100FBA174();
            if (auto* controller = actor2->getCharacterController())
                controller->sub_7100F60604();
            actor2->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10);
        }
    }
    if (_71)
        mCCAccessor.resetMotionType(mCCAccessor.sub_710072ACF8(actor));
}

void PlayASForDemo::loadParams_() {
    getStaticParam(&mAnimeDrivenSettings_s, "AnimeDrivenSettings");
    getDynamicParam(&mTargetIndex_d, "TargetIndex");
    getDynamicParam(&mSeqBank_d, "SeqBank");
    getDynamicParam(&mIsEnabledAnimeDriven_d, "IsEnabledAnimeDriven");
    getDynamicParam(&mClothWarpMode_d, "ClothWarpMode");
    getDynamicParam(&mMorphingFrame_d, "MorphingFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mASName_d, "ASName");
}

// NON_MATCHING: register allocation only (a `const bool has_object = _70;` local before the anime-driven load makes it match;
// a once-used local, not applied).
void PlayASForDemo::calc_() {
    int anime_driven = *mIsEnabledAnimeDriven_d;
    if (anime_driven == -1)
        anime_driven = *mAnimeDrivenSettings_s;
    if (anime_driven != 1) {
        sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, 0.0f);
    }
    if (isFailed())
        return;
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    if (m33()) {
        const f32 value = m32();
        if (value >= 0.0f)
            as_list->sub_710115F5C0(value, _a4, 0);
    }
    anime_driven = *mIsEnabledAnimeDriven_d;
    if (anime_driven == -1)
        anime_driven = *mAnimeDrivenSettings_s;
    if (_70) {
        if (anime_driven == 1)
            sub_710021B2F0();
    } else if (anime_driven == 1) {
        if (as_list->sub_710115FBC8(13, nullptr, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            if (!_71) {
                _71 = true;
                mCCAccessor.sub_710072AD1C(mCCAccessor.sub_710072ACF8(actor));
            }
            sub_71006F5584(actor);
        } else if (sub_71006F566C(actor)) {
            _71 = false;
            mCCAccessor.resetMotionType(mCCAccessor.sub_710072ACF8(actor));
        }
        sub_710021B474();
    }
    if (isFinishedAS(_a4, *mTargetIndex_d == -1 ? 0 : *mSeqBank_d))
        setFinished();
}

bool PlayASForDemo::m33() {
    return false;
}

float PlayASForDemo::m32() {
    if (auto* as_list = mActor->getASList())
        return as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
    return 0.0f;
}

const sead::SafeString& PlayASForDemo::m34() {
    auto* as_list = mActor->getASList();
    if (!as_list || mASName_d.isEmpty())
        return sead::SafeString::cEmptyString;
    as_list->sub_710115AA68(mASName_d);
    return mASName_d;
}

// NON_MATCHING: the original loads m02 / m22 together with the translation (`ldp s8, s0, [x8, #8]`) before the actor name
// compare and builds only the translation lanes; the translate matrix (makeT) here materialises the identity part.
void PlayASForDemo::sub_710021B2F0() {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list || !_70 || !actor->get7d0())
        return;
    sead::Matrix34f delta;
    as_list->sub_710115D4A4(m32(), &delta, true);
    sead::Matrix34f mtx;
    mtx.setMul(_74, delta);
    auto* controller = actor->getCharacterController();
    auto* body = actor->getMainBody();
    if (controller) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (body) {
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    } else {
        actor->sub_71011C88C0(mtx);
        return;
    }
    actor->setMtx(mtx, true, false);
    actor->nullsub_4648();
}

void PlayASForDemo::sub_710021AF3C() {
    sead::Matrix34f result;
    result.makeZero();
    if (_70) {
        if (const auto* mtx = static_cast<const sead::Matrix34f*>(mActor->get7d0())) {
            sead::Matrix34f trans;
            trans.makeT(mtx->getTranslation());
            const f32 yaw = sead::Mathf::atan2(mtx->m[0][2], mtx->m[2][2]);
            if (!(mActor->getName() == "TwnObj_HyruleCastleAncientPole_Past_A_01" && !mActor->getMapObject())) {
                sead::Matrix34f rot;
                rot.makeR(sead::Vector3f(0, yaw, 0));
                result.setMul(trans, rot);
            }
        }
    }
    _74 = result;
}

// The seq bank is only used with an explicit target index.
int PlayASForDemo::sub_710021BA28() {
    return *mTargetIndex_d == -1 ? 0 : *mSeqBank_d;
}

int PlayASForDemo::sub_710021BDC4() {
    return *mTargetIndex_d == -1 ? 0 : *mTargetIndex_d;
}

f32 PlayASForDemo::sub_710021BDD8() {
    if (*mTargetIndex_d == -1 && *mMorphingFrame_d >= 0.0f)
        return *mMorphingFrame_d;
    return -1.0f;
}

void PlayASForDemo::m36() {
    if (*mTargetIndex_d == -1) {
        if (auto* as_list = mActor->getASList())
            _a4 = as_list->sub_710115BC28(m34(), sub_710021BDD8());
    } else {
        playAS(m34().cstr(), *mIsIgnoreSame_d, sub_710021BDC4(), sub_710021BA28(), -1.0f);
        _a4 = sub_710021BDC4();
    }
}

}  // namespace uking::action

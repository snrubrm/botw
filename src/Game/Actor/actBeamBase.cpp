#include "Game/Actor/actBeamBase.h"
#include <aal/aalShape.h>
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBeam.h"

namespace uking::act {

BeamBase::BeamBase(const CreateArg& arg) : DynamicActor(arg) {
    _b90._40.reset();
    _be0.getKey().reset();
}

// NON_MATCHING: the original computes &_b90 and &_b90._40 into callee-saved registers before the inlined
// ~BoneAccessKeyEx call; we recompute them after it
BeamBase::~BeamBase() = default;

void BeamBase::initMaybe() {
    DynamicActor::initMaybe();
    sub_71000029CC();
    if (auto* physics = getPhysics()) {
        if (_c28.hasProc()) {
            physics->sub_7100FBDFA4(sub_7100738C18(&_c28, 0));
            physics->sub_7100FBDFA4(sub_7100738C18(&_c28, 1));
        } else {
            physics->sub_7100FBDFA4(nullptr);
        }
    }
}

void BeamBase::preDelete2_(const PreDeleteArg& arg) {
    DynamicActor::preDelete2_(arg);
    if (_c78) {
        _c78->destroy();
        _c78 = nullptr;
    }
    m158();
}

void BeamBase::updateMtxFromPhysics() {
    m163();
    ksys::act::Actor::updateMtxFromPhysics();
}

void BeamBase::sub_7100002DA8(ksys::act::Actor* actor) {
    auto* physics = getPhysics();
    auto* other_physics = actor->getPhysics();
    if (physics && other_physics) {
        physics->sub_7100FBDFA4(other_physics->get188(0));
        physics->sub_7100FBDFA4(other_physics->get188(1));
    }
    _c28.acquire(actor, false);
}

void BeamBase::sub_7100002F78() {
    sead::Matrix34f pose;
    if (sub_7100003494(&pose))
        pose.getTranslation(_c68);
}

// NON_MATCHING: the pose, position and target snapshot use separate stack storage.
void BeamBase::m163() {
    sead::Matrix34f pose;
    if (sub_7100003494(&pose))
        pose.getTranslation(_c68);
    sead::Vector3f position;
    m165(&position);
    reflectMaybe(position, sead::Vector3f(_c68));
}

void BeamBase::sub_7100003804(ksys::act::Actor* shooter, const sead::SafeString& bone) {
    auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(shooter, false);
    if (auto* model = shooter->getModel())
        _be0.search(model, bone);
}

void BeamBase::sub_710000395C(ksys::act::Actor* shooter, const sead::SafeString& bone,
                               const sead::Vector3f* offset) {
    auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(shooter, false);
    if (auto* model = shooter->getModel())
        _be0.search(model, bone);
    _c18 = *offset;
}

void BeamBase::m165(sead::Vector3f* out) {
    mMtx.getTranslation(*out);
}

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor).
static ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

static inline BeamBase* getBeamBase(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(accessor.getProc()));
    return sead::DynamicCast<BeamBase>(actor);
}

void sub_71000039E0(const ksys::act::ActorConstDataAccess& accessor, ksys::act::Actor* shooter,
                    const sead::SafeString& bone) {
    if (auto* beam = getBeamBase(accessor))
        beam->sub_7100003804(shooter, bone);
}

void sub_7100003B1C(const ksys::act::ActorConstDataAccess& accessor, f32 value) {
    if (auto* beam = getBeamBase(accessor)) {
        auto lock = sead::makeScopedLock(beam->_b90._0);
        beam->_c24 = value;
    }
}

void sub_7100003C34(const ksys::act::ActorConstDataAccess& accessor) {
    if (auto* beam = getBeamBase(accessor))
        beam->_c84.setBitOn(0);
}

s32 sub_7100003D30(const ksys::act::ActorConstDataAccess& accessor) {
    auto* beam = getBeamBase(accessor);
    return beam ? beam->getParam()->getRes().mGParamList->getBeam()->mBeamLevel.ref() : 0x1ff;
}

}  // namespace uking::act

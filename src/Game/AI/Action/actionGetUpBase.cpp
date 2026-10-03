#include "Game/AI/Action/actionGetUpBase.h"
#include <cmath>
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GetUpBase::GetUpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetUpBase::~GetUpBase() = default;

bool GetUpBase::init_(sead::Heap* heap) {
    _138.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_138);
    return true;
}

// NON_MATCHING: the original evaluates the three `x != 0` tests without branches (cset/orr) before the
// `scale > 0` branch and stores the scaled offset with three separate stores
void GetUpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    controller->sub_7100F5E7F0(0.0f);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        auto* handler = actor->_868;
        if (handler && handler->sub_71006ED9EC()) {
            actor->sub_71006DD92C(true);
            const f32 scale = handler->_b8;
            _84 = *mRootOffset_s;
            const f32 x = _84.x;
            const f32 y = _84.y;
            const f32 z = _84.z;
            if (scale > 0.0f && (x != 0.0f || y != 0.0f || z != 0.0f)) {
                const f32 inv_scale = 1.0f / scale;
                _84.x = inv_scale * x;
                _84.y = inv_scale * y;
                _84.z = inv_scale * z;
                _90.setName("Skl_Root");
                _90._68 = sead::Matrix34f::ident;
                actor->boneHandleStuff(&_90, false);
            }
        }
        const auto& mtx = actor->getMtx();
        const f32 angle = sead::Mathf::rad2deg(
            std::atan2(mtx(1, 2), std::sqrt(mtx(0, 2) * mtx(0, 2) + mtx(2, 2) * mtx(2, 2))));
        mActor->getASList()->x_6(9, 0, angle);
    }
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_138._0)) {
        unit->_8.sub_attach(mActor);
    }
    sub_7100741034(&_44, mActor);
    _80 = false;
    _74.value = 0;
    _74.prev_value = 0;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _40 = -1.0f;
    _20 = 0;
}

void GetUpBase::leave_() {
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_138._0))
        unit->_8.sub_detach(mActor);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_138._0))
        unit->_8.mHandle._68 = sead::Matrix34f::ident;
    if (_90._8)
        mActor->sub_71011DA868(&_90);
}

void GetUpBase::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mRootOffset_s, "RootOffset");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void GetUpBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GetUpBase::isChangeable() const {
    return false;
}

bool GetUpBase::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action

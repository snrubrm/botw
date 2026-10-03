#include "Game/AI/Action/actionRagdollFreeze.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_7102384718.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

RagdollFreeze::RagdollFreeze(const InitArg& arg) : Freeze(arg) {}

RagdollFreeze::~RagdollFreeze() = default;

bool RagdollFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void RagdollFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
    if (auto* handle = sub_7100225CA0()) {
        const auto& mtx = mActor->getMtx();
        const f32 pitch = sead::Mathf::rad2deg(
            std::atan2(mtx(1, 2), sead::Mathf::sqrt(mtx(0, 2) * mtx(0, 2) + mtx(2, 2) * mtx(2, 2))));
        sead::Matrix34f offset_mtx = sead::Matrix34f::ident;
        offset_mtx.setTranslation(
            *(pitch > -180.0f && pitch < 0 ? mDownBackCtrlOffset_s : mDownFrontCtrlOffset_s));
        handle->mHandle._68 = offset_mtx;
    }
}

Unk_7102384718Handle* RagdollFreeze::sub_7100225CA0() {
    if (_68._0) {
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_68._0)) {
            if (unit->mRefCount >= 1) {
                if (auto* unit2 = sead::DynamicCast<Unk_7102384718>(*_68._0))
                    return &unit2->_8;
            }
        }
    }
    return nullptr;
}

void RagdollFreeze::leave_() {
    Freeze::leave_();
}

void RagdollFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
}

void RagdollFreeze::calc_() {
    Freeze::calc_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor || !actor->m151(3))
        setFinished();
}

}  // namespace uking::action

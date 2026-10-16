#include "Game/Actor/Action/actionWizzrobeSummon.h"
#include <algorithm>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

WizzrobeSummon::WizzrobeSummon(const InitArg& arg) : TurnIgnite(arg) {}

// NON_MATCHING: the original inlines TurnIgnite's destructor (vtable stores + ParamPack dtor) into D1; with
// `~TurnIgnite() = default` in its header the vtable D1 slot of TurnIgnite folds into OnetimeStopASPlay's D2.
WizzrobeSummon::~WizzrobeSummon() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<64> name;
        for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
            name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
            enemy->sub_7100D3CFEC(name);
        }
    }
}

bool WizzrobeSummon::init_(sead::Heap* heap) {
    if (!TurnIgnite::init_(heap))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    sead::FixedSafeString<64> name;
    for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
        name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
        if (!enemy->sub_7100D3CED8(name, heap))
            return false;
    }
    return true;
}

void WizzrobeSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnIgnite::enter_(params);
}

void WizzrobeSummon::leave_() {
    TurnIgnite::leave_();
}

void WizzrobeSummon::loadParams_() {
    TurnIgnite::loadParams_();
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mWeaponIndex_s, "WeaponIndex");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
}

void WizzrobeSummon::m32(ksys::act::BaseProcHandle* handle) {
    if (handle) {
        auto* proc = handle->getProc();
        if (auto* summoned = sead::DynamicCast<ksys::act::Actor>(proc)) {
            auto* actor = mActor;
            sub_7100738C88(summoned, actor);
            sub_7100738D28(summoned, actor);
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                sead::FixedSafeString<64> name;
                for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
                    name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
                    if (!enemy->getActorPartsActor(name).hasProc() &&
                        enemy->sub_7100D3D108(name, proc))
                        break;
                }
            }
        }
        *mSummonCount_a += 1;
    }
    StopASIgnite::m32(handle);
}

const sead::Matrix34f& WizzrobeSummon::m33() {
    sub_71002BEDDC();
    return _f8;
}

void WizzrobeSummon::calc_() {
    TurnIgnite::calc_();
}

// NON_MATCHING: operand order of two squared-length additions and one store of the hit offset.
void WizzrobeSummon::sub_71002BEDDC() {
    auto* actor = mActor;
    _f8 = actor->getMtx();
    auto* weapon = sub_71005D83E8(actor, *mWeaponIndex_s);
    if (!weapon)
        return;

    sead::Vector3f pos;
    weapon->sub_71002E5DDC(&pos);
    pos.setMul(weapon->getMtx(), pos);
    if (auto* controller = actor->getCharacterController()) {
        sead::Matrix34f mtx;
        sead::Vector3f center;
        controller->sub_7100F62E6C(&center);
        controller->physicsXXXGetMtx_1(&mtx);
        center.setMul(mtx, center);
        center.y = pos.y;
        sead::Vector3f end = pos - center;
        end.normalize();
        end = end * 0.6f + pos;
        sead::Vector3f hit_pos;
        if (sub_710072E928(center, end, &hit_pos, nullptr, nullptr, 0.0f)) {
            hit_pos -= center;
            const f32 distance = std::max(hit_pos.normalize() + -0.6f, 0.0f);
            pos = hit_pos * distance + center;
        }
    }
    _f8.setTranslation(pos);
}

}  // namespace uking::action

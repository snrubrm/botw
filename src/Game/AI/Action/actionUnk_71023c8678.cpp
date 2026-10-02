#include "Game/AI/Action/actionUnk_71023c8678.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

Unk_71023c8678::Unk_71023c8678(ksys::act::ai::ActionBase* owner) : Unk_71025afc58(owner) {}

Unk_71023c8678::~Unk_71023c8678() {
    if (mMemoryPartsName_s.isEmpty())
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mOwner->getActor()))
        enemy->_1128.sub_7100D3CFEC(mMemoryPartsName_s);
}

bool Unk_71023c8678::init_(sead::Heap* heap) {
    if (mMemoryPartsName_s.isEmpty())
        return true;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mOwner->getActor()))
        enemy->_1128.sub_7100D3CED8(mMemoryPartsName_s, heap);
    return true;
}

void Unk_71023c8678::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
}

void Unk_71023c8678::calc_() {
    if (mOwner->getActor()->getASList()->x(0x47, nullptr, 0, 0,
                                           &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        sub_71002A81D4(*mIgniteHandle_d);
    }
}

void Unk_71023c8678::sub_71002A81D4(ksys::act::BaseProcHandle* handle) {
    if (!handle)
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(handle->getProc());
    if (!actor)
        return;

    sead::Vector3f pos;
    m13(&pos);
    const sead::Vector3f rot(
        0.0f,
        sead::GlobalRandom::instance()->getF32() * (2 * sead::Mathf::pi()) - sead::Mathf::pi(),
        0.0f);
    actor->sub_71011C88F8(&pos, &rot, nullptr);

    sead::Vector3f zero = sead::Vector3f::zero;
    actor->setVelocity(&zero, &zero);
    sub_7100738C88(actor, mOwner->getActor());

    auto* released = sead::DynamicCast<ksys::act::Actor>(handle->releaseAndWakeProc());
    if (!mMemoryPartsName_s.isEmpty()) {
        if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mOwner->getActor()))
            enemy->_1128.sub_7100D3D108(mMemoryPartsName_s, released);
    }
    m14(released);
}

void Unk_71023c8678::loadParams_() {
    getStaticParam(&mMemoryPartsName_s, "MemoryPartsName");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}

bool Unk_71023c8678::handleMessage_(const ksys::Message& message) {
    return true;
}

void Unk_71023c8678::m13(sead::Vector3f* pos) {
    mOwner->getActor()->getMtx().getTranslation(*pos);
}

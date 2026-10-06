#include "Game/AI/Action/actionForkSwapPartsItemFromDropTable.h"
#include "Game/AI/aiUnk_710073CDFC.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"

namespace uking::action {

ForkSwapPartsItemFromDropTable::ForkSwapPartsItemFromDropTable(const InitArg& arg) : Fork(arg) {}

ForkSwapPartsItemFromDropTable::~ForkSwapPartsItemFromDropTable() = default;

bool ForkSwapPartsItemFromDropTable::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkSwapPartsItemFromDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        setFailed();
        return;
    }
    auto* drop = mActor->getParam()->getRes().mDropTable;
    if (!drop) {
        setFailed();
        return;
    }
    auto* creator = ksys::act::ActorCreator::instance();
    if (!creator) {
        setFailed();
        return;
    }

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    for (s32 i = 0; i != 5; ++i) {
        const sead::SafeString& key = mPartsKey_s[i];
        if (key.isEmpty())
            continue;

        const s32 index = sub_710073CDFC(mActor, &enemy->getActorPartsActor(key));
        if (index < 0)
            continue;

        sead::FixedSafeString<64> actor_name;
        ksys::eco::getEcosystemActorName(&actor_name, drop->getRandomDropFromTable(index), pos);
        ksys::act::InstParamPack pack;
        pack->addPosition(pos);
        pack->add(-1, "Life");
        creator->requestCreateActor(actor_name.cstr(),
                                    ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                    &_80[i], &pack, nullptr, 1);
    }
}

void ForkSwapPartsItemFromDropTable::leave_() {
    Fork::leave_();
}

void ForkSwapPartsItemFromDropTable::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mPartsKey_s[0], "PartsKey0");
    getStaticParam(&mPartsKey_s[1], "PartsKey1");
    getStaticParam(&mPartsKey_s[2], "PartsKey2");
    getStaticParam(&mPartsKey_s[3], "PartsKey3");
    getStaticParam(&mPartsKey_s[4], "PartsKey4");
}

void ForkSwapPartsItemFromDropTable::calc_() {
    Fork::calc_();
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        setFailed();
        return;
    }

    bool finished = true;
    for (s32 i = 0; i != 5; ++i) {
        auto& handle = _80[i];
        if (!handle.isAllocatedOrFailed())
            continue;

        if (handle.isProcReady()) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(handle.releaseAndWakeProc());
            if (!actor)
                continue;

            const sead::SafeString& key = mPartsKey_s[i];
            if (key.isEmpty()) {
                actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            } else {
                actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                auto& link = enemy->getActorPartsActor(key);
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                enemy->sub_7100D3D2B4(key);
                enemy->sub_7100D3D108(key, actor);
            }
        } else if (handle.hasProcCreationFailed()) {
            handle.deleteProcIfFailed();
        } else {
            finished = false;
        }
    }

    if (finished)
        setEndState();
}

}  // namespace uking::action

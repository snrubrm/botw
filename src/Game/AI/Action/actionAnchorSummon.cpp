#include "Game/AI/Action/actionAnchorSummon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

static sead::Vector3f getPos(ksys::map::Object* o) {
    return o->getTranslate();
}

AnchorSummon::AnchorSummon(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

AnchorSummon::~AnchorSummon() {
    _70.freeBuffer();
    _80.freeBuffer();
}

// NON_MATCHING: register allocation only (the original computes &mActor->getMessageTransceiver() into the
// register that held the loop bound compare, ours reuses the actor register)
bool AnchorSummon::init_(sead::Heap* heap) {
    auto* object = mActor->getMapObject();
    if (!object)
        return true;
    auto* links = object->getLinkData();
    if (!links)
        return true;

    auto objects = links->mObjects;
    s32 count = 0;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (sead::SafeString(objects(i)->getUnitConfigName()) == "EnemySummonPoint")
            ++count;
    }
    _70.tryAllocBuffer(count, heap);
    for (s32 i = 0; i < count; ++i)
        _70[i]._8 = &mActor->getMessageTransceiver();
    _80.tryAllocBuffer(count, heap);
    return true;
}

void AnchorSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    mFlags.reset(Flag::Changeable);
    _90 = false;

    auto* object = mActor->getMapObject();
    if (!object)
        return;
    auto* links = object->getLinkData();
    if (!links)
        return;

    auto objects = links->mObjects;
    s32 index = 0;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (sead::SafeString(objects(i)->getUnitConfigName()) == "EnemySummonPoint") {
            sub_710008C850(getPos(objects(i)), index);
            ++index;
        }
    }
}

void AnchorSummon::leave_() {
    ActionWithPosAngReduce::leave_();
}

void AnchorSummon::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mSummonActor_d, "SummonActor");
    getDynamicParam(&mSummonActorEquip1_d, "SummonActorEquip1");
    getDynamicParam(&mSummonActorEquip2_d, "SummonActorEquip2");
}

void AnchorSummon::calc_() {
    ActionWithPosAngReduce::calc_();
    if (!isFinishedAS(0, 0))
        return;

    const s32 size = _80.size();
    auto* object = mActor->getMapObject();
    auto* links = object ? object->getLinkData() : nullptr;
    for (s32 i = 0; i < size; ++i) {
        if (_80[i].isProcReady()) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(_80[i].releaseAndWakeProc());
            if (actor) {
                actor->clearFadeInCreate();
                _70[i]._18.y(actor);
                if (links) {
                    auto objects = links->mObjects;
                    for (s32 j = 0; j < objects.size(); ++j) {
                        ksys::act::ActorConstDataAccess accessor;
                        objects(j)->getActorWithAccessor(accessor);
                        if (accessor.hasProc())
                            _70[i].sub_710070DD78(accessor, true);
                    }
                }
                _90 = true;
            }
        } else if (!_80[i].hasProcCreationFailed()) {
            if (_80[i].isAllocatedOrFailed())
                return;
        }
    }

    if (_90)
        setFinished();
    else
        setFailed();
}

}  // namespace uking::action

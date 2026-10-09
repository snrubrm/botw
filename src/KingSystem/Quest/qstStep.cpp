#include "KingSystem/Quest/qstStep.h"
#include <memory>
#include "Game/DLC/aocManager.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Quest/qstIndicator.h"

namespace ksys::qst {

// NON_MATCHING: regalloc
Step::Step(const u8** iter_data, sead::Heap* heap) : heap(heap) {
    if (*iter_data != nullptr) {
        iter = new (heap, std::nothrow_t()) al::ByamlIter(*iter_data);
    }
}

Step::ActLink::ActLink(const Args& args, sead::Heap* heap)
    : _18(args._28), name(args.name), heap(heap), unique_name(args.unique_name) {
    name_hash = sead::HashCRC32::calcStringHash(name);
    if (args.proc != nullptr)
        link.acquire(args.proc, false);
    if (args.iter_40 != nullptr)
        _40 = new (this->heap, 8) al::ByamlIter(*args.iter_40);
    _30 = args.iter_30 != nullptr ? new (this->heap, 8) al::ByamlIter(*args.iter_30) :
                                    new (this->heap, 8) al::ByamlIter();
    _1c = args._2c;
    _1d = args._2d;
}

Step::ActLink::~ActLink() {
    sub_71012B4274();
    if (_30 != nullptr) {
        delete _30;
        _30 = nullptr;
    }
    if (_40 != nullptr) {
        delete _40;
        _40 = nullptr;
    }
}

Step::~Step() {
    if (actor_data != nullptr) {
        delete actor_data;
        actor_data = nullptr;
    }
    if (indicator_info != nullptr) {
        delete indicator_info;
        indicator_info = nullptr;
    }
    if (iter != nullptr) {
        delete iter;
        iter = nullptr;
    }
    links.freeBuffer();
}

bool Step::sub_7100FDB89C(act::Actor* actor) const {
    for (int i = 0; i < links.size(); ++i) {
        if (!links[i]->link.hasProc())
            continue;
        if (links[i]->link.hasProcById(actor))
            return true;
    }
    return false;
}

bool Step::sub_7100FDB794(act::Actor* actor) const {
    if (indicator_info)
        return indicator_info->sub_7100FD4FC4(actor);
    return false;
}

bool Step::sub_7100FDB538(act::Actor* actor, const sead::SafeString& name) const {
    if (actor == nullptr)
        return false;
    if (!_28)
        return true;

    for (int i = 0; i < links.size(); ++i) {
        sead::SafeString actName(actor->getName());
        sead::SafeString uniqName(actor->getUniqueName());
        if (actName != links[i]->name)
            continue;

        if (uniqName != links[i]->unique_name)
            continue;

        if (links[i]->sub_71012B43D0(actor, name)) {
            return true;
        }
    }
    return false;
}

bool Step::initActorData([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (actor_data != nullptr) {
        // The photo object has already been created.
        out_message->format("写真対象は既に作成されています。");
        return false;
    }

    actor_data = new (heap, std::nothrow_t()) ActorData(heap);
    if (actor_data == nullptr) {
        // Due to insufficient memory, photo data could not be created.
        out_message->format("メモリ不足のため、写真情報を作成できませんでした。");
        return false;
    }
    return actor_data->init(iter, out_message);
}

bool Step::initIndicator([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (indicator_info != nullptr) {
        // The indicator information has already been created.
        out_message->format("光点情報は既に作成されています。");
        return false;
    }

    indicator_info = new (heap, std::nothrow_t()) Indicator(this, heap);
    if (indicator_info == nullptr) {
        // Due to insufficient memory, indicator information could not be created.
        out_message->format("メモリ不足のため、光点情報を作成できませんでした。");
        return false;
    }
    return indicator_info->init(iter, out_message);
}

bool Step::sub_7100FDC2A4(al::ByamlIter* iter) {
    al::ByamlIter evt_iter;
    al::ByamlIter trg_iter;
    const char* value;

    if (!iter->tryGetIterByKey(&evt_iter, "TriggerEvents"))
        return false;

    for (int i = 0; i < evt_iter.getSize(); ++i) {
        if (evt_iter.tryGetIterByIndex(&trg_iter, i) && trg_iter.isValid() &&
            trg_iter.tryGetStringByKey(&value, "Trigger")) {
            if (sead::SafeString("StepStart") == value)
                return true;
        }
    }
    return false;
}

}  // namespace ksys::qst

namespace ksys::qst {

void Step::ActLink::sub_71012B4274() {
    const auto* aoc = uking::aoc::Manager::instance();
    if ((!aoc || aoc->getVersion() == 0) && _1d != 0)
        return;
    if (link.hasProc()) {
        auto* actor = sead::DynamicCast<act::Actor>(link.getProc(nullptr));
        if (actor && actor->getSchedule()) {
            actor->getSchedule()->sub_7100D192C0(nullptr, &sead::SafeString::cNullChar, false);
            actor->getSchedule()->_2ec = actor->getSchedule()->_2f0;
            actor->x_6();
            actor->getActorFlags2().reset(act::Actor::ActorFlag2::_100);
        }
    }
    link.reset();
}

}  // namespace ksys::qst

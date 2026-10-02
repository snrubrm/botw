#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/behaviorDummyBehavior.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace ksys::act::ai {

Behavior::Behavior(const InitArg& arg)
    : mActor(arg.actor), mDefIdx(static_cast<u16>(arg.def_idx)) {}

inline res::AIProgram* Behavior::getAIProg() const {
    return mActor->getParam()->getRes().mAIProgram;
}

inline auto& Behavior::getDef() const {
    return getAIProg()->getBehaviors()[s16(mDefIdx)];
}

// NON_MATCHING: the first early return materialises `false` before the branch (block layout)
bool Behavior::init(sead::Heap* heap) {
    AIDefSet set;
    set.dynamic_params.num_params = 0;
    set.ai_tree_params.num_params = 0;
    AIClassDef::instance()->getDef(getDef().mClassName, &set, AIDefType::Behavior);

    if (!mActor->getRootAi()->loadMapUnitParams(set.map_unit_params, heap))
        return false;

    if (!mActor->getRootAi()->loadAITreeParams(set.ai_tree_params, heap))
        return false;

    m10();
    return m6(heap);
}

inline void Behavior::updateState(Behavior** pending_list) {
    switch (_13) {
    case 0:
        if (!_20) {
            _20 = *pending_list;
            *pending_list = this;
        }
        [[fallthrough]];
    case 3:
        _13 = _12 != 0 ? 1 : 2;
        break;
    case 1:
        if (_12 == 0)
            _13 = 3;
        break;
    case 2:
        if (_12 != 0)
            _13 = 3;
        break;
    default:
        _13 = 3;
        break;
    }
}

// NON_MATCHING: the original shares one block for states 0 and 3 and re-tests the state there
bool Behavior::sub_7100D24A10(Behavior** list, Behavior** pending_list) {
    if (_12 != 0) {
        ++_12;
        return false;
    }

    _18 = *list;
    *list = this;
    ++_12;
    updateState(pending_list);
    return true;
}

// NON_MATCHING: same state switch difference as sub_7100D24A10
bool Behavior::sub_7100D24AC0(Behavior** list, Behavior** pending_list) {
    if (_12 != 0) {
        --_12;
        if (_12 != 0)
            return false;
    }

    if (*list == this) {
        *list = _18;
    } else {
        for (auto* it = *list; it; it = it->_18) {
            if (it->_18 == this) {
                it->_18 = _18;
                break;
            }
        }
    }
    _18 = nullptr;
    updateState(pending_list);
    return true;
}

Behavior* Behavior::sub_7100D24B94() {
    if (_13 == 2) {
        m9();
        _13 = 0;
    }
    return _20;
}

Behavior* Behavior::sub_7100D24BD4() {
    if (_13 == 1)
        m8();
    _13 = 0;
    return _20;
}

void Behavior::x() {
    if (_13 == 0 || _13 == 3)
        m11();
}

s32 Behavior::getCalcTiming() const {
    return s16(getDef().mCalcTiming);
}

bool Behavior::isNoStop() const {
    return getDef().mNoStop != 0;
}

bool Behavior::getStaticParam(sead::SafeString* value, const sead::SafeString& key) const {
    return getAIProg()->getSInstParam(value, getDef(), key);
}

bool Behavior::getStaticParam(const s32** value, const sead::SafeString& key) const {
    return getAIProg()->getSInstParam(value, getDef(), key);
}

Behaviors::Behaviors() = default;

Behaviors::~Behaviors() {
    finalize();
}

void Behaviors::finalize() {
    for (s32 i = 0; i < mClasses.size(); ++i) {
        if (mClasses[i]) {
            delete mClasses[i];
            mClasses[i] = nullptr;
        }
    }

    mOnPreDeleteCbs.freeBuffer();
    mUpdateForPreDeleteCbs.freeBuffer();
    mClasses.freeBuffer();
}

bool Behaviors::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_behaviors = aiprog->getBehaviors().size();
    if (num_behaviors == 0)
        return true;

    if (!mClasses.tryAllocBuffer(num_behaviors, heap))
        return false;
    for (s32 i = 0, n = mClasses.size(); i != n; ++i)
        mClasses(i) = nullptr;
    auto it_class = mClasses.begin();
    const auto it_class_end = mClasses.end();

    Behavior::InitArg arg;
    arg.actor = actor;
    s32 predelete_cb_num = 0;
    s32 update_cb_num = 0;
    for (; it_class != it_class_end; ++it_class) {
        arg.def_idx = it_class.getIndex();
        const char* name = aiprog->getBehaviors()[it_class.getIndex()].mClassName;

        auto* factory = getFactory(name);
        if (factory)
            *it_class = factory->create_fn(arg, heap);
        else
            *it_class = new (heap) DummyBehavior(arg);

        if (!*it_class)
            return false;

        update_cb_num += (*it_class)->hasUpdateForPreDeleteCb();
        predelete_cb_num += (*it_class)->hasPreDeleteCb();
    }

    // Allocate the callback lists.
    if (predelete_cb_num != 0) {
        if (!mOnPreDeleteCbs.tryAllocBuffer(predelete_cb_num, heap))
            return false;
        for (s32 i = 0; i < predelete_cb_num; ++i)
            mOnPreDeleteCbs(i) = nullptr;
    }

    if (update_cb_num != 0) {
        if (!mUpdateForPreDeleteCbs.tryAllocBuffer(update_cb_num, heap))
            return false;
        for (s32 i = 0; i < update_cb_num; ++i)
            mUpdateForPreDeleteCbs(i) = nullptr;
    }

    // Initialize each class.
    s32 idx_cb1 = 0, idx_cb2 = 0;
    for (auto it = mClasses.begin(), end = mClasses.end(); it != end; ++it) {
        if (!(*it)->init(heap))
            return false;

        if ((*it)->hasUpdateForPreDeleteCb()) {
            mUpdateForPreDeleteCbs[idx_cb2] = *it;
            ++idx_cb2;
        }

        if ((*it)->hasPreDeleteCb()) {
            mOnPreDeleteCbs[idx_cb1] = *it;
            ++idx_cb1;
        }
    }

    return true;
}

bool Behaviors::updateForPreDelete() const {
    bool ok = true;
    for (auto* cb : mUpdateForPreDeleteCbs) {
        if (cb)
            ok &= cb->updateForPreDelete();
    }
    return ok;
}

void Behaviors::onPreDelete() const {
    for (auto* cb : mOnPreDeleteCbs) {
        if (cb)
            cb->onPreDelete();
    }
}

BehaviorFactory* Behaviors::getFactory(const sead::SafeString& name) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const s32 idx = sFactories.binarySearch(
        name_hash, +[](const BehaviorFactory& factory, const u32& hash) {
            if (factory.hash < hash)
                return -1;
            if (factory.hash > hash)
                return 1;
            return 0;
        });
    if (idx < 0)
        return nullptr;
    return sFactories.get(idx);
}

void Behaviors::setFactories(int count, BehaviorFactory* factories) {
    sFactories.setBuffer(count, factories);
}

sead::Buffer<BehaviorFactory> Behaviors::sFactories;

}  // namespace ksys::act::ai

#include "aal/aalSpatialCalculatorPool.h"
#include <codec/seadHashCRC32.h>
#include <cstring>
#include "aal/aalSpatialCalculatorFactory.h"

namespace aal {

namespace {
SpatialCalculatorFactory sDefaultFactory;
}

// 0x7100b90960
SpatialCalculatorPool::SpatialCalculatorPool()
    : mSearchStart(0), mDirtyCounter(0), mFactory(&sDefaultFactory) {}

// 0x7100b9098c (D1) / 0x7100b90a7c (D0)
SpatialCalculatorPool::~SpatialCalculatorPool() {
    finalize();
}

// 0x7100b90a0c
void SpatialCalculatorPool::finalize() {
    if (!mCalculators.isBufferReady())
        return;
    auto it = mCalculators.begin();
    const u32 num = mNumCalculators;
    for (u32 i = 0; i < num; ++i, ++it) {
        it->calculator->finalize();
        mFactory->destroy(it->calculator);
    }
    mCalculators.freeBuffer();
}

// 0x7100b90af8
void SpatialCalculatorPool::initialize(s32 num, sead::Heap* heap,
                                       ISpatialCalculatorFactory* factory) {
    if (mCalculators.isBufferReady())
        return;
    if (factory)
        mFactory = factory;
    mCalculators.tryAllocBuffer(num, heap, 8);
    memset(&mCalculators.front(), 0, u32(mCalculators.size()) * u32(sizeof(Entry)));
    mNumCalculators = 0;
    for (s32 i = 0; i < num; ++i) {
        SpatialCalculator* calculator = mFactory->create(heap);
        if (!calculator)
            break;
        calculator->initialize(i, &mDirtyCounter, heap);
        mCalculators[i].calculator = calculator;
        mCalculators[i].setting_hash = 0;
        ++mNumCalculators;
    }
    mSearchStart = 0;
}

// NON_MATCHING: the same searches, but the original lays the code out as one loop (the failed search for a shared
// calculator jumps back to the search for an unused one) and keeps the bounds in other registers.
// 0x7100b90c38
SpatialCalculator* SpatialCalculatorPool::alloc(const SpatialCalculator::Setting& setting,
                                                bool exclusive) {
    u32 hash = sead::HashCRC32::calcHash(&setting, sizeof(setting));
    if (hash == 0)
        hash = 1;

    if (!exclusive) {
        for (s32 i = mSearchStart; i != 0; --i) {
            Entry& entry = mCalculators(i - 1);
            if (entry.setting_hash == hash && entry.calculator->hasSetting(setting)) {
                entry.calculator->beginReferred();
                return entry.calculator;
            }
        }
        for (s32 i = mNumCalculators; i != mSearchStart; --i) {
            Entry& entry = mCalculators(i - 1);
            if (entry.setting_hash == hash && entry.calculator->hasSetting(setting)) {
                entry.calculator->beginReferred();
                return entry.calculator;
            }
        }
    }

    Entry* found = nullptr;
    s32 index = 0;
    for (s32 i = mSearchStart; i != mNumCalculators; ++i) {
        if (mCalculators(i).setting_hash == 0) {
            found = &mCalculators(i);
            index = i;
            break;
        }
    }
    if (!found) {
        for (s32 i = 0; i != mSearchStart; ++i) {
            if (mCalculators(i).setting_hash == 0) {
                found = &mCalculators(i);
                index = i;
                break;
            }
        }
    }
    if (!found)
        return nullptr;

    found->calculator->setup(setting);
    found->setting_hash = hash;
    mSearchStart = index + 1 < mNumCalculators ? index + 1 : 0;
    found->calculator->beginReferred();
    return found->calculator;
}

// 0x7100b90dec
void SpatialCalculatorPool::free(SpatialCalculator* calculator) {
    if (calculator && mCalculators.isBufferReady()) {
        calculator->endReferred();
        if (!calculator->isReferred()) {
            calculator->reset();
            mCalculators[calculator->getPoolIndex()].setting_hash = 0;
        }
    }
}

// 0x7100b90e58
void SpatialCalculatorPool::resetDirtyAll() {
    mDirtyCounter = mDirtyCounter + 1 == 0xffffffff ? 0 : mDirtyCounter + 1;
}

}  // namespace aal

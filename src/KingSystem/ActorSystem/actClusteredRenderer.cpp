#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include <utility>
#include <gsys/gsysG3dResModelEx.h>
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include <heap/seadHeap.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadScopedLock.h>
#include <thread/seadDelegateThread.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::act {

namespace {
// 0x7101e7dc54 (placeholder name): the grid offsets of the four regions.
const sead::Vector2i sRegionOffsets[4] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
}  // namespace

// NON_MATCHING: the original computes the FixedSafeString buffer pointers (0x110 / 0x124) before the
// memset (scheduling / register allocation only).
ClusteredRenderer::ClusteredRenderer() : mData(), mData2() {
    mData._e8 = 0xffff;
    mData._ec = 0xffff;
    mData._f0 = nullptr;
    mData.mThreadDelegate.bind(this, &ClusteredRenderer::sub_710124271C);
    mData.mThreadPriority = 20;
    mData.mThread = nullptr;
    mData.mHeap = nullptr;
    mData._110.clear();
    mData._108 = nullptr;
    mData._bc8 = sead::Vector3f::zero;
    mData._bf8 = 0;
    mData._bf0 = nullptr;
    mData._bd8.invalidate();
    mData._c44 = 0;
    mData._c38 = 1;
    mData._c40 = 1;
    mData._c3c = 1;
    mData._c48 = sead::Delegate1<ClusteredRenderer, res::TextureHandleList::Entry*>(
        this, &ClusteredRenderer::sub_7101242720);
    mData2._c68 = 0x180000;
    mData2._c6c = 0x480000;
    mData2._c70 = 2;
    mData2._c74 = 30.0f;
    mData2._c78 = 0;
    mData2._c80 = 0;
    mData2._c88 = 0;
    mData2._c90 = 0;
    mData2._c98 = 0;
    mData2._c9c = (mData2._c9c & ~0x40u) | 0x100000;
}

void ClusteredRenderer::sub_710124271C(sead::Thread*, sead::MessageQueue::Element) {
    sub_7101246FBC();
}

// NON_MATCHING: the original does not pass `this` to sub_710124474C / sub_7101244980 (their first argument is
// unused, so it looks dead-argument-eliminated); register allocation and a few compare forms differ.
void ClusteredRenderer::sub_7101246FBC() {
    s32 wait_ms = 0;
    auto& queue0 = mData.mQueues[0];
    auto& queue1 = mData.mQueues[1];
    auto& queue2 = mData.mQueues[2];

    mData._218.lock();

    while (!(mData2._c9c & 0x40000000)) {
        if (queue0.mRead == queue0.mWrite)
            break;
        mData._198.lock();
        if (queue0.mRead == queue0.mWrite) {
            mData._198.unlock();
            break;
        }
        auto& entry = queue0.mItems[queue0.mRead.increment() % 32];
        ClusteredRendererRegion* region = entry.mRegion;
        entry.mRegion = nullptr;
        res::Handle* handle = entry.mHandle;
        const u32 _14 = entry._14;
        if (entry.mFrame == region->_90) {
            region->_90 = mData._c38;
            const u32 frame = region->_90;
            mData._198.unlock();
            sub_710124474C(region);
            queue1.push({region, handle, frame, _14});
        } else {
            mData._198.unlock();
        }
    }

    while (!(mData2._c9c & 0x40000000)) {
        if (queue1.mRead == queue1.mWrite)
            break;
        if (mData._c38 < 3)
            break;
        auto& entry = queue1.mItems[queue1.mRead % 32];
        if (mData._c38 - entry.mFrame < 3)
            break;
        sub_7101244980(entry.mRegion, true);
        if (loadX_0(entry.mRegion, entry.mHandle, entry.mFrame) == 0) {
            queue2.push(entry);
        } else if (entry.mFrame == entry.mRegion->_90) {
            sub_710124474C(entry.mRegion);
            sub_7101244980(entry.mRegion, true);
        }
        entry.mRegion = nullptr;
        queue1.mRead.increment();
    }

    while (!(mData2._c9c & 0x40000000)) {
        if (queue2.mRead == queue2.mWrite)
            break;
        auto& entry = queue2.mItems[queue2.mRead % 32];
        const s32 result = sub_71012460A4(entry.mRegion, entry.mFrame);
        if (result == 1) {
            if (!(mData2._c9c & 0x40000000) && entry.mFrame == entry.mRegion->_90) {
                sub_710124474C(entry.mRegion);
                sub_7101244980(entry.mRegion, true);
            }
        } else if (result == 2) {
            wait_ms = 33;
            break;
        }
        entry.mRegion = nullptr;
        queue2.mRead.increment();
    }

    mData._218.unlock();
    if (mData2._c9c & 0x40000000)
        return;

    mData._198.lock();
    if (queue0.mRead == queue0.mWrite && queue1.mRead == queue1.mWrite && queue2.mRead == queue2.mWrite)
        mData2._c9c |= 4;
    else
        mData.mThread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
    mData._198.unlock();

    if (wait_ms == 0)
        sead::Thread::yield();
    else
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(wait_ms));
}

// NON_MATCHING: the original reloads mOwner before loading mIndex (C++14 evaluation order of |=, or an
// inline bit-set helper on the owner; not applied).
void ClusteredRenderer::sub_7101242720(res::TextureHandleList::Entry* entry) {
    auto* tex = static_cast<ClusteredRendererTexMaybe*>(entry->sub_71012BD4D8());
    ++tex->mOwner->mUseCount;
    tex->mOwner->mUsedBits->mWords[tex->mIndex >> 5] |= 1u << (tex->mIndex & 0x1f);
}

// The original keeps both vtable stores (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; },
// commit 96101229).
ClusteredRenderer::~ClusteredRenderer() { ; }

sead::SafeString ClusteredRenderer::getName() const {
    return "ClusteredRenderer";
}

bool ClusteredRenderer::sub_7101249FC0() {
    if (!mData._218.tryLock())
        return false;
    if (!mData._198.tryLock()) {
        mData._218.unlock();
        return false;
    }
    if (!mData._1d8.tryLock()) {
        mData._198.unlock();
        mData._218.unlock();
        return false;
    }
    return true;
}

void ClusteredRenderer::sub_710124A02C() {
    mData._1d8.unlock();
    mData._198.unlock();
    mData._218.unlock();
}

// TODO: 0x71012481f8 (2296 bytes), not decompiled yet; the vtable needs a definition.
void ClusteredRenderer::postCalcWorld(const gsys::ModelScene*, u32, u32, const gsys::ModelViewData*,
                                      int) {}

// TODO: 0x7101248af0 (1964 bytes), not decompiled yet; the vtable needs a definition.
void ClusteredRenderer::sub_7101248AF0(void*, const void*) {}

void ClusteredRenderer::startThread() {
    if ((mData2._c9c & 0x40000000) == 0)
        return;

    mData._c44 = 3;
    mData2._c9c |= 0x80000;
    mData.mThread = new (mData.mHeap, std::nothrow_t())
        sead::DelegateThread("act::ClusteredRenderer", &mData.mThreadDelegate, mData.mHeap,
                             sead::ThreadUtil::ConvertPrioritySeadToPlatform(mData.mThreadPriority),
                             sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x100000, 1);
    mData2._c9c &= ~0x40000000u;
    mData.mThread->setAffinity(sead::CoreIdMask(sead::CoreId::cSub1));
    mData.mThread->start();
    if (mData.mQueues[0].mRead != mData.mQueues[0].mWrite ||
        mData.mQueues[1].mRead != mData.mQueues[1].mWrite ||
        mData.mQueues[2].mRead != mData.mQueues[2].mWrite)
        mData.mThread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);

    auto lock = sead::makeScopedLock(mData._1d8);
    const s32 num = mData._f0->mCells.size();
    for (s32 i = 0; i < num; ++i)
        sub_7101243EEC(&mData._f0->mCells[i]);
}

void ClusteredRenderer::sub_71012439BC() {
    if (mData._f8)
        mData._f8->mFlag.setBit(sead::Heap::Flag::cDisposing);

    sub_7101243B70();

    mData.mHeap->destroy();
    mData.mHeap = nullptr;
    sub_7101243BD8(true);
    mData2._c9c &= ~0x4008000bu;

    if (mData._f0) {
        sub_7101243CD8(mData._f0);
        mData._f0 = nullptr;
    }

    mData._168.freeBuffer();

    if (mData._108) {
        gsys::Model::sub_7100BF69F8(mData._108);
        mData._108 = nullptr;
    }

    if (mData._f8) {
        if (mData._ba8.work()) {
            mData._f8->free(mData._ba8.work());
            mData._ba8.reset();
        }
        if (mData._bb8.work()) {
            mData._f8->free(mData._bb8.work());
            mData._bb8.reset();
        }
    }

    if (mData._bd8.isValid()) {
        mData._bd8.deleteGPUMemBlock();
        mData._bd8.invalidate();
    }

    if (mData._f8)
        mData._f8 = nullptr;
}

void ClusteredRenderer::sub_7101244210(s32 x, s32 z) {
    const u32 keep = sub_7101244C58(x, z);
    auto lock = sead::makeScopedLock(mData._198);

    for (s32 i = 0; i < 4; ++i) {
        if (keep & (1 << i))
            continue;

        ClusteredRendererRegion* region = mData._f0->mRegions[i];
        res::Handle* handle = mData._f0->mHandles[i];
        region->_90 = 0;
        if (region->mState != 2 || region->mState != 3) {
            for (auto it = mData._168.robustBegin(); it != mData._168.robustEnd(); ++it) {
                if (it->mRegion == region && it->mHandle == handle)
                    mData._168.erase(&*it);
            }
        }
        handle->requestUnload();
        region->mState.exchange(0);
    }

    mData._e8 = x;
    mData._ec = z;
    for (s32 i = 0; i < 4; ++i) {
        if (!(keep & (1 << i)))
            loadX(mData._f0, i);
    }
    if ((~keep & 0xf) != 0 && (mData2._c9c & 8))
        mData2._c9c &= ~4u;
}

u64 ClusteredRenderer::sub_7101244C58(s32 x, s32 z) {
    u32 dx;
    switch (x - mData._e8) {
    case -1:
        dx = 0;
        break;
    case 0:
        dx = 1;
        break;
    case 1:
        dx = 2;
        break;
    default:
        dx = 0xf;
        break;
    }
    const s32 dz = z - mData._ec;
    u32 code;
    if (dz == -1)
        code = dx;
    else if (dz == 0)
        code = dx | 0x10;
    else if (dz == 1)
        code = dx | 0x20;
    else
        code = dx | 0xf0;

    u64 keep = 0;
    switch (code) {
    case 0x00:
        std::swap(mData._f0->mRegions[3], mData._f0->mRegions[0]);
        std::swap(mData._f0->mHandles[3], mData._f0->mHandles[0]);
        keep = 0b1000;
        break;
    case 0x01:
        std::swap(mData._f0->mRegions[2], mData._f0->mRegions[0]);
        std::swap(mData._f0->mHandles[2], mData._f0->mHandles[0]);
        std::swap(mData._f0->mRegions[3], mData._f0->mRegions[1]);
        std::swap(mData._f0->mHandles[3], mData._f0->mHandles[1]);
        keep = 0b1100;
        break;
    case 0x02:
        std::swap(mData._f0->mRegions[1], mData._f0->mRegions[2]);
        std::swap(mData._f0->mHandles[1], mData._f0->mHandles[2]);
        keep = 0b0100;
        break;
    case 0x10:
        std::swap(mData._f0->mRegions[0], mData._f0->mRegions[1]);
        std::swap(mData._f0->mHandles[0], mData._f0->mHandles[1]);
        std::swap(mData._f0->mRegions[2], mData._f0->mRegions[3]);
        std::swap(mData._f0->mHandles[2], mData._f0->mHandles[3]);
        keep = 0b1010;
        break;
    case 0x11:
        keep = 0b1111;
        break;
    case 0x12:
        std::swap(mData._f0->mRegions[0], mData._f0->mRegions[1]);
        std::swap(mData._f0->mHandles[0], mData._f0->mHandles[1]);
        std::swap(mData._f0->mRegions[2], mData._f0->mRegions[3]);
        std::swap(mData._f0->mHandles[2], mData._f0->mHandles[3]);
        keep = 0b0101;
        break;
    case 0x20:
        std::swap(mData._f0->mRegions[1], mData._f0->mRegions[2]);
        std::swap(mData._f0->mHandles[1], mData._f0->mHandles[2]);
        keep = 0b0010;
        break;
    case 0x21:
        std::swap(mData._f0->mRegions[0], mData._f0->mRegions[2]);
        std::swap(mData._f0->mHandles[0], mData._f0->mHandles[2]);
        std::swap(mData._f0->mRegions[1], mData._f0->mRegions[3]);
        std::swap(mData._f0->mHandles[1], mData._f0->mHandles[3]);
        keep = 0b0011;
        break;
    case 0x22:
        std::swap(mData._f0->mRegions[0], mData._f0->mRegions[3]);
        std::swap(mData._f0->mHandles[0], mData._f0->mHandles[3]);
        keep = 0b0001;
        break;
    default:
        break;
    }
    return keep;
}

// NON_MATCHING: exchange(3): ours moves the constant 3 into the ldxr retry loop (one instruction moved).
void ClusteredRenderer::sub_71012443AC() {
    auto lock = sead::makeScopedLock(mData._198);

    for (auto it = mData._168.robustBegin(), end = mData._168.robustEnd(); it != end; ++it) {
        auto& item = *it;
        ClusteredRendererRegion* region = item.mRegion;
        res::Handle* handle = item.mHandle;

        const s32 state = region->mState;
        if (state != 3) {
            if (state != 2)
                continue;
            if (handle->isBusy())
                continue;
            handle->parseResource(nullptr);
            if (!handle->requestedLoad() || !handle->isSuccess()) {
                region->mState.exchange(7);
                mData._168.erase(&item);
                continue;
            }
            region->mState.exchange(3);
        }

        const u32 frame = mData._c38;
        if (frame < 4 || frame - item.mFrame < 4)
            continue;
        region->_90 = item.mFrame;

        if (!mData.mQueues[0].push(item))
            continue;
        region->mState.exchange(4);
        mData._168.erase(&item);
    }
}

void ClusteredRenderer::sub_710124474C(ClusteredRendererRegion* region) {
    region->mHeap->mFlag.setBit(sead::Heap::Flag::cDisposing);

    for (s32 i = 0; i < region->mModels.size(); ++i) {
        if (region->mModels[i].mEffectModel) {
            eft::Effect::instance()->getModelMgr().requestDeleteModel(nullptr,
                                                                      region->mModels[i].mEffectModel);
            eft::Effect::instance()->getModelMgr().release(nullptr, region->mModels[i].mEffectModel);
            region->mModels[i].mEffectModel = nullptr;
        }
        if (region->mModels[i].mXLink) {
            xlink::Manager::instance()->removeTransform(region->mModels[i].mXLink);
            region->mModels[i].mXLink->resetELinkEvents();
            region->mModels[i].mXLink->sub_7101230B18();
            delete region->mModels[i].mXLink;
            region->mModels[i].mXLink = nullptr;
        }
    }

    if (region->_94 & 1) {
        for (s32 i = 0; i < region->mSubs.size(); ++i) {
            ClusteredRendererRegion::Sub* sub = region->mSubs[i];
            if (!sub)
                continue;
            for (s32 j = 0; j < sub->_38.size(); ++j) {
                if (auto* model = region->mModels[sub->_38[j].mModelIndex].mResModel)
                    model->countDownReferenceCounter();
            }
        }
        region->_94 &= ~1u;
    }
}

void ClusteredRenderer::sub_7101244980(ClusteredRendererRegion* region, bool unload) {
    region->mHeap->mFlag.setBit(sead::Heap::Flag::cDisposing);

    for (s32 i = 0; i < region->mTextures.size(); ++i)
        region->mTextures[i].mEntry.sub_71012BD338();

    for (s32 i = 0; i < region->mResources.size(); ++i) {
        if (region->mResources[i]._0) {
            if (!unload && region->mResources[i].mHandle.isSuccess())
                region->mResources[i].mHandle.resetUnitFlag20000IfSuccess();
            region->mResources[i].mHandle.requestUnload();
        }
    }

    for (s32 i = 0; i < region->mSubs.size(); ++i) {
        if (region->mSubs[i]) {
            region->mSubs[i]->_38.freeBuffer();
            delete region->mSubs[i]->_30;
            delete region->mSubs[i];
        }
    }

    if (region->_88) {
        delete region->_88;
        region->_88 = nullptr;
    }

    region->mSubs.freeBuffer();
    region->mModels.freeBuffer();
    region->mResources.freeBuffer();
    region->_30.freeBuffer();
    region->_40.freeBuffer();
    region->mTextures.freeBuffer();
    region->mHeap->freeAll();
}

void ClusteredRenderer::sub_7101244598() {
    for (auto* region : mData._f0->mRegions) {
        if (region && region->_7c == 0 && region->mState == 1) {
            for (s32 i = 0; i < region->mModels.size(); ++i) {
                if (region->mModels[i].mXLink)
                    region->mModels[i].mXLink->sub_7101231500();
            }
        }
    }
}

void ClusteredRenderer::sub_7101244038(const sead::Vector3f* pos) {
    ++mData._c38;
    if (!(mData2._c9c & 1))
        return;

    if ((mData2._c9c & 0x4000001a) == 0x1a && isValidCoord(pos->x) && isValidCoord(pos->y) &&
        isValidCoord(pos->z)) {
        const s32 x = sead::Mathi::clamp(s32((pos->x - 250.0f) / 500.0f + 10.0f), 0, 18);
        const s32 z = sead::Mathi::clamp(s32((pos->z - 250.0f) / 500.0f + 8.0f), 0, 14);
        if (mData._e8 != x || mData._ec != z)
            sub_7101244210(x, z);
    }

    if (mData._168.size() != 0)
        sub_71012443AC();

    if (!(mData2._c9c & 0x40000000)) {
        if (mData.mQueues[0].mRead != mData.mQueues[0].mWrite ||
            mData.mQueues[1].mRead != mData.mQueues[1].mWrite ||
            mData.mQueues[2].mRead != mData.mQueues[2].mWrite) {
            mData.mThread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);
        }
    }
    mData._c40 = mData._c38;
}

void ClusteredRenderer::sub_710124A280(Unk_CellNode2* node, sead::FreeList* list) {
    node->mDisplayLists[0].freeBuffer();
    node->mDisplayLists[1].freeBuffer();
    node->mDisplayLists[2].freeBuffer();
    node->~Unk_CellNode2();
    list->free(node);
    node->_720 = 0;
}

// NON_MATCHING: Clang duplicates the queue compare after the node chain loop.
void ClusteredRenderer::Cell::sub_710124749C(sead::FreeList* node_list, sead::FreeList* node2_list) {
    while (!_1458.isEmpty()) {
        for (Unk_CellNode* node = _1458.pop(); node;) {
            Unk_CellNode* next = node->mNext;
            node->~Unk_CellNode();
            node_list->free(node);
            node = next;
        }
    }
    for (auto& queue : _16e8) {
        while (!queue.isEmpty())
            sub_710124A280(queue.pop(), node2_list);
    }
}

// NON_MATCHING: Clang hoists the row (z) test out of the inner loop; the original tests it per entry.
void ClusteredRenderer::sub_71012475EC(Cell* cell, const ClusteredRendererRegion* region, bool reset) {
    const s32 cx = sead::Mathf::floor((cell->mPos.x - region->mOrigin.x) / 25.0f);
    const s32 cz = sead::Mathf::floor((cell->mPos.z - region->mOrigin.y) / 25.0f);
    for (s32 dz = -4; dz <= 4; ++dz) {
        for (s32 dx = -4; dx <= 4; ++dx) {
            const s32 x = cx + dx;
            const s32 z = cz + dz;
            if (u32(z) >= 20 || u32(x) >= 20 || x + z * 20 < 0)
                continue;

            Cell::Entry& entry = cell->mEntries[(dz + 0x1000000 + cell->_1444) % 9]
                                               [(dx + 0x1000000 + cell->_1440) % 9];
            if (entry._8 == 0)
                continue;
            if (reset) {
                entry._0 = 0;
                entry._8 = 0;
                entry._18 = -1;
                entry._10 = sead::Vector2i::zero;
                if (entry._20) {
                    cell->_1458.push(entry._20);
                    entry._20 = nullptr;
                }
            }
            for (s32 i = 0; i < 3; ++i) {
                if (entry._28[i]) {
                    cell->_16e8[cell->_1454].push(entry._28[i]);
                    entry._28[i] = nullptr;
                }
            }
        }
    }
}

// NON_MATCHING: stack slot assignment of the three strings and the load request.
void ClusteredRenderer::loadX(ClusteredRendererCells* cells, s32 index) {
    ClusteredRendererRegion* region = cells->mRegions[index];
    res::Handle* handle = cells->mHandles[index];
    const u32 x = sRegionOffsets[index].x + mData._e8;
    const u32 z = sRegionOffsets[index].y + mData._ec;

    sead::FixedSafeString<256> path;
    const u32 letter = (x >> 1) + 'A';
    const u32 number = (z >> 1) + 1;
    sead::FixedSafeString<32> area{sead::FormatFixedSafeString<32>("%c-%d", letter, number)};
    sead::FixedSafeString<32> name{
        sead::FormatFixedSafeString<32>("%c-%d.%d%d", letter, number, x & 1, z & 1)};
    path.format("%s/%s/%s/%s_%s.%s", "Map", mData._110.cstr(), area.cstr(), name.cstr(),
                ActorDebug::instance() &&
                        ActorDebug::instance()->hasFlag(ActorDebug::Flag::_10000000) ?
                    "ClusteringPast" :
                    "Clustering",
                "blwp");

    res::LoadRequest req;
    req.mLaneId = 2;
    req.mRequester = "act::ClusteredRenderer";
    req._22 = true;
    if (aoc::Manager::instance())
        req.mAocFileDevice = aoc::Manager::instance()->getFileDeviceForMapFile(path);
    handle->requestLoad(path, &req, nullptr);

    auto* item = mData._168.emplaceBack();
    item->mRegion = region;
    item->mHandle = handle;
    item->mFrame = mData._c38;
    region->mCellX = x;
    region->mCellZ = z;
    region->mOrigin.x = static_cast<f32>(s32(x - 10)) * 500.0f;
    region->mOrigin.y = static_cast<f32>(s32(z - 8)) * 500.0f;
    region->_7c.exchange(1);
    region->_94 = 0;
    region->mState.exchange(2);
}

void ClusteredRenderer::sub_7101243EA8(ClusteredRenderer* renderer) {
    sead::Heap* heap = renderer->mData._f8;
    renderer->sub_71012439BC();
    delete renderer;
    heap->destroy();
}

void ClusteredRenderer::sub_7101243BD8(bool release) {
    auto lock = sead::makeScopedLock(mData._1d8);
    if ((mData2._c9c & 0x40000) == 0)
        return;

    const s32 num = mData._f0->mCells.size();
    for (s32 i = 0; i < num; ++i)
        sub_7101243EEC(&mData._f0->mCells[i]);

    if (release) {
        if ((mData2._c9c & 0x20000) != 0) {
            mData._bf0->destroy();
            mData2._c9c &= ~0x20000u;
        } else {
            mData._bf0->freeAll();
        }
    }
    mData._bf0 = nullptr;
    mData2._c9c &= ~0x40000u;
}

// NON_MATCHING: the original does not pass `this` to sub_710124474C / sub_7101244980 (as in sub_7101246FBC).
void ClusteredRenderer::sub_7101243CD8(ClusteredRendererCells* cells) {
    for (s32 i = 0; i < 4; ++i) {
        cells->mRegions[i]->mState.exchange(7);
        sub_710124474C(cells->mRegions[i]);
        sub_7101244980(cells->mRegions[i], true);
        delete cells->mRegions[i];
        delete cells->mHandles[i];
    }

    const s32 num = cells->mCells.size();
    for (s32 i = 0; i < num; ++i)
        sub_7101243EEC(&cells->mCells[i]);
    cells->mCells.freeBuffer();
    delete cells;
}

void ClusteredRenderer::sub_7101243EEC(Cell* cell) {
    for (s32 x = 0; x < 9; ++x) {
        for (s32 y = 0; y < 9; ++y) {
            Cell::Entry& entry = cell->mEntries[x][y];
            entry._0 = 0;
            entry._8 = 0;
            entry._18 = -1;
            entry._10 = sead::Vector2i::zero;
            if (entry._20) {
                cell->_1458.push(entry._20);
                entry._20 = nullptr;
            }
            for (s32 i = 0; i < 3; ++i) {
                if (entry._28[i]) {
                    cell->_16e8[cell->_1454].push(entry._28[i]);
                    entry._28[i] = nullptr;
                }
            }
        }
    }
    cell->sub_710124749C(&mData._ba8, &mData._bb8);
}

void ClusteredRenderer::sub_7101243B70() {
    if ((mData2._c9c & 0x40000000) != 0)
        return;

    mData._c44 = 3;
    mData2._c9c = (mData2._c9c & ~0x80000u) | 0x40000000;
    mData.mThread->quitAndWaitDoneSingleThread(false);
    delete mData.mThread;
    mData.mThread = nullptr;
}

void ClusteredRenderer::requestDraw() {
    if ((mData2._c9c & 0x22) == 0x22) {
        if (mData._c44 <= 0)
            mData._108->requestDraw();
        else
            --mData._c44;
    }
    mData._c3c = mData._c38;
}

}  // namespace ksys::act

namespace ksys::map {

void sub_7101249DF4(sead::Vector2<s32>* out, const sead::Vector3f* pos) {
    const sead::Vector2f xz(pos->x, pos->z);
    out->x = sead::Mathf::floor((xz.x - sead::Vector2f::zero.x) / 25.0f);
    out->y = sead::Mathf::floor((xz.y - sead::Vector2f::zero.y) / 25.0f);
}

}  // namespace ksys::map

namespace ksys::act {

// NON_MATCHING: the node walk: ours iterates the address of the next pointer (load then add 0xd0); the
// original loads _20 first and then follows mNext at 0xd0.
void ClusteredRenderer::sub_7101249E6C() {
    auto lock0 = sead::makeScopedLock(mData._218);
    auto lock1 = sead::makeScopedLock(mData._198);
    auto lock2 = sead::makeScopedLock(mData._1d8);

    auto& cells = mData._f0->mCells;
    for (s32 i = 0; i < cells.size(); ++i) {
        for (s32 z = 0; z < 9; ++z) {
            for (s32 x = 0; x < 9; ++x) {
                const ClusteredRendererRegion* region = cells[i].mEntries[z][x]._0;
                if (!region || region->_7c != 0 || region->mState != 1)
                    continue;
                for (Unk_CellNode* node = cells[i].mEntries[z][x]._20; node; node = node->mNext) {
                }
            }
        }
    }
    for (s32 z = 0; z < 9; ++z) {
        for (s32 x = 0; x < 9; ++x) {
            const ClusteredRendererRegion* region = cells[0].mEntries[z][x]._0;
            if (!region || region->_7c != 0 || region->mState != 1)
                continue;
            for (Unk_CellNode* node = cells[0].mEntries[z][x]._20; node; node = node->mNext) {
            }
        }
    }
}

}  // namespace ksys::act


s32 sub_7101240FE0() { return 28; }

s32 sub_7101241F64() { return 27; }

s32 sub_71011F1F98() { return 1; }

void* sub_71011F1FA0() { return nullptr; }

s32 sub_71011F2ECC() { return 0; }

s32 sub_71011F2ED4() { return 0; }

s32 sub_71011F2F74() { return 0; }

s32 sub_71011F3964() { return 1; }

void* sub_71011F396C() { return nullptr; }

u8* sub_71011F98E4(u8* self) { return self + 64; }

u8* sub_71011F98EC(u8* self) { return self + 16; }

u8* sub_71011F98F4(u8* self) { return self + 68; }

u8* sub_71011F98FC(u8* self) { return self + 52; }

u8* sub_71011F9904(u8* self) { return self + 76; }

u8* sub_71011F990C(u8* self) { return self + 52; }

s32 sub_71011FC4D0() { return 0; }

s32 sub_71012347C0() { return 0; }

void* sub_710123DD20() { return nullptr; }

s32 sub_710123DD2C() { return 0; }

s32 sub_710123DD40() { return 0; }

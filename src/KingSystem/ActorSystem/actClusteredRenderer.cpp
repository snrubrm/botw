#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadScopedLock.h>
#include <thread/seadDelegateThread.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Map/mapPlacementMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::act {

void ClusteredRenderer::startThread() {
    if ((_c9c & 0x40000000) == 0)
        return;

    _c44 = 3;
    _c9c |= 0x80000;
    mThread = new (mHeap, std::nothrow_t())
        sead::DelegateThread("act::ClusteredRenderer", &mThreadDelegate, mHeap,
                             sead::ThreadUtil::ConvertPrioritySeadToPlatform(mThreadPriority),
                             sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x100000, 1);
    _c9c &= ~0x40000000u;
    mThread->setAffinity(sead::CoreIdMask(sead::CoreId::cSub1));
    mThread->start();
    if (_558 != _55c || _860 != _864 || _b68 != _b6c)
        mThread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);

    auto lock = sead::makeScopedLock(_1d8);
    const s32 num = _f0->mCells.size();
    for (s32 i = 0; i < num; ++i)
        sub_7101243EEC(&_f0->mCells[i]);
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
    cell->sub_710124749C(&_ba8, _bb8);
}

void ClusteredRenderer::sub_7101243B70() {
    if ((_c9c & 0x40000000) != 0)
        return;

    _c44 = 3;
    _c9c = (_c9c & ~0x80000u) | 0x40000000;
    mThread->quitAndWaitDoneSingleThread(false);
    delete mThread;
    mThread = nullptr;
}

void ClusteredRenderer::requestDraw() {
    if ((_c9c & 0x22) == 0x22) {
        if (_c44 <= 0)
            _108->requestDraw();
        else
            --_c44;
    }
    _c3c = _c38;
}

}  // namespace ksys::act

namespace ksys::map {

void sub_7101249DF4(sead::Vector2<s32>* out, const sead::Vector3f* pos) {
    const sead::Vector2f xz(pos->x, pos->z);
    out->x = sead::Mathf::floor((xz.x - sead::Vector2f::zero.x) / 25.0f);
    out->y = sead::Mathf::floor((xz.y - sead::Vector2f::zero.y) / 25.0f);
}

}  // namespace ksys::map

// NON_MATCHING: placeholder destructor; the original (0x7101242774) also destroys members or bases
// this class does not declare yet.
Unk_7102516b30::~Unk_7102516b30() = default;

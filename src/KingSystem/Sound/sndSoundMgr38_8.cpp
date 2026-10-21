#include "KingSystem/Sound/sndSoundPointGrid.h"
#include "KingSystem/Sound/sndSound.h"
#include "Game/gameStatisticsMgr.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <aal/aalAttenuationMgr.h>
#include <aal/aalSpeakerBalanceUnifierMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/Actor/actSoundSystemActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace {
// Set up by the TU's 52-byte static initialiser 0x71010349dc.
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

namespace ksys::snd {

// TU 0x710102c1d8..0x71010349dc in the original (static initialiser 0x710102c1a4 ends the previous TU): also
// Unk_SoundMgr38_18 (0x710102cfdc..) and Unk_SoundMgr38_10 (0x7101031010..).

Unk_SoundMgr38_8::Unk_SoundMgr38_8() = default;

Unk_SoundMgr38_8::~Unk_SoundMgr38_8() {
    sub_710102C27C();
}

void Unk_SoundMgr38_8::sub_710102C27C() {
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
    if (mUnifier) {
        aal::SystemAccessor::getSpeakerBalanceUnifierMgr()->freeSpeakerBalanceUnifier(mUnifier);
        mUnifier = nullptr;
    }
    mPositions.freeBuffer();
}

void Unk_SoundMgr38_8::sub_710102C388(sead::Heap* heap) {
    mPositions.tryAllocBuffer(50, heap);
    mUnifier =
        aal::SystemAccessor::getSpeakerBalanceUnifierMgr()->allocSpeakerBalanceUnifier("ForestShake", nullptr);
    if (mUnifier) {
        mUnifier->initializeExtSounds(8, heap);
        if (auto* mgr = aal::SystemAccessor::getAttenuationMgr()) {
            auto* attenuator = mgr->getDefaultAttenuator();
            mUnifier->setAttenuator(attenuator);
        }
        mUnifier->setSpeakerBalanceMoveStep(2.0f);
        mUnifier->setEnvFxMoveStep(2.0f);
        mUnifier->setDistFilterMoveStep(2.0f);
        mUnifier->setTotalVolumeLimitEnabled(true);
    }
    _60 = new (heap) xlink2::HandleSLink;
}

void Unk_SoundMgr38_8::sub_710102C4B0() {
    if (!_68 || !mProcHandle.isAllocatedOrFailed())
        return;
    if (!mProcHandle.isProcReady())
        return;
    if (auto* proc = mProcHandle.getProc()) {
        mTree = sead::DynamicCast<uking::act::SoundSystemActor>(proc);
        mTree->getActorFlags2().set(act::Actor::ActorFlag2::NoDistanceCheck);
    }
    mProcHandle.releaseAndWakeProc();
}

// NON_MATCHING: the original computes the handle test as a value before the count check and reloads the event in the
// fade and the second test.
// Plays the forest shake sound while positions are in use (fades it out otherwise) and unifies its speaker balance.
void Unk_SoundMgr38_8::sub_710102C5AC() {
    auto lock = sead::makeScopedLock(mCS);
    auto* handle = _60;
    const bool active = handle->isActive();
    if (mPositions.size() > 0) {
        if (!active && mTree && handle) {
            *_60 = eft::searchAndEmitSLink(mTree, "ForestShake", false);
            if (_60->isActive())
                _60->getEvent()->resetFlagBit(1);
        }
    } else if (handle && active) {
        handle->fade(60);
    }

    if (!_60->isActive())
        return;
    auto* executor = static_cast<xlink2::EventSLink*>(_60->getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* source = executor->getHandle()->getSoundSource();
    if (!source || !mUnifier->isExtSoundSourceAddable(source))
        return;
    mUnifier->addExtSoundSource(source);
    source->setFadeInTime(1.0);
    source->setReleaseTime(1.0);
    const auto& setting = source->mSpatialSetting.getCalculatorSetting();
    mUnifier->setAttenuator(setting.attenuator);
    mUnifier->setListenerDirectivityEnabled(setting.flags & 0x20);
}

void Unk_SoundMgr38_8::sub_710102C7C0(sead::Heap* heap, act::ActorCreator* creator) {
    if (!mTree)
        creator->requestCreateActor("EnvSoundTree", heap, &mProcHandle, nullptr, nullptr, 1);
    _50 = 0;
}

void Unk_SoundMgr38_8::sub_710102C810() {
    _68 = true;
}

void Unk_SoundMgr38_8::sub_710102C81C() {
    if (_60)
        _60->fade(30);
    _68 = false;
}

void Unk_SoundMgr38_8::sub_710102C594() {
    if (_68 && mTree)
        sub_710102C5AC();
}

// NON_MATCHING: the original stores the zeroed position z before the vtable load (scheduling only).
Unk_71025018c0* Unk_SoundMgr38_8::sub_710102C924() {
    if (!mPositions.isBufferReady())
        return nullptr;
    auto lock = sead::makeScopedLock(mCS);
    auto* position = mPositions.emplaceBack();
    if (position)
        mUnifier->addUnifiable(position);
    return position;
}

void Unk_SoundMgr38_8::sub_710102C9E8(void* handle) {
    if (!handle || !mPositions.isBufferReady())
        return;
    auto* position = static_cast<Unk_71025018c0*>(handle);
    auto lock = sead::makeScopedLock(mCS);
    mUnifier->removeUnifiable(position);
    mPositions.erase(position);
}

void Unk_SoundMgr38_8::sub_710102C8F8() {
    mProcHandle.deleteProc();
    mTree = nullptr;
    _68 = false;
}

void Unk_SoundMgr38_18::sub_710102EB9C() {}

void Unk_SoundMgr38_18::sub_710102EE40() {
    _9627 = true;
    _9624 = true;
    _9629 = true;
}

void Unk_SoundMgr38_10::sub_7101031BB0() {
    if (!_10c1)
        return;

    if (mProcHandle.isAllocatedOrFailed() && mProcHandle.isProcReady()) {
        _18 = static_cast<act::Actor*>(mProcHandle.getProc());
        _18->getActorFlags2().set(act::Actor::ActorFlag2::NoDistanceCheck);
        mProcHandle.releaseAndWakeProc();
    }
    if (!_18)
        return;

    if (_11c0)
        _11c0->calc();
    sub_7101031CF8();
    if (_18) {
        if (_11c0) {
            for (s32 i = 0; i < 32; ++i) {
                const auto& point =
                    _11c0->mPoints[Unk_710251ad68::SoundType(Unk_710251ad68::SoundType::cBush)][i];
                if (point.distance != sead::Mathf::maxNumber() && !_18d0[i]) {
                    _11d0[i]._28[0] = point.pos.x;
                    _11d0[i]._28[1] = point.pos.y;
                    _11d0[i]._28[2] = point.pos.z;
                    _18d0[i] = true;
                }
            }
        }
        sub_7101033DD8();
    }
    sub_71010324A8();
    _1944 = _75c;
    _1948 = _774;
    _10d0 = false;
}

// NON_MATCHING: the original reads _18f8 before the flag search, reuses the event after the emission and keeps the
// second handle test before getAliveAssetExecutor.
void Unk_SoundMgr38_10::sub_7101033DD8() {
    auto lock = sead::makeScopedLock(mCS);
    if (!_18)
        return;

    bool any = false;
    for (s32 i = 0; i < 32; ++i) {
        if (_18d0[i]) {
            any = true;
            break;
        }
    }

    if (_18f8 && !any) {
        _18f0->fade(90);
        _18f8 = false;
        return;
    }
    if (!any)
        return;

    if (!_18f0->isActive()) {
        *_18f0 = eft::searchAndEmitSLink(_18, "BushShake", false);
        if (!_18f0->isActive())
            return;
        _18f0->getEvent()->resetFlagBit(1);
    }
    if (!_18f0->isActive())
        return;

    if (_18f0->isActive()) {
        auto* event = static_cast<xlink2::EventSLink*>(_18f0->getEvent());
        if (auto* executor = event->getAliveAssetExecutor()) {
            if (auto* source = executor->getHandle()->getSoundSource()) {
                if (_11c8->isExtSoundSourceAddable(source)) {
                    _11c8->addExtSoundSource(source);
                    source->setFadeInTime(1.5f);
                    source->setReleaseTime(1.5f);
                    const auto& setting = source->mSpatialSetting.getSpatialCalculatorSetting();
                    _11c8->setAttenuator(setting.attenuator);
                    _11c8->setListenerDirectivityEnabled(setting.flags & 0x20);
                }
            }
        }
    }
    _18f8 = true;
}

// NON_MATCHING: the original stores _10a8 = 0 inside the reset loop (once per point).
void Unk_SoundMgr38_10::sub_7101033328(sead::Heap* heap, act::ActorCreator* creator) {
    if (!_18)
        creator->requestCreateActor("EnvSoundGrass", heap, &mProcHandle, nullptr, nullptr, 1);
    _758 = false;
    _10c0 = false;
    _18f8 = false;
    _10c4 = 0;
    _10c8 = 0;
    if (_11c0)
        _11c0->reset();
    for (s32 i = 0; i < 32; ++i) {
        _ea8[i].pos = sead::Vector3f::zero;
        _ea8[i].active = false;
    }
    _10a8 = 0;
    _10d0 = true;
}

void Unk_SoundMgr38_10::sub_71010333E0() {
    _10c1 = true;
}

// NON_MATCHING: the two reset loops are strength-reduced to pointer loops here (the original keeps an
// index compare and a separately materialised float constant).
void Unk_SoundMgr38_10::sub_7101032870() {
    if (!_10c1 || !_18)
        return;

    sub_7101032940();

    for (s32 i = 0; i < 32; ++i) {
        mPositionActive[i] = false;
        mUnifier->removeUnifiable(&mPositions[i]);
    }

    _75c = 0.0f;
    _774 = 0.0f;
    for (s32 i = 0; i < 32; ++i) {
        _e88[i] = false;
        _788[i]._28[0] = 100000000.0f;
        _788[i]._28[1] = 100000000.0f;
        _788[i]._28[2] = 100000000.0f;
    }
    for (s32 i = 0; i < 32; ++i) {
        _18d0[i] = false;
        _11d0[i]._28[0] = 100000000.0f;
        _11d0[i]._28[1] = 100000000.0f;
        _11d0[i]._28[2] = 100000000.0f;
    }
}

// NON_MATCHING: same loop lowering as sub_7101032870.
void Unk_SoundMgr38_10::sub_710103362C() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);

    mProcHandle.deleteProc();
    _18 = nullptr;
    _758 = false;
    _10c0 = false;
    _18f8 = false;

    for (s32 i = 0; i < 32; ++i) {
        mPositionActive[i] = false;
        mUnifier->removeUnifiable(&mPositions[i]);
    }

    _75c = 0.0f;
    _774 = 0.0f;
    for (s32 i = 0; i < 32; ++i) {
        _e88[i] = false;
        _788[i]._28[0] = 100000000.0f;
        _788[i]._28[1] = 100000000.0f;
        _788[i]._28[2] = 100000000.0f;
    }

    _10c1 = false;
}

}  // namespace ksys::snd

Unk_7102501910::~Unk_7102501910() = default;

void Unk_7102501910::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}

Unk_7102501980::~Unk_7102501980() = default;

void Unk_7102501980::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}

Unk_7102501f10::~Unk_7102501f10() = default;

void Unk_7102501f10::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device, s32 index_a,
                                  s32 index_b, f32 spread) {
    *volume = mVolumes[device][index_b];
    for (auto& v : volume->volume)
        v *= spread;
}

namespace ksys::snd {

// Native 102F884 reads this mutable slope factor, initially 100.0f.
KSYS_VISIBILITY_HIDDEN f32 sWaterFlowSlopeFactor = 100.0f;

// NON_MATCHING: sampling temporaries and the flow value use different stack slots.
bool Unk_SoundMgr38_18::sub_710102F884(s32 x, s32 z, const sead::Vector2f& origin,
                                     tera::System* terrain, uking::StatisticsMgr* statistics,
                                     bool* updated) {
    const sead::Vector3f position(f32(x) * 5.0f + origin.x, 0.0f,
                                  f32(z) * 5.0f + origin.y);
    auto* cell = mCells[x][z];
    cell->_0 = 0.0f;
    cell->_4 = 0.0f;
    cell->_8 = 0.0f;
    cell->_18 = 0;
    cell->mPosition = position;
    const sead::Vector2f xz(position.x, position.z);
    f32 height = 0.0f;
    sead::Vector3f normal;
    const u32 height_result = tera::sub_710110B52C(&height, &normal, &xz, terrain);
    if (height_result == 1) {
        if (updated)
            *updated = true;
    } else if (height_result == 0) {
        return false;
    } else if (height_result == u32(-1)) {
        cell->_0 = 0.0f;
        cell->_4 = 0.0f;
        cell->_8 = 0.0f;
        cell->mPosition = sead::Vector3f::zero;
        cell->_18 = 0;
        return true;
    }
    cell->mPosition.y = height;
    const f32 normal_y = normal.y;
    f32 baseline_height = 0.0f;
    const u32 baseline_result = tera::sub_71011094A0(&baseline_height, &xz, terrain, -1, 0);
    if (baseline_result == 1) {
        if (updated)
            *updated = true;
    } else if (baseline_result == 0) {
        return false;
    } else if (baseline_result == u32(-1)) {
        cell->_0 = 0.0f;
        cell->_4 = 0.0f;
        cell->_8 = 0.0f;
        cell->mPosition = sead::Vector3f::zero;
        cell->_18 = 0;
        return true;
    }
    cell->_0 = sead::Mathf::clampMin(height - baseline_height, 0.0f);
    if (cell->_0 > 0.0f) {
        f32 flow = 0.0f;
        if (mWaterFlowStats) {
            if (statistics->sub_7100E33B10(&flow, 1, mWaterFlowStats, &position) != 0) {
                flow *= 50.0f;
            } else {
                flow = 0.0f;
                // Preserve the native negated upper-bound tests, including unordered inputs.
                if (!(sead::Mathf::abs(position.x) >= 5000.0f) && updated &&
                    !(sead::Mathf::abs(position.z) >= 4000.0f))
                    *updated = true;
            }
        }
        cell->_4 = flow;
        if (normal_y <= 0.0f) {
            cell->_4 = sWaterFlowSlopeFactor + 1.0f;
            cell->_8 = sead::Mathf::piHalf();
        } else {
            const f32 angle = std::acos(normal_y);
            cell->_4 *= (angle / sead::Mathf::piHalf()) * sWaterFlowSlopeFactor + 1.0f;
            cell->_8 = angle;
        }
        cell->_18 = 0;
        u32 attribute;
        if (tera::sub_710110B634(&attribute, &xz, terrain)) {
            const s32 index = s32(attribute >> 8);
            s32 first;
            s32 second;
            tera::sub_710110B7A4(&first, &second, index);
            if (first != -1) {
                if (index == 7)
                    cell->_18 = 3;
                else if (first == 12)
                    cell->_18 = 2;
                else if (first == 11)
                    cell->_18 = 1;
            }
        }
    }
    return true;
}

// NON_MATCHING: grid-center stores and bool aggregation are scheduled differently.
bool Unk_SoundMgr38_18::sub_710102F1E4() {
    const sead::Vector2i previous = mGridCenter;
    mGridCenter.x = s32(mListenerPosition.x / 5.0f);
    mGridCenter.y = s32(mListenerPosition.z / 5.0f);
    mGridShift.x = mGridCenter.x - previous.x;
    mGridShift.y = mGridCenter.y - previous.y;
    mGridPosition.x = f32(mGridCenter.x) * 5.0f;
    mGridPosition.y = f32(mGridCenter.y) * 5.0f;
    auto* placement = map::PlacementMgr::instance();
    if (!placement || !placement->mTeraSystem || !placement->mTeraSystem->_8 ||
        !uking::StatisticsMgr::instance()) {
        _962c = 2;
        return false;
    }
    auto* terrain = placement->mTeraSystem;
    auto* statistics = uking::StatisticsMgr::instance();
    const sead::Vector2f origin(f32(mGridCenter.x - 16) * 5.0f,
                                f32(mGridCenter.y - 16) * 5.0f);
    bool any_updated = false;
    for (s32 x = 0; x < 33; ++x) {
        for (s32 z = 0; z < 33; ++z) {
            bool updated = false;
            if (!sub_710102F884(x, z, origin, terrain, statistics, &updated)) {
                _962c = 2;
                return false;
            }
            if (updated)
                any_updated = true;
        }
    }
    _962c = any_updated ? 3 : 4;
    return true;
}

// NON_MATCHING: copy loops differ in index reloads and cell assignment scheduling.
bool Unk_SoundMgr38_18::sub_710102F33C(const sead::Vector2i& shift, bool* updated) {
    if (shift.x == 0 && shift.y == 0)
        return true;
    auto* placement = map::PlacementMgr::instance();
    if (!placement || !placement->mTeraSystem || !placement->mTeraSystem->_8 ||
        !uking::StatisticsMgr::instance())
        return false;
    auto* terrain = placement->mTeraSystem;
    auto* statistics = uking::StatisticsMgr::instance();
    const sead::Vector2f origin(f32(mGridCenter.x - 16) * 5.0f,
                                f32(mGridCenter.y - 16) * 5.0f);
    if (updated)
        *updated = false;
    if (shift.x < 0) {
        if (shift.y < 0) {
            if (shift.x > -33) {
                for (s32 x = 32; x >= -shift.x; --x) {
                    if (shift.y > -33) {
                        for (s32 z = 32; z >= -shift.y; --z)
                            *mCells[x][z] = *mCells[x + shift.x][z + shift.y];
                    }
                }
            }
            for (s32 x = 0; x < 33; ++x) {
                for (s32 z = 0; z < 33; ++z) {
                    if ((x < -shift.x || z < -shift.y) &&
                        !sub_710102F884(x, z, origin, terrain, statistics, updated))
                        return false;
                }
            }
        } else {
            if (shift.x > -33) {
                for (s32 x = 32; x >= -shift.x; --x) {
                    if (shift.y < 33) {
                        for (s32 z = 0; z < 33 - shift.y; ++z)
                            *mCells[x][z] = *mCells[x + shift.x][z + shift.y];
                    }
                }
            }
            for (s32 x = 0; x < 33; ++x) {
                for (s32 z = 0; z < 33; ++z) {
                    if ((x < -shift.x || z >= 33 - shift.y) &&
                        !sub_710102F884(x, z, origin, terrain, statistics, updated))
                        return false;
                }
            }
        }
    } else if (shift.y < 0) {
        if (shift.x < 33) {
            for (s32 x = 0; x < 33 - shift.x; ++x) {
                if (shift.y > -33) {
                    for (s32 z = 32; z >= -shift.y; --z)
                        *mCells[x][z] = *mCells[x + shift.x][z + shift.y];
                }
            }
        }
        for (s32 x = 0; x < 33; ++x) {
            for (s32 z = 0; z < 33; ++z) {
                if ((x >= 33 - shift.x || z < -shift.y) &&
                    !sub_710102F884(x, z, origin, terrain, statistics, updated))
                    return false;
            }
        }
    } else {
        if (shift.x < 33) {
            for (s32 x = 0; x < 33 - shift.x; ++x) {
                if (shift.y < 33) {
                    for (s32 z = 0; z < 33 - shift.y; ++z)
                        *mCells[x][z] = *mCells[x + shift.x][z + shift.y];
                }
            }
        }
        for (s32 x = 0; x < 33; ++x) {
            for (s32 z = 0; z < 33; ++z) {
                if ((x >= 33 - shift.x || z >= 33 - shift.y) &&
                    !sub_710102F884(x, z, origin, terrain, statistics, updated))
                    return false;
            }
        }
    }
    return true;
}

}  // namespace ksys::snd

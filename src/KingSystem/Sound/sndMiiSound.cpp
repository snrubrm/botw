#include "KingSystem/Sound/sndMiiSound.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/System/Timer.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::snd {

// Initialized by 0x71012ce620, followed by the four SafeString objects below.
// NON_MATCHING: the compiler places the initialization record after the strings in GlobalMerge.
static util::InitTimeInfoEx sMiiSoundInitTimeInfo;
static sead::SafeString sVoiceDirectory = "Voice/";
static sead::SafeString sCommonVoiceDirectory = "Voice/Common/";
static sead::SafeString sVoicePrefix = "NV_";
static sead::SafeString sCustomVoicePrefix = "Custom_";

Unk_710251b6f0::Unk_710251b6f0() {
    mPendingName.clear();
}

Unk_710251b6f0::~Unk_710251b6f0() {
    auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
    auto lock = sead::makeScopedLock(requests.mCS);
    requests.mQueue.erase(this);
}

void Unk_710251b6f0::sub_71012CD614() {
    if (mHandle.requestedLoad() && mHandle.isReadyOrNeedsParse() && mHandle.parseResource(nullptr)) {
        auto* resource = sead::DynamicCast<Unk_7102502978>(mHandle.getResource());
        if (mHandle.isSuccess() && resource) {
            sead::FixedSafeString<64> path;
            path.format("%s.bars", mName.cstr());
            resource->sub_7101057588(path);
            if (!mPendingName.isEmpty())
                mState = 1;
        }
    }
    Timer::update(&mTimer, 1.0f);
}

void Unk_710251b6f0::sub_71012CD7A4() {
    mTimer = 0.0f;
    _119 = false;
    _11a = false;
    mPendingName.clear();
    if (sub_71012CD880(mName, mIsCustomVoice)) {
        auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
        requests.mQueue.push(this);
        _114 = requests.mCounter;
        if (mHandle.isSuccess())
            mState = 0;
    }
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
void Unk_710251b6f0::sub_71012CD4E8(sead::Heap*, mii::UMii* umii) {
    mName.clear();
    if (umii->getPersonal().voice_type.ref() == "None") {
        mState = 2;
    } else {
        mName.appendWithFormat("NV_%s", umii->getPersonal().voice_type.ref().cstr());
        mIsCustomVoice = umii->getPersonal().voice_type.ref().startsWith(sCustomVoicePrefix);
    }
}

// NON_MATCHING: the directory strings have different GlobalMerge offsets.
bool Unk_710251b6f0::sub_71012CD880(const sead::SafeString& name, bool is_custom_voice) {
    sead::FixedSafeString<128> path;
    if (is_custom_voice) {
        const char* directory = sVoiceDirectory.cstr();
        const char* locale = sub_710105E7B4(nullptr);
        path.format("%s%s/%s.bars", directory, locale, name.cstr());
    } else {
        path.format("%s%s.bars", sCommonVoiceDirectory.cstr(), name.cstr());
    }
    res::LoadRequest request;
    request.mLoadDataAlignment = 0x1000;
    request.mRequester = "Sound";
    request._22 = true;
    request.mLaneId = 2;
    request.mArena = SoundMgr::instance()->_60->mArena;
    return mHandle.requestLoad(path, &request);
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
bool Unk_710251b6f0::sub_71012CDA58(const sead::SafeString& name) const {
    if (mState == 2)
        return false;
    return name.startsWith(sVoicePrefix);
}

void Unk_710251b6f0::requestUnloadMaybe() {
    mHandle.requestUnload();
    mState = 0;
}

Unk_710251b710::Unk_710251b710() = default;

Unk_710251b710::~Unk_710251b710() {
    mQueue.freeBuffer();
}

void Unk_710251b710::sub_71012CDF98(sead::Heap* heap) {
    mQueue.alloc(16, heap);
}

// NON_MATCHING: the list sentinel and sound name addresses are scheduled in a different order.
bool Unk_710251b710::sub_71012CE4D8(Unk_710251b6f0* sound) {
    if (sound->_114 == mCounter)
        return false;
    sound->_114 = mCounter;
    for (const auto& name : mNames) {
        if (name == sound->mName)
            return false;
    }
    return true;
}

}  // namespace ksys::snd

Unk_710251ba58::~Unk_710251ba58() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012d455c) also destroys members or bases
// this class does not declare yet.
Unk_710251bb98::~Unk_710251bb98() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012d9e94) also destroys members or bases
// this class does not declare yet.
Unk_710251bf80::~Unk_710251bf80() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da034) also destroys members or bases
// this class does not declare yet.
Unk_710251c0b8::~Unk_710251c0b8() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da1dc) also destroys members or bases
// this class does not declare yet.
Unk_710251c1f0::~Unk_710251c1f0() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da37c) also destroys members or bases
// this class does not declare yet.
Unk_710251c328::~Unk_710251c328() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da51c) also destroys members or bases
// this class does not declare yet.
Unk_710251c460::~Unk_710251c460() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da74c) also destroys members or bases
// this class does not declare yet.
Unk_710251c598::~Unk_710251c598() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012da8ec) also destroys members or bases
// this class does not declare yet.
Unk_710251c6d0::~Unk_710251c6d0() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012daa8c) also destroys members or bases
// this class does not declare yet.
Unk_710251c808::~Unk_710251c808() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012dac2c) also destroys members or bases
// this class does not declare yet.
Unk_710251c940::~Unk_710251c940() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012dadcc) also destroys members or bases
// this class does not declare yet.
Unk_710251ca78::~Unk_710251ca78() = default;

Unk_710251cbf0::~Unk_710251cbf0() = default;

Unk_710251cd38::~Unk_710251cd38() {
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
}

void Unk_710251cd38::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
Unk_710251cbf0::Unk_710251cbf0(void* arg, sead::Heap* heap) : Unk_7102518688(ElementName(), heap, false) {
    _48 = arg;
    ElementName name;
    name.mName = "grass_fire";
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

Unk_710251cbf0* ksys::act::Unk_71024dd490::sub_71012DF1A0(void* arg) {
    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical)
        return nullptr;
    sead::Heap* parent = chemical->_78;
    if (!parent)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&chemical->_28);
    auto* heap = sead::ExpHeap::tryCreate(0x2000, "ElementHolder", parent, 8,
                                          sead::Heap::cHeapDirection_Forward, true);
    if (!heap) {
        if (!(chemical->_84 & 4))
            elementEmitMaybe();
        return nullptr;
    }
    auto* element = new (parent, std::nothrow_t()) Unk_710251cbf0(arg, heap);
    if (!element) {
        elementEmitMaybe();
        heap->destroy();
        return nullptr;
    }
    if (mMaxElementHeapSize < heap->getSize())
        mMaxElementHeapSize = heap->getSize();
    if (!element->mHolder) {
        elementEmitMaybe();
        element->m32();
        delete element;
        return nullptr;
    }
    return element;
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
Unk_710251cd38::Unk_710251cd38(void* arg, sead::Heap* heap) : Unk_7102518688(ElementName(), heap, false) {
    _48 = arg;
    ElementName name;
    name.mName = "grass_fire_warm";
    name._28 = 2;
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

Unk_710251cd38* ksys::act::Unk_71024dd490::sub_71012DF384(void* arg) {
    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical)
        return nullptr;
    sead::Heap* parent = chemical->_78;
    if (!parent)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&chemical->_28);
    auto* heap = sead::ExpHeap::tryCreate(0x2000, "ElementHolder", parent, 8,
                                          sead::Heap::cHeapDirection_Forward, true);
    if (!heap) {
        if (!(chemical->_84 & 4))
            elementEmitMaybe();
        return nullptr;
    }
    auto* element = new (parent, std::nothrow_t()) Unk_710251cd38(arg, heap);
    if (!element) {
        elementEmitMaybe();
        heap->destroy();
        return nullptr;
    }
    if (mMaxElementHeapSize < heap->getSize())
        mMaxElementHeapSize = heap->getSize();
    if (!element->mHolder) {
        elementEmitMaybe();
        element->m32();
        delete element;
        return nullptr;
    }
    return element;
}

// NON_MATCHING: placeholder destructor; the original (0x71012e86e8) also destroys members or bases
// this class does not declare yet.
Unk_710251cf40::~Unk_710251cf40() = default;

Unk_710251b810::~Unk_710251b810() = default;

Unk_710251b888::~Unk_710251b888() = default;

Unk_710251b900::~Unk_710251b900() = default;

Unk_710251b978::~Unk_710251b978() = default;

Unk_710251b9f0::~Unk_710251b9f0() = default;

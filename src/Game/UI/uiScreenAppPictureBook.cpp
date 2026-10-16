#include "Game/UI/uiScreens.h"
#include <limits>
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// Initialized as two FLT_MAX components by native 9384e4; read as the
// optional layout size by 93bb48 and copied by both parameter lifetime bodies.
KSYS_VISIBILITY_HIDDEN sead::Vector2f sUnk_71025D5CE8{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max()};

// 0x7100938c94
// NON_MATCHING: Vector2 component copies differ (the original copies sUnk_71025D5CE8 as one 64-bit value).
ScreenAppPictureBookEntry::Params::Params() {
    _28.clear();
    _80.clear();
    _d8.clear();
    _130.format("N_PartsSize_00");
    _188.clear();
    _1e0.clear();
    _238 = 0;
    _240.clear();
    _298 = 3;
    _29c = 0;
    _2a0 = 1;
    _2a4 = 1;
    _2a8 = sUnk_71025D5CE8;
    _2c8 = false;
    _2c9 = false;
    _2ca = true;
    _2cb = true;
    _2b0 = sead::Vector2f::zero;
    _2b8 = sead::Vector2f::zero;
    _2c0 = sead::Vector2f::zero;
    _2cc = false;
    _2cd = true;
    _2d0 = nullptr;
}

// 0x7100938e9c
// NON_MATCHING: Vector2 component copies differ (the original copies sUnk_71025D5CE8 as one 64-bit value).
ScreenAppPictureBookEntry::Params::~Params() {
    _28.clear();
    _80.clear();
    _d8.clear();
    _130.clear();
    _188.clear();
    _1e0.clear();
    _238 = 0;
    _240.clear();
    _298 = 0;
    _29c = -1;
    _2a0 = -1;
    _2a4 = -1;
    _2a8 = sUnk_71025D5CE8;
    _2b0 = sead::Vector2f::zero;
    _2b8 = sead::Vector2f::zero;
    _2c0 = sead::Vector2f::zero;
    _2d0 = nullptr;
    _2cc = false;
    _2cd = false;
    _2c8 = false;
    _2c9 = false;
    _2ca = false;
    _2cb = false;
}

// 0x710093a13c / 0x710093a238
// NON_MATCHING: D1 has Vector2 component-copy differences; D0 retains a D1 call
// rather than inlining the lifetime body and dropping dead parameter resets.
ScreenAppPictureBookEntry::~ScreenAppPictureBookEntry() {
    if (mIconControl) {
        delete mIconControl;
        mIconControl = nullptr;
    }
    if (mPageControl) {
        delete mPageControl;
        mPageControl = nullptr;
    }
    if (mGuideControl) {
        delete mGuideControl;
        mGuideControl = nullptr;
    }
}

void ScreenAppPictureBookUnk::sub_7100943E80(sead::Heap* heap, s32 count) {
    if (count < 1)
        return;
    mEntries.allocBuffer(count, heap);
    for (s32 i = 0; i < count; ++i)
        mEntries.pushBack(new (heap, 8) ScreenAppPictureBookEntry);
}

// NON_MATCHING: empty-string comparison loads and page-count branches are scheduled differently.
// 0x710093ac7c
void ScreenAppPictureBookEntry::sub_710093AC7C() {
    sub_710093BB48();
    sub_710093BDFC();
    if (mParams._d8.isEmpty()) {
        _2f4 = mParams._29c;
    } else if (mParams._29c == 0) {
        _2f4 = 0;
    } else {
        const s32 count = mParams._2a0 * mParams._2a4;
        _2f4 = mParams._29c < count ? 1 : sead::Mathf::ceil(f32(mParams._29c) / f32(count));
    }
    sub_710093C040();
    if (mIconControl)
        mIconControl->sub_7100988010(mParams._238);
    if (mPageControl)
        mPageControl->sub_7100936A28(_2f4);
    if (mGuideControl)
        mGuideControl->sub_7100936BCC(mController->_40[2], mController->_40[3]);
}

// NON_MATCHING: vector copies and bound-check branches are scheduled differently.
// 0x710093ae60
void ScreenAppPictureBookEntry::sub_710093AE60(const sead::Vector2f& position) {
    const auto low = position + _368;
    const auto high = position + _370;
    switch (mController->mConfig._60) {
    case 0:
        _378 = low.y > 0.0f ? low : high.y < 0.0f ? high : sead::Vector2f::zero;
        break;
    case 1:
        _378 = low.y < 0.0f ? low : high.y > 0.0f ? high : sead::Vector2f::zero;
        break;
    case 2:
        _378 = low.x < 0.0f ? low : high.x > 0.0f ? high : sead::Vector2f::zero;
        break;
    case 3:
        _378 = low.x > 0.0f ? low : high.x < 0.0f ? high : sead::Vector2f::zero;
        break;
    }
    // Native 93af30..6c uses ordered lower/upper tests: unordered values
    // choose the upper bound, unlike Mathf::clamp's unordered pass-through.
    _380.x = low.x < _358.getMin().x ? _358.getMin().x :
             low.x <= _358.getMax().x ? low.x : _358.getMax().x;
    _380.y = low.y < _358.getMin().y ? _358.getMin().y :
             low.y <= _358.getMax().y ? low.y : _358.getMax().y;
}

// 0x710093af74
void ScreenAppPictureBookEntry::sub_710093AF74() {
    if (!mController)
        return;
    if (mIconControl) {
        if (_38d) {
            mIconControl->sub_7100988060(true);
            return;
        }
        if (mIconControl->sub_710098807C()) {
            if (_2f4 > 0)
                mIconControl->sub_7100988060(false);
        } else if (!mIconControl->sub_710098807C() && _2f4 < 1) {
            mIconControl->sub_7100988060(true);
        }
        if (mIconControl->sub_710098807C())
            return;
    }
    if (mPageControl) {
        if (mController->_2e8 == _2f0)
            mPageControl->sub_7100936A7C(mController->_2f0);
        else
            mPageControl->sub_7100936AD8();
    }
    if (mIconControl) {
        if (!mIconControl->sub_7100988040()) {
            if (mController->_2e8 == _2f0)
                mIconControl->sub_710098802C(true);
        } else if (mIconControl->sub_7100988040() && mController->_2e8 != _2f0) {
            mIconControl->sub_710098802C(false);
        }
        if (!mIconControl->sub_7100988040())
            return;
    }
    if (mGuideControl) {
        if (mController)
            mGuideControl->sub_7100936BD4((mController->_30 & 4) != 0,
                                         (mController->_30 & 8) != 0);
        else
            mGuideControl->sub_7100936BD4(false, false);
    }
}

// 0x710093bb48
// NON_MATCHING: case 0 tests _d0 == 3 before _d0 == 1 and does not share the madd tail; the empty-string path
// stores _38.y before the shared tail.
void ScreenAppPictureBookEntry::sub_710093BB48() {
    if (!mGroupList)
        return;

    if (mParams._d8.isEmpty()) {
        if (mParams._2a8.x != std::numeric_limits<f32>::max())
            mGroupList->_38.x = mParams._2a8.x;
        if (mParams._2a8.y != std::numeric_limits<f32>::max())
            mGroupList->_38.y = mParams._2a8.y;
    } else {
        Unk_7102474f10** it = mGroupList->mUnits.data();
        Unk_7102474f10** end = it + mGroupList->mUnits.size();
        for (; it != end; ++it) {
            Unk_7102474f10* group = *it;
            for (s32 i = 0; i < group->mUnits.size(); ++i) {
                s32 index;
                switch (mController->mConfig._64) {
                case 0:
                    switch (mController->mConfig._68) {
                    case 1:
                        index = (i % mParams._2a4) * mParams._2a0 + i / mParams._2a4;
                        break;
                    case 3:
                        index = i;
                        break;
                    default:
                        continue;
                    }
                    break;
                case 1:
                    switch (mController->mConfig._68) {
                    case 3:
                        index = (mParams._2a0 - 1 - i / mParams._2a4) * mParams._2a4 + i % mParams._2a4;
                        break;
                    case 0:
                        index = (i % mParams._2a4) * mParams._2a0 + (mParams._2a0 - 1 - i / mParams._2a4);
                        break;
                    default:
                        continue;
                    }
                    break;
                case 2:
                    switch (mController->mConfig._68) {
                    case 2:
                        index = i + mParams._2a4 - 2 * (i % mParams._2a4) - 1;
                        break;
                    case 1:
                        index = (mParams._2a4 - 1 - i % mParams._2a4) * mParams._2a0 + i / mParams._2a4;
                        break;
                    default:
                        continue;
                    }
                    break;
                case 3:
                    switch (mController->mConfig._68) {
                    case 2:
                        index = (mParams._2a0 - 1 - i / mParams._2a4) * mParams._2a4 +
                                (mParams._2a4 - 1 - i % mParams._2a4);
                        break;
                    case 0:
                        index = (mParams._2a4 - 1 - i % mParams._2a4) * mParams._2a0 +
                                (mParams._2a0 - 1 - i / mParams._2a4);
                        break;
                    default:
                        continue;
                    }
                    break;
                default:
                    continue;
                }
                group->mUnits.unsafeAt(i)->_3c = index;
            }
        }

        if (mParams._2a4 > 1) {
            mGroupList->_38.x = mGroupList->_20.x - mParams._2a4 * mGroupList->_30.x;
            mGroupList->_38.x /= mParams._2a4 - 1;
        } else {
            mGroupList->_38.x = 0.0f;
        }
        if (mParams._2a0 > 1) {
            mGroupList->_38.y = mGroupList->_20.y - mParams._2a0 * mGroupList->_30.y;
            mGroupList->_38.y /= mParams._2a0 - 1;
        } else {
            mGroupList->_38.y = 0.0f;
        }
    }

    mGroupList->_40.x = mGroupList->_30.x + mGroupList->_38.x;
    mGroupList->_40.y = mGroupList->_30.y + mGroupList->_38.y;
}

// 0x710093bdfc
// NON_MATCHING: register allocation of the center vector and scheduling of the _318 / _308 sizes.
void ScreenAppPictureBookEntry::sub_710093BDFC() {
    const sead::Vector2f& center = sead::Vector2f::zero;
    _2f8.setFromCenterAndXY(center, 0.0f, 0.0f);
    _308.setFromCenterAndXY(center, 0.0f, 0.0f);
    _318.setFromCenterAndXY(center, 0.0f, 0.0f);
    _328.setFromCenterAndXY(center, 0.0f, 0.0f);

    auto* list = mGroupList;
    if (!list)
        return;

    if (mParams._2a8.x == std::numeric_limits<f32>::max())
        mParams._2a8.x = list->_38.x;
    if (mParams._2a8.y == std::numeric_limits<f32>::max())
        mParams._2a8.y = list->_38.y;

    const s32 count = sead::Mathi::max(mParams._298 - 2, 1);
    f32 width = list->_20.x;
    f32 height = list->_20.y;
    for (s32 i = 1; i < count; ++i) {
        width += list->_20.x + mParams._2a8.x;
        height += list->_20.y + mParams._2a8.y;
    }
    _2f8.setFromCenterAndXY(center, width, height);

    const sead::Vector2f page_size = mParams._2a8 + list->_30;
    const sead::Vector2f margin(sead::Mathf::max(mParams._2a8.x, 0.0f) + 0.001f,
                                sead::Mathf::max(mParams._2a8.y, 0.0f) + 0.001f);
    const f32 box_width = _2f8.getSizeX();
    const f32 box_height = _2f8.getSizeY();
    _318.setFromCenterAndXY(center, mParams._2c0.x + margin.x + box_width,
                            mParams._2c0.y + margin.y + box_height);
    _308.setFromCenterAndXY(center, mParams._2b8.x + (page_size.x + page_size.x) + box_width,
                            mParams._2b8.y + (page_size.y + page_size.y) + box_height);
    _328.setFromCenterAndXY(center, box_width - list->_30.x, box_height - list->_30.y);
}

// 0x710093c040
// NON_MATCHING: the original copies the zero vector into _338 / _340 as one 64-bit value; scheduling of the
// _348 size.
void ScreenAppPictureBookEntry::sub_710093C040() {
    auto* list = mGroupList;
    if (!list || !mController)
        return;

    const sead::Vector2f& center = sead::Vector2f::zero;
    _338 = center;
    _340 = center;
    _348.setFromCenterAndXY(center, 0.0f, 0.0f);
    _358.setFromCenterAndXY(center, 0.0f, 0.0f);

    const s32 pages = _2f4;
    const s32 gaps = pages - 1;
    if (gaps < 0)
        return;

    if (mController->mConfig._58 == 0) {
        _338.x = pages * list->_20.x + gaps * mParams._2a8.x;
        _338.y = list->_20.y;
    } else if (mController->mConfig._58 == 1) {
        _338.x = list->_20.x;
        _338.y = list->_20.y * pages + mParams._2a8.y * gaps;
    }

    if (pages > 1) {
        if (mController->mConfig._58 == 0) {
            _340.x = list->_20.x + mParams._2a8.x;
            _340.y = 0.0f;
        } else if (mController->mConfig._58 == 1) {
            _340.x = 0.0f;
            _340.y = list->_20.y + mParams._2a8.y;
        }
    }

    const f32 width = 2 * (mParams._2a8.x + list->_20.x);
    const f32 height = 2 * (mParams._2a8.y + list->_20.y);
    _348.setFromCenterAndXY(center, mParams._2b0.x + width + _2f8.getSizeX(),
                            mParams._2b0.y + height + _2f8.getSizeY());

    sead::Vector2f scroll = center;
    switch (mController->mConfig._60) {
    case 0:
        scroll.y = -(_340.y * gaps);
        break;
    case 1:
        scroll.y = _340.y * gaps;
        break;
    case 2:
        scroll.x = _340.x * gaps;
        break;
    case 3:
        scroll.x = -(_340.x * gaps);
        break;
    }
    _358.set(scroll.x, scroll.y, 0.0f, 0.0f);
}

// 0x710093a500
void ScreenAppPictureBookEntry::sub_710093A500(sead::Heap* heap) {
    const s32 count = mParams._298;
    if (count > 0) {
        mRecords.allocBuffer(count, heap, 8);
        for (s32 i = 0; i < count; ++i)
            mRecords.pushBack(new (heap, 8) PictureBookGroupRecord{0, sead::Vector2f::zero, -1});
    }
    sub_710093A5C0(heap);
    sub_710093A758();
    sub_710093AC7C();
}

// 0x710093a5c0
void ScreenAppPictureBookEntry::sub_710093A5C0(sead::Heap* heap) {
    eui::LayoutEx* page = nullptr;
    eui::LayoutEx* guide = nullptr;
    if (!mParams._188.isEmpty()) {
        auto* button = nn::font::DynamicCast<eui::UniteButton>(
            mController->mScreen->sub_7100A480B4(mParams._188));
        if (button) {
            mIconControl = new (heap, 8) Unk_7102477468;
            if (mIconControl)
                mIconControl->sub_7100987FBC(button);
            page = button->mLayout->findPartsLayout("Pa_Scroll_00");
            guide = button->mLayout->findPartsLayout("Pa_Rstick_00");
        }
    }
    if (!mParams._1e0.isEmpty()) {
        // Native93A6C8..D0 treats this optional named pane as Parts and uses
        // its established layout link at +f0, without a runtime type test.
        auto* parts = static_cast<nn::ui2d::Parts*>(
            mController->mScreen->sub_7100A48104(mParams._1e0, nullptr));
        if (parts)
            page = static_cast<eui::LayoutEx*>(parts->mPartsLayoutLink.layout);
    }
    if (page) {
        mPageControl = new (heap, 8) Unk_7102474c28;
        if (mPageControl)
            mPageControl->sub_7100936998(page);
    }
    if (guide) {
        mGuideControl = new (heap, 8) Unk_7102474c48;
        if (mGuideControl)
            mGuideControl->sub_7100936B18(guide);
    }
}

// 0x7100939f68 (D1) / 0x7100939fb8 (D0)
Unk_7102474f10::~Unk_7102474f10() {
    _8 = nullptr;
    mEntry = nullptr;
    mController = nullptr;
    mUnits.clear();
    _30 = nullptr;
    mRecord = nullptr;
    delete _40;
    _40 = nullptr;
}

// 0x710093a2f8
void ScreenAppPictureBookEntry::sub_710093A2F8(sead::Heap* heap,
                                               sead::PtrArray<PictureBookGroupList>* lists) {
    sead::FixedSafeString<64> path;
    if (mParams._28.isEmpty())
        path.format("%s%02d", mParams._80.cstr(), 0);
    else
        path.format("%s/%s%02d", mParams._28.cstr(), mParams._80.cstr(), 0);

    eui::PartsEx* parts = eui::sub_7100945088(mController->mScreen->sub_7100A48104(path, nullptr));
    if (!parts || !parts->mPartsLayoutLink.layout)
        return;

    for (PictureBookGroupList& list : *lists) {
        if (list.mUnits.size() > 0 && list.mUnits(0)->_8 == parts->mPartsLayoutLink.layout) {
            mGroupList = &list;
            return;
        }
    }
    lists->pushBack(new (heap) PictureBookGroupList);
    mGroupList = lists->back();
}

// 0x710093c24c
void ScreenAppPictureBookEntry::sub_710093C24C(sead::Heap* heap) {
    if (!mGroupList)
        return;
    s32 count = mParams._298;
    if (count <= 0)
        return;
    mGroupList->mUnits.allocBuffer(count, heap);
    do {
        mGroupList->mUnits.pushBack(new (heap) Unk_7102474f10);
    } while (--count != 0);
}

// 0x710093c304
void ScreenAppPictureBookEntry::sub_710093C304(sead::Heap* heap) {
    if (!mGroupList)
        return;
    const s32 count = mGroupList->mUnits.size();
    for (s32 i = 0; i < count; ++i) {
        eui::LayoutEx* layout = sub_710093C48C(heap, i);
        if (!layout)
            continue;
        mGroupList->mUnits(i)->_8 = layout;
        mGroupList->mUnits(i)->mEntry = this;
        mGroupList->mUnits(i)->mController = mController;
        Unk_7102474f10* group = mGroupList->mUnits(i);
        ScreenAppPictureBookEntry* entry = group->mEntry;
        if (!entry->mParams._240.isEmpty() && group->_8) {
            group->_30 = group->_8->tryCreateAnimatorAuto(entry->mParams._240.cstr(), true);
            if (group->_30)
                group->_30->StopAtMin();
            if (group->_8)
                group->_8->startAnimCloseImpl_(false, true);
        }
        mGroupList->mUnits(i)->mEntry = nullptr;
    }
    for (s32 i = 0; i < count; ++i) {
        if (mGroupList->mUnits(i)->_8 && mParams._2d0)
            mGroupList->mUnits(i)->_40 = mParams._2d0->create(heap, i);
    }
}

// NON_MATCHING: the original copies Vector2f::zero into _34 as one 64-bit value (ours: two floats), which
// shifts the registers after it
// 0x710093c660
void ScreenAppPictureBookEntry::sub_710093C660() {
    if (!mGroupList)
        return;
    sead::FixedSafeString<64> name;
    if (mParams._d8.isEmpty()) {
        for (auto it = mGroupList->mUnits.begin(), end = mGroupList->mUnits.end(); it != end; ++it) {
            if (it->mUnits.size() < 1 || !it->_8)
                continue;
            it->mUnits(0)->_8 = it->_8;
            it->mUnits(0)->_10 =
                static_cast<eui::AnimButton*>(mController->mScreen->sub_7100A4810C(it->_8));
            if (it->mUnits(0)->_10) {
                mController->mScreen->sub_7100A48258(it->mUnits.front(), it->mUnits(0)->_10);
                it->mUnits(0)->_28 =
                    mController->mScreen->findBoxCursorNodeByButton(it->mUnits(0)->_10);
            } else {
                it->mUnits(0)->_28 = nullptr;
            }
            it->mUnits(0)->_18 = &*it;
            it->mUnits(0)->_20 = mController;
            it->mUnits(0)->_34 = sead::Vector2f::zero;
            it->mUnits(0)->_3c = 0;
            it->mUnits(0)->_40 = 0;
            it->mUnits(0)->_44 = 0;
        }
    } else {
        for (auto it = mGroupList->mUnits.begin(), end = mGroupList->mUnits.end(); it != end; ++it) {
            if (it->mUnits.size() < 1 || !it->_8)
                continue;
            for (s32 row = 0; row < mParams._2a0; ++row) {
                for (s32 column = 0; column < mParams._2a4; ++column) {
                    const s32 index = column + row * mParams._2a4;
                    name.format("%s%02d", mParams._d8.cstr(), index);
                    eui::LayoutEx* layout = it->_8->findPartsLayout(name.cstr());
                    if (!layout)
                        continue;
                    it->mUnits(index)->_8 = layout;
                    it->mUnits(index)->_10 =
                        static_cast<eui::AnimButton*>(mController->mScreen->sub_7100A4810C(layout));
                    if (it->mUnits(index)->_10) {
                        mController->mScreen->sub_7100A48258(it->mUnits[index],
                                                             it->mUnits(index)->_10);
                        it->mUnits(index)->_28 = mController->mScreen->findBoxCursorNodeByButton(
                            it->mUnits(index)->_10);
                    }
                    it->mUnits(index)->_18 = &*it;
                    it->mUnits(index)->_20 = mController;
                    it->mUnits(index)->_34 = sead::Vector2f::zero;
                    it->mUnits(index)->_3c = -1;
                    it->mUnits(index)->_40 = row;
                    it->mUnits(index)->_44 = column;
                }
            }
        }
    }
}

// NON_MATCHING: the original copies _2a8 as one 64-bit value (ours: two floats, like the other vectors)
// 0x7100938f28
void ScreenAppPictureBookEntry::Params::sub_7100938F28(const Params& other) {
    _28 = other._28;
    _80 = other._80;
    _d8 = other._d8;
    _130 = other._130;
    _188 = other._188;
    _1e0 = other._1e0;
    _238 = other._238;
    _240 = other._240;
    _298 = other._298;
    _29c = other._29c;
    _2a0 = other._2a0;
    _2a4 = other._2a4;
    _2a8 = other._2a8;
    _2b0 = other._2b0;
    _2b8 = other._2b8;
    _2c0 = other._2c0;
    _2c8 = other._2c8;
    _2c9 = other._2c9;
    _2ca = other._2ca;
    _2cb = other._2cb;
    _2cc = other._2cc;
    _2cd = other._2cd;
    _2d0 = other._2d0;
}

// NON_MATCHING: the original zeroes the strings with one memset before constructing them (value-initialised;
// ours has none) and schedules the stores differently
// 0x710093952c
PictureBookListConfig::PictureBookListConfig() {
    _0.clear();
    _74 = {0.28f, 300.0f};
    _7c = 0.1f;
    _58 = 0;
    _5c = 0;
    _64 = 0;
    _68 = 3;
    _60 = 3;
    _6c = {0, 0};
    _a0 = 0x4000000;
    _a4 = 0x8000000;
    _80 = {0, 0};
    _88 = 0;
    _8c = 0;
    _a8 = 0;
    _90 = 0x2000;
    _94 = 0x4000;
    _98 = 0;
    _9c = 0;
    mStrings._b0.clear();
    mStrings._108.clear();
    mStrings._160.clear();
    mStrings._1b8.clear();
    _210 = true;
    _218 = false;
    _214 = 30;
}

// 0x71009396ec
void PictureBookListConfig::sub_71009396EC() {
    _0.clear();
    _58 = -1;
    _5c = 0;
    _60 = -1;
    _64 = -1;
    _68 = -1;
    _6c = {0, 0};
    _74 = {0, 0};
    _7c = 0;
    _80 = {0, 0};
    _88 = 0;
    _8c = 0;
    _90 = 0;
    _94 = 0;
    _98 = 0;
    _9c = 0;
    _a0 = 0;
    _a4 = 0;
    _a8 = 0;
    mStrings._b0.clear();
    mStrings._108.clear();
    mStrings._160.clear();
    mStrings._1b8.clear();
    _210 = false;
    _218 = false;
    _214 = 30;
}

// NON_MATCHING: the original copies _6c, _74 and _80 as 64-bit values (ours: float by float)
// 0x7100939764
void PictureBookListConfig::sub_7100939764(const PictureBookListConfig& other) {
    _0 = other._0;
    _58 = other._58;
    _5c = other._5c;
    _60 = other._60;
    _64 = other._64;
    _68 = other._68;
    _6c = other._6c;
    _7c = other._7c;
    _74 = other._74;
    _80 = other._80;
    _88 = other._88;
    _8c = other._8c;
    _90 = other._90;
    _94 = other._94;
    _98 = other._98;
    _9c = other._9c;
    _a0 = other._a0;
    _a4 = other._a4;
    _a8 = other._a8;
    mStrings._b0 = other.mStrings._b0;
    mStrings._108 = other.mStrings._108;
    mStrings._160 = other.mStrings._160;
    mStrings._1b8 = other.mStrings._1b8;
    _210 = other._210;
    _214 = other._214;
    _218 = other._218;
}

// 0x7100943fe0
void ScreenAppPictureBookUnk::sub_7100943FE0(sead::Heap* heap, s32 count) {
    if (count > 0)
        mGroupLists.allocBuffer(count, heap);
}

// NON_MATCHING: the not-found -1 goes through w2 instead of w1 (register allocation)
// 0x710093e42c
bool ScreenAppPictureBookUnk::sub_710093E42C(s32 index, s32 mode) {
    s32 entry_index = -1;
    s32 entry = -1;
    if (mEntries.data()) {
        const s32 count = mEntries.size();
        if (count != 0) {
            s32 rest = sead::Mathi::clamp(index, 0, _2ac - 1);
            ScreenAppPictureBookEntry** end = mEntries.data() + count;
            for (ScreenAppPictureBookEntry** p = mEntries.data(); p != end; ++p) {
                ScreenAppPictureBookEntry* e = *p;
                if (e) {
                    const s32 next = rest - e->mParams._29c;
                    if (next < 0) {
                        entry_index = rest;
                        entry = e->_2f0;
                        break;
                    }
                    rest = next;
                }
            }
        }
    }
    return sub_710093DAFC(entry_index, entry, mode);
}

// 0x710093e428
u32 ScreenAppPictureBookUnk::sub_710093E428(s32 index) {
    return sub_710093E784(index);
}

// NON_MATCHING: only the order of the two loop initialisers (`mov w9, wzr` before `mov x10, xzr` in the original)
// 0x710093e900
u32 ScreenAppPictureBookUnk::sub_710093E900(s32 base, s32 count) {
    s32 sum = 0;
    if (!mEntries.data())
        return sub_710093E784(0);
    for (s32 i = 0; i < count; ++i) {
        if (mEntries.size() > static_cast<u64>(i) && mEntries.data()[i])
            sum += mEntries.data()[i]->mParams._29c;
    }
    return sub_710093E784(sum + base);
}

// 0x710093f10c
void ScreenAppPictureBookUnk::sub_710093F10C(s32 index, s32* out_index, s32* out_value) {
    if (!mEntries.data())
        return;
    const s32 count = mEntries.size();
    if (count == 0)
        return;
    ScreenAppPictureBookEntry** end = mEntries.data() + count;
    for (ScreenAppPictureBookEntry** p = mEntries.data(); p != end; ++p) {
        ScreenAppPictureBookEntry* entry = *p;
        if (entry) {
            const s32 rest = index - entry->mParams._29c;
            if (rest < 0) {
                *out_value = entry->_2f0;
                *out_index = index;
                return;
            }
            index = rest;
        }
    }
}

// NON_MATCHING: the operands of the running-sum add are swapped (one instruction)
// 0x71009418d0
void ScreenAppPictureBookUnk::sub_71009418D0(f32 delta, s32 mode) {
    if (sead::Mathf::equalsEpsilon(0.0f, delta))
        return;
    switch (mConfig._58) {
    case 0:
        _2d0.x += delta;
        break;
    case 1:
        _2d0.y += delta;
        break;
    }
    sub_7100941C30(_2d0, &_2f0, &_2e8);
    const s32 index = _2f0;
    const s32 entry_count = _2e8;
    _2dc = 0;
    if (mEntries.data()) {
        for (s32 i = 0; i < entry_count; ++i) {
            if (ScreenAppPictureBookEntry* entry = mEntries.at(i))
                _2dc += entry->_2f4;
        }
        _2dc += index;
    }
    _338 = mode;
    if (mode == 1 || mode == 2)
        sub_7100941D70(mode != 2);
}

// NON_MATCHING: the original adds the item offset first and copies Vector2f::zero as one 64-bit value; register
// allocation
// 0x7100944bc4
sead::Vector2f ScreenAppPictureBookUnk::sub_7100944BC4(s32 index, s32 col, s32 row, s32 entry_index) {
    sead::Vector2f pos = sead::Vector2f::zero;
    if (entry_index < 0 || mEntries.size() < 1 || entry_index >= _2a8)
        return pos;
    sub_71009419E0(index, entry_index, &pos);
    ScreenAppPictureBookEntry* entry = mEntries(entry_index);
    PictureBookGroupList* list = entry->mGroupList;
    if (list->mUnits.size() >= 1) {
        const s32 count = entry->mParams._2a0 * entry->mParams._2a4;
        for (s32 i = 0; i < count; ++i) {
            Unk_7102474e38* unit = list->mUnits(0)->mUnits.at(i);
            if (unit->_40 == col && unit->_44 == row) {
                return list->_28 + _304 + (pos + unit->_34 + _2c0);
            }
        }
    }
    pos = sead::Vector2f::zero;
    return pos;
}

// 0x7100944d18
void ScreenAppPictureBookUnk::sub_7100944D18(const ScreenAppPictureBookEntry* entry, s32 index, s32* x,
                                             s32* y) const {
    const s32 cols = entry->mParams._2a0;
    const s32 rows = entry->mParams._2a4;
    switch (mConfig._64) {
    case 0:
        if (mConfig._68 == 3) {
            *x = index / rows;
            *y = index % rows;
        } else if (mConfig._68 == 1) {
            *x = index % cols;
            *y = index / cols;
        }
        break;
    case 1:
        if (mConfig._68 == 3) {
            *x = cols - 1 - index / rows;
            *y = index % rows;
        } else if (mConfig._68 == 0) {
            *x = cols - 1 - index % cols;
            *y = index / cols;
        }
        break;
    case 2:
        if (mConfig._68 == 2) {
            *x = index / rows;
            *y = rows - 1 - index % rows;
        } else if (mConfig._68 == 1) {
            *x = index % cols;
            *y = rows - 1 - index / cols;
        }
        break;
    case 3:
        if (mConfig._68 == 2) {
            *x = cols - 1 - index / rows;
            *y = rows - 1 - index % rows;
        } else if (mConfig._68 == 0) {
            *x = cols - 1 - index % cols;
            *y = rows - 1 - index / cols;
        }
        break;
    }
}

// NON_MATCHING: the original branches on one fccmp chain for isInside; ours materialises the four compares
// 0x7100941c30
void ScreenAppPictureBookUnk::sub_7100941C30(const sead::Vector2f& offset, s32* out_index, s32* out_entry) {
    sead::Vector2f pos = sead::Vector2f::zero;
    for (s32 e = 0; e < _2a8; ++e) {
        if (mEntries(e)->_38d)
            continue;
        const s32 count = mEntries(e)->_2f4;
        for (s32 i = 0; i < count; ++i) {
            sub_71009419E0(i, e, &pos);
            pos += offset;
            ScreenAppPictureBookEntry* entry = mEntries(e);
            const sead::Vector2f size = entry->mGroupList->_20 + entry->mParams._2a8;
            sead::BoundBox2f box;
            box.setFromCenterAndXY(sead::Vector2f::zero, size.x, size.y);
            if (box.isInside(pos)) {
                *out_index = i;
                *out_entry = e;
                return;
            }
        }
    }
}

// NON_MATCHING: the original tests each axis with one fcmp / fccmp pair (both bounds computed first); ours
// branches between the two compares
// 0x710093b9f4
void ScreenAppPictureBookEntry::sub_710093B9F4(PictureBookGroupRecord* record) {
    if (_38d)
        return;
    if (record->_c < 0)
        return;
    const f32 x = _378.x + record->mPosition.x;
    const f32 half_width = mGroupList->_20.x * 0.5f;
    const f32 left = x - half_width;
    const f32 right = x + half_width;
    if (_308.getMin().x <= right && left <= _308.getMax().x) {
        const f32 y = _378.y + record->mPosition.y;
        const f32 half_height = mGroupList->_20.y * 0.5f;
        const f32 top = y + half_height;
        const f32 bottom = y - half_height;
        if (_308.getMin().y <= top && bottom <= _308.getMax().y)
            return;
    }
    if (!(record->_0 & 1))
        return;
    Unk_7102474f10* group = nullptr;
    for (auto& it : mGroupList->mUnits) {
        if (it.mRecord == record) {
            group = &it;
            break;
        }
    }
    if (!group)
        return;
    record->_0 &= ~1u;
    if (auto* item = group->_40) {
        item->m5();
        item->_8 = nullptr;
    }
    const s32 count = group->mUnits.size();
    for (s32 i = 0; i < count; ++i) {
        Unk_7102474e38* unit = group->mUnits(i);
        unit->_30 = 0;
        unit->_8->mPane->SetVisible(false);
        if (unit->_10)
            unit->_10->setFlag10(false);
    }
    group->mEntry = nullptr;
    group->mRecord = nullptr;
}

// 0x710093ad60
void ScreenAppPictureBookEntry::sub_710093AD60(const sead::Vector2f& position) {
    sub_710093AE60(position);
    if (mController) {
        switch (mController->mConfig._58) {
        case 0:
            _388 = sead::Mathf::floor((sead::Mathf::abs(_380.x) + _340.x * 0.5f) / _340.x);
            break;
        case 1:
            _388 = sead::Mathf::floor((sead::Mathf::abs(_380.y) + _340.y * 0.5f) / _340.y);
            break;
        }
    }
    sub_710093AF74();
    for (s32 i = 0; i < sead::Mathi::min(mParams._298, _2f4); ++i)
        sub_710093B0D8(mRecords.at(i));
}

// NON_MATCHING: register allocation (the two zero results of the search and the clamp temporaries)
// 0x7100941354
f32 ScreenAppPictureBookUnk::sub_7100941354(s32 index) {
    s32 item = 0;
    s32 entry_value = 0;
    if (mEntries.data() && mEntries.size() != 0) {
        ScreenAppPictureBookEntry** end = mEntries.data() + mEntries.size();
        for (ScreenAppPictureBookEntry** p = mEntries.data(); p != end; ++p) {
            ScreenAppPictureBookEntry* entry = *p;
            if (entry) {
                const s32 rest = index - entry->_2f4;
                if (rest < 0) {
                    item = index;
                    entry_value = entry->_2f0;
                    break;
                }
                index = rest;
            }
        }
    }
    sead::Vector2f pos = sead::Vector2f::zero;
    sub_71009419E0(item, entry_value, &pos);
    pos.x = sead::Mathf::clamp(-pos.x, _2b0.getMin().x, _2b0.getMax().x);
    pos.y = sead::Mathf::clamp(-pos.y, _2b0.getMin().y, _2b0.getMax().y);
    switch (mConfig._58) {
    case 0:
        return _2d0.x - pos.x;
    case 1:
        return _2d0.y - pos.y;
    default:
        return 0;
    }
}

// 0x710093a008
void Unk_7102474f10::sub_710093A008(s32 mode) {
    switch (mode) {
    case 3:
        if (_30)
            _30->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
        else if (_8)
            _8->sub_7100BDDE7C(false, 0, true);
        break;
    case 4:
        if (_30)
            _30->PlayAuto(1.0f);
        else if (_8)
            _8->sub_7100BDDE7C(false, 0, true);
        break;
    case 5:
        if (_30)
            _30->StopAtMax();
        else if (_8)
            _8->sub_7100BDDE7C(false, 1, true);
        break;
    }
}

// 0x710093a0a8
void Unk_7102474f10::sub_710093A0A8(s32 mode) {
    switch (mode) {
    case 0:
        if (_30)
            _30->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
        else if (_8)
            _8->startAnimCloseImpl_(false, false);
        break;
    case 1:
        if (_30)
            _30->PlayAuto(-1.0f);
        else if (_8)
            _8->startAnimCloseImpl_(false, false);
        break;
    case 2:
        if (_30)
            _30->StopAtMin();
        else if (_8)
            _8->startAnimCloseImpl_(false, true);
        break;
    }
}

// 0x710093f594
void ScreenAppPictureBookUnk::sub_710093F594(bool flag) {
    bool old = _2c & 1;
    if (!((old ^ flag) & 1))
        return;
    u32 flags = flag ? (_2c | 1) : (_2c & ~1u);
    _2c = flags;
    _38 = nullptr;
    if (flags & 1) {
        sub_710093F670();
    } else {
        if (PictureBookItem* item = _318) {
            if (item->_10) {
                item->_10 = false;
                item->m9();
            }
            _318 = nullptr;
        }
    }
    sub_710093F7F8(flag & 1);
    sub_710093F924(true);
    if (!flag) {
        ScreenEx* screen = mScreen;
        eui::BoxCursorNode* node = screen->mActiveCursorNode;
        if (node == nullptr)
            return;
        if (sub_710093FBF0(node) < 0)
            return;
        screen->mActiveCursorNode = nullptr;
        return;
    }
    if (old)
        return;
    sub_710093E784(_310);
}

// 0x710093f670
// NON_MATCHING: lowering only (all loads/stores/calls/branches match, including both loop
// skeletons with their reloads, the record/match logic and the select/deselect truth table).
// Four small diffs remain: _2e4 is loaded before mEntries.size() (ours loads them in compare order); the
// else-path null check is mov+cmp+beq while ours uses cbz; the select block loads _318 after the
// _10 store while ours loads it before; (all scheduling/codegen-shape, no semantic difference).
void ScreenAppPictureBookUnk::sub_710093F670() {
    if ((_2c & 1) == 0)
        return;
    u32 n = mGroupLists.size();
    if (s32(n) < 1)
        return;
    u64 count298 = n;
    u32 lim = n;
    u64 i = 0;
    while (true) {
        if (lim > i) {
            PictureBookGroupList* group = mGroupLists.data()[i];
            if (group && group->mUnits.size() >= 1) {
                u32 count = group->mUnits.size();
                u64 last = u64(count) - 1;
                u64 j = 0;
                while (true) {
                    if (count > j) {
                        Unk_7102474f10* g = group->mUnits.data()[j];
                        if (g) {
                            ScreenAppPictureBookEntry* entry = g->mEntry;
                            s32 rb = -1;
                            if (PictureBookGroupRecord* record = g->mRecord)
                                rb = record->_c;
                            bool sel;
                            if (mEntries.size() > _2e4) {
                                if (mEntries.data()[_2e4] != entry)
                                    sel = false;
                                else
                                    sel = _2ec == rb;
                            } else {
                                if (entry != nullptr)
                                    sel = false;
                                else
                                    sel = _2ec == rb;
                            }
                            if (PictureBookItem* item = g->_40) {
                                bool old = item->_10;
                                if (!old && sel) {
                                    item->_10 = true;
                                    item->m8(_318);
                                    _318 = item;
                                }
                                if (old && !sel) {
                                    item->_10 = false;
                                    item->m9();
                                }
                            }
                        }
                    }
                    if (last != j) {
                        count = group->mUnits.size();
                        ++j;
                        continue;
                    }
                    break;
                }
            }
        }
        ++i;
        if (i != count298) {
            lim = mGroupLists.size();
            continue;
        }
        break;
    }
}

// 0x710093f7f8
// NON_MATCHING: the 7-operand flag expression is lowered to branches plus a cset, while the original
// funnels all false paths to a shared mov w1,0; registers differ in that block.
void ScreenAppPictureBookUnk::sub_710093F7F8(bool flag) {
    s64 count = mGroupLists.size();
    if (count == 0)
        return;
    PictureBookGroupList** outer = mGroupLists.data();
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->mUnits.size();
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->mUnits.data();
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            Unk_7102474f10* g = *group;
            for (Unk_7102474e38& u : g->mUnits) {
                if (!flag) {
                    if (eui::AnimButton* button = u._10)
                        button->setFlag10(false);
                } else {
                    eui::AnimButton* button = u._10;
                    if (button) {
                        u32 flags = u._30;
                        ScreenAppPictureBookUnk* ctrl = u._20;
                        ScreenAppPictureBookEntry* entry = u._18->mEntry;
                        button->setFlag10((flags & 4) && (ctrl->_2c & 1) &&
                                          ctrl->_340 == 2 && (flags & 2) &&
                                          ((flags & 1) || entry->mParams._2ca) && !entry->_38c &&
                                          entry->_38d == 0);
                    }
                }
            }
        }
    }
}

// 0x710093fbf0
// NON_MATCHING: regalloc in the found block (load/mul operand registers), and the mEntries.data()-null path returns 0
// via mov w0,wzr while the original returns the null pointer itself via mov w0,w8.
s32 ScreenAppPictureBookUnk::sub_710093FBF0(eui::BoxCursorNode* node) {
    s32 result = -1;
    s64 count = mGroupLists.size();
    if (count == 0)
        return -1;
    Unk_7102474e38* l = nullptr;
    PictureBookGroupList** outer = mGroupLists.data();
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->mUnits.size();
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->mUnits.data();
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            Unk_7102474f10* g = *group;
            if (g->mEntry == nullptr)
                continue;
            if (g->mRecord == nullptr)
                continue;
            if (g->mRecord->_c < 0)
                continue;
            for (Unk_7102474e38& unit : g->mUnits) {
                if ((unit._30 & 4) != 0 && unit._28 == node) {
                    l = &unit;
                    goto found;
                }
            }
        }
    }
    return result;
found:
    if (mEntries.data() == nullptr)
        return 0;
    Unk_7102474f10* group = l->_18;
    PictureBookGroupRecord* record = group->mRecord;
    ScreenAppPictureBookEntry* entry = group->mEntry;
    s32 base = record->_c;
    s32 span = entry->mParams._2a0;
    s32 start = l->_3c;
    s32 step = entry->mParams._2a4;
    s32 limit = entry->_2f0;
    s32 total = start + base * span * step;
    u64 i = 0;
    s32 sum = 0;
    if (limit >= 1) {
        for (; i != limit; ++i) {
            if (mEntries.size() > i) {
                if (ScreenAppPictureBookEntry* e = mEntries.data()[i])
                    sum += e->mParams._29c;
            }
        }
    }
    return total + sum;
}

// File-static rodata tables for sub_710093F924 (values verified against the original with fstr;
// our addresses differ from the original's file-local ones, so the adrp/add pairs cannot match
// and the function caps at m).
namespace {
const u32 sUnk_7101E794A8[4] = {2, 1, 8, 4};
const u32 sUnk_7101E794B8[4] = {1, 2, 4, 8};
const s64 sUnk_7101E79C80[4] = {1, 0, 3, 2};
}  // namespace

// 0x710093f924
// NON_MATCHING: data addressing plus search-layout lowering (all table values verified against the
// original, but the three file-static tables live at different addresses so every adrp/add pair
// differs; the backward-search block sits inline while the original outlines it, with knock-on
// register allocation through the search; the entry loops, the _30 updates, the layout null checks
// and the whole animation tail match).
void ScreenAppPictureBookUnk::sub_710093F924(bool flag) {
    if (!flag && (_28 & 0x30) == 0)
        return;
    s64 c = mConfig._60;
    _30 = 0;
    eui::LayoutEx* layout_a;
    eui::LayoutEx* layout_b;
    u32 mask_b;
    u32 mask_a;
    if (u32(c) <= 3) {
        s64 idx = sUnk_7101E79C80[c];
        mask_a = sUnk_7101E794A8[c];
        mask_b = sUnk_7101E794B8[c];
        layout_a = _40[idx];
        layout_b = _40[u32(c)];
    } else {
        layout_a = nullptr;
        layout_b = nullptr;
        mask_b = 8;
        mask_a = 4;
    }
    u32 bits;
    if ((_2c & 1) == 0) {
        bits = 0;
        _30 = 0;
        _30 = bits & ~mask_b;
    } else {
        bits = mask_a;
        _30 = mask_a;
        if (_2f0 <= 0) {
            bool found_back = false;
            if (_2e8 >= 1) {
                s64 i = s64(_2e8) - 1;
                while (true) {
                    ScreenAppPictureBookEntry* e = mEntries.data()[i];
                    if (e->mParams._29c > 0 && !e->_38c && !e->_38d) {
                        found_back = true;
                        break;
                    }
                    if (i < 1)
                        break;
                    --i;
                }
            }
            if (found_back) {
                bits = mask_a;
                _30 = mask_a;
            } else {
                bits = 0;
                _30 = 0;
            }
        }
        bool found_fwd = false;
        ScreenAppPictureBookEntry* entry = mEntries.data()[_2e8];
        if (entry->_2f4 - 1 <= _2f0) {
            found_fwd = true;
        } else {
            s64 last = s64(mEntries.size()) - 1;
            if (s32(_2e8) < s32(last)) {
                s64 i = _2e8;
                while (true) {
                    ScreenAppPictureBookEntry* e = mEntries.data()[i + 1];
                    if (e->mParams._29c > 0 && !e->_38c && !e->_38d) {
                        found_fwd = true;
                        break;
                    }
                    ++i;
                    if (i >= last)
                        break;
                }
            }
        }
        if (found_fwd)
            _30 = bits | mask_b;
        else
            _30 = bits & ~mask_b;
    }
    if (!layout_a)
        return;
    if (!layout_b)
        return;
    if (flag) {
        if ((_30 & mask_a) == 0)
            layout_a->startAnimCloseImpl_(false, true);
        else
            layout_a->sub_7100BDDE7C(false, 1, true);
        if ((_30 & mask_b) == 0) {
            layout_b->startAnimCloseImpl_(false, true);
            return;
        }
        layout_b->sub_7100BDDE7C(false, 1, true);
    } else {
        if ((_30 & mask_a) == 0) {
            layout_a->startAnimCloseImpl_(false, false);
        } else if (layout_b->_91 - 1u < 2u) {
            sub_7100AA1D5C(layout_a, layout_b, true);
        } else {
            layout_a->sub_7100BDDE7C(false, 0, true);
        }
        if ((_30 & mask_b) == 0) {
            layout_b->startAnimCloseImpl_(false, false);
            return;
        }
        if (layout_a->_91 - 1u < 2u) {
            sub_7100AA1D5C(layout_b, layout_a, true);
            return;
        }
        layout_b->sub_7100BDDE7C(false, 0, true);
    }
}
// 0x710093d628
ScreenAppPictureBookUnk::ScreenAppPictureBookUnk() = default;

// NON_MATCHING: when mEntries has no buffer the original jumps straight to the config reset (ours tests mEntries
// again; one branch target)
// 0x710093d76c
ScreenAppPictureBookUnk::~ScreenAppPictureBookUnk() {
    for (auto& list : mGroupLists) {
        for (auto& group : list.mUnits) {
            for (auto& unit : group.mUnits)
                unit.m5();
        }
    }

    if (mGroupLists.data() && mEntries.data()) {
        const s32 count = mGroupLists.size();
        for (s32 i = 0; i < count; ++i) {
            PictureBookGroupList* list = mGroupLists[i];
            ScreenAppPictureBookEntry* entry = mEntries[i];
            if (!list || !entry)
                continue;
            const s32 num_units = entry->mParams._2a0 * entry->mParams._2a4;
            for (s32 j = 0; j < entry->mParams._298; ++j) {
                Unk_7102474f10* group = list->mUnits[j];
                if (!group)
                    continue;
                for (s32 k = 0; k < num_units; ++k)
                    delete group->mUnits[k];
                group->mUnits.freeBuffer();
                delete group;
            }
            list->mUnits.freeBuffer();
            delete list;
        }
        mGroupLists.freeBuffer();
    }

    if (mEntries.data()) {
        for (s32 i = 0; i < _2a8; ++i) {
            ScreenAppPictureBookEntry* entry = mEntries[i];
            if (!entry)
                continue;
            for (s32 j = 0; j < entry->mParams._298; ++j)
                delete entry->mRecords[j];
            entry->mRecords.freeBuffer();
            delete entry;
        }
        mEntries.freeBuffer();
    }

    mConfig.sub_71009396EC();
}

// 0x71025d6054: the colour of the scroll limit box drawn by Update, red (1, 0, 0, 1); one of the colours the TU's
// static initialiser 0x71009384e4 sets in its block of statics at 0x71025d5fd0
KSYS_VISIBILITY_HIDDEN sead::Color4f sUnk_71025D6054;

// NON_MATCHING: written from the binary, not tuned (the record search, loop shapes and register allocation differ)
// 0x710094211c
void ScreenAppPictureBookUnk::Update(f32 dt) {
    _28 = 0;
    _34 = 0;
    sub_7100942AE0();

    if (u32(_340 - 1) < 2) {
        bool enabled = false;
        if (_2e8 >= 0 && mEntries.size() > _2e8) {
            ScreenAppPictureBookEntry* entry = mEntries[_2e8];
            if (entry) {
                for (auto& record : entry->mRecords) {
                    if (record._c == _2f0) {
                        enabled = (record._0 & 1) != 0;
                        break;
                    }
                }
            }
        }
        if (enabled)
            _28 |= 0x200;
        else
            _28 &= ~0x200u;
    }

    if (_2c & 1) {
        if (eui::ScreenMgr::instance()->getBoxCursorMgr() && mScreen->mActiveCursorNode &&
            sub_710093FBF0(mScreen->mActiveCursorNode) >= 0)
            _28 |= 0x100;
        else
            _28 &= ~0x100u;
        _34 = sub_7100942D78();
        if (!sub_7100943080())
            sub_710094033C();
    }

    if (_2e0 != _2dc)
        _28 |= _2dc < _2d8 ? 0x20 : 0x10;

    if (_338 == 0 && (_28 & 0x30) && _3a0) {
        if (_2e4 == _2e8)
            _3a0->_0.mDelegate(_3a0->_0.mName.cstr());
        else
            _3a0->_b8.mDelegate(_3a0->_b8.mName.cstr());
    }

    const sead::Vector2f prev = _2c0;
    if (_2d0 != _2c0)
        sub_7100AA21F4(mScreen, &_2c0, _2d0, mConfig._74.x, mConfig._74.y, mConfig._7c);
    _2c0.x = sead::Mathf::clamp(_2c0.x, _2b0.getMin().x, _2b0.getMax().x);
    _2c0.y = sead::Mathf::clamp(_2c0.y, _2b0.getMin().y, _2b0.getMax().y);
    const sead::Vector2f delta = prev - _2c0;
    sub_7100943520(delta);
    sub_7100941C30(_2c0, &_2ec, &_2e4);

    _2d8 = 0;
    if (mEntries.data()) {
        for (s32 i = 0; i < _2e4; ++i) {
            ScreenAppPictureBookEntry* entry = mEntries[i];
            if (entry)
                _2d8 += entry->_2f4;
        }
        _2d8 += _2ec;
    }

    const s32 direction = getMoveDirectionMaybe(_2c8, _2c0);
    _334 = direction;
    if (direction == -1) {
        if (_330 != 1)
            _28 |= 0x80;
        _330 = 1;
    } else {
        if (_330 != 0)
            _28 |= 0x40;
        _330 = 0;
    }
    _338 = -_330;

    sub_710093F924(false);

    for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
        if (*it)
            (*it)->sub_710093AD60(_2c0);
    }

    if (_330 != 1) {
        for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
            ScreenAppPictureBookEntry* entry = *it;
            if (!entry)
                continue;
            for (s32 i = 0; i < sead::Mathi::min(entry->mParams._298, entry->_2f4); ++i)
                entry->sub_710093B684(entry->mRecords[i]);
            for (s32 i = 0; i < sead::Mathi::min(entry->mParams._298, entry->_2f4); ++i)
                entry->sub_710093B830(entry->mRecords[i]);
        }
    }

    sub_710093F670();
    _328 = nullptr;

    if (_2c & 1) {
        if (_30c != _310) {
            Unk_7102474e38* unit = sub_7100943684(_310);
            if (unit) {
                ScreenAppPictureBookEntry* entry = unit->_18->mEntry;
                if ((unit->_30 & 2) && ((unit->_30 & 1) || entry->mParams._2ca) && !entry->_38c &&
                    !entry->_38d) {
                    if (unit->_28)
                        _30c = _310;
                } else {
                    _30c = -1;
                    _310 = -1;
                }
            }
        }
        if (_310 == -1 && (_28 & 0x100) && mScreen->mActiveCursorNode) {
            const s32 index = sub_710093FBF0(mScreen->mActiveCursorNode);
            if (index >= 0)
                _310 = index;
        }

        if (_30c == _310) {
            Unk_7102474e38* unit = sub_7100943684(_30c);
            eui::BoxCursorMgr* mgr = eui::ScreenMgr::instance()->getBoxCursorMgr();
            if (unit && unit->_28 && mgr) {
                eui::BoxCursorNode* node = unit->_28;
                mgr->m5(node);
                _328 = node;

                s32 index = _30c;
                for (s32 i = 0; i < _2a8; ++i) {
                    ScreenAppPictureBookEntry* entry = mEntries(i);
                    if (index - entry->mParams._29c >= 0) {
                        index -= entry->mParams._29c;
                        continue;
                    }
                    const s32 per_page = entry->mParams._2a0 * entry->mParams._2a4;
                    for (s32 page = 0; page < entry->_2f4; ++page) {
                        if (index - per_page < 0) {
                            sub_7100944D18(mEntries[i], index, &_2f4, &_2f8);
                            goto found;
                        }
                        index -= per_page;
                    }
                }
            found:
                if (_320 == u32(mConfig._214))
                    m10();
                if (_320 <= u32(mConfig._214))
                    ++_320;
            }
        }
        sub_71009437C8();
    }

    if (!_3a8)
        _3b0 = 0;
    if (_3c4 & 1)
        sub_7100AA9A40(_2b0, mScreen, sUnk_71025D6054, false, false, false);

    if (mEntries.data()) {
        for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
            if (*it)
                (*it)->sub_710093CD20();
        }
    }

    _2c8 = _2c0;
    _2e0 = _2dc;
    m7();

    for (auto& list : mGroupLists) {
        for (auto& group : list.mUnits) {
            if (!group.mEntry || !group.mRecord || group.mRecord->_c < 0)
                continue;
            if (group._40)
                group._40->m6();
            for (auto& unit : group.mUnits) {
                if (unit._30 & 4)
                    unit.m6();
            }
        }
    }

    if (_330 != 1) {
        for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
            ScreenAppPictureBookEntry* entry = *it;
            if (!entry)
                continue;
            for (s32 i = 0; i < sead::Mathi::min(entry->mParams._298, entry->_2f4); ++i)
                entry->sub_710093B9F4(entry->mRecords[i]);
        }

        for (auto& list : mGroupLists) {
            for (auto& group : list.mUnits) {
                if (!group._8)
                    continue;
                if (group.mEntry && group.mRecord && group.mRecord->_c >= 0) {
                    const nn::util::Float3 pos = {
                        list._10.x + group.mEntry->_378.x + group.mRecord->mPosition.x,
                        list._10.y + group.mEntry->_378.y + group.mRecord->mPosition.y, 0.0f};
                    group._8->mPane->SetPosition(pos);
                    group._8->mPane->SetVisible(true);
                } else {
                    group._8->mPane->SetVisible(false);
                }
            }
        }
    }

    sub_71009439B0();
}

// 0x71025d6128: part of the TU's block of statics (set up by 0x71009384e4)
KSYS_VISIBILITY_HIDDEN sead::SafeString sUnk_71025D6128 = "SlideObject";

// NON_MATCHING: the original addresses "SlideObject" inside the TU's block of statics (0x71025d5fd0 + 0x158),
// which swaps two registers
// 0x7100944004
void ScreenAppPictureBookUnk::sub_7100944004(ScreenEx* screen, const PictureBookListConfig& config,
                                             eui::ControlBase* control) {
    mScreen = screen;
    if (!screen)
        return;
    mConfig.sub_7100939764(config);
    sub_7100944138();
    mScreen->mControls.linkNext(&control->_8);
    mScreen->_370.pushBack(control);
    if (mConfig._0.isEmpty())
        mConfig._0.format("%d", mScreen->sub_7100A482A4(this));
    _348.format("%s:%s", sUnk_71025D6128.cstr(), mConfig._0.cstr());
    mName = _348.cstr();
}

// NON_MATCHING: the original copies Vector2f::zero as one 64-bit value, merges the `*axis += value` tails of the
// switches and counts the page loop down in one register
// 0x71009419e0
void ScreenAppPictureBookUnk::sub_71009419E0(s32 index, s32 entry_index, sead::Vector2f* out) {
    if ((index | entry_index) < 0)
        return;
    *out = sead::Vector2f::zero;
    const auto add = [](f32* axis, f32 value) { *axis += value; };
    // moves `out` by one page of `entry` along the list direction (0: down, 1: up, 2: left, 3: right)
    const auto move_page = [&](const ScreenAppPictureBookEntry* entry) {
        f32* axis;
        f32 value;
        switch (mConfig._60) {
        case 0:
            axis = &out->y;
            value = entry->_340.y;
            break;
        case 1:
            axis = &out->y;
            value = -entry->_340.y;
            break;
        case 2:
            axis = &out->x;
            value = -entry->_340.x;
            break;
        case 3:
            axis = &out->x;
            value = entry->_340.x;
            break;
        default:
            return;
        }
        add(axis, value);
    };
    // moves `out` from the entry `a` to the next entry `b` (half of each layout plus the spacing between them)
    const auto move_between = [&](const ScreenAppPictureBookEntry* a, const ScreenAppPictureBookEntry* b) {
        f32* axis;
        f32 value;
        switch (mConfig._60) {
        case 0:
            axis = &out->y;
            value = mConfig._6c.y + (a->mGroupList->_20.y * 0.5f + b->mGroupList->_20.y * 0.5f);
            break;
        case 1:
            axis = &out->y;
            value = -(mConfig._6c.y + (a->mGroupList->_20.y * 0.5f + b->mGroupList->_20.y * 0.5f));
            break;
        case 2:
            axis = &out->x;
            value = -(mConfig._6c.x + (a->mGroupList->_20.x * 0.5f + b->mGroupList->_20.x * 0.5f));
            break;
        case 3:
            axis = &out->x;
            value = mConfig._6c.x + (a->mGroupList->_20.x * 0.5f + b->mGroupList->_20.x * 0.5f);
            break;
        default:
            return;
        }
        add(axis, value);
    };
    ScreenAppPictureBookEntry* prev = nullptr;
    for (s32 i = 0; i < _2a8; ++i) {
        ScreenAppPictureBookEntry* entry = mEntries[i];
        if (entry->_38d)
            continue;
        if (prev)
            move_between(prev, entry);
        const s32 num_pages = entry->_2f4;
        if (num_pages > 0) {
            if (i == entry_index) {
                for (s32 page = 0; page < num_pages; ++page) {
                    if (page == index)
                        return;
                    if (page != num_pages - 1)
                        move_page(entry);
                }
            } else {
                for (s32 page = num_pages - 1; page != 0; --page)
                    move_page(entry);
            }
        }
        prev = entry;
    }
}

// NON_MATCHING: the direction switch is laid out differently (the original jumps from the direction test into the
// cases) and _80 is loaded as a pair
// 0x710093dafc
bool ScreenAppPictureBookUnk::sub_710093DAFC(s32 index, s32 entry_index, s32 mode) {
    const s32 entry_idx = sead::Mathi::clamp(entry_index, 0, _2a8 - 1);
    if (!mEntries.data())
        return false;
    ScreenAppPictureBookEntry* entry = mEntries[entry_idx];
    if (!entry)
        return false;
    const s32 item = sead::Mathi::clamp(index, 0, entry->_2f4 - 1);
    const bool locked = entry->_38c || entry->_38d;
    if (mode != 2 && locked)
        return false;

    _2dc = 0;
    for (s32 i = 0; i < entry_idx; ++i) {
        if (ScreenAppPictureBookEntry* previous = mEntries[i])
            _2dc += previous->_2f4;
    }
    _2dc += item;
    _2f0 = item;
    _2e8 = entry_idx;

    sub_71009419E0(item, entry_idx, &_2d0);
    _2d0.x = -_2d0.x;
    _2d0.y = -_2d0.y;
    _2d0.x = sead::Mathf::clamp(_2d0.x, _2b0.getMin().x, _2b0.getMax().x);
    _2d0.y = sead::Mathf::clamp(_2d0.y, _2b0.getMin().y, _2b0.getMax().y);

    // start scrolling a bit before the target
    const sead::Vector2f lead = mConfig._80;
    if (!(lead.x == 0.0f && lead.y == 0.0f)) {
        switch (getMoveDirectionMaybe(_2c0, _2d0)) {
        case 0:
            _2c0.y = _2d0.y - lead.y;
            break;
        case 1:
            _2c0.y = _2d0.y + lead.y;
            break;
        case 2:
            _2c0.x = _2d0.x + lead.x;
            break;
        case 3:
            _2c0.x = _2d0.x - lead.x;
            break;
        }
    }

    _338 = mode;
    if (u32(mode - 1) < 2) {
        sub_7100941D70(mode != 2);
        s32 unit_index = -1;
        sub_710093E258(entry_idx, item, 0, 0, &unit_index);
        sub_710093E784(unit_index);
    }
    return true;
}

// NON_MATCHING: branch layout and register allocation (the original reads mEntries' buffer once up front)
// 0x710093ec3c
void ScreenAppPictureBookUnk::sub_710093EC3C(s32 index, s32 mode) {
    // the entry and page of the unit `index`
    s32 entry_idx = 0;
    s32 page = 0;
    const auto find_page = [&] {
        s32 rest = index;
        for (s32 i = 0; i < _2a8; ++i) {
            const ScreenAppPictureBookEntry* entry = mEntries(i);
            if (rest - entry->mParams._29c >= 0) {
                rest -= entry->mParams._29c;
                continue;
            }
            for (s32 p = 0; p < entry->_2f4; ++p) {
                if (rest - entry->mParams._2a0 * entry->mParams._2a4 < 0) {
                    entry_idx = i;
                    page = p;
                    return;
                }
                rest -= entry->mParams._2a0 * entry->mParams._2a4;
            }
        }
    };
    find_page();

    s32 item = -1;
    s32 entry_id = -1;
    if (mEntries.data()) {
        s32 overall = 0;
        for (s32 i = 0; i < entry_idx; ++i) {
            if (const ScreenAppPictureBookEntry* entry = mEntries[i])
                overall += entry->_2f4;
        }
        if (mEntries.size() != 0) {
            s32 rest = sead::Mathi::clamp(overall + page, 0, _2ac - 1);
            for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
                const ScreenAppPictureBookEntry* entry = *it;
                if (entry && rest - entry->_2f4 < 0) {
                    item = rest;
                    entry_id = entry->_2f0;
                    break;
                }
                if (entry)
                    rest -= entry->_2f4;
            }
        }
    }
    sub_710093DAFC(item, entry_id, mode);
    sub_710093E784(index);
}

// NON_MATCHING: the original copies Vector2f::zero as 64-bit values and tail-calls sub_710093F594
// 0x7100944290
void ScreenAppPictureBookUnk::sub_7100944290(sead::Heap* heap) {
    _2ac = 0;
    for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
        if (*it)
            _2ac += (*it)->_2f4;
    }

    _2b0.setFromCornerAndXY(sead::Vector2f::zero, 0.0f, 0.0f);
    {
        sead::Vector2f last = sead::Vector2f::zero;
        if (mEntries.size() > 0) {
            // the last page of the last entry that has pages
            const s32 last_entry = _2a8 - 1;
            s32 page = -1;
            if (last_entry >= 0) {
                s32 i = _2a8;
                s32 count;
                do {
                    count = mEntries(i - 1)->_2f4;
                    if (i < 2)
                        break;
                    --i;
                } while (count < 1);
                page = count - 1;
            }
            sub_71009419E0(page, last_entry, &last);
        }
        _2b0.set(0.0f, 0.0f, -last.x, -last.y);
    }

    const s32 num_entries = mEntries.size();
    for (s32 i = 0; i < num_entries; ++i) {
        ScreenAppPictureBookEntry* entry = mEntries[i];
        if (entry->_2f4 > 0) {
            sub_71009419E0(0, i, &entry->_368);
            sub_71009419E0(entry->_2f4 - 1, i, &entry->_370);
        } else {
            entry->_368 = sead::Vector2f::zero;
            entry->_370 = sead::Vector2f::zero;
        }
    }

    sub_710094004C();
    _33c = -1;

    // closed (2) unless the last group of an entry has an animator or an open animation (0)
    const auto is_animated = [this] {
        if (!mEntries.data())
            return false;
        for (ScreenAppPictureBookEntry** it = mEntries.data(), **end = it + mEntries.size(); it != end; ++it) {
            if (!*it)
                continue;
            bool animated = false;
            for (auto& group : (*it)->mGroupList->mUnits)
                animated = group._30 || (group._8 && group._8->mOpenAnimator);
            if (animated)
                return true;
        }
        return false;
    };
    _340 = is_animated() ? 0 : 2;

    m5(heap);
    for (auto& list : mGroupLists) {
        for (auto& group : list.mUnits) {
            for (auto& unit : group.mUnits)
                unit.m4(heap);
        }
    }
    sub_710093F594(false);
}

// 0x710093dad4
void ScreenAppPictureBookUnk::sub_710093DAD4(s32 value) {
    if (_33c <= value)
        _33c = value;
}

// 0x710093dae8
void ScreenAppPictureBookUnk::sub_710093DAE8(s32 value) {
    if (_33c <= value)
        _33c = value;
}

// 0x7100939f58
bool ScreenAppPictureBookUnk::sub_7100939F58() const {
    return _340 == 2;
}

// 0x710093f278
void ScreenAppPictureBookUnk::sub_710093F278(s32 value, s32 index) {
    if (mEntries.data() && static_cast<u32>(index) < mEntries.size()) {
        ScreenAppPictureBookEntry* entry = mEntries.data()[index];
        if (entry)
            entry->mParams._29c = value;
    }
    sub_710093F29C();
}

// 0x710093fd14
void ScreenAppPictureBookUnk::sub_710093FD14(s32 index) {
    if (index >= 0 && mEntries.data() && index < _2a8)
        mEntries.data()[index]->_38c = true;
    sub_710093F7F8(_2c & 1);
    sub_710093F924(true);
}

// 0x710093fd6c
void ScreenAppPictureBookUnk::sub_710093FD6C() {
    for (s64 i = 0; i < _2a8; ++i)
        mEntries.data()[i]->_38c = false;
    sub_710093F7F8(_2c & 1);
    sub_710093F924(true);
}

// 0x710093fdcc
void ScreenAppPictureBookUnk::sub_710093FDCC(s32 index) {
    if (index >= 0 && mEntries.data() && index < _2a8)
        mEntries.data()[index]->_38d = true;
    sub_710093F29C();
    sub_710093F924(true);
}

// 0x710093fe1c
void ScreenAppPictureBookUnk::sub_710093FE1C() {
    for (s64 i = 0; i < _2a8; ++i)
        mEntries.data()[i]->_38d = false;
    sub_710093F29C();
    sub_710093F924(true);
}

// 0x710093fe74
bool ScreenAppPictureBookUnk::sub_710093FE74(s32 index) const {
    if (index < 0 || index >= _2a8)
        return true;
    return mEntries.data()[index]->_38d;
}

// 0x71009401e4
void ScreenAppPictureBookUnk::sub_71009401E4() {
    s64 count = mGroupLists.size();
    if (count == 0)
        return;
    PictureBookGroupList** outer = mGroupLists.data();
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->mUnits.size();
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->mUnits.data();
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            for (Unk_7102474e38& u : (*group)->mUnits) {
                eui::AnimButton* button = u._10;
                if (button && !(button->mFlags & 0x10))
                    button->ForceOff();
            }
        }
    }
}

// 0x7100940288
void ScreenAppPictureBookUnk::sub_7100940288() {
    s64 count = mGroupLists.size();
    if (count == 0)
        return;
    PictureBookGroupList** outer = mGroupLists.data();
    PictureBookGroupList** end = outer + count;
    for (; outer != end; ++outer) {
        PictureBookGroupList* o = *outer;
        s64 n = o->mUnits.size();
        if (n == 0)
            continue;
        Unk_7102474f10** group = o->mUnits.data();
        Unk_7102474f10** gend = group + n;
        for (; group != gend; ++group) {
            for (Unk_7102474e38& u : (*group)->mUnits) {
                eui::AnimButton* button = u._10;
                if (button && button->IsDowning())
                    button->ForceOff();
            }
        }
    }
}

}  // namespace uking::ui

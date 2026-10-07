#include "aal/aalCustomCurve.h"
#include <basis/seadNew.h>
#include "aal/aalCurveReader.h"

namespace aal {

// NON_MATCHING: the original stores the zero count of the segment list right after the name copy.
// 0x7100ba2868
CustomCurve::CustomCurve(const sead::SafeString& name) : Curve(name) {
    mSegments.initOffset(offsetof(CustomCurveSegment, mListNode));
}

// NON_MATCHING: the node address of the erased segment is calculated with swapped operands, and the original D0 calls D2
// (here D2 is inlined into D0).
// 0x7100ba2aa8 (D2) / 0x7100ba2b48 (D0)
CustomCurve::~CustomCurve() {
    for (CustomCurveSegment& segment : mSegments.robustRange()) {
        mSegments.erase(&segment);
        delete &segment;
    }
}

// 0x7100ba2b6c
void CustomCurve::setupFromResourceReader(const CustomCurveReader& reader, sead::Heap* heap) {
    if (!reader.isValid())
        return;

    for (s32 i = 0; i < reader.getNumOfSegments(); ++i) {
        CustomCurveSegment* segment = new (heap) CustomCurveSegment;
        const CustomCurveReader::SegmentParam* param = reader.getSegmentParam(i);
        segment->mPosition = param->position;
        segment->mValue = param->value;
        segment->mType = CustomCurveType(param->type);
        segment->mCoefficient = param->coefficient;
        addSegment(segment);
    }
}

// NON_MATCHING: the original also tests the segment object of the position search for null (a second return path).
// 0x7100ba2c38
bool CustomCurve::addSegment(CustomCurveSegment* segment) {
    if (!segment)
        return false;

    for (CustomCurveSegment& other : mSegments) {
        if (other.mPosition == segment->mPosition)
            return false;
    }

    mSegments.pushBack(segment);
    mSegments.insertionSort([](const CustomCurveSegment* lhs, const CustomCurveSegment* rhs) {
        if (!lhs || !rhs)
            return false;
        return lhs->mPosition > rhs->mPosition;
    });
    return true;
}

}  // namespace aal

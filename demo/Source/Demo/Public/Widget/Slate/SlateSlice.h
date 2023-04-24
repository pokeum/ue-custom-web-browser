#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * Slate Widget Class
 */
class DEMO_API SSlateSlice : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateSlice)
	{}
	SLATE_ARGUMENT(FSlateBrush*, Brush)
	SLATE_ARGUMENT(float, Angle)
	SLATE_ARGUMENT(float, ArcSize)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	FInvalidatableBrushAttribute Brush;
	float Angle;
	float ArcSize;

public:
	// Paint the slice
	virtual int32 OnPaint(
		const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled
	) const override;

	void SetBrush(FSlateBrush* InBrush);
	void SetAngle(float InAngle);
	void SetArcSize(float InArcSize);
};

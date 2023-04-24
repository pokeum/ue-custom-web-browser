#include "Widget/Slate/SlateSlice.h"

#include "SlateOptMacros.h"

/*
 * The BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION and END_SLATE_FUNCTION_BUILD_OPTIMIZATION
 * are often used around the Construct function as it can end up having a very complex expression
 * that the compiler may spend a lot of time trying to optimize.
 * (These macros turn optimizations off and on again.)
 */
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlateSlice::Construct(const FArguments& InArgs)
{
	// Each SLATE_ARGUMENT that is defined in the class header is added as a member in the FArguments structure,
	// with an underscore prefixed to its name.
	
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	Angle = InArgs._Angle;
	ArcSize = InArgs._ArcSize;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SSlateSlice::OnPaint(
	const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled
) const
{
	const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
	const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
	const FVector2D Center = Pos + 0.5 * Size;
	const float Radius = FMath::Min(Size.X, Size.Y) * 0.5f;

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	const FLinearColor LinearColor = ColorAndOpacity.Get() * InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	const FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	const int NumSegments = FMath::RoundToInt(ArcSize / 10.0f);
	TArray<FSlateVertex> Vertices;
	Vertices.Reserve(NumSegments + 3);

	// Add center vertex
	Vertices.AddZeroed();
	FSlateVertex& CenterVertex = Vertices.Last();

	CenterVertex.Position = Center;
	CenterVertex.Color = FinalColorAndOpacity;

	// Add edge vertices
	for (int i = 0; i < NumSegments + 2; ++i)
	{
		const float CurrentAngle = FMath::DegreesToRadians(ArcSize * i / NumSegments + Angle);
		const FVector2D EdgeDirection(FMath::Cos(CurrentAngle), FMath::Sin(CurrentAngle));
		const FVector2D OuterEdge(Radius*EdgeDirection);

		Vertices.AddZeroed();
		FSlateVertex& OuterVert = Vertices.Last();

		OuterVert.Position = Center + OuterEdge;
		OuterVert.Color = FinalColorAndOpacity;	
	}

	TArray<SlateIndex> Indices;
	for (int i = 0; i <= NumSegments; ++i)
	{
		Indices.Add(0);
		Indices.Add(i);
		Indices.Add(i + 1);
	}

	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle( *SlateBrush );
	FSlateDrawElement::MakeCustomVerts(
		OutDrawElements,
		LayerId,
		Handle,
		Vertices,
		Indices,
		nullptr,
		0,
		0
	);
	return LayerId;
}

void SSlateSlice::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SSlateSlice::SetAngle(float InAngle)
{
	Angle = InAngle;
}

void SSlateSlice::SetArcSize(float InArcSize)
{
	ArcSize = InArcSize;
}
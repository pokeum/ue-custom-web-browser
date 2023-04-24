#include "Widget/UMG/Slice.h"
#include "Widget/Slate/SlateSlice.h"

#define LOCTEXT_NAMESPACE "Slice"

TSharedRef<SWidget> USlice::RebuildWidget()
{
	MySlice = SNew(SSlateSlice)
		// SLATE_ARGUMENT
		.Brush(&Brush)
		.Angle(Angle)
		.ArcSize(ArcSize);
	
	return  MySlice.ToSharedRef();
}

void USlice::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	
	MySlice.Reset();
}

void USlice::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	MySlice->SetBrush(&Brush);
	MySlice->SetAngle(Angle);
	MySlice->SetArcSize(ArcSize);
}

#if WITH_EDITOR
const FText USlice::GetPaletteCategory()
{
	return LOCTEXT("CustomPaletteCategory", "Experimental");
}
#endif
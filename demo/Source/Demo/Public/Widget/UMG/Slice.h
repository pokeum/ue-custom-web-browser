// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Slice.generated.h"

/**
 * UMG Widget Class
 */
UCLASS()
class DEMO_API USlice : public UWidget
{
	GENERATED_BODY()
	
protected:
	// UMG Widget class holds a Slate widget instance.
	TSharedPtr<class SSlateSlice> MySlice;

	// RebuildWidget constructs the Slate widget,
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	// And ReleaseSlateResources clears them up again.
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

/*
 * Passing properties
 * : In order to have the widget to draw a slice,
 *   we need to add some properties to determine its appearance.
 */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearance")
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearance")
	float ArcSize;

/*
 * Updating properties
 * : For the editor to work properly we need to update the properties in the Slate widget whenever they change in the UMG widget.
 *   We do that by overriding the SynchronizeProperties function.
 */
public:
	virtual void SynchronizeProperties() override;

public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};

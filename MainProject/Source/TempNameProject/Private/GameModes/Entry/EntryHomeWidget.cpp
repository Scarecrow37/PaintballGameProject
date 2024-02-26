// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Entry/EntryHomeWidget.h"

void UEntryHomeWidget::NativeConstruct()
{
}

UUserWidget* UEntryHomeWidget::GetEntrySoundWidget()
{
	return EntrySoundWidget;
}

bool UEntryHomeWidget::EntrySoundISVisible()
{
	return EntrySoundWidget->IsVisible();
}

void UEntryHomeWidget::ToggleVisibleWidget()
{
	if (EntrySoundISVisible())
	{
		EntrySoundWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		EntrySoundWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
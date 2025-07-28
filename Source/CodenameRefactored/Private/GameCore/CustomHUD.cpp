// Copyright (C) 2025 Erdeni Arsalanov. All Rights Reserved.


#include "GameCore/CustomHUD.h"
#include "UI/AttributesWidget.h"


void ACustomHUD::Init()
{
	AttributeWidget = CreateWidget<UAttributesWidget>(GetOwningPlayerController(),AttributeWidgetClass);
	AttributeWidget->BindToAttributes();
	AttributeWidget->AddToViewport();
}

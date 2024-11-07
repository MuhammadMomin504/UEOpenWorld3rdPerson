// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location, 25.f, 12, FColor:: Red, true);
#define DRAW_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location, 25.f, 12, FColor:: Red, false, -1.f );
#define DRAW_LINE(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor:: Red, true);
#define DRAW_LINE_SingleFrame(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor:: Red, false, -1.f, , 1.f);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.0f, FColor:: Red, true);
#define DRAW_POINT_SingleFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.0f, FColor:: Red, false, -1.f, , 1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor:: Red, true, -1.f, , 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.0f, FColor:: Red, true); \
	}

#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor:: Red, false, -1.f, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.0f, FColor:: Red, false, -1.f); \
	}
// Fill out your copyright notice in the Description page of Project Settings.

#include "SpectatorShape.h"


// Sets default values
ASpectatorShape::ASpectatorShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a cube as a simple collision representation.
	//CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// Set the root component to be the collision component.
	//RootComponent = CollisionComponent;

	CustomMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("CustomMesh"));
	SetRootComponent(CustomMesh);
	CustomMesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void ASpectatorShape::BeginPlay()
{
	Super::BeginPlay();
	GenerateCubeMesh();
}

// Called every frame
void ASpectatorShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Moving mesh right one unit every tick example
	// Moving the mesh
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *TempActorName);
	//for (int32 index = 0; index < Vertices.Num(); index++)
	//{
	//	// Moving each vertex 1 unit forward
	//	Vertices[index] += FVector(1, 0, 0);
	//}
	//CustomMesh->UpdateMeshSection(0, Vertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>()); 
	// Moving mesh left one unit every tick example
	//for (int32 index = 0; index < Vertices.Num(); index++)
	//{
	//	// Moving each vertex 1 unit forward
	//	Vertices[index] += FVector(-1, 0, 0);
	//}
	//CustomMesh->UpdateMeshSection(0, Vertices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>());
}


void ASpectatorShape::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}


void ASpectatorShape::GenerateCubeMesh()
{
	// 6 sides on cube, 4 verts each (corners)

	//These are relative locations to the placed Actor in the world
	Vertices.Add(FVector(-500, -1500, 0)); //lower left - 0
	Vertices.Add(FVector(-500, -1500, 1250)); //upper left - 1
	Vertices.Add(FVector(-500, 1500, 0)); //lower right - 2 
	Vertices.Add(FVector(-500, 1500, 1250)); //upper right - 3

	Vertices.Add(FVector(500, -1500, 0)); //lower front left - 4
	Vertices.Add(FVector(500, -1500, 1250)); //upper front left - 5

	Vertices.Add(FVector(500, 1500, 1250)); //upper front right - 6
	Vertices.Add(FVector(500, 1500, 0)); //lower front right - 7

	//Back face of cube
	AddTriangle(0, 2, 3);
	AddTriangle(3, 1, 0);

	//Left face of cube
	AddTriangle(0, 1, 4);
	AddTriangle(4, 1, 5);

	//Front face of cube
	AddTriangle(4, 5, 7);
	AddTriangle(7, 5, 6);

	//Right face of cube
	AddTriangle(7, 6, 3);
	AddTriangle(3, 2, 7);

	//Top face
	AddTriangle(1, 3, 5);
	AddTriangle(6, 5, 3);

	//bottom face
	AddTriangle(2, 0, 4);
	AddTriangle(4, 7, 2);

	TArray<FLinearColor> VertexColors;
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.5f, 1.f, 0.5f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 1.f));

	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(), true);
}

// Copyright Acinex Games 2021

#include "GOAPController.h"
#include "GOAPPlanner.h"
#include "GOAPSettings.h"

// Sets default values
AGOAPController::AGOAPController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGOAPController::BeginPlay()
{
	Super::BeginPlay();

	Settings = GetDefault<UGOAPSettings>();

	for (auto Class : Settings->DefaultActions)
		ActionClasses.Add(Class);

	for (FGOAPGoal Goal : ReachedGoals)
		ReachedState.AddVertex(Goal.Name.ToString(), Goal.Value);

	for (FGOAPGoal Goal : DesiredGoals)
		DesiredState.AddVertex(Goal.Name.ToString(), Goal.Value);

	Planner = new UGOAPPlanner();
	Planner->Initialize(&ReachedState, &DesiredState, ActionClasses, MaxDepth, this);
}

void AGOAPController::UpdateGoals(const TArray<FGOAPGoal>& Goals)
{
	for (const FGOAPGoal Goal : Goals)
		DesiredState.AddVertex(Goal.Name.ToString(), Goal.Value);
}

void AGOAPController::SetGoals(const TArray<FGOAPGoal>& Goals)
{
	DesiredState.Clear();
	UpdateGoals(Goals);
}

void AGOAPController::UpdateReachedGoals(const TArray<FGOAPGoal>& Goals)
{
	for (const FGOAPGoal Goal : Goals)
		ReachedState.AddVertex(Goal.Name.ToString(), Goal.Value);
}

void AGOAPController::SetReachedGoals(const TArray<FGOAPGoal>& Goals)
{
	ReachedState.Clear();
	UpdateReachedGoals(Goals);
}

UGOAPAction* AGOAPController::GetCurrentAction() const
{
	return Plan.Num() > 0 ? Plan[0] : nullptr;
}

bool AGOAPController::ExecuteGoalOrientatedActionPlan()
{
	if (!bIsContinuous && !GeneratePlan() || Plan.Num() == 0)
		return false;

	UGOAPAction* Action = Plan[Plan.Num() - 1];

	if (bIsContinuous)
		Action->TickAction(GetPawn(), GetWorld()->GetDeltaSeconds());
	else
		Action->Execute(GetPawn());

	const EGOAPActionResult Result = Action->GetResult();

	bIsContinuous = Result == EGOAPActionResult::Continue;

	if (Result == EGOAPActionResult::Complete)
		ReachedState.Join(Action->GetEffects());

	return true;
}

bool AGOAPController::GeneratePlan()
{
	if (ActionClasses.Num() == 0 || DesiredState.IsEmpty())
		return false;

	Plan = Planner->GeneratePlan(GetPawn());

	return true;
}

void AGOAPController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bExecuteEveryTick)
		ExecuteGoalOrientatedActionPlan();
}

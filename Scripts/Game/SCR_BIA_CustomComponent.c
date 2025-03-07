[EntityEditorProps(category: "GameScripted/Badger", description: "Defines a spawn area for a given side", color: "0 0 255 255")]
// [EntityEditorProps(category: "GameScripted/Badger", description: "Defines a spawn area for a given side", color: "0 0 255 255")]
class SCR_BIA_CustomComponentClass : SCR_BaseGameModeComponentClass
{
    
}

class SCR_BIA_CustomComponent : SCR_BaseGameModeComponent
{
	override void EOnInit(IEntity owner)
	{
		Print("=== Custom Component Initialized ===");
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{	

	}
}
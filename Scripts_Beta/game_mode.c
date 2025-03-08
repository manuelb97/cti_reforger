// since any game mode inherits from this, this should trigger always
modded class SCR_BaseGameMode
{
	override void OnInit()
	{
	    super.OnInit();
	    Print("=== Custom Game Mode Initialized ===");
	    Diag.Log("=== Custom Game Mode Initialized ===");
	}
	
    override void OnGameStart()
    {
        super.OnGameStart();
        Print("=== Custom Game Mode Startup Script Running ===");
		Diag.Log("=== Custom Game Mode Startup Script Running ===");
    }
}

modded class SCR_GameModeCampaign // Or whatever actual game mode class is used in your mission
{
	override void OnInit()
	{
	    super.OnInit();
	    Print("=== Custom Game Mode Initialized ===");
	    Diag.Log("=== Custom Game Mode Initialized ===");
	}
	
    override void OnGameStart()
    {
        super.OnGameStart();
        Print("=== Custom Campaign Game Mode Startup Script Running ===");
        Diag.Log("=== Custom Campaign Game Mode Startup Script Running ===");
    }
}

modded class SCR_GameModeCampaign : SCR_BaseGameMode
{
    // Override the OnGameStart method to add custom functionality
    override void OnGameStart()
    {
        // Call the original functionality (super will call the base class's OnGameStart())
        super.OnGameStart();

        // Add custom logic to print something in the log
        Diag.Log("=== Custom Message: Game Started ===");
        Print("=== Custom Message: Game Started ===");
    }
}
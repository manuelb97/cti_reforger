class GameMode_Campaign1_Class: SCR_GameModeCampaign 
{
	// user script
	// AIWaypoint 
	
	/*
	{1B0E3436C30FA211}Prefabs/AI/Waypoints/AIWaypoint_Attack.et
	{EAAE93F98ED5D218}Prefabs/AI/Waypoints/AIWaypoint_CaptureRelay.et
	{35BD6541CBB8AC08}Prefabs/AI/Waypoints/AIWaypoint_Cycle.et
	{93291E72AC23930F}Prefabs/AI/Waypoints/AIWaypoint_Defend.et
	{3AB6B883AF54D965}Prefabs/AI/Waypoints/AIWaypoint_Defend_ConflictBaseTeamBackup.et
	{06B1B14B6DE3C983}Prefabs/AI/Waypoints/AIWaypoint_Defend_ConflictBaseTeamPatrol.et
	{2A81753527971941}Prefabs/AI/Waypoints/AIWaypoint_Defend_CP.et
	{A0509D3C4DD4475E}Prefabs/AI/Waypoints/AIWaypoint_Follow.et
	{06E1B6EBD480C6E0}Prefabs/AI/Waypoints/AIWaypoint_ForcedMove.et
	{36ED7C150D5BB654}Prefabs/AI/Waypoints/AIWaypoint_Heal.et
	{4ECD14650D82F5CA}Prefabs/AI/Waypoints/AIWaypoint_Loiter_CO.et
	{AAE8882E0DE0761A}Prefabs/AI/Waypoints/AIWaypoint_Defend_Hierarchy.et
	{FAD1D789EE291964}Prefabs/AI/Waypoints/AIWaypoint_Defend_Large.et
	{712F4795CF8B91C7}Prefabs/AI/Waypoints/AIWaypoint_GetIn.et
	{B049D4C74FBC0C4D}Prefabs/AI/Waypoints/AIWaypoint_GetInNearest.et
	{750A8D1695BD6998}Prefabs/AI/Waypoints/AIWaypoint_Move.et
	{97FB527ECC7CA49E}Prefabs/AI/Waypoints/AIWaypoint_ObservationPost.et
	{A33AF7FC5004F294}Prefabs/AI/Waypoints/AIWaypoint_Defend_Large_CO.et
	{2FCBE5C76E285A7B}Prefabs/AI/Waypoints/AIWaypoint_DefendSmall.et
	{8AD8C82346156494}Prefabs/AI/Waypoints/AIWaypoint_GetInSelected.et
	{C40316EE26846CAB}Prefabs/AI/Waypoints/AIWaypoint_GetOut.et
	{1966BC58CE769D69}Prefabs/AI/Waypoints/AIWaypoint_OpenGate.et
	{22A875E30470BD4F}Prefabs/AI/Waypoints/AIWaypoint_Patrol.et
	{CE97215CE55CF734}Prefabs/AI/Waypoints/AIWaypoint_DeploySmokeCover.et
	{E5002E8CD9D1F4AF}Prefabs/AI/Waypoints/AIWaypoint_GetOutInstant.et
	{FBA8DC8FDA0E770D}Prefabs/AI/Waypoints/AIWaypoint_Patrol_Hierarchy.et
	{A88F0B6CF25BD1DE}Prefabs/AI/Waypoints/AIWaypoint_Scout.et
	{B3E7B8DC2BAB8ACC}Prefabs/AI/Waypoints/AIWaypoint_SearchAndDestroy.et
	{ED8277F35B46B4AA}Prefabs/AI/Waypoints/AIWaypoint_Suppress.et
	{70AAB1ABF7469613}Prefabs/AI/Waypoints/AIWaypoint_Suppress_Commanding.et
	{70FE5AA8B4BCA67A}Prefabs/AI/Waypoints/AIWaypoint_Suppress_Editor.et
	{04A06A6742FB0AF8}Prefabs/AI/Waypoints/AIWaypoint_UserAction.et
	{531EC45063C1F57B}Prefabs/AI/Waypoints/AIWaypoint_Wait.et
	*/
	
	protected void AISpawner(string spawnGroup, vector spawnPosition, string waypointType, vector waypointPosition)
	{
		// Generate the resource 
		Resource resource = GenerateAndValidateResource(spawnGroup);
		
		if (!resource)
		{
			Print(("[AISpawner] unable to load resource for the spawn group: " + spawnGroup, LogLevel.ERROR));
			return;
		}
		
		// Generate the spawn parameters and spawn the group 
		SCR_AIGroup group = SCR_AIGroup.Cast(GetGame().SpawnEntityPrefab(resource, null, GenerateSpawnParameters(spawnPosition)));
		
		if (!group)
		{
			Print(("[AISpawner] unable to spawn group", LogLevel.ERROR));
			return;
		}
		
		// Create the waypoint for the group
		CreateWaypoint(group, waypointType, waypointPosition);
	}
	
	protected void CreateWaypoint(SCR_AIGroup group, string waypointType, vector waypointPosition)
	{
		// Generate the resource 
		Resource resource = GenerateAndValidateResource(waypointType);
		
		if (!resource)
		{
			Print("[Create waypoint] unable to load resource for the waypoint: " + waypointType, LogLevel.ERROR);
			return;
		}
		
		// Generate the spawn parameteres and create the waypoint
		AIWaypoint waypoint = AIWaypoint.Cast(GetGame().SpawnEntityPrefab(resource, null, GenerateSpawnParameters(waypointPosition)));
		
		if (!waypoint)
		{
			Print(("[CreateWaypoint] unable to create waypoint", LogLevel.ERROR));
			return;
		}
		
		// Assign the waypoint to the group
		group.AddWaypoint(waypoint);
	}
	
	protected Resource GenerateAndValidateResource(string resourceToLoad)
	{
		// Load the resource 
		Resource resource = Resource.Load(resourceToLoad);
		
		// Validate the prefab and show an appropriate error if invalid 
		if (!resource)
		{
			Print(("[GenerateAndValidateResource] unable to create waypoint", LogLevel.ERROR));
			return null;
		}
		
		// Return the resource
		return resource;
	}
	
	protected EntitySpawnParams GenerateSpawnParameters(vector position)
	{
		// Create a new set of spawn parameters 
		EntitySpawnParams params = EntitySpawnParams(); 
		params.TransformMode = ETransformMode.WORLD;
		
		// Assign the position to those parameters 
		params.Transform[3] = position;
		
		// Return the set of spawn parameters
		return params;
	}

	override void OnGameStart()
	{
		super.OnGameStart();
		
		// String variables for our resources 
		string spawnGroup = "{DDF3799FA1387848}Prefabs/Groups/BLUFOR/Group_US_RifleSquad.et";
		string waypointType = "";
		
		// Entity variables for our positions 
		IEntity spawnPosition = GetGame().GetWorld().FindEntityByName("").getOrigin();
		IEntity waypointPosition = GetGame().GetWorld().FindEntityByName("").getOrigin();
		
		// Execute AI spawning using delayed call
		GetGame().GetCallqueue().CallLater(AISpawner, 10000, false, spawnGroup, spawnPosition, waypointType, waypointPosition);
	}

};


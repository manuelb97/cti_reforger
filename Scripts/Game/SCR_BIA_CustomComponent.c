[EntityEditorProps(category: "GameScripted/Badger", description: "Defines a spawn area for a given side", color: "0 0 255 255")]
// [EntityEditorProps(category: "GameScripted/Badger", description: "Defines a spawn area for a given side", color: "0 0 255 255")]
class SCR_BIA_CustomComponentClass : SCR_BaseGameModeComponentClass
{
    
}

class SCR_BIA_CustomComponent : SCR_BaseGameModeComponent
{
	private ref array<IEntity> foundBuildings = {};
	private ref array<IEntity> nearbyBuildings = {};
	private bool addBuilding;
	private bool addNearbyBuilding;

	bool AddEntity(IEntity ent)
	{
		if (!ent)
			return true;
			
		if (addBuilding) 
		{
			foundBuildings.Insert(ent);
		}
		if (addNearbyBuilding) 
		{
			nearbyBuildings.Insert(ent);
		}
		return true;
	}

    void MarkHostileSectors()
    {
        Print("=== Marking Hostile Sectors ===");
        
        float searchRadius = 5000.0;
		int minNearbyBuildings = 3;
        float maxNearbyBuildingDist = 300.0;
        float minDistBetweenSectors = 500.0;
		array<vector> sectorCenters = {};

        // Query entities by sphere to find buildings
        vector mapCenter = Vector(0, 0, 0);
		addBuilding = true;
        GetGame().GetWorld().QueryEntitiesBySphere(mapCenter, searchRadius, 
            AddEntity,
            FilterBuildingEntities, 
            EQueryEntitiesFlags.STATIC);
		addBuilding = false;
        
        foreach (IEntity building : foundBuildings)
        {
            vector pos = building.GetOrigin();
            nearbyBuildings.Clear();
            
			addNearbyBuilding = true;
			GetGame().GetWorld().QueryEntitiesBySphere(pos, maxNearbyBuildingDist, 
                AddEntity,
                FilterBuildingEntities, 
                EQueryEntitiesFlags.STATIC);
			addNearbyBuilding = false;
            
            if (nearbyBuildings.Count() >= minNearbyBuildings)
            {
                bool tooClose = false;
                foreach (vector sectorPos : sectorCenters)
                {
                    if (vector.Distance(sectorPos, pos) < minDistBetweenSectors)
                    {
                        tooClose = true;
                        break;
                    }
                }
                
                if (!tooClose)
                {
                    sectorCenters.Insert(pos);
                }
            }
        }
        
		if (sectorCenters.GetSizeOf() > 0)
		{
        	CreateMapMarkers(sectorCenters);
		} else 
		{
			Print("no buildings found");
		}
    }

    static bool FilterBuildingEntities(IEntity entity)
    {
        if (!entity) return false;

        Resource resource;
        string resourceName = resource.ToString();
        return resourceName.Contains("barracks") || resourceName.Contains("cargo");
    }

    void CreateMapMarkers(array<vector> positions)
    {
        foreach (vector pos : positions)
        {
            SCR_MapMarkerBase marker = new SCR_MapMarkerBase();
            marker.SetWorldPos(pos[0], pos[1]);
            marker.SetColorEntry(Color.RED);
        }
    }
	
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        MarkHostileSectors();
    }
}

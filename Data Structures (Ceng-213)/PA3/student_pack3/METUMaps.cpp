#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    // TODO
    map=Graph(mapFilePath);
    this->potentialPathCount=potentialPathCount;
    cachedPaths= KeyedHashTable(potentialPathCount * map.TotalVertexCount());
    inJourney=0;
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
      if(inJourney)
    {
        PrintUnableToChangeDestination();
    }
    else
    {
        this->destination=name;
    }

}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if(inJourney)
    {
        PrintUnableToChangeStartingLoc();
    }
    else
    {
        this->startingLoc=name;
    }
}

void METUMaps::StartJourney()
{
    // TODO
    
    std::vector<int> ordered;
    
    //int available= map.ShortestPath(ordered,startingLoc,destination);

    std::vector<std::vector<int> > ordered_new;
    
   int s = 0, t = 0;
    for(int i=0;i<map.TotalVertexCount();i++)
    {
        if(map.VertexName(i) == startingLoc)
            s = true;
        if(map.VertexName(i) == destination)
            t = true;
    }
    if(inJourney)
    {
        PrintAlreadyInJourney();
    }
    
    else if(s!=1 || t!=1)
    {
        PrintCalculatingRoutes(startingLoc,destination);
        PrintLocationNotFound();
    }

    else
    {
        PrintCalculatingRoutes(startingLoc,destination);

        map.MultipleShortPaths(ordered_new,startingLoc,destination,potentialPathCount);

        std::vector<int> path;

        for(int i=0;i<ordered_new.size();i++)
        {
            path=ordered_new[i];
            for(int j=0;j<path.size()-1;j++)
            {
                std::vector<int> small_cache;
                for(int k=j;k<path.size();k++)
                {
                    small_cache.push_back(path[k]);
                }

                cachedPaths.Insert(GenerateKey(map.VertexName(small_cache[0]),map.VertexName(small_cache[small_cache.size()-1])),small_cache);


            }
            
        }
        this->currentLoc=this->startingLoc;
        inJourney=1;
        currentRoute=ordered_new[0];
    }
}

void METUMaps::EndJourney()
{
    // TODO
    if(!inJourney)
    {
        PrintJourneyIsAlreadFinished();
    }
    else
    {
        cachedPaths.ClearTable();
        destination="";
        startingLoc="";
        currentLoc="";
    }
    
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
     int mark=-1;
    for(int i=0;i< map.TotalVertexCount();i++)
    {
        if(map.VertexName(i)==name)
        {
            mark=1;
        }
    }


    if(!inJourney)
    {
        PrintNotInJourney();
    }
    else if(mark !=1)
    {
        PrintLocationNotFound();
    }
    else if(name==destination)
    {
        PrintJourneyCompleted();
    }

    else
    { 
        std::vector<int> value;
        std::vector<int> short_path;
        int did_it=cachedPaths.Find(value,GenerateKey(name,destination));
        if(did_it)
        {
            PrintCachedLocationFound(name,destination);
            currentRoute=value;
            currentLoc=name;
        }

        else
        {
            PrintCalculatingRoutes(name,destination);
            map.ShortestPath(short_path,name,destination);

            for(int j=0;j<short_path.size()-1;j++)
            {
                std::vector<int> small_cache;
                for(int k=j;k<short_path.size();k++)
                {
                    small_cache.push_back(short_path[k]);
                }

                cachedPaths.Insert(GenerateKey(map.VertexName(short_path[j]),map.VertexName(short_path[short_path.size()-1])),small_cache);


            }
            
            currentRoute=short_path;
            currentLoc=name;
            
        }
        

       

    }
    
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}
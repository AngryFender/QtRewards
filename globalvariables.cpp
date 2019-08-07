#include "globalvariables.h"

database *SkyData;

database *global_get_database()
{
    if(SkyData == nullptr)
    {
        SkyData = new database;
    }
    return SkyData;
}

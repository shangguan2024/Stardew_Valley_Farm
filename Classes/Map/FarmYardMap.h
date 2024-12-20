// FarmYardMap.h
#ifndef _FARM_YARD_MAP_
#define _FARM_YARD_MAP_

#include "MapBase.h"

class FarmYardMap : public MapBase {
public:
	FarmYardMap();
	~FarmYardMap();

protected:
	void initContants() override;
};

#endif // !_FARM_YARD_MAP_

// BeachMap.h
#ifndef _BEACH_MAP_
#define _BEACH_MAP_

#include "MapBase.h"

class BeachMap : public MapBase {
public:
	BeachMap();
	~BeachMap();

protected:
	void initContants() override;
};

#endif // !_BEACH_MAP_

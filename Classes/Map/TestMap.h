// TestMap.h
#ifndef _TEST_MAP_
#define _TEST_MAP_

#include "MapBase.h"

class TestMap : public MapBase {
public:
	TestMap();
	~TestMap();

protected:
	void initContants() override;
};

#endif // !_TEST_MAP_

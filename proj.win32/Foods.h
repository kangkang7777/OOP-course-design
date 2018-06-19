#ifndef _Foods_H_
#define _Foods_H_

#include "Entity.h"

class Foods : public Entity {
public:
	Foods();
	~Foods();

	static Foods * create(const std::string& filename);
	bool init(const std::string& filename);
};

#endif
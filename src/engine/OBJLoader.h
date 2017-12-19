#pragma once

#include "RawModel.h"
#include "Loader.h"

#include <vector>
#include <string>

class OBJLoader {
public:

  static RawModel_ptr loadObjModel(std::string fileName, Loader & loader);

private:
};

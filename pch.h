// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#include <memory.h>

#ifdef WIN32
#include <fcntl.h>
#include <io.h>
#endif // WIN32



#include <vector>
#include <array>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cassert>
 
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace photoncpp {
	using MatrixInt = std::vector<std::vector<int>>;
	using Color = uint32_t;
	using BitSet = std::vector<bool>;
}

#include "PhotonAaMatrix.h"
#include "PhotonDot.h"
#include "PhotonLine.h"
#include "PhotonRow.h"
#include "PhotonInputStream.h"
#include "PhotonOutputStream.h"
#include "PhotonProjectType.h"
#include "PhotonMatrix.h"
#include "PhotonLayer.h"
#include "PhotonFileHeader.h"
#include "PhotonFileLayer.h"
#include "PhotonFilePreview.h"
#include "PhotonFilePrintParameters.h"

#endif //PCH_H

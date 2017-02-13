#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace FilesSystem{
	using namespace boost::filesystem;
	
    path getDataPath();
    path getPrefPath();
}

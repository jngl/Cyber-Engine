#pragma once

#include <GE/Core/Types.hpp>
#include <string>

namespace core {
	class Color {
	public:
		Color();
		Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a=255);
		virtual ~Color();

		virtual std::string toString();

		UInt8 red;
		UInt8 green;
		UInt8 blue;
		UInt8 alpha;
	};
} /* namespace core */

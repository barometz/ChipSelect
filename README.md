# ChipSelect

* [Usage](README.md#usage)
* [Building](README.md#building)

ChipSelect is a small library that can help a factory method select specific implementations based on a query string. It was inspired by a recurring pattern encountered while building flash memory programmers, which often have more or less hierarchical naming patterns:

* **AL** indicates the hypothetical vendor Allied Lithographics
  * **AL32** is AL's line of 32-bit microcontrollers
    * **AL32T1** is a line with peripherals that makes it good for audio interfacing
      * **AL32T103** is a specific variant
        * **AL32T103A** comes in a 100-pin package (A), but we're not interested in the pins
          * **AL32T103?G** is any package with 1 MB storage
          * **AL32T103?I** is any package with 2 MB storage
      * **AL32T105** is another variant, but is programmed much like the T103
    * **AL32T4** is used in various system control settings
      * **AL32T407**
  * **AL8** is AL's line of 8-bit microcontrollers
    * And so on, and on.

Hopefully the library can be useful in other contexts as well, but that's the general idea.

## Usage
The selection tree is defined by nodes with three attributes each: a query string, an optional list of child nodes, and an optional result. A small example looks like this:

```C++
#include "Selector.h"

using S = ChipSelect::Selector<ReturnValue, ArgType1, ArgType2>;

const std::vector<S> selectors = 
{
	{
		"AL8"
	},
	{
		"AL32",
		{
			"T1",
			{ "03", {}, [](auto a1, auto a2) { return CAL32T10x(a1, a2, 5); } },
			{ "05", {}, [](auto a1, auto a2) { return CAL32T10x(a1, a2, 10); } }
		}
	}
};

ReturnValue Create(const std::string& query, ArgType1 one, ArgType2 two)
{
	std::optional<std::function<ReturnValue(ArgType1, ArgType2)> result = S::Parse("STM32F103");
	if (result)
	{
		auto createFunction = result.value();
		return createFunction(one, two);
	}
	else
	{
		/* return a default */
	}
}
```

There is also support for:
* **Wildcards**, since some parts of the name just don't matter to your application
* **Aliases**, because sometimes a name changes and both can be used for the same goal
* **Fallback results** to provide generic solutions when the more specific ones don't match

For more details, see tests/Populated.cpp.

## Building

ChipSelect requires C++17 and is been tested with g++ 7.1.0 (`--std=c++1z`) as well as MSVC++ 14.1/VS 2017 (`/std:c++latest`).

To include it in your project, you only need the `src/` and `include/` folders. Most of the heavy lifting is done in `Selector.h`; you can  turn it into a header-only library by copying the definitions from `StringTools.cpp` into `StringTools.h` and inlining them.

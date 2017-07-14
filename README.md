# ChipSelect

ChipSelect is a small library that can help a factory method select specific implementations based on a query string. It was inspired by a recurring pattern encountered while building flash memory programmers, which often have more or less hierarchical naming patterns:

* **STM** indicates the vendor ST Microelectronics
  * **STM32** are 32-bit microcontrollers by ST
    * **STM32F1** is a family of devices with similar programming interfaces
	* **STM32F4** is a family of devices with similar programming interfaces
	  * **STM32F407** is a variant with particular peripherals
	  * **STM32F437** is a variant with different peripherals, but is programmed almost identically to the F407
	    * **STM32F437VG** has 1 MB of flash storage
		* **STM32F437AG** also has 1 MB of flash storage, but different pinning (which is not relevant to the programming software)
		* **STM32F437AI** has 2 MB of flash storage, and shares its pin layout with the F437AG
  * **STM8** are 8-bit microcontrollers by ST
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
		"STM8"
	},
	{
		"STM32",
		{
			"F1",
			{ "03", {}, [](auto a1, auto a2) { return CSTM32F103(); } },
			{ "05", {}, [](auto a1, auto a2) { return CSTM32F105(); } }
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

There is also support for aliases and fallback results. For more details, see tests/Populated.cpp.

## Building

ChipSelect requires C++17 and is been tested with g++ 7.1.0 (`--std=c++1z`) as well as MSVC++ 14.1/VS 2017 (`/std:c++latest`).

To include it in your project, you only need the `src/` and `include/` folders. Most of the heavy lifting is done in `Selector.h`; you can  turn it into a header-only library by copying the definitions from `StringTools.cpp` into `StringTools.h` and inlining them.

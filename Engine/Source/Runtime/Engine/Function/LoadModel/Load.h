#pragma once
#include "../Factory/LoadFactory.hpp"

namespace BEngine
{
	class Load
	{

	public:

		virtual ~Load() {}

		virtual void LoadModel() = 0;




	};


}
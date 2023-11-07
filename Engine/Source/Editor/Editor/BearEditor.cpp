
#include "EditorLayer.h"



#include <Launch/EntryPoint.h>





namespace BEngine
{

	class BearEditor : public Application
	{

	public:
		BearEditor()
			:Application("Bear")
		{
			PushLayer(new EditorLayer());
		}
		~BearEditor()
		{

		}
	};

	Application* BEngine::CreateApplication()
	{
		return new BearEditor();
	}


}

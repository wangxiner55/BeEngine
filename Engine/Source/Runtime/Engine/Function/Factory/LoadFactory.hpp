#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>
#include "../LoadModel/Load.h"



namespace BEngine
{
	class Load;

	struct factory
	{
		
		template<typename T>
		struct register_t
		{
			register_t(const std::string& key)
			{
				factory::get().map_.emplace(key, [] {return new T(); });
			}

			template<typename... Args>
			register_t(const std::string& key, Args... args)
			{
				factory::get().map_.emplace(key, [=] { return new T(args...); });
			}
			//static Load* create() { return new T; }
		};



		Load* produce(const std::string& key)
		{
			if (map_.find(key) == map_.end())
				throw std::invalid_argument("the Load key is not exist!");

			return map_[key]();
		}






		std::unique_ptr<Load> produce_unique(const std::string& key)
		{
			return std::unique_ptr<Load>(produce(key));
		}

		std::shared_ptr<Load> produce_shared(const std::string& key)
		{
			return std::shared_ptr<Load>(produce(key));
		}


		static factory& get()
		{
			static factory instance;
			return instance;
		}




	private:
		factory() {};
		factory(const factory&) = delete;
		factory(factory&&) = delete;

		std::map<std::string, std::function<Load*()>> map_;
	};


#define REGISTER_MESSAGE_VNAME(T) reg_msg_##T##_
#define REGISTER_MESSAGE(T, key, ...) static factory::register_t<T> REGISTER_MESSAGE_VNAME(T)(key, ##__VA_ARGS__);


}
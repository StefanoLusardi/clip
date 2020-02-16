#pragma once

#include "Api.hpp"
#include <utility>

namespace clip
{

	template<class T>
	class ArgumentValue;

	template<class T>
	ArgumentValue<T> value()
	{
		return ArgumentValue<T>();
	}

	template<class T>
	ArgumentValue<T> value(T&& v)
	{
		return ArgumentValue<T>(std::forward<T>(v));
	}

	template <typename T>
	class CLIP_API ArgumentValue
	{
	public:
		ArgumentValue(const ArgumentValue&) = default;
		ArgumentValue(ArgumentValue&&) noexcept = default;

		ArgumentValue& operator=(const ArgumentValue&) = delete;
		ArgumentValue& operator=(ArgumentValue&&) noexcept = default;

		~ArgumentValue() { }

		bool isRequired() const { return _required; }
		ArgumentValue isRequired(bool required) { _required = required; return *this; }
		
		T defaultValue() const { return _v; }
		ArgumentValue defaultValue(const T& t) { _v = t; return *this; }

		friend ArgumentValue<T> clip::value<T>();
		friend ArgumentValue<T> clip::value<T>(T&& v);

	protected:
		ArgumentValue() : _v{}, _required{ false } { }
		ArgumentValue(T&& v) : _v{ v }, _required{ false } { }

	private:
		T _v;
		bool _required;
	};

}

#pragma once

#include "Api.hpp"
#include "ArgumentValue.hpp"

#include <optional>
#include <string>
#include <vector>

namespace clip
{
	template <typename T = std::nullptr_t>
	class CLIP_API OptionalArgument
	{
	public:
		~OptionalArgument() = default;

		OptionalArgument(const std::vector<std::string>& names)
			: _names{ names }
			, _argValue{ std::nullopt } { }

		OptionalArgument(const std::vector<std::string>& names, const std::string& description)
			: _names{ names }
			, _description{ description }
			, _argValue{ std::nullopt } { }
		
		OptionalArgument(const std::vector<std::string>& names, const std::string& description, ArgumentValue<T>&& value)
			: _names{ names }
			, _description{ description }
			, _argValue{ std::make_optional(value) } { }

		OptionalArgument(OptionalArgument&& other) noexcept
			: _names{ std::move(other._names) }
			, _description{ std::move(other._description) }
			, _argValue{ std::move(other._argValue) } { }

		std::vector<std::string> names() const noexcept { return _names; }
		
		std::string description() const noexcept { return _description; }
		
		[[nodiscard]] bool hasValue() const noexcept { return _argValue.has_value(); }

		[[nodiscard]] bool isValueRequired() const noexcept
		{ 
			if (!hasValue())
				return false; // considering to throw an exception
				
			return _argValue.value().isRequired();
		}

		T getValue() const noexcept
		{
			if (!hasValue())
				return {};

			return _argValue.value().defaultValue();
		}
	
	private:
		std::optional<ArgumentValue<T>> _argValue;
		std::vector<std::string> _names;
		std::string _description;
	};
}

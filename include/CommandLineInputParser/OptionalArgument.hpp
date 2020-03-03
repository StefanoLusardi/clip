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

		explicit OptionalArgument(const std::vector<std::string>& names)
			: _names{ names }
			, _argValue{ std::nullopt } { checkNames(names); }

		explicit OptionalArgument(const std::vector<std::string>& names, const std::string& description)
			: _names{ names }
			, _description{ description }
			, _argValue{ std::nullopt } { }
		
		explicit OptionalArgument(const std::vector<std::string>& names, const std::string& description, ArgumentValue<T>&& value)
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

	protected:
		constexpr void checkNames(const std::vector<std::string>& names) const
		{
			// static_assert(names.size() > 0, "OptionalArgument must have at least one valid name"); 
		}
	
	private:
		std::optional<ArgumentValue<T>> _argValue;
		std::vector<std::string> _names;
		std::string _description;
	};
}

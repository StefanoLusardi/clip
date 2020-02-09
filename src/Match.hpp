#pragma once

#include <stdexcept>

namespace clip
{

	class CommandLineParser::Match
	{
	public:
		enum class Index { Full, Dash, Name, Equal, Value, SIZE };

		void next()
		{
			if (_index == Index::SIZE) { throw std::out_of_range("Match::Index next() has been called after Match::Index::SIZE"); }

			int idx = static_cast<int>(_index);
			_index = static_cast<Match::Index>(++idx);
		}

		Match::Index index() { return _index; }
		static int size() noexcept { return static_cast<int>(Match::Index::SIZE); }

	private:
		Match::Index _index = Match::Index::Full;
	};

}
//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "IReader.hpp"

namespace s3d
{
	/// <summary>
	/// アーカイブの読み込み
	/// </summary>
	class ArchivedFileReader : public IReader
	{
	private:

		std::shared_ptr<IReader> m_reader;

		int64 m_offset = 0;

		int64 m_size = 0;

		int64 m_pos = 0;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ArchivedFileReader() = default;

		ArchivedFileReader(std::shared_ptr<IReader> reader, int64 offset, int64 size)
			: m_reader(reader)
			, m_offset(offset)
			, m_size(size)
		{
			if (m_offset > m_reader->size())
			{
				m_offset = m_reader->size();
			}

			if (m_offset + m_size > m_reader->size())
			{
				m_size = m_reader->size() - m_offset;
			}
		}

		bool isOpened() const override
		{
			if (!m_reader)
			{
				return false;
			}

			return m_reader->isOpened();
		}

		explicit operator bool() const { return isOpened(); }

		int64 size() const override
		{
			if (!m_reader)
			{
				return 0;
			}

			return m_size;
		}

		int64 getPos() const override
		{
			if (!m_reader)
			{
				return 0;
			}

			return m_pos;
		}

		bool setPos(int64 pos) override
		{
			if (!m_reader)
			{
				return false;
			}

			if (pos < 0 || pos > m_size)
			{
				return false;
			}

			m_pos = pos;

			return true;
		}

		int64 skip(int64 offset) override
		{
			if (!m_reader)
			{
				return 0;
			}

			if (m_pos + offset > m_size)
			{
				offset = m_size - m_pos;
			}

			m_pos += offset;

			return m_pos;
		}

		int64 read(void* buffer, int64 size) override
		{
			if (!m_reader)
			{
				return 0;
			}

			if (m_pos + size > m_size)
			{
				size = m_size - m_pos;
			}

			m_reader->setPos(m_offset + m_pos);

			const int64 readSize = m_reader->read(buffer, size);

			m_pos += readSize;

			return readSize;
		}

		int64 read(void* buffer, int64 pos, int64 size) override
		{
			if (!m_reader)
			{
				return 0;
			}

			if (pos < 0)
			{
				return 0;
			}

			if (m_pos + pos > m_size)
			{
				return 0;
			}

			if (m_pos + pos + size > m_size)
			{
				size = m_size - pos;
			}

			return m_reader->read(buffer, m_offset + pos, size);
		}

		bool supportsLookahead() const override
		{
			if (!m_reader)
			{
				return false;
			}

			return m_reader->supportsLookahead();
		}

		int64 lookahead(void* buffer, int64 size) const override
		{
			if (!m_reader)
			{
				return 0;
			}

			if (m_pos + size > m_size)
			{
				size = m_size - m_pos;
			}

			return m_reader->lookahead(buffer, m_offset + m_pos, size);
		}

		int64 lookahead(void* buffer, int64 pos, int64 size) const override
		{
			if (!m_reader)
			{
				return 0;
			}

			if (pos < 0)
			{
				return 0;
			}

			if (m_pos + pos > m_size)
			{
				return 0;
			}

			if (m_pos + pos + size > m_size)
			{
				size = m_size - pos;
			}

			return m_reader->lookahead(buffer, m_offset + pos, size);
		}
	};
}

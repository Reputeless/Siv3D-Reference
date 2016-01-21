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
# include "Handle.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ファイルへの変更アクション
	/// </summary>
	enum class FileAction
	{
		None,

		Removed,

		Modified,

		Unknown,
	};

	/// <summary>
	/// ファイル変更検知
	/// </summary>
	class FileMonitor
	{
	private:

		class Handle {};

		using FileMonitorHandle = Siv3DHandle<Handle>;

		std::shared_ptr<FileMonitorHandle> m_handle;

	public:

		FileMonitor();

		FileMonitor(const FilePath& path);

		~FileMonitor();

		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const FileMonitor& fileMonitor) const;

		bool operator != (const FileMonitor& fileMonitor) const;

		bool monitor(const FilePath& path);

		bool hasChanged() const;

		FileAction retrieve();

		FilePath path() const;
	};
}

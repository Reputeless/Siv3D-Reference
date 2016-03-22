//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2015 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class PipeServer
	{
	private:

		class CPipeServer;

		std::shared_ptr<CPipeServer> pImpl;

	public:

		PipeServer();

		explicit PipeServer(const FilePath& path);

		~PipeServer();

		bool open(const FilePath& path);

		bool close(bool wait = false);

		explicit operator bool() const
		{
			return isOpened();
		}

		bool isOpened() const;

		bool write(const std::string& cmd);

		size_t available() const;

		bool read(std::string& dst);
	};
}

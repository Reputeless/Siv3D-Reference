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

namespace s3d
{
	class HandwritingTrainer
	{
	private:

		class CHandwritingTrainer;

		std::shared_ptr<CHandwritingTrainer> pImpl;

	public:

		HandwritingTrainer();

		~HandwritingTrainer();

		bool add(const String& name, const Size& areaSize, const Array<Array<Point>>& strokes);

		void clear();

		bool saveModelFile(const FilePath& path) const;
	};
}

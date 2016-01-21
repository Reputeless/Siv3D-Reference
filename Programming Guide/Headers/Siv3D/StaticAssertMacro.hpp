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

# define S3D_STATIC_ASSERT_IMPL(expr)	static_assert(expr, #expr)
# define s3d_static_assert(...)			S3D_STATIC_ASSERT_IMPL((__VA_ARGS__))

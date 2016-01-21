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

# ifdef NO_S3D_USING
#	ifndef NO_CHARACTERSET_USING
#		define NO_CHARACTERSET_USING
#	endif
#	ifndef NO_FORMATTING_LITERALS_USING
#		define NO_FORMATTING_LITERALS_USING
#	endif
#	ifndef NO_CHRONO_LITERALS_USING
#		define NO_CHRONO_LITERALS_USING
#	endif
#	ifndef NO_MATH_USING
#		define NO_MATH_USING
#	endif
#	ifndef S3D_EASING_DEFINED
#		define S3D_EASING_DEFINED
#	endif
#	ifndef S3D_EXPRESSIONPARSER_DEFINED
#		define S3D_EXPRESSIONPARSER_DEFINED
#	endif
#	ifndef S3D_LOOP_DEFINED
#		define S3D_LOOP_DEFINED
#	endif
# else
	using namespace s3d;
# endif

# ifndef NO_CHARACTERSET_USING
	using namespace s3d::CharacterSet;
# endif

# ifndef NO_FORMATTING_LITERALS_USING
	using namespace s3d::literals::formatting_literals;
# endif

# ifndef NO_CHRONO_LITERALS_USING
	using namespace s3d::literals::chrono_literals;
	using namespace std::chrono_literals;
# endif

# ifdef S3D_MATH_DEFINED
#	ifndef NO_MATH_USING
		using namespace s3d::Math;
#	endif
# endif

# ifdef S3D_EASING_DEFINED
#	ifndef NO_EASING_USING
		using s3d::Easing::EaseIn;
		using s3d::Easing::EaseOut;
		using s3d::Easing::EaseInOut;
#	endif
# endif

# ifdef S3D_EXPRESSIONPARSER_DEFINED
#	ifndef NO_EXPRESSIONPARSER_USING
		using s3d::ExpressionParser::Evaluate;
		using s3d::ExpressionParser::EvaluateOpt;
#	endif
# endif

# ifdef S3D_LOOP_DEFINED
#	ifndef NO_LOOP_USING
		using namespace s3d::loop;
#	endif
# endif
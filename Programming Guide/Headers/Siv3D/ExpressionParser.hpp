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
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"

# ifndef S3D_EXPRESSIONPARSER_DEFINED
#	define S3D_EXPRESSIONPARSER_DEFINED
# endif

namespace s3d
{
	namespace ExpressionParser
	{
		double Evaluate(const String& expression);

		double Evaluate(const String& expression, const Array<std::pair<String, double>>& variables);

		Optional<double> EvaluateOpt(const String& expression);

		Optional<double> EvaluateOpt(const String& expression, const Array<std::pair<String, double>>& variables);
	}

	class ParsedExpression
	{
	private:

		class CParsedExpression;

		std::shared_ptr<CParsedExpression> pImpl;

	public:

		ParsedExpression();

		explicit ParsedExpression(const String& expression);

		bool isValid() const;

		operator bool() const
		{
			return isValid();
		}

		double evaluate() const;

		double evaluate(const Array<std::pair<String, double>>& variables) const;

		Optional<double> evaluateOpt() const;

		Optional<double> evaluateOpt(const Array<std::pair<String, double>>& variables) const;
	};
}

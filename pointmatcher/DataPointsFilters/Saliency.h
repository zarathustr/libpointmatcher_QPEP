// kate: replace-tabs off; indent-width 4; indent-mode normal
// vim: ts=4:sw=4:noexpandtab
/*

Copyright (c) 2010--2018,
François Pomerleau and Stephane Magnenat, ASL, ETHZ, Switzerland
You can contact the authors at <f dot pomerleau at gmail dot com> and
<stephane at magnenat dot net>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ETH-ASL BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#pragma once

#include "PointMatcher.h"

template<typename T>
struct SaliencyDataPointsFilter : public PointMatcher<T>::DataPointsFilter
{
  	// Type definitions
	typedef PointMatcher<T> PM;
	typedef typename PM::DataPoints DataPoints;
	typedef typename PM::DataPointsFilter DataPointsFilter;

	typedef PointMatcherSupport::Parametrizable Parametrizable;
	typedef PointMatcherSupport::Parametrizable P;
	typedef Parametrizable::Parameters Parameters;
	typedef Parametrizable::ParameterDoc ParameterDoc;
	typedef Parametrizable::ParametersDoc ParametersDoc;
	typedef Parametrizable::InvalidParameter InvalidParameter;
	
	typedef typename DataPoints::Index Index;

	typedef typename PointMatcher<T>::DataPoints::InvalidField InvalidField;
	
	typedef typename PM::Matrix Matrix;
	typedef typename PM::Vector Vector;

	inline static const std::string description()
	{
		return "Point cloud enhancement: compute geometric features saliencies throught Tensor Voting framework.";
	}

	inline static const ParametersDoc availableParameters()
	{
		return {
			{"k", "Number of neighbors to consider", "50", "6", "4294967295", &P::Comp<std::size_t>},
			{"sigma", "Scale of the vote.", "0.2", "0.", "+inf", &P::Comp<T>},
			{"keepNormals", "Flag to keep normals computed by TV.", "1", "0", "1", P::Comp<bool>},
			{"keepLabels", "Flag to keep labels computed by TV.", "1", "0", "1", P::Comp<bool>},
			{"keepTensors", "Flag to keep elements Tensors computed by TV.", "1", "0", "1", P::Comp<bool>}
		};
	}

public:
	const std::size_t k;
	const T sigma;
	const bool keepNormals;
	const bool keepLabels;
	const bool keepTensors;
	
	//Ctor, uses parameter interface
	SaliencyDataPointsFilter(const Parameters& params = Parameters());
	//SaliencyDataPointsFilter();
	
	//Dtor
	virtual ~SaliencyDataPointsFilter() {};

	virtual DataPoints filter(const DataPoints& input);
	virtual void inPlaceFilter(DataPoints& cloud);

private:
};
	

